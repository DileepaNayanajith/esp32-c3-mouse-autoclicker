# Arduino IDE setup for the reference sketch

1. Install Arduino IDE and Espressif's ESP32 board support. Select the ESP32-C3 target appropriate to your board and its USB settings. The reference sketch compiled during publication with Arduino-ESP32 3.3.10 for `esp32:esp32:esp32c3` in simulation configuration. Your physical board and USB settings still need verification.
2. Copy `firmware/MouseAutoClicker/config.example.h` to `config.h` in the same folder. Set a unique 8–63 character AP password. The placeholder is rejected by the sketch and the local file is ignored by Git.
3. Leave `AUTOCLICKER_SIMULATION` at `1`. Open `MouseAutoClicker.ino`, compile for your actual board and upload. No third-party Arduino libraries are required beyond the board package's WiFi/WebServer libraries.
4. Open Serial Monitor at 115200 baud, connect to the configured AP and open the address printed there, commonly `http://192.168.4.1/`.
5. Verify Start, Stop, mode/rate controls and the simulation indicator before connecting mouse-contact wiring.
6. Review the real mouse circuit, then set a verified output GPIO and disable simulation only when the NPN interface is suitable. The pin is intentionally unset; no original GPIO has been guessed. Verify reset behavior and add hardware pull-down/driver provisions as needed.

This is a fresh reference implementation. The supplied screenshot belongs to the earlier original interface and is not a screenshot of this new dashboard. Defaults, range limits, pulse width, session cap and protocol are new implementation choices. GPIO/USB settings and physical operation still require testing on the board.
