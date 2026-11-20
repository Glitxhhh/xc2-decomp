#include "ml/path_util.h"

#include <string.h>

namespace ml {

const char *PathUtil::getFilePtrFromPath(const char *path) {
  for (int i = strlen(path); i > 0; i--) {
    char c = path[i - 1];
    if (c == '/' || c == '\\' || c == ':') {
      return path + i;
    }
  }
  return path;
}

const char *PathUtil::getFileExtPtr(const char *path) {
  int length = strlen(path);
  for (int i = 0; i < length - 1; i++) {
    if (path[i] == '.') {
      return path + (i + 1);
    }
  }
  return nullptr;
}

void PathUtil::itoa(mm::mtl::FixStr<16> &string, int value, int digits) {
  string = "";
  for (int i = 0; i < digits; i++) {
    char text[2] = {};
    int unit = 1;
    for (int j = 0; j < i; j++) {
      unit *= 10;
    }
    int digit = value % (unit * 10) / unit;
    text[0] = '0' + digit;
    mm::mtl::FixStr<16> character(text);
    string = character + string.c_str();
  }
}

void PathUtil::htoa(mm::mtl::FixStr<16> &string, u32 value, int digits) {
  string = "";
  for (int i = 0; i < digits; i++) {
    char text[2] = {};
    u32 unit = 1;
    for (int j = 0; j < i; j++) {
      unit *= 16;
    }
    // The game compares (digit & 0xfe) < 10 (0x710075bc54: and w9, w8, #0xfe; cmp w9, #10), which clang gives for a byte digit; an int or u32 digit is
    // compared whole and gives 96 instructions against the game's 97 (char, unsigned char and u8 match; s8 and u16 do not).
    u8 digit = value % (unit * 16) / unit;
    text[0] = digit < 10 ? '0' + digit : 'a' + digit - 10;
    mm::mtl::FixStr<16> character(text);
    string = character + string.c_str();
  }
}

} // namespace ml
