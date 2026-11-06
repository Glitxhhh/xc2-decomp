#pragma once

#include "types.h"

// Opus decoder of the SDK. It is not in open-ead nnheaders: the class and function names come from the imports of the
// game (_ZN2nn5codec11OpusDecoderC1Ev, _ZN2nn5codec11OpusDecoderD1Ev), the size from the layout of
// ssd::StreamController. The members are unknown.

namespace nn {
namespace codec {

class OpusDecoder {
public:
  OpusDecoder();
  ~OpusDecoder();

  u8 _00[0x30];
};

static_assert(sizeof(OpusDecoder) == 0x30, "");

} // namespace codec
} // namespace nn
