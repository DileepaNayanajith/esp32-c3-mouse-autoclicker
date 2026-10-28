# Hardware

| Item | Evidence |
| --- | --- |
| Existing wired mouse | Supplied open-mouse photo |
| ESP32-C3 controller | Owner confirmation; board visible in photo |
| 2N2222 NPN transistor | Owner confirmation |
| Added wiring and resistors | Visible in photo; values not confirmed |
| Phone Wi-Fi web controller | Supplied screenshot |

The mouse's original USB electronics continue to produce mouse events; the reference sketch does not implement USB HID. ESP32-C3 USB Serial/JTAG is not being used as a general USB mouse interface here.

The exact mouse model, click GPIO, transistor package/pinout, resistor values, supply connection and common-ground arrangement need to be recorded from the real build. No guessed pin mapping is presented as original wiring.
