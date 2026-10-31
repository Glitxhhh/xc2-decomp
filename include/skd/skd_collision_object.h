#pragma once
#include <stddef.h>

#include "anm/anm_reference_object.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "mm_math/mm_vec4.h"
#include "types.h"

namespace skd {

struct ResCollisionCapsule;
struct ResCollisionPlane;
struct ResCollisionShpere;

class CollisionObject : public anm::ReferenceObject {
public:
  void update();
};

// Layout evidence for the collision shapes below: ShpereCollObj::calc (0x710097ae94), CapsuleCollObj::calc
// (0x710097b0ec) and PlaneCollObj::calc (0x710097b6dc) read the resource and the bone index and write the world
// space members; the copies of their Vector expand show the Vec3 and Vec4 members copied one by one, and their
// Vector resize zero-fills new elements (no user-provided default constructor).
class ShpereCollObj {
public:
  const ResCollisionShpere *unknown00; // Inferred role: resource; original member name unknown.
  mm::Vec3 unknown10;                  // Inferred role: world center; original member name unknown.
  u16 unknown20;                       // Inferred role: bone index; original member name unknown.
};

static_assert(offsetof(ShpereCollObj, unknown10) == 0x10, "");
static_assert(offsetof(ShpereCollObj, unknown20) == 0x20, "");
static_assert(sizeof(ShpereCollObj) == 0x30, "");

class CapsuleCollObj {
public:
  const ResCollisionCapsule *unknown00; // Inferred role: resource; original member name unknown.
  mm::Vec3 unknown10;                   // Inferred role: first world end point; original member name unknown.
  mm::Vec3 unknown20;                   // Inferred role: second world end point; original member name unknown.
  u16 unknown30;                        // Inferred role: bone index; original member name unknown.
};

static_assert(offsetof(CapsuleCollObj, unknown10) == 0x10, "");
static_assert(offsetof(CapsuleCollObj, unknown20) == 0x20, "");
static_assert(offsetof(CapsuleCollObj, unknown30) == 0x30, "");
static_assert(sizeof(CapsuleCollObj) == 0x40, "");

// Inferred world transform of a plane collision: its copy (Vec3 member by member, then the Quat as raw bytes) runs
// before the bone index in Vector<PlaneCollObj>::expand (0x710097d0d4), so the two members form one struct; original
// name unknown.
struct unknown001 {
  mm::Vec3 unknown00; // Inferred role: world position; original member name unknown.
  mm::Quat unknown10; // Inferred role: world rotation; original member name unknown.
};

static_assert(offsetof(unknown001, unknown10) == 0x10, "");
static_assert(sizeof(unknown001) == 0x20, "");

class PlaneCollObj {
public:
  const ResCollisionPlane *unknown00; // Inferred role: resource; original member name unknown.
  mm::Vec4 unknown10;                 // Inferred role: world plane (normal and distance); original member name unknown.
  unknown001 unknown20;               // Inferred role: world transform; original member name unknown.
  u16 unknown40;                      // Inferred role: bone index; original member name unknown.
};

static_assert(offsetof(PlaneCollObj, unknown10) == 0x10, "");
static_assert(offsetof(PlaneCollObj, unknown20) == 0x20, "");
static_assert(offsetof(PlaneCollObj, unknown40) == 0x40, "");
static_assert(sizeof(PlaneCollObj) == 0x50, "");

} // namespace skd
