#pragma once
#include <stddef.h>

#include "anm/anm_array-inl.h"
#include "anm/anm_reference_object.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "mm_math/mm_vec4.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace anm {
class Pose;
} // namespace anm

namespace skd {

class CollisionObject;
class DynamicsSolver;
class ForceInterface;

struct ResSolver {
  const char *unknown00; // Inferred role: name; original member name unknown.
  u8 _08[0x58 - 0x08];
};

static_assert(sizeof(ResSolver) == 0x58, "");

// Layout evidence for the resource structs below: setResCollision (0x710097570c), setResConstraint (0x7100976094) and
// DynamicsImporter::importXML (0x7100976704) fill them, and the copies of their Vector push_back and expand show which
// members are copied one by one (the Vec4 members) and which are copied as raw bytes.

// Collision shape read from the dynamics xml; the shapes derive from it (setResCollision takes a ResCollision *).
struct ResCollision {
  u32 unknown00;         // Inferred role: shape type (0 sphere, 1 capsule, 2 plane); original member name unknown.
  const char *unknown08; // Inferred role: name; original member name unknown.
  const char *unknown10; // Inferred role: bound joint name ("bind_joint"); original member name unknown.
  u32 unknown18;         // Inferred role: collision type ("col_type"); original member name unknown.
  mm::Vec4 unknown20;    // Inferred role: local translation, w = 1; original member name unknown.
  mm::Quat unknown30;    // Inferred role: local rotation; original member name unknown.
};

static_assert(offsetof(ResCollision, unknown08) == 0x08, "");
static_assert(offsetof(ResCollision, unknown10) == 0x10, "");
static_assert(offsetof(ResCollision, unknown18) == 0x18, "");
static_assert(offsetof(ResCollision, unknown20) == 0x20, "");
static_assert(offsetof(ResCollision, unknown30) == 0x30, "");
static_assert(sizeof(ResCollision) == 0x40, "");

struct ResCollisionShpere : ResCollision {
  f32 unknown40; // Inferred role: radius; original member name unknown.
};

static_assert(offsetof(ResCollisionShpere, unknown40) == 0x40, "");
static_assert(sizeof(ResCollisionShpere) == 0x50, "");

struct ResCollisionCapsule : ResCollision {
  f32 unknown40; // Inferred role: radius; original member name unknown.
  f32 unknown44; // Inferred role: height; original member name unknown.
};

static_assert(offsetof(ResCollisionCapsule, unknown40) == 0x40, "");
static_assert(offsetof(ResCollisionCapsule, unknown44) == 0x44, "");
static_assert(sizeof(ResCollisionCapsule) == 0x50, "");

struct ResCollisionPlane : ResCollision {};

static_assert(sizeof(ResCollisionPlane) == 0x40, "");

struct ResNode {
  const char *unknown00; // Inferred role: name; original member name unknown.
  const char *unknown08; // Inferred role: bound joint name ("bind_joint"); original member name unknown.
  f32 unknown10;         // Inferred role: model space restore rate ("restoreMS"); original member name unknown.
  f32 unknown14;         // Inferred role: local space restore rate ("restoreLS"); original member name unknown.
  f32 unknown18;         // Inferred role: damping ("damping"); original member name unknown.
  f32 unknown1c;         // Inferred role: power gain ("powergain"); original member name unknown.
  f32 unknown20;         // Inferred role: float attribute of the node; original member name unknown.
  u16 unknown24;         // Inferred role: flag set from an integer attribute; original member name unknown.
};

static_assert(offsetof(ResNode, unknown20) == 0x20, "");
static_assert(offsetof(ResNode, unknown24) == 0x24, "");
static_assert(sizeof(ResNode) == 0x28, "");

struct ResNodeCollision {
  u16 unknown00; // Inferred role: first node index; original member name unknown.
  u16 unknown02; // Inferred role: second node index; original member name unknown.
  f32 unknown04; // Inferred role: position ratio between the two nodes; original member name unknown.
  f32 unknown08; // Inferred role: radius ("radius"); original member name unknown.
  u32 unknown0c; // Inferred role: attribute copied from the constraint xml; original member name unknown.
};

static_assert(offsetof(ResNodeCollision, unknown0c) == 0x0c, "");
static_assert(sizeof(ResNodeCollision) == 0x10, "");

// Constraint between two nodes; the constraints derive from it (setResConstraint takes a ResConstraint *).
struct ResConstraint {
  const char *unknown00; // Inferred role: name; original member name unknown.
  f32 unknown08;         // Inferred role: distance ("distance"); original member name unknown.
  u16 unknown0c;         // Inferred role: first node index ("bind_node0"); original member name unknown.
  u16 unknown0e;         // Inferred role: second node index ("bind_node1"); original member name unknown.
};

static_assert(offsetof(ResConstraint, unknown0c) == 0x0c, "");
static_assert(offsetof(ResConstraint, unknown0e) == 0x0e, "");
static_assert(sizeof(ResConstraint) == 0x10, "");

// Angle limit; the name comes from skd::limitCone(ResConstraint const &, ResConeLimit const &, NodeArray *), which
// applyStickConstraints calls with the member at 0x10 of each ResStickConstraint. The 8-byte copy at 0x20 in
// Vector<ResHingeConstraint>::push_back shows the hinge constraint holds one too.
struct ResConeLimit {
  f32 unknown00;  // Inferred role: limit angle in radians ("angle"); original member name unknown.
  bool unknown04; // Inferred role: limit enabled ("use_limit"); original member name unknown.
};

static_assert(offsetof(ResConeLimit, unknown04) == 0x04, "");
static_assert(sizeof(ResConeLimit) == 0x08, "");

struct ResStickConstraint : ResConstraint {
  ResConeLimit unknown10; // Inferred role: angle limit; original member name unknown.
};

static_assert(offsetof(ResStickConstraint, unknown10) == 0x10, "");
static_assert(sizeof(ResStickConstraint) == 0x18, "");

struct ResSpringConstraint : ResConstraint {
  f32 unknown10; // Inferred role: spring rate ("spring"); original member name unknown.
  f32 unknown14; // Inferred role: maximum extension ("extendMax"); original member name unknown.
  f32 unknown18; // Inferred role: maximum shrink ("shrinkMax"); original member name unknown.
};

static_assert(offsetof(ResSpringConstraint, unknown18) == 0x18, "");
static_assert(sizeof(ResSpringConstraint) == 0x20, "");

struct ResHingeConstraint : ResConstraint {
  mm::Vec4 unknown10;     // Inferred role: hinge axis, w = 1; original member name unknown.
  ResConeLimit unknown20; // Inferred role: angle limit; original member name unknown.
};

static_assert(offsetof(ResHingeConstraint, unknown10) == 0x10, "");
static_assert(offsetof(ResHingeConstraint, unknown20) == 0x20, "");
static_assert(sizeof(ResHingeConstraint) == 0x30, "");

// Simulated node, one per ResNode: NodeArray::NodeArray (0x710098234c) resizes its Vector<Node> to the ResNode count.
// Layout evidence: the element copy of Vector<Node>::extend (copy_construct_n at 0x71009825b8) copies the Vec3 members
// one by one and the Quat members as raw bytes, and resize zero-fills new nodes; applySpringConstraints reads and
// moves the position at 0x50.
struct Node {
  mm::Vec3 unknown00; // Inferred role: translation; original member name unknown.
  mm::Quat unknown10; // Inferred role: rotation; original member name unknown.
  mm::Vec3 unknown20; // Inferred role: vector, use not determined; original member name unknown.
  mm::Vec3 unknown30; // Inferred role: vector, use not determined; original member name unknown.
  mm::Quat unknown40; // Inferred role: rotation; original member name unknown.
  mm::Vec3 unknown50; // Inferred role: current position; original member name unknown.
  mm::Vec3 unknown60; // Inferred role: vector, use not determined; original member name unknown.
  mm::Vec3 unknown70; // Inferred role: vector, use not determined; original member name unknown.
  mm::Vec3 unknown80; // Inferred role: vector, use not determined; original member name unknown.
  mm::Vec3 unknown90; // Inferred role: vector, use not determined; original member name unknown.
  u16 unknowna0;      // Inferred role: index, use not determined; original member name unknown.
};

static_assert(offsetof(Node, unknown10) == 0x10, "");
static_assert(offsetof(Node, unknown40) == 0x40, "");
static_assert(offsetof(Node, unknown50) == 0x50, "");
static_assert(offsetof(Node, unknowna0) == 0xa0, "");
static_assert(sizeof(Node) == 0xb0, "");

struct ResCollisionArray;

struct ResDynamics {
  u8 _00[0x18 - 0x00];
  const ResCollisionArray *unknown18;     // Inferred role: collisions; original member name unknown.
  const anm::Array<ResSolver> *unknown20; // Inferred role: solvers; original member name unknown.
};

static_assert(offsetof(ResDynamics, unknown18) == 0x18, "");
static_assert(offsetof(ResDynamics, unknown20) == 0x20, "");

class Dynamics : public anm::ReferenceObject {
public:
  void update(f32 deltaTime);
  void notifyMovement(const mm::Vec3 &position, const mm::Quat &rotation, const mm::Vec3 &previousPosition, const mm::Quat &previousRotation);
  void resetDynamics();
  f32 getSolverBlendWeight(u32 index) const;
  void setSolverBlendWeight(u32 index, f32 weight);

