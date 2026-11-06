#include "event/group.h"

#include <math.h>

#include "event/chara_obj.h"
#include "mm_math/mm_mat44.h"

namespace event {

Group::Group() : unknown410(0.0f, 0.0f, 0.0f), unknown420(0.0f), unknown424(0.0f) {}

void Group::clear() { unknown08.clear(); }

void Group::push(const CharaObj *chara) { unknown08.push_back(chara); }

void Group::pop(const CharaObj *chara) {
  for (const CharaObj **it = unknown08.begin(); it != unknown08.end(); it++) {
    if (*it == chara) {
      unknown08.erase(it);
      return;
    }
  }
}

void Group::update(bool isUpdateDir) {
  if (!unknown08.empty()) {
    updatePos_Radius();
    if (isUpdateDir) {
      updateDir();
    }
  }
}

void Group::updatePos_Radius() {
  mm::Vec3 center = unknown08.front()->getPos();
  f32 radius = 0.0f;
  for (const CharaObj **it = unknown08.begin() + 1; it != unknown08.end(); it++) {
    mm::Vec3 pos = (*it)->getPos();
    mm::Vec3 diff = pos - center;
    if (diff.x * diff.x + diff.y * diff.y + diff.z * diff.z < radius * radius) {
      continue;
    }
    if (fabsf(diff.x) <= 0.000001f && fabsf(diff.y) <= 0.000001f && fabsf(diff.z) <= 0.000001f) {
      continue;
    }
    diff.unknown001();
    center = (pos + (center - diff * radius)) * 0.5f;
    mm::Vec3 delta = pos - center;
    radius = sqrtf(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
  }
  unknown410 = center;
  unknown420 = radius;
}

void Group::updateDir() {
  mm::Vec3 sum(0.0f, 0.0f, 0.0f);
  for (const CharaObj **it = unknown08.begin(); it != unknown08.end(); it++) {
    mm::Mat44 mat;
    mat.setRotY((*it)->getRot().y);
    mm::Vec3 dir;
    dir.x = 0.0f * mat.rows[0][0] + 0.0f * mat.rows[1][0] + 1.0f * mat.rows[2][0] + mat.rows[3][0];
    dir.y = 0.0f * mat.rows[0][1] + 0.0f * mat.rows[1][1] + 1.0f * mat.rows[2][1] + mat.rows[3][1];
    dir.z = 0.0f * mat.rows[0][2] + 0.0f * mat.rows[1][2] + 1.0f * mat.rows[2][2] + mat.rows[3][2];
    sum += dir;
  }
  f32 invCount = 1.0f / unknown08.size();
  unknown424 = -atan2f(sum.x * invCount, -(sum.z * invCount));
}

} // namespace event
