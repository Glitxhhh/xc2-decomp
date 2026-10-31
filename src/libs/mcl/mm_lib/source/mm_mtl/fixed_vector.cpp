#include "mm_mtl/fixed_vector.h"

namespace mm {
namespace mtl {

template void FixedVector<unsigned short, 16>::push_back(const unsigned short &value);
template FixedVector<signed char, 3>::~FixedVector();

} // namespace mtl
} // namespace mm
