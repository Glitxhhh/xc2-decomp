// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/execute/title/title_main.cpp.
#include "mm_mtl/delegate.h"  // IWYU pragma: keep
#include "mm_mtl/singleton.h" // IWYU pragma: keep

namespace tl {

class TitleMain; // IWYU pragma: keep

} // namespace tl

template mm::mtl::PtrSingleton<tl::TitleMain>::~PtrSingleton();
template void mm::mtl::Delegate<void(tl::TitleMain *)>::staticFuncInvoker(const mm::mtl::Delegate<void(tl::TitleMain *)> *, tl::TitleMain *);
