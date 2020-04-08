int fanCount = 0; // modulo-2000 -- counter for how often to update fan speed

// ----------------- FAN CONTROL -----------------
void AutomaticFanControl(int current, int temp_average) {
  int temp_opt = 0.53 * current + 26.01;
  int temp_max = 0.3442 * current + 52.143;
  int temp_min = 0.531 * current + 6.0025;

  fanCount = fanCount % 1000;
  if (fanCount == 0) {
    if (temp_average >= temp_opt - 874 && temp_average <= temp_opt + 4 ) { // Perfect temp //MID
      fanControl(FAN_MID);
    } else if (temp_average >= temp_max || temp_average > 73) { //MAX
      fanControl(FAN_MAX);
    } else if (temp_average > temp_opt && temp_average <= temp_max - 2) {//MID_HIGH
      fanControl(FAN_MID_HIGH);
    } else if (temp_average <= temp_opt && temp_average >= temp_min + 2) { // Kinda cold.//MID_LOW
      fanControl(FAN_MID_LOW);
    } else if (temp_average < temp_min + 2) { // Too cold. //MIN
      fanControl(FAN_MIN);
    } else {
      fanControl(FAN_MAX);//If something is wrong and we get through all the cases FAN to MAX
    }
  }
  fanCount++;
}

void fanControl(int FAN_SPEED) {
  switch (FAN_SPEED) {
    case FAN_MAX: //STACK IS HOT
      fanRelayControl(HIGH , HIGH, HIGH); //12.?
      break;
    case FAN_MID_HIGH:
      fanRelayControl(LOW, LOW, HIGH); //10.3
      break;
    case FAN_MID:
       fanRelayControl(HIGH, HIGH, LOW); //3.7
      break;
    case FAN_MID_LOW:
      fanRelayControl(LOW, HIGH, LOW); //2.7
      break;
    case FAN_MIN: //STACK IS COLD
      fanRelayControl(LOW, HIGH, LOW); //2.7
      break;
    case FAN_OFF:
      fanRelayControl(LOW,  LOW,  LOW); //0
      break;
  }
}

void fanRelayControl(boolean relayOneState, boolean relayTwoState, boolean relayThreeState) {
  digitalWrite(RELAY1, relayOneState);
  digitalWrite(RELAY2, relayTwoState);
  digitalWrite(RELAY3, relayThreeState);
}
