#pragma once

namespace ml {

class DebDraw;
class Scn;
class WinView;

class ScnUtil {
public:
  static bool setPerspective(const Scn *scn, DebDraw *debDraw, const WinView *view);
};

} // namespace ml
