#include <netppm/netppm.h>
#include <viewport/viewport.h>
#include <color/color.h>
#include <gtx/color_space.hpp>
#include <stdio.h>

int main(){

  ivec2 size(1024, 1024);
  ViewPort<double> view_port(size, 3.0, -3.0, 3.0, -3.0);
  NetPPM image = NetPPM(size);

  image.map_each_pixel([&view_port] (const vec2 &pixel_coord) {

    complex<double> z = view_port.pixel_to_complex(pixel_coord);
    z = z - 1.0 - std::pow(z, -1);
    auto hsv = complex_to_hsv(z);
    return glm::rgbColor(hsv) * vec3(255, 255, 255);
  });

  image.write_file("output.ppm");

  return 0;
}
