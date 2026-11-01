#pragma once
#include <new>
#include <stddef.h>

#include "mm/mm_std_base.h"
#include "mm_mtl/allocator.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/rtti.h"
#include "mm_mtl/unique_ptr.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace ai {

// Inferred role: type of an Event, switched on by the onEvent overrides of the gf::pc::TaskField classes; original name
// unknown.
enum unknown002 {
  UNKNOWN002_UNKNOWN_1 = 1, // Inferred role: ActivateEvent.
  UNKNOWN002_UNKNOWN_2 = 2, // Inferred role: CreateEvent.
  UNKNOWN002_UNKNOWN_4 = 4, // Inferred role: DestroyEvent.
};

// Layout evidence: BehaviorNode::setActiveNotiryChildren (0x7100542eec) passes the type at 0x00 and the active flag at
// 0x04 to onEvent; BehaviorTree::createTask passes type 2 and the gf::pc::TaskField onEvent overrides dispatch types 1, 2
// and 4 to onChangeActivate, onCreate and onDestroy.
struct Event {
  explicit Event(unknown002 type) : unknown00(type) {}

  u32 unknown00; // Inferred role: type; original member name unknown.
};

struct ActivateEvent : Event {
  explicit ActivateEvent(bool isActive) : Event(UNKNOWN002_UNKNOWN_1), unknown04(isActive) {}

  bool unknown04; // Inferred role: new active state; original member name unknown.
};

struct CreateEvent : Event {
  CreateEvent() : Event(UNKNOWN002_UNKNOWN_2) {}
};

struct DestroyEvent : Event {
  DestroyEvent() : Event(UNKNOWN002_UNKNOWN_4) {}
};

static_assert(offsetof(ActivateEvent, unknown04) == 0x04, "");
static_assert(sizeof(ActivateEvent) == 0x08, "");

// Layout evidence: BlackBoard::BlackBoard (0x7100941ae8) only stores the vtable, and the UniquePtr release in
// BehaviorTree::~BehaviorTree calls the deleting destructor at vtable slot 2.
class BlackBoard {
public:
  static mm::mtl::RTTI m_rtti;

  BlackBoard();
  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual ~BlackBoard();
};

static_assert(sizeof(BlackBoard) == 0x08, "");

// Layout evidence: BehaviorNode::BehaviorNode (0x7100943408) stores the name FixStr at 0x0c (length at 0x2c), the
// active flag at 0x30 and the flags argument at 0x34; BehaviorTree::execute calls onEvent at vtable offset 0x30.
class BehaviorNode : public mm::mtl::ReferenceObject {
public:
  static mm::mtl::RTTI m_rtti;

  BehaviorNode(const char *name, u32 flags);
  ~BehaviorNode() override;
  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual bool execute(BlackBoard &blackBoard);
  virtual bool checkCondition(const BlackBoard &blackBoard);
  // Inline: the game emits it with the vtables of the gf::pc::TaskField classes (0x7100542eec).
  virtual void setActiveNotiryChildren(BlackBoard &blackBoard, bool isActive) {
    if (unknown30 != isActive) {
      unknown30 = isActive;
      if ((unknown34 & 1) != 0) {
        ActivateEvent event(isActive);
        onEvent(blackBoard, event);
      }
    }
  }
  // Inline: the game emits it with the vtables of the gf::pc::TaskField classes (0x7100542f3c).
  virtual void onEvent(BlackBoard &blackBoard, const Event &event) {}

  mm::mtl::FixStr<32> unknown0c; // Inferred role: name; original member name unknown.
  bool unknown30;                // Inferred role: active; original member name unknown.
  u32 unknown34;                 // Inferred role: flags (bit 0 activate event, 1 create event, 2 destroy event); original member name unknown.
};

static_assert(offsetof(BehaviorNode, unknown0c) == 0x0c, "");
static_assert(offsetof(BehaviorNode, unknown30) == 0x30, "");
static_assert(offsetof(BehaviorNode, unknown34) == 0x34, "");
static_assert(sizeof(BehaviorNode) == 0x38, "");

// Only the reference counted base is declared (reference count at 0x08 in Vector<IntrusivePtr<BehaviorNodeInfo>>::destroy):
// the members are not decompiled yet.
class BehaviorNodeInfo : public mm::mtl::ReferenceObject {};

// Layout evidence: TaskNode::TaskNode (0x7100944540) only calls the BehaviorNode constructor and stores the vtable.
class TaskNode : public BehaviorNode {
public:
  static mm::mtl::RTTI m_rtti;

  TaskNode(const char *name, u32 flags);
  ~TaskNode() override;
  const mm::mtl::RTTI *getRTTI() const override;
};

static_assert(sizeof(TaskNode) == 0x38, "");

// Layout evidence: CompositeNode::CompositeNode (0x7100943720) builds the child vector at 0x38 with the allocator argument
// and resizes it to the child count; the member name comes from the assert of CompositeNode::attachChild.
class CompositeNode : public BehaviorNode {
public:
  static mm::mtl::RTTI m_rtti;

  CompositeNode(const char *name, u32 childNum, mm::mtl::IAllocator *allocator);
  ~CompositeNode() override;
  const mm::mtl::RTTI *getRTTI() const override;
  void setActiveNotiryChildren(BlackBoard &blackBoard, bool isActive) override;
  void attachChild(u32 index, BehaviorNode *node);
  void detachChild(u32 index);
  void detachChildAll();

  mm::mtl::Vector<BehaviorNode *> m_childNodes;
};

static_assert(offsetof(CompositeNode, m_childNodes) == 0x38, "");
static_assert(sizeof(CompositeNode) == 0x60, "");

// The game has no constructor symbol for the three composite nodes: BehaviorTree::createComposite inlines them.
class ParallelNode : public CompositeNode {
public:
  static mm::mtl::RTTI m_rtti;

