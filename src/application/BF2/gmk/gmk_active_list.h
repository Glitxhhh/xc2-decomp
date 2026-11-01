#pragma once
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/singleton.h"

namespace gmk {

template <typename T> class TGmkActiveList : public mm::mtl::PtrSingleton<TGmkActiveList<T>> {
public:
  TGmkActiveList() : unknown20(false) {}
  ~TGmkActiveList() override {}

  mm::mtl::IntrusiveList<T> unknown08; // Inferred role: active gimmicks; original member name unknown.
  bool unknown20;                      // Inferred role: list being updated; original member name unknown.
};

} // namespace gmk
