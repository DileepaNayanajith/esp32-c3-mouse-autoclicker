#include <cassert>
#include <initializer_list>
#include "../firmware/MouseAutoClicker/Settings.h"
using namespace autoclicker;
int main() {
  uint16_t n = 42;
  for (const char* s : {"", "0", "601", "-1", "2.5", "60x", " 60", "9999999999999"})
    assert(!parseCpm(s, n));
  assert(!parseCpm(nullptr, n));
  assert(parseCpm("1", n) && n == 1);
  assert(parseCpm("600", n) && n == 600);
  Settings s; assert(valid(s));
  s.minimumCpm = 121; assert(!valid(s));
  s.minimumCpm = 30; s.maximumCpm = 601; assert(!valid(s));
}
