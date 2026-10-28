# Reference firmware API

All state changes use POST. GET `/` serves the dashboard; GET `/app.js` serves its script. GET `/api/status` returns `running`, `simulation`, `mode`, normal/minimum/maximum CPM and commanded pulse attempts since boot.

POST `/api/settings` accepts URL-encoded `mode` (`normal` or `random`), `normal`, `minimum`, `maximum`. All rates are whole numbers from 1–600, minimum must not exceed maximum. Invalid requests return 400 and leave the previous settings unchanged. Valid settings stop clicking immediately. POST `/api/start` begins a run; repeated starts while running do not reset its five-minute limit. POST `/api/stop` releases the output and stops.

Normal timing uses integer milliseconds: `60000 / CPM`. Random mode uniformly chooses an integer CPM within inclusive configured bounds for each interval; this does not produce uniformly distributed time intervals or guarantee an average configured rate. Pulses are nominally 25 ms. A stalled loop skips missed timing slots rather than replaying them in a burst. Neither attempts nor configured CPM establishes delivered mouse clicks.

The AP password controls local Wi-Fi access. There is no separate per-client authentication or TLS, so anyone connected to the AP can control it. Keep it on the local controller network. Reboot always starts stopped and resets settings to defaults. Browser closure does not stop immediately: use Stop, the five-minute cap, or disconnect power.
