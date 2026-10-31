#pragma once

namespace mm {
namespace mtl {
namespace mtl_detail {

struct nulltype {};

} // namespace mtl_detail

// The game constructs FixStr elements from a default constructed temporary: the elements are copied from default arguments.
template <typename T0, typename T1 = mtl_detail::nulltype, typename T2 = mtl_detail::nulltype, typename T3 = mtl_detail::nulltype, typename T4 = mtl_detail::nulltype> class Tuple {
public:
  Tuple(const T0 &a0 = T0(), const T1 &a1 = T1(), const T2 &a2 = T2(), const T3 &a3 = T3(), const T4 &a4 = T4()) : unknown00(a0), unknown001(a1), unknown002(a2), unknown003(a3), unknown004(a4) {}

  T0 unknown00;  // Inferred role: first element; original member name unknown.
  T1 unknown001; // Inferred role: second element; original member name unknown (offset depends on the element types).
  T2 unknown002; // Inferred role: third element; original member name unknown (offset depends on the element types).
  T3 unknown003; // Inferred role: fourth element; original member name unknown (offset depends on the element types).
  T4 unknown004; // Inferred role: fifth element; original member name unknown (offset depends on the element types).
};

} // namespace mtl
} // namespace mm