  ParallelNode(const char *name, u32 childNum, mm::mtl::IAllocator *allocator) : CompositeNode(name, childNum, allocator) {}
  ~ParallelNode() override;
  const mm::mtl::RTTI *getRTTI() const override;
  bool execute(BlackBoard &blackBoard) override;
  bool checkCondition(const BlackBoard &blackBoard) override;
};

class SelectorNode : public CompositeNode {
public:
  static mm::mtl::RTTI m_rtti;

  SelectorNode(const char *name, u32 childNum, mm::mtl::IAllocator *allocator) : CompositeNode(name, childNum, allocator) {}
  ~SelectorNode() override;
  const mm::mtl::RTTI *getRTTI() const override;
  bool execute(BlackBoard &blackBoard) override;
  bool checkCondition(const BlackBoard &blackBoard) override;
};

class SequenceNode : public CompositeNode {
public:
  static mm::mtl::RTTI m_rtti;

  SequenceNode(const char *name, u32 childNum, mm::mtl::IAllocator *allocator) : CompositeNode(name, childNum, allocator) {}
  ~SequenceNode() override;
  const mm::mtl::RTTI *getRTTI() const override;
  bool execute(BlackBoard &blackBoard) override;
  bool checkCondition(const BlackBoard &blackBoard) override;
};

static_assert(sizeof(ParallelNode) == 0x60, "");
static_assert(sizeof(SelectorNode) == 0x60, "");
static_assert(sizeof(SequenceNode) == 0x60, "");

// Layout evidence: RootNode::RootNode (0x71009434e0) clears the child node at 0x38, named by the assert of
// RootNode::attachChild.
class RootNode : public BehaviorNode {
public:
  static mm::mtl::RTTI m_rtti;

  RootNode();
  ~RootNode() override;
  const mm::mtl::RTTI *getRTTI() const override;
  bool execute(BlackBoard &blackBoard) override;
  void setActiveNotiryChildren(BlackBoard &blackBoard, bool isActive) override;
  void attachChild(BehaviorNode *node);
  void detachChild();

  BehaviorNode *m_pChildNode;
};

static_assert(offsetof(RootNode, m_pChildNode) == 0x38, "");
static_assert(sizeof(RootNode) == 0x40, "");

// Layout evidence: BehaviorTree::BehaviorTree (0x7100941b2c) constructs the root node at 0x00 and clears the black board
// at 0x40, the node vector at 0x48, the allocator at 0x70 and the setup flag at 0x78; the game has no BehaviorTree vtable.
// The member names m_pNodes, m_pAllocator and m_setup come from the asserts of the createTask template.
class BehaviorTree {
public:
  BehaviorTree();
  ~BehaviorTree();
  void beginSetup(u32 nodeNum, mm::mtl::IAllocator *allocator);
  void endSetup();
  void cleanup();
  void attachRoot(u32 nodeID);
  void attachComposite(u32 parentID, u32 childID, u32 index);
  void execute();

  // __LINE__ must be 47 as in the original header: it is the line argument of the first assert.
  // Inferred role: creates the black board of the given type; original name unknown.
#line 46
  template <typename T> void unknown003() {
    MM_ASSERT(m_setup == true);
    MM_ASSERT(m_pAllocator);
    void *buffer = m_pAllocator->allocate(sizeof(T), alignof(T));
    unknown40.reset(new (buffer) T());
  }

  // __LINE__ must be 60 as in the original header: it is the line argument of the first assert.
#line 59
  template <typename T> void createTask(u32 nodeID, const char *name) {
    MM_ASSERT(m_setup == true);
    MM_ASSERT(m_pAllocator);
    MM_ASSERT(m_pNodes[nodeID] == nullptr);
    void *buffer = m_pAllocator->allocate(sizeof(T), alignof(T));
    m_pNodes[nodeID] = new (buffer) T(name);
    if ((m_pNodes[nodeID]->unknown34 & 2) != 0) {
      CreateEvent event;
      m_pNodes[nodeID]->onEvent(*unknown40, event);
    }
  }

  // __LINE__ must be 79 as in the original header: it is the line argument of the first assert.
#line 78
  template <typename T> void createComposite(u32 nodeID, const char *name, u32 childNum) {
    MM_ASSERT(m_setup == true);
    MM_ASSERT(m_pAllocator);
    MM_ASSERT(m_pNodes[nodeID] == nullptr);
    void *buffer = m_pAllocator->allocate(sizeof(T), alignof(T));
    m_pNodes[nodeID] = new (buffer) T(name, childNum, m_pAllocator);
  }

  // Inferred role: black board of the given type, null when it has another type; original name unknown.
  template <typename T> T *unknown001() const {
    BlackBoard *blackBoard = unknown40.get();
    if (blackBoard == nullptr) {
      return nullptr;
    }
    return mm::mtl::dynamicCast<T>(blackBoard);
  }

  RootNode unknown00;                       // Inferred role: root node; original member name unknown.
  mm::mtl::UniquePtr<BlackBoard> unknown40; // Inferred role: black board; original member name unknown.
  mm::mtl::Vector<mm::mtl::IntrusivePtr<BehaviorNode>> m_pNodes;
  mm::mtl::IAllocator *m_pAllocator;
  bool m_setup;
};

static_assert(offsetof(BehaviorTree, unknown40) == 0x40, "");
static_assert(offsetof(BehaviorTree, m_pNodes) == 0x48, "");
static_assert(offsetof(BehaviorTree, m_pAllocator) == 0x70, "");
static_assert(offsetof(BehaviorTree, m_setup) == 0x78, "");
static_assert(sizeof(BehaviorTree) == 0x80, "");

} // namespace ai
