// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/gf/object/component/pc/field/gf_pc_param_field.cpp.
#include "gf/object/component/pc/field/gf_pc_param_field.h"

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"
#include "gf/object/component/behavior/movement/gf_move_brake.h"
#include "gf/object/component/behavior/movement/gf_move_fall.h"
#include "gf/object/component/behavior/movement/gf_move_jump.h"
#include "gf/object/component/behavior/movement/gf_move_jump_back.h"
#include "gf/object/component/behavior/movement/gf_move_run.h"
#include "gf/object/component/behavior/movement/gf_move_slide.h"
#include "gf/object/component/behavior/movement/gf_move_turn.h"
#include "gf/object/component/behavior/movement/gf_move_walk.h"
#include "gf/object/component/behavior/movement/gf_move_water_rise.h"
#include "gf/object/component/behavior/movement/gf_move_water_sink.h"
#include "gf/object/component/pc/plugin/gf_pc_fade_plugin.h"
#include "mm_mtl/vector.h"

namespace gf {
namespace pc {

fw::Reflection *createReflectionField() {
#line 130
  fw::Reflection *reflection = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::Reflection();
  reflection->unknown10.resize(20, nullptr);
  FieldParam::createReflection(reflection, "common", 0);
  GfMoveBrakeControler::createReflection(reflection, "brake", 1);
  GfMoveWalkControler::createReflection(reflection, "walk", 2);
  GfMoveRunControler::createReflection(reflection, "run", 3);
  GfMoveTurnControler::createReflection(reflection, "turn", 4);
  GfMoveTurnControler::createReflection(reflection, "idle_turn", 5);
  GfMoveJumpControler::createReflection(reflection, "jump", 6);
  GfMoveJumpBackControler::createReflection(reflection, "jump_back", 7);
  GfMoveFallControler::createReflection(reflection, "fall_down", 8);
  WaterCommonParam::createReflection(reflection, "water_common", 9);
  GfMoveRunControler::createReflection(reflection, "swim", 10);
  GfMoveTurnControler::createReflection(reflection, "water_turn", 11);
  GfMoveWaterSinkControler::createReflection(reflection, "water_sink", 12);
  GfMoveWaterRiseControler::createReflection(reflection, "water_rise", 13);
  GfMoveWaterRiseControler::createReflection(reflection, "water_hole_rise", 14);
  WallCommonParam::createReflection(reflection, "wall_common", 15);
  WallMoveParam::createReflection(reflection, "wall_move", 16);
  GfMoveSlideControler::createReflection(reflection, "slide_move", 17);
  FadeParam::createReflection(reflection, "water_fade", 18);
  UniqueIdleParam::createReflection(reflection, "unique_idle", 19);
  return reflection;
}

fw::Reflection *createReflectionFieldAI() {
#line 184
  fw::Reflection *reflection = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::Reflection();
  reflection->unknown10.resize(8, nullptr);
  FollowMainPcParam::createReflection(reflection, "follow_main", 0);
  FollowMainPcParam::createReflection(reflection, "follow_water_main", 1);
  FollowBuddyPcParam::createReflection(reflection, "follow_buddy", 2);
  FollowBuddyPcParam::createReflection(reflection, "follow_water_buddy", 3);
  JumpAIParam::createReflection(reflection, "ai_jump", 4);
  WallAiParam::createReflection(reflection, "wall_ai", 5);
  ForceWarpAiParam::createReflection(reflection, "high_jump_ai", 6);
  ForceWarpAiParam::createReflection(reflection, "water_warp_ai", 7);
  return reflection;
}

} // namespace pc
} // namespace gf
