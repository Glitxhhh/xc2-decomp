#include "framework/anim/anim_res_asm_resolver.h"

#include "anm/anm_mirror_mapper.h"
#include "anm/anm_reference_object.h"
#include "anm/anm_simple_mapper.h"
#include "arc/arc_data.h"

namespace fw {

AnimResAsmResolver::AnimResAsmResolver(mm::mtl::IAllocator &allocator) : unknown08(&allocator), m_skekelton(nullptr), m_mirrorMapper(nullptr), m_simpleMapper(nullptr), unknown48(&allocator) {}

AnimResAsmResolver::~AnimResAsmResolver() {
  anm::unknown001(m_mirrorMapper);
  anm::unknown001(m_simpleMapper);
}

const anm::Skeleton *AnimResAsmResolver::getSkekelton() const { return m_skekelton; }

anm::MirrorMapper *AnimResAsmResolver::getMirrorMapper() const { return m_mirrorMapper; }

anm::SimpleMapper *AnimResAsmResolver::getSimpleMapper() const { return m_simpleMapper; }

} // namespace fw
