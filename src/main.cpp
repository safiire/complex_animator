#include <netppm/netppm.h>
#include <maybe/maybe.h>
#include <stdio.h>

int main(){

  NetPPM image = NetPPM(1024, 1024);
  Maybe<int> n = 123;
  Maybe<int> m(n);

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

  }).otherwise([] (void) {
    printf("Otherwise works!\n");

  });

  return 0;
}
