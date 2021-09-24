#include "utilities.hpp"
#include "surface.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"
#include "camera.hpp"
#include "material.hpp"

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

int main()
{
    // Image

    const double aspect_ratio = 16.0/9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width/aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    Surface image(image_width, image_height, "image_depth_of_field.png");

    // World

    double R = cos(pi/4);
    Hittable_list world;

    auto material_ground = make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    auto material_center = make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
    auto material_left = make_shared<Dielectric>(1.5);
    auto material_right = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 0.0);

    world.add(make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5, material_center));
    world.add(make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, material_left));
    world.add(make_shared<Sphere>(Point3(0.0, 0.0, -1.0), -0.45, material_left));
    world.add(make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, material_right));
    // Camera

    Point3 lookfrom(3, 3, 2);
    Point3 lookat(0, 0, -1);
    Vec3 vup(0, 1, 0);
    double dist_to_focus = (lookfrom-lookat).length();
    double aperture = 2.0;

    Camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

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
}
