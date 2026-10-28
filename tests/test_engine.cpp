#include <cassert>
#include <cstdint>
#include "../firmware/MouseAutoClicker/ClickEngine.h"
using namespace autoclicker;
static uint16_t upper(uint16_t, uint16_t high) { return high; }
int main() {
  ClickEngine e(upper);
  e.tick(0); assert(!e.pressed() && !e.running());
  e.start(100); e.tick(100); assert(e.pressed() && e.attempts() == 1);
  e.tick(124); assert(e.pressed());
  e.tick(125); assert(!e.pressed());
  e.tick(1099); assert(!e.pressed());
  e.tick(1100); assert(e.pressed() && e.attempts() == 2);
  e.stop(); assert(!e.pressed() && !e.running());
  Settings s; s.mode = Mode::Random; s.minimumCpm = 120; s.maximumCpm = 120;
  assert(e.configure(s)); e.start(0); e.tick(0); e.tick(25);
  e.tick(499); assert(!e.pressed()); e.tick(500); assert(e.pressed());
  e.stop(); const uint32_t nearWrap = UINT32_MAX - 10;
  e.start(nearWrap); e.tick(nearWrap); e.tick(14); assert(!e.pressed());
  e.tick(489); assert(e.pressed()); // 500 ms after start, across wrap.
  e.tick(nearWrap + ClickEngine::maxRunMs); assert(!e.running() && !e.pressed());
  e.start(10); e.tick(10); e.start(11); assert(e.pressed());
  s.normalCpm = 0; assert(!e.configure(s)); assert(e.running());
  s.normalCpm = 60; assert(e.configure(s)); assert(!e.running());
  e.start(100); e.tick(100); e.tick(10000); assert(!e.pressed());
  auto before = e.attempts(); e.tick(10001); assert(e.attempts() == before + 1);
  e.tick(10002); assert(e.attempts() == before + 1);
}
