// FC States
#define FC_INITIAL 0
#define FC_STANDBY 1
#define FC_STARTUP 2
#define FC_RUN 3
#define FC_ALARM 4
#define FC_SHUTDOWN 5

// FC Startup Substates
#define FC_STARTUP_FAN_SPOOLUP 6
#define FC_STARTUP_STARTUP_PURGE 7
#define FC_STARTUP_END 8

// Analog Pins
//SENSOR PROXY BOARD
#define CURRENT_PIN 0             //Max expected at 2.5V
#define STACK_THEMRMISTOR_PIN 1 
#define AMB_THEMRMISTOR_PIN 2
#define VOLTAGE_PIN 3             //Expected input 1.7V
#define HYDROGEN_PIN 4

// Digital Pins (finalized for the current configuration)
//VALVE AND CONTACTOR RELAY BANK
#define PURGE_PIN 5 
#define SUPPLY_PIN 6
#define FC_RELAY_PIN 7
#define RESISTOR_PIN 8
//FAN RELAY BANK(Relay3 has lowest resistance)
#define RELAY1 11  
#define RELAY2 10
#define RELAY3 9
//ON BTN
#define SYSTEM_ON_PIN 12
//LED READOUT Changed
#define STATE_LED_RED 4
#define STATE_LED_BLUE 3
#define STATE_LED_YELLOW 2

#define LED_ON 1023
 
// Valve, Relay States
#define OPEN 0
#define CLOSED 1

// Sensor Alarm Thresholds
#define FC_MIN_CURRENT          0   // A
#define FC_MAX_CURRENT          75  // A

#define FC_RUN_MIN_VOLTAGE      0  // V
#define FC_MAX_VOLTAGE          28  // V
#define FC_MAX_H2_READ          10  // ppm
#define FC_RUN_MIN_TEMP         0   // deg C 
#define FC_MIN_TEMP             15  // deg C 
#define FC_MAX_TEMP             75  // deg C
#define HYDROGEN_MAX            4.5 // ppm

// Constant System Parameters
#define PURGE_INTERVAL  2300.0 // A*s
#define PURGE_DURATION  300 // TODO: 300ms 

// Fan Speeds  
#define FAN_MAX       5
#define FAN_MID_HIGH  4
#define FAN_MID       3
#define FAN_MID_LOW   2
#define FAN_MIN       1
#define FAN_OFF       0

// Program constants (determined via testing)
#define STARTUP_PURGE_TIME 		 200 // ms
#define STANDBY_DELAY_TIME       3000 // ms
#define SHUTDOWN_DELAY_TIME      180000 // ms //3 minutes 3*60*1000

//gain value(Current Sens)
#define G 22.0605 // AnalogIn=9.2745 Current+1.2991 -> Max Amps reading at 1023= 110.3A -> 110.3/5=22.06
//Hydrogen Const
#define H_CONST 1.5 // Data sheet shows a linear relation. Set to one for now

// Thermistor Curve Coefficients For Steinhart-Hart.
#define A_TEMP 0.000757     // 0.0052
#define B_TEMP 0.000274     // -1.0979
#define C_TEMP 0.000000127  // 81.298
#define THERM_V_IN 6.0
#define R2   10000 //Originally 60
