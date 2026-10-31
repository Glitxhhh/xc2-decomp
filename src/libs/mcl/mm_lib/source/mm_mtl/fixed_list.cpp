#include "mm_mtl/fixed_list.h"

namespace mm {
namespace mtl {

template FixedList<unsigned int, 64>::iterator FixedList<unsigned int, 64>::erase(FixedList<unsigned int, 64>::iterator it);
template FixedList<unsigned short, 512>::iterator FixedList<unsigned short, 512>::erase(FixedList<unsigned short, 512>::iterator it);

} // namespace mtl
} // namespace mm
