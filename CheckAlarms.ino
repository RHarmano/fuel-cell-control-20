/*
 * Must include DisplayDataC.h for LCD screen update
 */
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//---------------------------------------------------------DISPLAY VARIABLES
int disp0_values[5];     //voltage, current, power
int disp1_values[5];     //amb temp., fc temp., hydrogen
int disp2_values[4];   //speed, distance, time

//---------------------------------------------------------INCLUDE EXTERNAL FUNCTION FILES
//#include "LogoC.h"

// Index Counter
int arrayIndex = 0; // modulo-100  -- counter for averaging sensor value arrays

// Flags
boolean arrays_filled = false;

// Averaged values
double amb_temp;
double stack_temp;
double fc_current;
double fc_voltage;
double amb_hydrogen;
double tempInput;

// Sensor Arrays
#define ARRAY_SIZE 100
unsigned short stackTempArray[ARRAY_SIZE];
unsigned short stackCurrentArray[ARRAY_SIZE];
unsigned short stackVoltageArray[ARRAY_SIZE];
unsigned short ambientTempArray[ARRAY_SIZE];
unsigned short hydrogenArray[ARRAY_SIZE];

void all_off() {
  for(int pin = STATE_LED_RED; pin < STATE_LED_YELLOW; pin++) {
    digitalWrite(pin, LOW);
  }
}

void bench_alarm(LiquidCrystal_I2C lcd){
  // Check all alarm properties to make sure they're within the safe range
  // If not, set fc_alarm to true.
  // Current, Voltage, Hydrogen and Temperature (Stack and Ambient) are checked

  // Take measurements
  ambientTempArray[arrayIndex]  = analogRead(AMB_THEMRMISTOR_PIN);
  stackTempArray[arrayIndex]    = analogRead(STACK_THEMRMISTOR_PIN);
  stackVoltageArray[arrayIndex] = analogRead(VOLTAGE_PIN);
  stackCurrentArray[arrayIndex] = analogRead(CURRENT_PIN);
  hydrogenArray[arrayIndex]     = analogRead(HYDROGEN_PIN);

  arrayIndex++;
  if (arrayIndex == ARRAY_SIZE) {
    arrays_filled = true;
    arrayIndex = 0;
  }

  // if the arrays have not yet been filled keep taking measurements or their averages will be incorrect
  if (!arrays_filled)
    return;

  unsigned long amb_temp_total     = 0;
  unsigned long stack_temp_total   = 0;
  unsigned long fc_voltage_total   = 0;
  unsigned long fc_current_total   = 0;
  unsigned long amb_hydrogen_total = 0;

  for (int i = 0; i < ARRAY_SIZE; i++) {
    amb_temp_total     += ambientTempArray[i];
    stack_temp_total   += stackTempArray[i];
    fc_voltage_total   += stackVoltageArray[i];
    fc_current_total   += stackCurrentArray[i];
    amb_hydrogen_total += hydrogenArray[i];
  }

  // Uses the average sensor value to determine the actual values for ambient temp, stack temp, etc.
  amb_temp     = TemperatureComputation(amb_temp_total / ARRAY_SIZE);
  stack_temp   = TemperatureComputation(stack_temp_total / ARRAY_SIZE);
  fc_voltage   = voltageComputation(fc_voltage_total / ARRAY_SIZE);
  fc_current   = currentComputation(fc_current_total / ARRAY_SIZE);
  amb_hydrogen = hydrogenComputation(amb_hydrogen_total / ARRAY_SIZE);

  /*
   *  CALL void prep_data(int voltage_in, int current_in, int amb_temp_in, int fc_temp_in, int hydrogen_in)
   *  to assert changes to the monitor
   */
  Arr2 a = prep_data(fc_voltage, fc_current, amb_temp, stack_temp, amb_hydrogen);
  displayRefresh(lcd, a);
  
  //Always checking for hydrogen leaking, regardless of state
  if (amb_hydrogen > HYDROGEN_MAX){
      fc_alarm = true;
      digitalWrite(STATE_LED_RED, HIGH);  
      delay(250);
      digitalWrite(STATE_LED_RED, LOW);
  }
  if (fc_current < FC_MIN_CURRENT || fc_current > FC_MAX_CURRENT) {
    fc_alarm = true;
    digitalWrite(STATE_LED_BLUE, HIGH);
    delay(250);
    digitalWrite(STATE_LED_BLUE, LOW);
  }
  if (FC_State == FC_RUN) {
//    if (fc_voltage < FC_RUN_MIN_VOLTAGE || fc_voltage > FC_MAX_VOLTAGE ) {//
//      fc_alarm = true;
//      digitalWrite(STATE_LED_RED, HIGH);  
//      delay(250);
//      digitalWrite(STATE_LED_RED, LOW);
//    }
    if (amb_temp < FC_RUN_MIN_TEMP || amb_temp > FC_MAX_TEMP) {
      fc_alarm = true;
      digitalWrite(STATE_LED_YELLOW, HIGH);
      delay(250);
      digitalWrite(STATE_LED_YELLOW, LOW);
    }
    if (stack_temp < FC_RUN_MIN_TEMP || stack_temp > FC_MAX_TEMP) {
      fc_alarm = true;
      digitalWrite(STATE_LED_YELLOW, HIGH);
      delay(250);
      digitalWrite(STATE_LED_YELLOW, LOW);
    }
  }
  else {
    if (amb_temp < FC_MIN_TEMP || amb_temp > FC_MAX_TEMP) {
      fc_alarm = true;
      digitalWrite(STATE_LED_YELLOW, HIGH);
      delay(250);
      digitalWrite(STATE_LED_YELLOW, LOW);
    }
    if (stack_temp < FC_MIN_TEMP || stack_temp > FC_MAX_TEMP) {
      fc_alarm = true;
      digitalWrite(STATE_LED_YELLOW, HIGH);
      delay(250);
      digitalWrite(STATE_LED_YELLOW, LOW);
    }
  }
}
