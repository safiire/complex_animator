#include <viewport/viewport.h>


template <typename T>
complex<T> ViewPort<T>::pixel_to_complex(ivec2 coord) {
  T half_width = _size.x / 2.0;
  T half_height = _size.y / 2.0;
  T dx = (_right - _left) / _size.x;
  T dy = (_bottom - _top) / _size.y;
  return complex<T>((coord.x - half_width) * dx, (coord.y - half_height) * dy);
}
