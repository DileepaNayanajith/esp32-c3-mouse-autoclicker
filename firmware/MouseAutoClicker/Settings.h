#pragma once
#include <stdint.h>
#include <stddef.h>
namespace autoclicker {
enum class Mode { Normal, Random };
struct Settings {
  uint16_t normalCpm = 60;
  uint16_t minimumCpm = 30;
  uint16_t maximumCpm = 120;
  Mode mode = Mode::Normal;
};
inline bool valid(const Settings& s) {
  return s.normalCpm >= 1 && s.normalCpm <= 600 &&
    s.minimumCpm >= 1 && s.maximumCpm <= 600 &&
    s.minimumCpm <= s.maximumCpm &&
    (s.mode == Mode::Normal || s.mode == Mode::Random);
}
// Strict decimal input: no signs, decimals, whitespace or trailing text.
inline bool parseCpm(const char* text, uint16_t& result) {
  if (!text || !*text) return false;
  unsigned value = 0;
  for (const char* p = text; *p; ++p) {
    if (*p < '0' || *p > '9') return false;
    value = value * 10 + unsigned(*p - '0');
    if (value > 600) return false;
  }
  if (value < 1) return false;
  result = static_cast<uint16_t>(value);
  return true;
}
}  // namespace autoclicker
