#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h" // IWYU pragma: keep

namespace mm {
namespace mtl {

template void FixedVector<unsigned short, 16>::push_back(const unsigned short &value);
template FixedVector<signed char, 3>::~FixedVector();
template FixStr<256> *FixedVector<FixStr<256>, 32>::insert(FixStr<256> *it, const FixStr<256> &value);

} // namespace mtl
} // namespace mm
