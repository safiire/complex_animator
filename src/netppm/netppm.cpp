#include <netppm/netppm.h>


NetPPM::NetPPM(const NetPPM& other) :
  _size(other._size), _data(std::make_unique<char[]>(buffer_size())){
  std::memcpy(_data.get(), other._data.get(), buffer_size());
  printf("NetPPM copy constructor\n");
}


NetPPM::NetPPM(NetPPM&& other) {
  _size = other._size;
  _data.swap(other._data);
  _size = glm::vec2(0, 0);
  printf("NetPPM move constructor\n");
}


uint32_t NetPPM::buffer_size() const {
  return 3 * _size.x * _size.y;
}


uint32_t NetPPM::get_offset(uint32_t x, uint32_t y) const {

}
