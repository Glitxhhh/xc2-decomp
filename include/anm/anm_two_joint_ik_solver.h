#pragma once

namespace mm {
struct Vec3;
} // namespace mm

namespace anm {

void projectNormal(const mm::Vec3 &normal, const mm::Vec3 &vector, mm::Vec3 *pPerpendicular, mm::Vec3 *pParallel);

} // namespace anm
