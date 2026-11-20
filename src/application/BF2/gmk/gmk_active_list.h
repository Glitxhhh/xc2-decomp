#pragma once
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gmk {

template <typename T> class TGmkActiveList : public mm::mtl::PtrSingleton<TGmkActiveList<T>> {
public:
  TGmkActiveList() : unknown20(false) {}
  ~TGmkActiveList() override {}

  // Inferred helper: updates the gimmicks of the list, flagged as being updated meanwhile; GmkManager::seqUpdate (1.0.0: 0x71005dacfc)
  // repeats it for its five lists. Original name unknown.
  static void unknown001(f32 deltaTime) {
    TGmkActiveList *list = TGmkActiveList::get();
    list->unknown20 = true;
    for (typename mm::mtl::IntrusiveList<T>::iterator it = list->unknown08.begin(); it != list->unknown08.end(); ++it) {
      it->updateInActiveList(deltaTime);
    }
    TGmkActiveList::get()->unknown20 = false;
  }

  mm::mtl::IntrusiveList<T> unknown08; // Inferred role: active gimmicks; original member name unknown.
  bool unknown20;                      // Inferred role: list being updated; original member name unknown.
};

} // namespace gmk
