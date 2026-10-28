#pragma once
static const char DASHBOARD_JS[] PROGMEM = R"JS(
const el=id=>document.getElementById(id);let dirty=false,busy=false;
async function refresh(){try{const r=await fetch('/api/status',{cache:'no-store'});if(!r.ok)throw Error('Status unavailable');const s=await r.json();
el('status').textContent=s.running?'RUNNING':'STOPPED';el('details').textContent=(s.simulation?'SIMULATION — no GPIO output. ':'Hardware output enabled. ')+s.mode+' · '+s.normalCpm+' normal CPM';el('attempts').textContent=s.attempts+' commanded pulses since boot (not measured mouse clicks)';
if(!dirty){el('mode').value=s.mode;el('normal').value=s.normalCpm;el('minimum').value=s.minimumCpm;el('maximum').value=s.maximumCpm;}
}catch(e){el('status').textContent='Connection lost';el('details').textContent='Stop cannot be confirmed. Disconnect controller power if needed.';}}
async function post(path,body){if(busy)return;busy=true;try{const r=await fetch(path,{method:'POST',body:new URLSearchParams(body)});const text=await r.text();if(!r.ok)throw Error(text);el('feedback').textContent=text;if(path==='/api/settings')dirty=false;}catch(e){el('feedback').textContent=e.message;}finally{busy=false;await refresh();}}
el('settings').addEventListener('input',()=>dirty=true);
el('settings').addEventListener('submit',e=>{e.preventDefault();if(Number(el('minimum').value)>Number(el('maximum').value)){el('feedback').textContent='Minimum must not exceed maximum.';return;}post('/api/settings',{mode:el('mode').value,normal:el('normal').value,minimum:el('minimum').value,maximum:el('maximum').value});});
for(const b of document.querySelectorAll('[data-cpm]'))b.addEventListener('click',()=>{el('normal').value=b.dataset.cpm;dirty=true;});
el('start').addEventListener('click',()=>{if(dirty){el('feedback').textContent='Apply your settings before starting.';return;}post('/api/start',{});});
el('stop').addEventListener('click',()=>post('/api/stop',{}));refresh();setInterval(refresh,1000);
)JS";
