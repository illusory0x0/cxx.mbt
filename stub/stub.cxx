#include <moonbit_cxx.h>

using namespace moonbit;

#include <algorithm>

extern "C" {
void register_callback(Ref<Closure<Unit, Unit>> callback) {
  (*callback)(trivial);
}

void cxx_sort(FixedArray<Int> xs, Ref<Closure<Int, Int, Int>> compare) {
  std::sort(xs, xs + fixedarray_length(xs),
            [&](int lhs, int rhs) -> bool { return (*compare)(lhs, rhs) < 0; });
}

struct Point {};

void cxx_sort_point(FixedArray<Ref<Point>> xs, Ref<Closure<Int, Ref<Point>, Ref<Point>>> compare) {
  std::sort(xs, xs + fixedarray_length(xs),
            [&](Ref<Point> lhs, Ref<Point> rhs) -> bool { return (*compare)(lhs, rhs) < 0; });
}



}
