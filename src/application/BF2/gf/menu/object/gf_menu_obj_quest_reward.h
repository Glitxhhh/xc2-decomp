#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_reference_quest.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjQuestReward : public GfMenuObject {
public:
  struct OpenParam {
    OpenParam() : unknown08(0), unknown0c(0) {}

    mm::mtl::IntrusivePtr<GfMenuReferenceQuest> unknown00;  // Inferred role: quest of the reward; original member name unknown.
    u32 unknown08;                                          // Inferred role: object handle of the reward layout; original member name unknown.
    u32 unknown0c;                                          // Role and original member name unknown.
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown10; // Inferred role: mission of the reward; original member name unknown.
  };

  GfMenuObjQuestReward(u32 handle);
  ~GfMenuObjQuestReward() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static void create(GfMenuCallContext *context, const OpenParam &param, bool isAnim);
  static void open(GfMenuCallContext *context, bool isAnim);
  static void close(GfMenuCallContext *context, bool isAnim);
};

static_assert(offsetof(GfMenuObjQuestReward::OpenParam, unknown08) == 0x08, "");
static_assert(offsetof(GfMenuObjQuestReward::OpenParam, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjQuestReward::OpenParam, unknown10) == 0x10, "");
static_assert(sizeof(GfMenuObjQuestReward::OpenParam) == 0x18, "");

} // namespace gf
