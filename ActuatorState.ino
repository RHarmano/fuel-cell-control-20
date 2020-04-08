// ----------------- CHANGE STATES FOR PURGE, SUPPLY, FAN, RELAY, RESISTOR -----------------
void setPurgeState(int state) {
  // !state means that when you "close" the valve it actually closes (sends 0 instead of 1)
  // and when you set setPurgeState(OPEN) it sends a 1, actually opening the valve
  digitalWrite(PURGE_PIN, !state);
}

void setSupplyState(int state) {
  // !state means that when set setPurgeState(CLOSED) the valve closes (sends 0 instead of 1)
  // and when you set setPurgeState(OPEN) it sends a 1, actually opening the valve
  digitalWrite(SUPPLY_PIN, !state);
}

void setRelayState(int state) {
  digitalWrite(FC_RELAY_PIN, state);
}

void setResistorState(int state) {
  digitalWrite(RESISTOR_PIN, state);
}

void setAllSafe(void) {
  fanControl(FAN_OFF);
  setSupplyState(CLOSED);
  setPurgeState(CLOSED);
  setRelayState(OPEN);
  setResistorState(OPEN);
}
