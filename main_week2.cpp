#include "hittable_list.hpp"
#include "material.hpp"
#include "sphere.hpp"
#include "moving_sphere.hpp"
#include "surface.hpp"
#include "camera.hpp"

Color ray_color(const Ray& r, const Hittable& world, int depth)
{
    Hit_record rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth<=0)
        return Color(0, 0, 0);

    if (world.hit(r, 0.001, infinity, rec)) {
        Ray scattered;
        Color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation*ray_color(scattered, world, depth-1);
        return Color(0, 0, 0);
    }

    Vec3 unit_direction = unit_vector(r.get_direction());
    double t = 0.5*(unit_direction.y+1.0);
    return (1.0-t)*Color(1.0, 1.0, 1.0)+t*Color(0.5, 0.7, 1.0);
}

Hittable_list random_scene()
{
    Hittable_list world;

    auto checker = make_shared<Checker_texture>(Color(0.2, 0.3, 0.1), Color(0.9, 0.9, 0.9));
    world.add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, make_shared<Lambertian>(checker)));

    for (int a = -11; a<11; a++) {
        for (int b = -11; b<11; b++) {
            double choose_mat = random_double();
            Point3 center(a+0.9*random_double(), 0.2, b+0.9*random_double());

            if ((center-Point3(4, 0.2, 0)).length()>0.9) {
                shared_ptr<Material> sphere_material;

                if (choose_mat<0.8) {
                    // diffuse
                    Vec3 albedo = Color::random()*Color::random();
                    sphere_material = make_shared<Lambertian>(albedo);
                    Point3 center2 = center+Vec3(0, random_double(0, 0.5), 0);
                    world.add(make_shared<Moving_sphere>(center, center2, 0.0, 1.0, 0.2, sphere_material));
                }
                else if (choose_mat<0.95) {
                    // metal
                    Vec3 albedo = Color::random(0.5, 1);
                    double fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<Metal>(albedo, fuzz);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else {
                    // glass
                    sphere_material = make_shared<Dielectric>(1.5);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<Dielectric>(1.5);
    world.add(make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.add(make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

    return world;
}

Hittable_list two_spheres()
{
    Hittable_list objects;

    auto checker = make_shared<Checker_texture>(Color(0.2, 0.3, 0.1), Color(0.9, 0.9, 0.9));

    objects.add(make_shared<Sphere>(Point3(0, -10, 0), 10, make_shared<Lambertian>(checker)));
    objects.add(make_shared<Sphere>(Point3(0, 10, 0), 10, make_shared<Lambertian>(checker)));

    return objects;
}

int main()
{
    // Image

    const double aspect_ratio = 16.0/9.0;
    const int image_width = 400;
    int image_height = static_cast<int>(image_width/aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    Surface image(image_width, image_height, "checker_spheres.png");

    // World

    Hittable_list world;

    Point3 lookfrom;
    Point3 lookat;
    double vfov = 40.0;
    double aperture = 0.0;

    switch (0) {
    case 1:
        world = random_scene();
        lookfrom = Point3(13, 2, 3);
        lookat = Point3(0, 0, 0);
        vfov = 20.0;
        aperture = 0.1;
        break;

    default:
    case 2:
        world = two_spheres();
        lookfrom = Point3(13, 2, 3);
        lookat = Point3(0, 0, 0);
        vfov = 20.0;
        break;
    }

    // Camera

    Vec3 vup(0, 1, 0);
    double dist_to_focus = 10.0;
    image_height = static_cast<int>(image_width/aspect_ratio);

    Camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);

    // Render

    for (int j = image_height-1; j>=0; j--) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i<image_width; i++) {
            Color pixel_color(0, 0, 0);
            for (int s = 0; s<samples_per_pixel; s++) {
                double u = (i+random_double())/(image_width-1);
                double v = (j+random_double())/(image_height-1);
                Ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            image.write_color(pixel_color, samples_per_pixel);
        }
    }
    image.render();
    //testing brach
}
