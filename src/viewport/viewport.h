#pragma once
#include <glm.hpp>
#include <complex>

using namespace glm;
using namespace std;
using namespace std::complex_literals;

template <typename T>
class ViewPort {
  private:
  ivec2 _size;
  T _top;
  T _left;
  T _right;
  T _bottom;

  public:
  ViewPort(ivec2 size, T top, T left, T right, T bottom) :
    _size(size), _top(top), _left(left), _right(right), _bottom(bottom) {}

  complex<T> pixel_to_complex(ivec2 coord);
};
