#pragma once
#include "types.h"

#include <stddef.h>

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

struct stCsvbRowInfo;
struct stCsvbDataInfo;

// Header of a CSVB file followed by the pointers GetCsvbInfo resolves into the file (0x10 bytes of file header, then 0x20 bytes of pointers).
struct stCsvbInfo {
  u32 unknown00; // Inferred role: file magic; original member name unknown.
  u16 unknown04; // Inferred role: row count; original member name unknown.
  u16 unknown06; // Inferred role: data count; original member name unknown.
  u32 unknown08; // Inferred role: size of the byte data block; original member name unknown.
  u32 unknown0c; // Inferred role: size of the string block; original member name unknown.
  const stCsvbRowInfo *unknown10;
  const stCsvbDataInfo *unknown18;
  const u8 *unknown20; // Inferred role: byte data block; original member name unknown.
  const char *unknown28;
};

static_assert(offsetof(stCsvbInfo, unknown10) == 0x10, "");
static_assert(sizeof(stCsvbInfo) == 0x30, "");

namespace csvb {

class CCsvbUtility {
public:
  static void EndianSwap4(void *value);
  static void EndianSwap2(void *value);
  static bool LoadFile(const char *path, void **data, u32 *size);
  static void SaveFile(const char *path, const void *data, u32 size);
  static int GetCsvbFormat(const void *data);
  static bool GetCsvbInfo(stCsvbInfo &info, const void *data, u32 size, bool endianSwap);
  static void *CreateCsvbRows(mtl::ALLOC_HANDLE handle, const stCsvbRowInfo *rows, u16 count, bool endianSwap);
  static void *CreateCsvbRows(mm::mtl::IAllocator *allocator, const stCsvbRowInfo *rows, u16 count, bool endianSwap);
  static void *CreateCsvbData(mtl::ALLOC_HANDLE handle, const stCsvbDataInfo *info, u16 count, const u8 *data, const char *strings, bool endianSwap);
  static void *CreateCsvbData(mm::mtl::IAllocator *allocator, const stCsvbDataInfo *info, u16 count, const u8 *data, const char *strings, bool endianSwap);
};

} // namespace csvb
