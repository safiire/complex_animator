#pragma once
#include <memory>
#include <glm.hpp>
#include <cstdint>

class NetPPM {
  private:
  glm::vec2 _size;
  std::unique_ptr<char[]> _data;

  public:
  NetPPM(uint32_t width, uint32_t height) :
    _size(glm::vec2(width, height)), _data(std::make_unique<char[]>(3 * width * height)) {}

  NetPPM(const NetPPM& other);
  NetPPM(NetPPM&& other);

  uint32_t buffer_size() const;
  uint32_t get_offset(uint32_t x, uint32_t y) const;
  uint32_t get_offset(const glm::vec2 &point) const;

  glm::vec3 get_pixel(const glm::vec2 &point) const;
  glm::vec3 get_pixel(uint32_t x, uint32_t y) const;

  bool set_pixel(const glm::vec2 &position, const glm::vec3 &color);
  bool set_pixel(uint32_t x, uint32_t y, const glm::vec3 color);
  bool write_file(const char *filename) const;
};
