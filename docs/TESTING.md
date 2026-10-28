# Validation and pending hardware checks

Portable host tests exercise malformed inputs, range checks, steady timing, pulse release, stop, deterministic random bounds, unsigned millisecond rollover, repeated start, configuration stopping and skipped deadlines. They run without Arduino hardware and do not prove firmware compilation or electrical operation.

Before enabling transistor output:

- Compile and upload on the selected ESP32-C3/core combination; record versions and result.
- Measure actual switch contacts, polarity and voltages, verify transistor pinout and resistor selection.
- Verify controller reset/power loss releases the interface and manual clicks remain possible.
- Measure pulse widths and 30/60/120/300 CPM behavior, then random intervals and rate limits.
- Check Stop during activity, invalid requests, configuration changes, a five-minute run timeout and browser/Wi-Fi disconnection.
- Confirm delivered mouse clicks using a local test counter with a harmless target, comparing them with commanded pulses.

The default controller starts stopped. Network processing, Wi-Fi load and hardware behavior affect timing; a software timeout cannot protect against every firmware hang or failed transistor. Keep power disconnect accessible during tests. No accuracy, compatibility or long-term reliability results are claimed.
