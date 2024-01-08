#include <iostream>

#include "rtweekend.h"

#include "camera.h"
#include "hittable_list.h"
#include "sphere.h"

int main() {
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));
    
    camera cam;

    cam.ASPECT_RATIO = 16.0 / 9.0;
    cam.IMAGE_WIDTH = 400;
    cam.SAMPLES_PER_PIXEL = 100;
    
    cam.render(world);
}
