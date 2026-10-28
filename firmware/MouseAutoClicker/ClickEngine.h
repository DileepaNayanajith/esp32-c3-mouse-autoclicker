#pragma once
#include "Settings.h"
namespace autoclicker {
class ClickEngine {
 public:
  using RandomCpm = uint16_t (*)(uint16_t, uint16_t);
  static constexpr uint32_t pulseMs = 25;
  static constexpr uint32_t maxRunMs = 300000;
  explicit ClickEngine(RandomCpm randomCpm) : randomCpm_(randomCpm) {}
  bool configure(const Settings& next) {
    if (!valid(next)) return false;
    stop(); settings_ = next; return true;
  }
  void start(uint32_t now) {
    // Repeated start requests do not extend a session or truncate a pulse.
    if (running_) return;
    running_ = true; pressed_ = false; started_ = now; nextPress_ = now;
  }
  void stop() { running_ = false; pressed_ = false; }
  void tick(uint32_t now) {
    if (!running_) return;
    if (uint32_t(now - started_) >= maxRunMs) { stop(); return; }
    if (pressed_) {
      if (uint32_t(now - pressedAt_) >= pulseMs) pressed_ = false;
      return;
    }
    if (int32_t(now - nextPress_) < 0) return;
    uint16_t cpm = settings_.normalCpm;
    if (settings_.mode == Mode::Random) {
      cpm = randomCpm_(settings_.minimumCpm, settings_.maximumCpm);
      if (cpm < settings_.minimumCpm || cpm > settings_.maximumCpm)
        cpm = settings_.minimumCpm;
    }
    pressed_ = true; pressedAt_ = now; ++attempts_;
    // Never replay missed deadlines as a burst after a long loop stall.
    nextPress_ = now + 60000UL / cpm;
  }
  bool running() const { return running_; }
  bool pressed() const { return pressed_; }
  uint32_t attempts() const { return attempts_; }
  const Settings& settings() const { return settings_; }
 private:
  RandomCpm randomCpm_;
  Settings settings_;
  bool running_ = false, pressed_ = false;
  uint32_t started_ = 0, pressedAt_ = 0, nextPress_ = 0, attempts_ = 0;
};
}  // namespace autoclicker
