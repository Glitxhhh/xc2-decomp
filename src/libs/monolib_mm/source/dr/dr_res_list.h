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

// Inferred helper: unlinks a node linked through unknown08 and unknown10 from a doubly linked list and clears its links; original name unknown.
template <typename T> inline void unknown004(T *&first, T *&last, T *node) {
  T *previous = node->unknown08;
  T *next = node->unknown10;
  if (previous == nullptr) {
    if (next == nullptr) {
      first = nullptr;
      last = nullptr;
    } else {
      first = next;
      next->unknown08 = nullptr;
    }
  } else if (next == nullptr) {
    last = previous;
    previous->unknown10 = nullptr;
  } else {
    previous->unknown10 = next;
    node->unknown10->unknown08 = node->unknown08;
  }
  node->unknown08 = nullptr;
  node->unknown10 = nullptr;
}

} // namespace ml
