#pragma once
static const char DASHBOARD_HTML[] PROGMEM = R"HTML(
<!doctype html><html lang="en"><head><meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1"><title>Mouse Auto Clicker</title>
<style>
:root{font-family:system-ui;color:#edf2fa;background:#15181d;color-scheme:dark}body{max-width:680px;margin:auto;padding:24px}h1{margin-bottom:4px}p{color:#b8c1cf}.card{background:#232830;border-radius:18px;padding:22px;margin:20px 0}.row{display:flex;gap:12px;flex-wrap:wrap}button,input,select{font:inherit;border-radius:9px;padding:13px;border:1px solid #566273}button{cursor:pointer;background:#246eea;color:white}button.stop{background:#a62c3e}button:disabled{opacity:.5}label{display:block;margin:16px 0 6px}input,select{box-sizing:border-box;width:100%}strong{font-size:24px}output{display:block;margin-top:12px;min-height:1.5em}small{color:#bac3d1}
</style></head><body><h1>Mouse Auto Clicker</h1><p>ESP32-C3 · Reference controller</p>
<section class="card" aria-live="polite"><strong id="status">Connecting…</strong><p id="details"></p><small id="attempts"></small></section>
<div class="row"><button id="start">Start</button><button class="stop" id="stop">Stop</button></div>
<form id="settings" class="card"><label for="mode">Mode</label><select id="mode"><option value="normal">Normal</option><option value="random">Random</option></select>
<label for="normal">Normal speed (clicks per minute)</label><input id="normal" type="number" min="1" max="600" value="60" required>
<div class="row" style="margin-top:12px"><button type="button" data-cpm="30">30 CPM</button><button type="button" data-cpm="60">60 CPM</button><button type="button" data-cpm="120">120 CPM</button><button type="button" data-cpm="300">300 CPM</button></div>
<label for="minimum">Random minimum (CPM)</label><input id="minimum" type="number" min="1" max="600" value="30" required>
<label for="maximum">Random maximum (CPM)</label><input id="maximum" type="number" min="1" max="600" value="120" required>
<p><button type="submit">Apply settings and stop</button></p></form>
<output id="feedback" aria-live="polite"></output><p>Every run stops after five minutes. Settings changes stop clicking. Keep a way to disconnect power.</p><script src="/app.js"></script></body></html>
)HTML";
