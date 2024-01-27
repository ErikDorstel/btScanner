void memlog() {
  Serial.print("Heap: " + String(ESP.getHeapSize()));
  Serial.print(" Free: " + String(ESP.getFreeHeap()));
  Serial.print(" Min: " + String(ESP.getMinFreeHeap()));
  Serial.println(" Max: " + String(ESP.getMaxAllocHeap()));
  if (ESP.getPsramSize()) {
    Serial.print("RAM: " + String(ESP.getPsramSize()));
    Serial.print(" Free: " + String(ESP.getFreePsram()));
    Serial.print(" Min: " + String(ESP.getMinFreePsram()));
    Serial.println(" Max: " + String(ESP.getMaxAllocPsram())); } }
