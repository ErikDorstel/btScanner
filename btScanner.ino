boolean debug=true;

const char* appName="btScanner";
const char* appDesc="BT Classic and BLE";

#include "memlog.h"
#include "btscan.h"
#include "WLAN.h"
#include "DNS.h"
#include "HTTP.h"

void setup() {
  if (debug) { Serial.begin(115200); }
  initBTScan();
  initWLAN();
  initDNS();
  initHTTP(); }

void loop() { wlanWorker(); dnsWorker(); httpWorker(); btScanWorker(); }
