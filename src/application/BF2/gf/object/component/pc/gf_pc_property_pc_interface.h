#pragma once

namespace fw {
class MessageObject;
struct Message;
} // namespace fw

namespace gf {

class GfComPropertyPc;

namespace pc {

// The game has no symbol for setup, cleanup and flush of GfPropertyPcInterface, nor a vtable: they are pure virtual.
class GfPropertyPcInterface {
public:
  virtual void setup(const GfComPropertyPc &property) = 0;
  virtual void cleanup(const GfComPropertyPc &property) = 0;
  virtual void flush(const GfComPropertyPc &property) = 0;
  virtual void flushOwner(GfComPropertyPc &property);
  virtual bool recieveMessage(const GfComPropertyPc &property, fw::MessageObject *sender, fw::Message &message);
};

} // namespace pc
} // namespace gf
