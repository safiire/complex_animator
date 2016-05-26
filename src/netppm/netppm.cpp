#include <netppm/netppm.h>


NetPPM::NetPPM(const NetPPM& other) :
  _size(other._size), _data(make_unique<char[]>(buffer_size())){
  memcpy(_data.get(), other._data.get(), buffer_size());
}


NetPPM::NetPPM(NetPPM&& other) {
  _size = other._size;
  _data.swap(other._data);
  _size = ivec2 {0, 0};
}


void NetPPM::map_each_pixel(function<ivec3 (const vec2 &pixel_coord)> f){
  for(int y = 0; y < _size.y; y++){
    for(int x = 0; x < _size.x; x++){

      vec2 coord {x, y};
      set_pixel(coord, f(coord));
    }
  }
}


uint32_t NetPPM::buffer_size() const {
  return 3 * _size.x * _size.y;
}


Maybe<uint32_t> NetPPM::get_offset(uint32_t x, uint32_t y) const {
  uint32_t offset = (y * _size.x * 3) + (x * 3);
  if(offset < buffer_size()){
    return Maybe<uint32_t>(offset);
  }else{
    return Nothing<uint32_t>();
  }
}


Maybe<uint32_t> NetPPM::get_offset(const ivec2 &coord) const {
  return get_offset(coord.x, coord.y);
}


Maybe<ivec3> NetPPM::get_pixel(uint32_t x, uint32_t y) const {
  bool is_nothing = true;
  ivec3 pixel;
  get_offset(x, y).if_exists([&] (uint32_t offset) {
    is_nothing = false;
    pixel.r = _data[offset + 0];
    pixel.g = _data[offset + 1];
    pixel.b = _data[offset + 2];
  });
  return is_nothing ? Nothing<ivec3>() : Maybe<ivec3>(pixel);
}


Maybe<ivec3> NetPPM::get_pixel(const ivec2 &coord) const {
  return get_pixel(coord.x, coord.y);
}


bool NetPPM::set_pixel(uint32_t x, uint32_t y, const ivec3 pixel) {
  bool success = false;
  get_offset(x, y).if_exists([&] (uint32_t offset) {
    success = true;
    _data[offset + 0] = pixel.r;
    _data[offset + 1] = pixel.g;
    _data[offset + 2] = pixel.b;
  });
  return success;
}


bool NetPPM::set_pixel(const ivec2 &coord, const ivec3 &pixel) {
  return set_pixel(coord.x, coord.y, pixel);
}


bool NetPPM::write_file(const char *filename) const {
  FILE *fp = fopen(filename, "wb");
  if(!fp)
    return false;
  fprintf(fp, "P6 %d %d 255\n", _size.x, _size.y);
  fwrite(_data.get(), sizeof(char), buffer_size(), fp);
  fclose(fp);
  return true;
}
