///|
#borrow(f)
extern "c" fn register_callback(f : () -> Unit) = "register_callback"

///|
#borrow(xs, f)
extern "c" fn cxx_sort(xs : FixedArray[Int], f : (Int, Int) -> Int) = "cxx_sort"


///|
fn test_1() -> Unit {
  fn callback() {
    println("hello")
  }

  register_callback(callback)
  register_callback(callback)
  register_callback(callback)
  let xs : FixedArray[Int] = @quickcheck.samples(10) |> FixedArray::from_array
  let mut is_rev = false
  fn comp(x : Int, y : Int) {
    if is_rev {
      y.compare(x)
    } else {
      x.compare(y)
    }
  }

  cxx_sort(xs, comp)
  println(xs)
  is_rev = true
  cxx_sort(xs, comp)
  println(xs)
}

struct Point {
  x : Int 
  y : Int 
} derive(@quickcheck.Arbitrary,Show, Compare,Eq)

///|
#borrow(xs, f)
extern "c" fn cxx_sort_point(xs : FixedArray[Point], f : (Point, Point) -> Int) = "cxx_sort_point"

///|
fn main {
  let xs = @quickcheck.samples(5) |> FixedArray::from_array
  println(xs)
  cxx_sort_point(xs,Point::compare)
  println(xs)
}
