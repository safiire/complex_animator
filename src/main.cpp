#include <netppm/netppm.h>
#include <maybe/maybe.h>
#include <stdio.h>

int main(){

  NetPPM image = NetPPM(1024, 1024);

  for(int y = 0; y < 1024; y++){
    for(int x = 0; x < 1024; x++){
      uint8_t r = (x ^ y) % 256;
      uint8_t g = (x & y) % 256;
      uint8_t b = (x | y) % 256;
      image.set_pixel(x, y, ivec3(r, g, b));
    }
  }
  image.write_file("output.ppm");

  Maybe<NetPPM> maybe_image = std::move(image);
  Maybe<NetPPM> copy_image(image);

  NetPPM copied_netppm = image;
  NetPPM moved_netppm = std::move(image);

  maybe_image.if_exists([] (NetPPM ppm){
    printf("The buffer size is %d\n", ppm.buffer_size());
  });

  Maybe<int> nothing;
  nothing.if_exists([] (int a) {
    printf("This won't happen %d\n", a);

  })->otherwise([] (void) {
    printf("Otherwise works!\n");

  });

  return 0;
}
