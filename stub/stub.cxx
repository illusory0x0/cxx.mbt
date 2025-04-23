#include <algorithm>
#include <iostream>
#include <moonbit_cxx_borrow.h>
#include <type_holes.h>

using namespace moonbit::types;
using namespace moonbit::operators;
using namespace type_holes;

extern "C" {
void register_callback(Closure<Unit> callback) { callback(); }

void cxx_sort(FixedArray<Int> xs, Closure<Int, Int, Int> compare) {
  std::sort(xs.begin(), xs.end(), [&](Int lhs, Int rhs) -> Bool {
    return reinterpret_as_bool(compare(lhs, rhs));
  });
}

enum class Point {};

void cxx_sort_point(FixedArray<Ref<Point>> xs,
                    Closure<Int, Ref<Point>, Ref<Point>> compare) {
  auto rc = Rc(xs);
  auto x = Rc(*xs.begin());

  xs.increment_strong_count();
  xs.decrement_strong_count();
  ::std::sort(xs.begin(), xs.end(),
              [&](Ref<Point> lhs, Ref<Point> rhs) -> Bool {
                return reinterpret_as_bool(compare(lhs, rhs));
              });
}
void test_option_int(Option<Int> x) {
  std::cout << std::boolalpha;
  std::cout << x.is_none() << '\n';
}
}