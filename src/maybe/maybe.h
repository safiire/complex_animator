#include <functional>

template <typename T>
class Maybe {
  private:
  T* _ptr;

  struct Placeholder {
    uint8_t _[sizeof(T)];
  };
  Placeholder _memory;

  struct Otherwise {
    bool call;
    Otherwise(bool call) : call(call) {}
    void otherwise(std::function< void (void)> f){
      if(call) f();
    }
  };

  public:
  Maybe() : _ptr(nullptr) {}

  Maybe(T &&other) : _ptr(nullptr) {
    std::memcpy(&_memory, &other, sizeof(T));
    _ptr = reinterpret_cast<T*>(&_memory);
    printf("Maybe move constructor\n");
  }

  Maybe(const T& other) : _ptr(nullptr) {
    std::memcpy(&_memory, &other, sizeof(T));
    _ptr = reinterpret_cast<T*>(&_memory);
    printf("Maybe copy constructor\n");
  }

  explicit operator bool() const {
    return _ptr != nullptr;
  }

  Otherwise& if_exists(std::function<void (T&)> f) {
    Otherwise branch(true);
    if(*this) {
      f(*_ptr);
      branch.call = false;
    }
    return branch;
  }

};
