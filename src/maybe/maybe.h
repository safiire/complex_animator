#pragma once
#include <functional>

using namespace std;

template <typename T>
class Maybe {
  private:
  T* _ptr;

  struct Placeholder {
    uint8_t _[sizeof(T)];
  };
  Placeholder _memory;

  struct Otherwise {
    bool _call;
    Otherwise(bool call) : _call(call) {}
    void otherwise(function< void (void)> f){
      if(_call) f();
    }
  };

  public:
  Maybe() : _ptr(nullptr) {}

  Maybe(T &&other) : _ptr(nullptr) {
    memcpy(&_memory, &other, sizeof(T));
    _ptr = reinterpret_cast<T*>(&_memory);
    printf("Maybe move constructor\n");
  }

  Maybe(const T& other) : _ptr(nullptr) {
    memcpy(&_memory, &other, sizeof(T));
    _ptr = reinterpret_cast<T*>(&_memory);
    printf("Maybe copy constructor\n");
  }

  explicit operator bool() const {
    return _ptr != nullptr;
  }

  unique_ptr<Otherwise> if_exists(function<void (T&)> f) {
    Otherwise branch(true);
    if(*this) {
      f(*_ptr);
      return make_unique<Otherwise>(false);
    }
    return make_unique<Otherwise>(true);
  }
};


template <typename T>
Maybe<T> Nothing() {
  return Maybe<T> {};
}
