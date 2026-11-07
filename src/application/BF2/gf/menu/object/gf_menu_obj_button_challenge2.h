#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjButtonChallenge2 : public GfMenuObject {
public:
  // Layout from the open overload with two bool arguments (0x7100420938): its arguments fill the first two members and the constant 0.25 the last one.
  struct OptionParam {
    bool unknown00; // Inferred role: display the button (isDispButton argument of open); original member name unknown.
    bool unknown01; // Inferred role: play the sound (isSound argument of open); original member name unknown.
    bool unknown02; // Role and original member name unknown.
    f32 unknown04;  // Inferred role: constant 0.25 set by open, a time; original member name unknown.
  };

  void initialize() override;
  void finalize() override;
  void update() override;
  static void open(GfMenuCallContext *context, unsigned int challenge, bool isDispButton, bool isSound);
  static void open(GfMenuCallContext *context, unsigned int challenge, const OptionParam &option);
  static void openSequence(GfMenuCallContext *context, unsigned int challenge, bool isDispButton, bool isSound);
  static void resume(GfMenuCallContext *context);
  static void close(GfMenuCallContext *context);
  static void dispRelationHUD(bool);
  u32 getResultPoint() const;

  u8 _24[0x90 - 0x24];
  int unknown90; // Inferred role: challenge in progress; original member name unknown.
  u32 unknown94; // Inferred role: number of challenges done before the current one; original member name unknown.
  u32 unknown98; // Inferred role: points gained; original member name unknown.
  u8 _9c[0xa0 - 0x9c];
  GfMenuSequence<GfMenuObjButtonChallenge2, 8> unknown0a0; // Inferred role: queued steps; original member name unknown.
  u8 _330[0x4a8 - 0x330];
};

static_assert(offsetof(GfMenuObjButtonChallenge2::OptionParam, unknown04) == 0x4, "");
static_assert(sizeof(GfMenuObjButtonChallenge2::OptionParam) == 0x8, "");
static_assert(offsetof(GfMenuObjButtonChallenge2, unknown90) == 0x90, "");
static_assert(offsetof(GfMenuObjButtonChallenge2, unknown94) == 0x94, "");
static_assert(offsetof(GfMenuObjButtonChallenge2, unknown98) == 0x98, "");
static_assert(sizeof(GfMenuObjButtonChallenge2) == 0x4a8, "");

} // namespace gf
