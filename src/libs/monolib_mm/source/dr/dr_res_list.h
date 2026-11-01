#pragma once

namespace ml {

// Inferred helper: unlinks a node from a doubly linked list and clears its links; original name unknown.
template <typename T> inline void unknown001(T *&first, T *&last, T *node) {
  T *previous = node->unknown00;
  T *next = node->unknown08;
  if (previous == nullptr) {
    if (next == nullptr) {
      first = nullptr;
      last = nullptr;
    } else {
      first = next;
      next->unknown00 = nullptr;
    }
  } else if (next == nullptr) {
    last = previous;
    previous->unknown08 = nullptr;
  } else {
    previous->unknown08 = next;
    node->unknown08->unknown00 = node->unknown00;
  }
  node->unknown00 = nullptr;
  node->unknown08 = nullptr;
}

// Inferred helper: finds the node of a resource key in a list and adds a reference to it; original name unknown.
template <typename T> inline T *unknown003(T *first, const void *key) {
  for (T *node = first; node != nullptr; node = node->unknown08) {
    if (node->unknown10 == key) {
      node->unknown18++;
      return node;
    }
  }
  return nullptr;
}

} // namespace ml
