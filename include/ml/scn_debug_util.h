#pragma once

namespace mm {
struct Mat44;
struct Vec3;
} // namespace mm

namespace ml {

class DebDraw;
class ScnObjCam;
class ScnObjModel;

class ScnDebugUtil {
public:
  static bool renderGuide(DebDraw *debDraw, const ScnObjCam *cam, const mm::Vec3 &position, int offset, int length, mm::Vec3 *screen);
  static void renderCamera(DebDraw *debDraw, ScnObjCam *cam, const mm::Mat44 *matrix);
  static void renderSekeleton(DebDraw *debDraw, const ScnObjCam *cam, ScnObjModel *model);
};

} // namespace ml
