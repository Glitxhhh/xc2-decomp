#pragma once

namespace ai {
class State;
} // namespace ai

namespace gf {

class GfComPropertyPc;

namespace pc {

bool IsBuddy(GfComPropertyPc &property);
bool isWallState(ai::State *state);

} // namespace pc
} // namespace gf
