#pragma once

namespace bin {

class BinaryResolver {
public:
  static void *resolve(void *data);
  static bool restore(void *data);
};

} // namespace bin
