#pragma once

namespace mm {
struct Vec3;
struct Mat44;
class Sphere;
} // namespace mm

namespace ml {

class ScnObjCam;

class ScnCamUtil {
public:
  static bool getScreenPos(mm::Vec3 &screen, const ScnObjCam *cam, bool isBack, const mm::Vec3 &position);
  static bool getScreenPos(mm::Vec3 &screen, const ScnObjCam *cam, const mm::Vec3 &position);
  static void getPerspective(mm::Mat44 &matrix, const ScnObjCam *cam);
  static void getSphereScreenRadius(mm::Sphere &sphere, const ScnObjCam *cam, const mm::Vec3 &position, float radius);
  static bool isDispScreen(const ScnObjCam *cam, const mm::Vec3 &position);
};

} // namespace ml
