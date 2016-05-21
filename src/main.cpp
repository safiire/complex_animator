#include <netppm/netppm.h>
#include <maybe/maybe.h>
#include <stdio.h>

int main(){

  NetPPM image = NetPPM(1024, 1024);

  Maybe<NetPPM> maybe_image = move(image);
  Maybe<NetPPM> copy_image(image);

  NetPPM copied_netppm = image;
  NetPPM moved_netppm = move(image);

  maybe_image.if_exists([] (NetPPM ppm){
    printf("The buffer size is %d\n", ppm.buffer_size());
  });

  return 0;
}