  const anm::Array<ResSolver> *unknown18;      // Inferred role: res solvers; original member name unknown.
  mm::mtl::Vector<DynamicsSolver *> unknown20; // Inferred role: solvers; original member name unknown.
  anm::Pose *unknown48;                        // Inferred role: pose; original member name unknown.
  ForceInterface *unknown50;                   // Inferred role: force; original member name unknown.
  u8 _58[0x188 - 0x58];
  u32 unknown188;              // Inferred role: iteration count; original member name unknown.
  CollisionObject *unknown190; // Inferred role: collision object; original member name unknown.
  f32 unknown198;              // Inferred role: max move distance; original member name unknown.
  f32 unknown19c;              // Inferred role: max rotation; original member name unknown.
};

static_assert(offsetof(Dynamics, unknown18) == 0x18, "");
static_assert(offsetof(Dynamics, unknown20) == 0x20, "");
static_assert(offsetof(Dynamics, unknown48) == 0x48, "");
static_assert(offsetof(Dynamics, unknown50) == 0x50, "");
static_assert(offsetof(Dynamics, unknown188) == 0x188, "");
static_assert(offsetof(Dynamics, unknown190) == 0x190, "");
static_assert(offsetof(Dynamics, unknown198) == 0x198, "");
static_assert(offsetof(Dynamics, unknown19c) == 0x19c, "");

} // namespace skd
