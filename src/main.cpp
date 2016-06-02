#include <netppm/netppm.h>
#include <viewport/viewport.h>
#include <color/color.h>
#include <gtx/color_space.hpp>
#include <stdio.h>


int main(){
  using namespace std;
  using namespace glm;

  ivec2 size(1024, 1024);
  ViewPort<double> view_port(size, 3.0, -3.0, 3.0, -3.0);
  NetPPM image = NetPPM(size);

  int fps = 30;
  int total_time = 30;
  int total_frames = total_time * fps;

  double t = 0.0;
  double t_delta = pow(fps, -1);
  char filename[256];

  for(int frame = 0; frame < total_frames; frame++){

    image.map_each_pixel([&view_port, &t] (const vec2 &pixel_coord) {

      complex<double> z = view_port.pixel_to_complex(pixel_coord);

      //z = z - (1.0 * t) - std::pow(z, -1 * t);
      //z = sin(z * t) * cos(z * t) * pow(z, -1);
      //z = pow(z, 5 * sin(t)) + 1.0;
      z = sin(3.141592653589793 * z * t) / (3.141592653589793 * z * t);

      auto hsv = complex_to_hsv(z);
      return glm::rgbColor(hsv) * vec3(0, 255, 255);
    });

    sprintf(filename, "out/output_%05d.ppm", frame);
    image.write_file(filename);
    t += t_delta;
  }

  return 0;
}
