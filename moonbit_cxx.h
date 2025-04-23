#include <concepts>
#include <cstdint>
#include <type_traits>
#include <utility>
extern "C" {
#include <moonbit.h> // moonbit.h now doesn't support C++ FFI
}

namespace moonbit {
// https://docs.moonbitlang.com/en/latest/language/ffi.html#types
using Bool = int32_t;
using Int = int32_t;
using UInt = uint32_t;
using Int64 = int64_t;
using UInt64 = uint64_t;
using Double = double;
using Float = float;
using Char = int32_t;
using Byte = uint8_t;

template<typename T> using FixedArray = T*;

template <typename T> using Ref = T*;

template <typename T, std::constructible_from<T>... Args>
Ref<T> from_cxx(Args &&...args) noexcept {
  auto obj = moonbit_make_external_object(
      [](Ref<T> obj) { obj->~T(); }, sizeof(T));
  return new (obj) T{std::forward<Args>(args)...};
}

template<typename T>
concept moonbit_abi = std::is_pointer_v<T> || std::is_arithmetic_v<T>;

template<moonbit_abi T> 
void decref(T obj) noexcept {
  if constexpr (std::is_pointer_v<T>) {
    moonbit_decref(obj); // this is unsafe
  }
}

template<moonbit_abi T> 
void incref(T obj) noexcept {
  if constexpr (std::is_pointer_v<T>) {
    moonbit_incref(obj); // this is unsafe
  } 
}

template <moonbit_abi R, moonbit_abi...Args> 
struct Closure {
  using Self = Closure<R,Args...>;
  R (*code)(Self* self,Args...args) noexcept;

  R operator()(Args...args) noexcept { // do not use & or && here
    moonbit_incref(code);
    (... , incref(args));
    return this->code(this,args...);
  }  
};
}
