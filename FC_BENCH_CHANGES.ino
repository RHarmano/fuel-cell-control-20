#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
#include <Array.h>

#include "FC_Constants.h"
// Screen must be initialized
LiquidCrystal_I2C lcd(0x27,20,4);           // set the LCD address to 0x27 for a 16 chars and 2 line display
// Struct for array returns
struct Arr2{
  int concat_disp[2][5];
};
#include "LogoC.h"

// System-Wide Flags
boolean fc_on = false;
boolean fc_alarm = false;

// System-Wide Counters
unsigned long Current_Time = 1;             // would overflow after 25 days if left running forever (hopefully)
unsigned long Last_Time = 0;
unsigned long LOOP_TIME = 0;

// Global States
int FC_State = FC_INITIAL;
int FC_SubState = FC_STARTUP_STARTUP_PURGE;
int FAN_State = FAN_MID;                    // First Fan state assumed is MID at startup


// ----------------- SETUP ----------------- //
void setup() {
  // State LEDs
  pinMode(STATE_LED_RED, OUTPUT);
  pinMode(STATE_LED_YELLOW, OUTPUT);
  pinMode(STATE_LED_BLUE, OUTPUT);

  // Purge, supply, FC relay, FC fan relay, and resistor relay.
  pinMode(PURGE_PIN, OUTPUT);
  pinMode(SUPPLY_PIN, OUTPUT);
  pinMode(FC_RELAY_PIN, OUTPUT);
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RESISTOR_PIN, OUTPUT);

  delay(100);
  setAllSafe();
  initializeLCD();
  initializeLogo();
  displayLogo();
  displayTemplate();
  delay(1000);
}

// ----------------- LOOP ----------------- //
void loop() {
  bench_alarm(lcd);
  System();
  FC();

  // keep track of the time between loops
  Last_Time = Current_Time;
  Current_Time = millis();
  LOOP_TIME = Current_Time - Last_Time;
  //pinCheck();
}
