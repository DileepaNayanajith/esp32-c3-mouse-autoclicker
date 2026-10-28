/* New reference firmware; not recovered original code or hardware-tested.
 * Drives an active-high NPN base interface only after circuit verification.
 */
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "config.h"
#include "ClickEngine.h"
#include "Dashboard.h"
#include "DashboardScript.h"
#if !AUTOCLICKER_SIMULATION
static_assert(AUTOCLICKER_CLICK_PIN >= 0, "Configure a verified output pin first");
#endif
static uint16_t randomCpm(uint16_t low, uint16_t high) {
  return static_cast<uint16_t>(random(low, static_cast<long>(high) + 1));
}
autoclicker::ClickEngine engine(randomCpm);
WebServer server(80);
void outputClick() {
#if !AUTOCLICKER_SIMULATION
  digitalWrite(AUTOCLICKER_CLICK_PIN, engine.pressed() ? HIGH : LOW);
#endif
}
void reply(int code, const String& text) {
  server.sendHeader("Cache-Control", "no-store");
  server.send(code, "text/plain; charset=utf-8", text);
}
void status() {
  const auto& s = engine.settings();
  String json = "{\"running\":";
  json += engine.running() ? "true" : "false";
  json += ",\"simulation\":";
  json += AUTOCLICKER_SIMULATION ? "true" : "false";
  json += ",\"mode\":\"";
  json += s.mode == autoclicker::Mode::Normal ? "normal" : "random";
  json += "\",\"normalCpm\":" + String(s.normalCpm);
  json += ",\"minimumCpm\":" + String(s.minimumCpm);
  json += ",\"maximumCpm\":" + String(s.maximumCpm);
  json += ",\"attempts\":" + String(engine.attempts()) + "}";
  server.sendHeader("Cache-Control", "no-store");
  server.send(200, "application/json", json);
}
void settings() {
  autoclicker::Settings s;
  if (!server.hasArg("mode") || !server.hasArg("normal") ||
      !server.hasArg("minimum") || !server.hasArg("maximum")) {
    reply(400, "All settings are required"); return;
  }
  const String mode = server.arg("mode");
  if (mode != "normal" && mode != "random") { reply(400, "Invalid mode"); return; }
  s.mode = mode == "normal" ? autoclicker::Mode::Normal : autoclicker::Mode::Random;
  if (!autoclicker::parseCpm(server.arg("normal").c_str(), s.normalCpm) ||
      !autoclicker::parseCpm(server.arg("minimum").c_str(), s.minimumCpm) ||
      !autoclicker::parseCpm(server.arg("maximum").c_str(), s.maximumCpm) ||
      !engine.configure(s)) { reply(400, "Use 1–600 CPM and minimum <= maximum"); return; }
  outputClick(); reply(200, "Settings applied; clicking stopped");
}
void setup() {
  Serial.begin(115200);
#if !AUTOCLICKER_SIMULATION
  digitalWrite(AUTOCLICKER_CLICK_PIN, LOW);
  pinMode(AUTOCLICKER_CLICK_PIN, OUTPUT);
#endif
  randomSeed(esp_random());
  const String password = AUTOCLICKER_AP_PASSWORD;
  if (password.length() < 8 || password.length() > 63 ||
      password == "CHANGE-ME-before-upload") {
    Serial.println("Set your own 8–63 character AP password in config.h"); return;
  }
  WiFi.mode(WIFI_AP);
  if (!WiFi.softAP(AUTOCLICKER_AP_SSID, AUTOCLICKER_AP_PASSWORD)) {
    Serial.println("AP startup failed; clicking remains stopped"); return;
  }
  server.on("/", HTTP_GET, [] { server.send_P(200, "text/html; charset=utf-8", DASHBOARD_HTML); });
  server.on("/app.js", HTTP_GET, [] { server.send_P(200, "application/javascript", DASHBOARD_JS); });
  server.on("/api/status", HTTP_GET, status);
  server.on("/api/settings", HTTP_POST, settings);
  server.on("/api/start", HTTP_POST, [] { engine.start(millis()); reply(200, "Started; automatic stop in five minutes"); });
  server.on("/api/stop", HTTP_POST, [] { engine.stop(); outputClick(); reply(200, "Stopped"); });
  server.onNotFound([] { reply(404, "Not found"); });
  server.begin();
  Serial.print("Controller address: http://"); Serial.println(WiFi.softAPIP());
}
void loop() {
  engine.tick(millis()); outputClick();
  // Avoid HTTP work while a pulse is high; slow clients should not extend it.
  if (!engine.pressed()) server.handleClient();
}
