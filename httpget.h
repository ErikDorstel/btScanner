String httpget(String request) {
  String response="";

  // webUI specific pages

  if (request.indexOf("/getScan")>=0) {
    for (int i=0;i<maxBTCDevices;i++) {
      if (btcDevices[i].active) {
        response+="BTC - ";
        response+=btcDevices[i].name; response+=" - ";
        response+=btcDevices[i].address; response+=" - ";
        response+=String(btcDevices[i].cod,HEX); response+=" - ";
        response+=String(btcDevices[i].rssi); response+=" dBm - ";
        response+=String(btcDevices[i].distance); response+=" m - ";
        response+=String(btcDevices[i].last); response+="<br>"; } }
    for (int i=0;i<maxBLEDevices;i++) {
      if (bleDevices[i].active) {
        response+="BLE - ";
        response+=bleDevices[i].name; response+=" - ";
        response+=bleDevices[i].address; response+=" - ";
        response+=bleDevices[i].mid; response+=" - ";
        response+=String(bleDevices[i].appearance,HEX); response+=" - ";
        response+=String(bleDevices[i].txpower); response+=" dBm - ";
        response+=String(bleDevices[i].rssi); response+=" dBm - ";
        response+=String(bleDevices[i].distance); response+=" m - ";
        response+=String(bleDevices[i].last); response+="<br>"; } }
    response+="&nbsp;"; }

  // WLAN Choose specific pages

  else if (request.indexOf("/appName")>=0) {
    response+=String(appName) + ",";
    response+=String(appDesc) + ","; }

  else if (request.indexOf("/chooseAP")>=0) { response=choose_html; }

  else if (request.indexOf("/statusAP")>=0) { if (wlanConfig.statusStation) { response="<div class=\"x1\">WLAN AP " + wlanConfig.ssidStation + " connected.</div>";
    response+="<div class=\"x1\">IP Address " + WiFi.localIP().toString() + "</div>"; } else { response="<div class=\"x1\">No WLAN AP connected.</div>"; } }

  else if (request.indexOf("/configAP")>=0) {
    if (WiFi.softAPgetStationNum()==0) { response=a2h(wlanConfig.ssidStation) + "," + a2h(wlanConfig.passwordStation) + ","; }
    else { response=a2h(wlanConfig.ssidStation) + ",,"; } }

  else if (request.indexOf("/scanAP")>=0) {
    wlanTimer=millis()+20000; int indexes=WiFi.scanNetworks(); response+="<div class=\"x1\"><table>"; for (int index=0;index<indexes;++index) { if (WiFi.SSID(index)!="") {
      response+="<tr><td onclick=\"setAP(\'" + WiFi.SSID(index) + "\');\">" + WiFi.RSSI(index) + "&nbsp;dB&nbsp;&nbsp;&nbsp;&nbsp;" + WiFi.SSID(index) + "</td></tr>"; } } response+="</table></div>"; }

  else if (request.indexOf("/connectAP")>=0) {
    int a=request.indexOf(",")+1; int b=request.indexOf(",",a)+1;
    if (!wlanConfig.statusStation || WiFi.softAPgetStationNum()==0) {
      wlanConfig.ssidStation=h2a(request.substring(a,b-1)); wlanConfig.passwordStation=h2a(request.substring(b)); wlanConfig.reconnectCount=0; reconnectWLAN(); }
    else { if (debug) { Serial.println("WLAN Station reconnect prevented."); } } }

  // Default page

  else if (request.indexOf("/favicon.ico")>=0) { }

  else { response=index_html; }

  return response; }
