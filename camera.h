#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>

#include "rtweekend.h"

#include "color.h"
#include "hittable.h"

class camera {
    public:
        double ASPECT_RATIO = 1.0;
        int IMAGE_WIDTH = 100;
        int SAMPLES_PER_PIXEL = 10;

        void render(const hittable& world) {
            initialize();

            std::cout << "P3\n" << IMAGE_WIDTH << " " << IMAGE_HEIGHT << "\n255\n";

            for (int row = 0; row < IMAGE_HEIGHT; row++) {
                std::clog << "\rScanlines remaining: " << (IMAGE_HEIGHT - row) << " " << std::flush;
                for (int col = 0; col < IMAGE_WIDTH; col++) {
                    color pixel_color(0,0,0);
                    for (int sample = 0; sample < SAMPLES_PER_PIXEL; ++sample) {
                        ray r = get_ray(col, row);
                        pixel_color += ray_color(r, world);
                    }
                    write_color(std::cout, pixel_color, SAMPLES_PER_PIXEL);
                }
            }

            std::clog << "\rDone.                 \n";
        }

    private:
        int IMAGE_HEIGHT;
        point3 CAMERA_CENTER;
        point3 pixel00_loc;
        vec3 pixel_delta_u;
        vec3 pixel_delta_v;

        void initialize() {
            IMAGE_HEIGHT = static_cast<int>(IMAGE_WIDTH / ASPECT_RATIO);
            IMAGE_HEIGHT = (IMAGE_HEIGHT < 1) ? 1 : IMAGE_HEIGHT;

            CAMERA_CENTER = point3(0, 0, 0);

            auto FOCAL_LENGTH = 1.0;
            auto VIEWPORT_HEIGHT = 2.0;
            auto VIEWPORT_WIDTH = VIEWPORT_HEIGHT * (static_cast<double>(IMAGE_WIDTH) / IMAGE_HEIGHT);

            auto viewport_u = vec3(VIEWPORT_WIDTH, 0, 0);
            auto viewport_v = vec3(0, -VIEWPORT_HEIGHT, 0);

            pixel_delta_u = viewport_u / IMAGE_WIDTH;
            pixel_delta_v = viewport_v / IMAGE_HEIGHT;

            auto viewport_upper_left = CAMERA_CENTER - vec3(0, 0, FOCAL_LENGTH) - viewport_u/2 - viewport_v/2;
            pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

        }

        ray get_ray(int i, int j) const {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto pixel_sample = pixel_center + pixel_sample_square();

            auto ray_origin = CAMERA_CENTER;
            auto ray_direction = pixel_sample - ray_origin;

            return ray(ray_origin, ray_direction);
        }

        vec3 pixel_sample_square() const {
            auto px = -0.5 + random_double();
            auto py = -0.5 + random_double();
            return (px * pixel_delta_u) + (py * pixel_delta_v);
        }

        color ray_color(const ray& r, const hittable& world) {
            hit_record rec;
            if (world.hit(r, interval(0, infinity), rec)) { return 0.5*(rec.normal + color(1, 1, 1)); }

            vec3 unit_direction = unit_vector(r.direction());
            auto a = 0.5*(unit_direction.y() + 1.0);
            return (1.0 - a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0); 
        }
};

#endif