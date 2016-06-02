#pragma once
#include <memory>
#include <functional>
#include <glm.hpp>
#include <cstdint>
#include <maybe/maybe.h>
#include <stdio.h>

using namespace glm;
using namespace std;

class NetPPM {
  private:
  ivec2 _size;
  unique_ptr<char[]> _data;

  public:
  NetPPM(uint32_t width, uint32_t height) :
    _size(ivec2(width, height)), _data(make_unique<char[]>(3 * width * height)) {}
  NetPPM(ivec2 size) :
    _size(size), _data(make_unique<char[]>(3 * size.x * size.y)) {}

  NetPPM(const NetPPM& other);
  NetPPM(NetPPM&& other);

  void map_each_pixel(function<ivec3 (const vec2 &&pixel_coord)> f);

  uint32_t buffer_size() const;
  Maybe<uint32_t> get_offset(uint32_t x, uint32_t y) const;
  Maybe<uint32_t> get_offset(const ivec2 &coord) const;

  Maybe<ivec3> get_pixel(uint32_t x, uint32_t y) const;
  Maybe<ivec3> get_pixel(const ivec2 &coord) const;

  bool set_pixel(uint32_t x, uint32_t y, const ivec3 &pixel);
  bool set_pixel(const ivec2 &coord, const ivec3 &pixel);
  bool write_file(const char *filename) const;
};
