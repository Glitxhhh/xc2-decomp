#pragma once
#include <stddef.h>
#include <string.h>

#include "ml/dev_font.h"
#include "ml/msg_param.h"
#include "ml/reslist.h"
#include "ml/threadval.h"
#include "ml/win_view_frame.h"
#include "ml/win_view_port.h"
#include "ml/work_obj.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "types.h"

namespace ml {
class IWorkEvent;

class WinView : public WorkObj, public FontLayer {
public:
  // Inferred base: the constructor runs the WinViewPort constructor and updateViewPort inlines WinViewPort::setSize.
  struct RENDER_INFO : public WinViewPort {
    u8 _28[0x30 - 0x28];
    bool unknown30; // Inferred role: split horizontal; original member name unknown.
    u8 _31[0x34 - 0x31];
    s16 unknown34; // Inferred role: split line; original member name unknown.
    u8 _36[0x38 - 0x36];
    s16 unknown38; // Inferred role: split line when horizontal; original member name unknown.
    u8 _3a[0x3c - 0x3a];
    u32 unknown3c; // Inferred role: first split view wid; original member name unknown.
    u32 unknown40; // Inferred role: second split view wid; original member name unknown.
    u8 _44[0x48 - 0x44];
    WinViewFrame unknown48; // Inferred role: frame; original member name unknown.
  };

  WinView(const char *name, WorkObj *parent);
  static WinView *getView(bool isResetShadow);
  void updateViewPort(const mm::Rect<int> &rect);
  void renderView();

  void setRect(const mm::Rect<int> &rect) {
    updateViewPort(rect);
    if (unknown53c) {
      memcpy(unknown1b8.m_front, unknown1b8.m_back, sizeof(RENDER_INFO));
    }
  }

  void setTitle(const char *title);
  void attachWorkEvent(IWorkEvent *event, bool isFront);
  const mm::Pnt<int> &getFramePos(bool isBack) const;
  void addFramePos(const mm::Pnt<int> &pos);
  void addScroll(const mm::Pnt<int> &scroll);
  mm::Pnt<int> getFrame2ViewOffset(bool isBack) const;
  mm::Pnt<int> getPos(bool isBack) const;
  mm::Pnt<int> getSize(bool isBack) const;
  mm::Rect<int> getRect(bool isBack) const;
  mm::Pnt<int> getClientPos(bool isBack) const;
  mm::Pnt<int> getClientSize(bool isBack) const;
  bool isSplitHolizon() const;
  bool isCurrent() const;
  WorkObj *getRootProc();
  void setRootRenderWID(WinView *view);
  void attachRenderWork(const WorkObj *work);
  WinView *getSplitView1();
  WinView *getSplitView2();
  const WinView *getSplitView1() const;
  const WinView *getSplitView2() const;
  void setDisp(bool isDisp, bool isInvalidCurrent);
  void setCurrent();
  void setFullScreen();
  void deleteSplitView();
  bool hasCurrent() const;
  mm::Pnt<int> getFrameAbsPos(bool isBack) const;
  mm::Pnt<int> getAbsPos(bool isBack) const;
  mm::Rect<int> getAbsRect(bool isBack) const;
  mm::Rect<int> getRealAbsRect(bool isBack) const;
  void normalizeAbsRect(mm::Rect<int> &rect, bool isBack) const;
  mm::Rect<int> getClientAbsRect(bool isBack) const;
  mm::Rect<int> getClientScissorAbsRect(bool isBack) const;
  bool isSplit(bool isBack) const;
  void initializeClientScreen(bool isSkipClear);
  s32 getSplitLine(bool isBack) const;
  WinView *getParentView();
  const WinView *getParentView() const;
  // evtFocusOn stays the first declared virtual: it is the key function, so the vtable and the implicit destructors are
  // only emitted once it is defined.
  virtual void evtFocusOn();
  virtual void evtFocusOff();
  virtual void detachRenderWork(const WorkObj *work);
  virtual void detachWorkEvent(const IWorkEvent *event);
  virtual void destroyCtrlMemory();
  virtual void applyRect();
  virtual void getViewOfs(mm::Rect<int> &rect, bool isBack);
  void wkTail() override;
  bool wkStandbyLogin() override;
  bool wkStandbyLogout() override;
  void updateMsg();
  void applyPrio();

  threadval<RENDER_INFO> unknown1b8; // Inferred role: render info; original member name unknown.
  reslist<u32> unknown338;           // Inferred role: render work ids; original member name unknown.
  u8 _378[0x3b8 - 0x378];
  u32 unknown3b8;          // Inferred role: state flags; original member name unknown.
  u32 unknown3bc;          // Inferred role: frame flags; original member name unknown.
  MsgParam<10> unknown3c0; // Inferred role: event messages; original member name unknown.
  u8 _4d0[0x514 - 0x4d0];
  mm::Col4 unknown514;      // Inferred role: back color, scaled by the transparency for the clear color; original member name unknown.
  f32 unknown524;           // Inferred role: transparency; original member name unknown.
  s32 unknown528;           // Inferred role: sort priority among the child views; original member name unknown.
  mm::Rect<int> unknown52c; // Inferred role: rect saved while the view is full screen; original member name unknown.
  bool unknown53c;          // Inferred role: copy the back render info to the front when the rect changes; original member name unknown.
  u8 _53d[0x590 - 0x53d];
};

static_assert(sizeof(WinView::RENDER_INFO) == 0xb0, "");
static_assert(offsetof(WinView::RENDER_INFO, unknown08) == 0x08, "");
static_assert(offsetof(WinView::RENDER_INFO, unknown30) == 0x30, "");
static_assert(offsetof(WinView::RENDER_INFO, unknown48) == 0x48, "");
static_assert(offsetof(WinView, unknown1b8) == 0x1b8, "");
static_assert(offsetof(WinView, unknown338) == 0x338, "");
static_assert(offsetof(WinView, unknown3b8) == 0x3b8, "");
static_assert(offsetof(WinView, unknown3c0) == 0x3c0, "");
static_assert(offsetof(WinView, unknown514) == 0x514, "");
static_assert(offsetof(WinView, unknown524) == 0x524, "");
static_assert(offsetof(WinView, unknown528) == 0x528, "");
static_assert(offsetof(WinView, unknown52c) == 0x52c, "");
static_assert(offsetof(WinView, unknown53c) == 0x53c, "");
static_assert(sizeof(WinView) == 0x590, "");

} // namespace ml
