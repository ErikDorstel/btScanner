const char *index_html=R"(

<!DOCTYPE html>
<html lang="en"><head>
<title>btScanner</title>
<meta name="author" content="Erik Dorstel">
<meta name="generator" content="vi">
<meta name="repository" content="https://github.com/ErikDorstel/btScanner">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<meta charset="utf-8">
<style>
html   { font-family:Arial; }
div    { background-color:#e0e0e0; color:#000000; border:0px; padding:0px; margin:0px; text-align:center; width:100%; user-select:none; display:inline-block; }
select { background-color:#f0f0f0; color:#000000; font-size:1.0em; border:0px; padding:0px; margin:0px; }
table  { margin-left:auto; margin-right:auto; }
td     { text-align:right; }
.x0a   { background-color:#c2d5ed; padding:0.2em 0em 0.1em; width:100%; font-size:1.5em; }
.x0b   { background-color:#c2d5ed; padding:0.1em 0em 0.2em; width:100%; font-size:1.2em; }
.x0    { background-color:#c2d5ed; padding:0.3em 0em; width:100%; font-size:1.4em; }
.x1a   { background-color:#f0f0f0; padding:0.3em 0em; width:100%; font-size:1.4em; }
.x1b   { background-color:#e0e0e0; padding:0.3em 0em; width:100%; font-size:1.4em; }
.x2    { background-color:#e0e0e0; padding:0.3em 0em; width:48%; font-size:1.4em; }
.x3    { background-color:#e0e0e0; padding:0.3em 0em; width:32%; font-size:1.4em; }
.x4    { background-color:#e0e0e0; padding:0.3em 0em; width:24%; font-size:1.4em; }
.but   { background-color:#f0f0f0; padding:0.1em 0.4em; }
</style>
<script>

function webUIinit() {
  red="#E09090"; green="#90E090"; yellow="#FFE460"; gray="#e0e0e0"; darkgray="#d0d0d0"; blue="#c2d5ed";
  appName="&nbsp;"; appDesc="&nbsp;"; ajaxObj=[]; requestAJAX('appName'); setScanTimer(true); }

function doDisplay() { }

function setScanTimer(now) { clearScanTimer(); scanTimer=window.setInterval("getScan();",5000); if (now) { getScan(); } }
function clearScanTimer() { if (typeof scanTimer!=='undefined' ) { window.clearInterval(scanTimer); ajaxObj["getScan"].abort(); } }
function getScan() { requestAJAX('getScan'); }

function requestAJAX(value) {
  ajaxObj[value]=new XMLHttpRequest; ajaxObj[value].url=value; ajaxObj[value].open("GET",value,true);
  ajaxObj[value].setRequestHeader("Content-Type","application/x-www-form-urlencoded");
  ajaxObj[value].addEventListener('load',replyAJAX); ajaxObj[value].send(); }

function replyAJAX(event) {
  if (event.target.status==200) {
    if (event.target.url=="appName") {
      id("appName").innerHTML=event.target.responseText.split(",")[0];
      id("appDesc").innerHTML=event.target.responseText.split(",")[1]; }
    else if (event.target.url=="getScan") { id("scanresult").innerHTML=event.target.responseText; } } }

function mapValue(value,inMin,inMax,outMin,outMax) { return (value-inMin)*(outMax-outMin)/(inMax-inMin)+outMin; }
function id(id) { return document.getElementById(id); }

</script></head><body onload="webUIinit();">

<div><div class="x0a" id="appName">&nbsp;</div></div>
<div><div class="x0b" id="appDesc">&nbsp;</div></div>

<div><div class="x1b" onclick="location.replace('/chooseAP');">Choose WLAN AP</div></div>

<div>
<div><div class="x1a" id="scanresult">&nbsp;</div></div>
</div>

</body></html>

)";
