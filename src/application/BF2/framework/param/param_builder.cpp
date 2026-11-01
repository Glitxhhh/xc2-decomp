#include "framework/param/param_builder.h"

#include "bin/bin_binary_resolver.h"
#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"

namespace fw {

mm::mtl::IntrusivePtr<ParamList> ParamBuilder::importBinary(void *data, Reflection *reflection) {
  const ParamList::unknown006 *binary = static_cast<const ParamList::unknown006 *>(bin::BinaryResolver::resolve(data));
#line 90
  ParamList *list = new (Allocator::getProcAllocator(), 16, __FILE__, __LINE__) ParamList(binary);
  if (reflection != nullptr) {
    list->unknown18 = reflection;
  }

  return list;
}

bool ParamBuilder::restore(void *data) { return bin::BinaryResolver::restore(data); }

} // namespace fw
