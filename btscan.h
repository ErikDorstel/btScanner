// ESP32 Arduino Core Library 2.0.9
// minimal 1.9 MB Flash for Apps

#define maxBTCDevices 50
#define maxBLEDevices 50
#define btScanDuration 10
#define btScanIdleTime 2
#define btDeviceMaxLast 10

// BT
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

BTScanResults* btcDeviceList=SerialBT.getScanResults();

struct btcDevicesStruct {
  bool active=false;
  String name;
  String address;
  uint32_t cod=0;
  int rssi=0;
  double distance=0;
  int last=0; } btcDevices[maxBTCDevices];

// BLE

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

BLEScan* pBLEScan;

struct bleDevicesStruct {
  bool active=false;
  String name;
  String address;
  String mid;
  uint16_t appearance=0;
  int txpower=0;
  int rssi=0;
  double distance=0;
  int last=0; } bleDevices[maxBLEDevices];

// Methods

void addBTCDevices() {
  for (int i=0;i<maxBTCDevices;i++) {
    if (btcDevices[i].active) { btcDevices[i].last++; if (btcDevices[i].last > btDeviceMaxLast) { btcDevices[i].active=false; } } }
  btcDeviceList=SerialBT.getScanResults(); int btcCount=btcDeviceList->getCount();
  if (debug) { Serial.println("found " + String(btcCount) + " BTC devices at " + String(millis())); }
  if (debug) { memlog(); }
  for (int j=0;j<btcCount;j++) {
    BTAdvertisedDevice *btcDevice=btcDeviceList->getDevice(j);
    for (int i=0;i<maxBTCDevices;i++) { if (btcDevices[i].address == btcDevice->getAddress().toString()) { btcDevices[i].active=false; } }
    for (int i=0;i<maxBTCDevices;i++) {
      if (!btcDevices[i].active) {
        btcDevices[i].active=true;
        btcDevices[i].name=String(btcDevice->getName().c_str());
        btcDevices[i].address=btcDevice->getAddress().toString();
        btcDevices[i].cod=btcDevice->getCOD();
        btcDevices[i].rssi=btcDevice->getRSSI();
        btcDevices[i].distance=pow(10.0,(-60.0-btcDevice->getRSSI())/30.0);
        btcDevices[i].last=0;
        break; } } } }

void addBLEDevices(BLEScanResults bleDeviceList) {
  for (int i=0;i<maxBLEDevices;i++) {
    if (bleDevices[i].active) { bleDevices[i].last++; if (bleDevices[i].last > btDeviceMaxLast) { bleDevices[i].active=false; } } }
  int bleCount=bleDeviceList.getCount();
  if (debug) { Serial.println("found " + String(bleCount) + " BLE devices at " + String(millis())); }
  if (debug) { memlog(); }
  for (int j=0;j<bleCount;j++) {
    BLEAdvertisedDevice bleDevice=bleDeviceList.getDevice(j);
    for (int i=0;i<maxBLEDevices;i++) { if (bleDevices[i].address == String(bleDevice.getAddress().toString().c_str())) { bleDevices[i].active=false; } }
    for (int i=0;i<maxBLEDevices;i++) {
      if (!bleDevices[i].active) {
        bleDevices[i].active=true;
        bleDevices[i].name=String(bleDevice.getName().c_str());
        bleDevices[i].address=String(bleDevice.getAddress().toString().c_str());
        char *pHex=BLEUtils::buildHexData(nullptr,(uint8_t*)bleDevice.getManufacturerData().c_str(),bleDevice.getManufacturerData().length());
        bleDevices[i].mid=String(pHex).substring(0,4); free(pHex);
        bleDevices[i].appearance=bleDevice.getAppearance();
        int txpower=bleDevice.getTXPower(); bleDevices[i].txpower=txpower;
        int rssi=bleDevice.getRSSI(); bleDevices[i].rssi=rssi;
        if (txpower) { rssi-=txpower-10; }
        bleDevices[i].distance=pow(10.0,(-60.0-rssi)/30.0);
        bleDevices[i].last=0;
        break; } } } }

void doBTScanAsync() {
  static uint64_t btcScanTimer=10000; static uint64_t bleScanTimer=0;

  if (millis()>=btcScanTimer) {
    btcScanTimer=millis()+((btScanDuration+btScanIdleTime)*1000);
    bleScanTimer=millis()+(btScanDuration*500);
    addBTCDevices(); SerialBT.discoverAsync(nullptr,btScanDuration*1000); }

  if (bleScanTimer && millis()>=bleScanTimer) {
    bleScanTimer=0;
    pBLEScan->start(btScanDuration,addBLEDevices,false); } }

void initBTScan() {
  SerialBT.begin("ESP32 BTC Proximity");

  BLEDevice::init("ESP32 BLE Proximity");
  pBLEScan=BLEDevice::getScan();
  pBLEScan->setActiveScan(true);
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99); }

void btScanWorker() { doBTScanAsync(); }
