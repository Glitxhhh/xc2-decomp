#include "dr/dr_environment_tex.h"

#include <new>

#include "grlib/cglib_texture.h"
#include "grlib/cglib_texture_buffer.h"

namespace ml {

namespace {

// Inferred role: texture table entry of the environment resource; original name unknown.
struct unknown001 {
  u32 unknown00; // Inferred role: image offset; original member name unknown.
  u32 unknown04; // Inferred role: image size; original member name unknown.
};

} // namespace

DrEnvironmentTex::DrEnvironmentTex() : unknown00(nullptr), unknown08(0) {}

int DrEnvironmentTex::getTextureWork(int count) { return count * sizeof(grlib::CGLibTextureBuffer); }

void DrEnvironmentTex::setupTexture(void *work, int count, const u8 *table, const u8 *data) {
  unknown00 = static_cast<grlib::CGLibTextureBuffer *>(work);
  unknown08 = count;
  const unknown001 *entry = reinterpret_cast<const unknown001 *>(table);
  for (int i = 0; i < unknown08; i++) {
    new (&unknown00[i]) grlib::CGLibTextureBuffer();
    grlib::CGLibTexture::createTextureImagePtrs(unknown00[i], data + entry->unknown00, entry->unknown04, false, nullptr, true);
    entry++;
  }
}

grlib::CGLibTextureBuffer *DrEnvironmentTex::getTexture(int index) { return &unknown00[index]; }

void DrEnvironmentTex::releaseTexture() {
  if (unknown08 != 0) {
    for (int i = 0; i < unknown08; i++) {
      unknown00[i].release();
    }
    unknown08 = 0;
    unknown00 = nullptr;
  }
}

} // namespace ml
