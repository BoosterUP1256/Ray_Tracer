#include "hittable_list.hpp"
#include "material.hpp"
#include "sphere.hpp"
#include "moving_sphere.hpp"
#include "surface.hpp"
#include "camera.hpp"
#include "aarect.hpp"

Color ray_color(const Ray& r, const Color& background, const Hittable& world, int depth)
{
    Hit_record rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth<=0)
        return {0, 0, 0};

    // If the ray hits nothing, return the background color.
    if (!world.hit(r, 0.001, infinity, rec))
        return background;

    Ray scattered;
    Color attenuation;
    Color emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);

    if (!rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        return emitted;

    return emitted+attenuation*ray_color(scattered, background, world, depth-1);
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

Hittable_list two_perlin_spheres()
{
    Hittable_list objects;

    auto pertext = make_shared<Noise_texture>(4);
    objects.add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, make_shared<Lambertian>(pertext)));
    objects.add(make_shared<Sphere>(Point3(0, 2, 0), 2, make_shared<Lambertian>(pertext)));

    return objects;
}

Hittable_list earth()
{
    auto earth_texture = make_shared<Image_texture>("../resources/earthmap.jpg");
    auto earth_surface = make_shared<Lambertian>(earth_texture);
    auto globe = make_shared<Sphere>(Point3(0, 0, 0), 2, earth_surface);

    return Hittable_list(globe);
}

Hittable_list simple_light()
{
    Hittable_list objects;

    auto pertext = make_shared<Noise_texture>(4);
    objects.add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, make_shared<Lambertian>(pertext)));
    objects.add(make_shared<Sphere>(Point3(0, 2, 0), 2, make_shared<Lambertian>(pertext)));

    auto difflight = make_shared<Diffuse_light>(Color(4, 4, 4));
    objects.add(make_shared<Xy_rect>(3, 5, 1, 3, -2, difflight));

    return objects;
}

Hittable_list cornell_box()
{
    Hittable_list objects;

    auto red = make_shared<Lambertian>(Color(.65, .05, .05));
    auto white = make_shared<Lambertian>(Color(.73, .73, .73));
    auto green = make_shared<Lambertian>(Color(.12, .45, .15));
    auto light = make_shared<Diffuse_light>(Color(15, 15, 15));

    objects.add(make_shared<Yz_rect>(0, 555, 0, 555, 555, green));
    objects.add(make_shared<Yz_rect>(0, 555, 0, 555, 0, red));
    objects.add(make_shared<Xz_rect>(213, 343, 227, 332, 554, light));
    objects.add(make_shared<Xz_rect>(0, 555, 0, 555, 0, white));
    objects.add(make_shared<Xz_rect>(0, 555, 0, 555, 555, white));
    objects.add(make_shared<Xy_rect>(0, 555, 0, 555, 555, white));

    return objects;
}

int main()
{
    // Image

    double aspect_ratio = 16.0/9.0;
    int image_width = 400;
    int image_height = static_cast<int>(image_width/aspect_ratio);
    int samples_per_pixel = 100;
    const int max_depth = 50;

    //Surface image(image_width, image_height, "cornell_box.png");

    // World

    Hittable_list world;

    Point3 lookfrom;
    Point3 lookat;
    double vfov = 40.0;
    double aperture = 0.0;
    Color background(0, 0, 0);

    switch (0) {
    case 1:
        world = random_scene();
        background = Color(0.70, 0.80, 1.00);
        lookfrom = Point3(13, 2, 3);
        lookat = Point3(0, 0, 0);
        vfov = 20.0;
        aperture = 0.1;
        break;

    case 2:
        world = two_spheres();
        background = Color(0.70, 0.80, 1.00);
        lookfrom = Point3(13, 2, 3);
        lookat = Point3(0, 0, 0);
        vfov = 20.0;
        break;

    case 3:
        world = two_perlin_spheres();
        background = Color(0.70, 0.80, 1.00);
        lookfrom = Point3(13, 2, 3);
        lookat = Point3(0, 0, 0);
        vfov = 20.0;
        break;

    case 4:
        world = earth();
        background = Color(0.70, 0.80, 1.00);
        lookfrom = Point3(13, 2, 3);
        lookat = Point3(0, 0, 0);
        vfov = 20.0;
        break;

    case 5:
        world = simple_light();
        samples_per_pixel = 400;
        background = Color(0, 0, 0);
        lookfrom = Point3(26, 3, 6);
        lookat = Point3(0, 2, 0);
        vfov = 20.0;
        break;

    default:
    case 6:
        world = cornell_box();
        aspect_ratio = 1.0;
        image_width = 600;
        samples_per_pixel = 100;  //200 in book
        background = Color(0, 0, 0);
        lookfrom = Point3(278, 278, -800);
        lookat = Point3(278, 278, 0);
        vfov = 40.0;
        break;
    }

    Vec3 vup(0, 1, 0);
    double dist_to_focus = 10.0;
    image_height = static_cast<int>(image_width/aspect_ratio);

    Camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);
    Surface image(image_width, image_height, "cornell_box.png");

    // Render

    for (int j = image_height-1; j>=0; j--) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i<image_width; i++) {
            Color pixel_color(0, 0, 0);
            for (int s = 0; s<samples_per_pixel; s++) {
                double u = (i+random_double())/(image_width-1);
                double v = (j+random_double())/(image_height-1);
                Ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, background, world, max_depth);
            }
            image.write_color(pixel_color, samples_per_pixel);

        }
    }
    image.render();
}
