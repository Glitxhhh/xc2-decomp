#include "ml/win_view_port.h"

#include "ml/dev_graph.h"

namespace ml {

WinViewPort::WinViewPort()
    : unknown00(DevGraph::getRootWidth(), DevGraph::getRootHeight()), unknown08(DevGraph::getRootWidth(), DevGraph::getRootHeight()), unknown10(0, 0), unknown18(0, 0), unknown20(0, 0) {}

void WinViewPort::setSize(const mm::Pnt<int> &size) {
  unknown00 = size;
  mm::Pnt<int> clientSize(unknown00.x - unknown18.x - unknown20.x, unknown00.y - unknown18.y - unknown20.y);
  if (unknown10.x > unknown08.x - clientSize.x) {
    unknown10.x = unknown08.x - clientSize.x;
  }
  if (unknown10.y > unknown08.y - clientSize.y) {
    unknown10.y = unknown08.y - clientSize.y;
  }
  if (unknown10.x < 0) {
    unknown10.x = 0;
  }
  if (unknown10.y < 0) {
    unknown10.y = 0;
  }
}

void WinViewPort::setWorkSize(const mm::Pnt<int> &size) { unknown08 = size; }

} // namespace ml
