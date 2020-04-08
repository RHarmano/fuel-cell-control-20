// Flags
boolean standby_timer_set = false;
boolean fc_fan_time_set = false;
boolean timer_time_set = false;

// Counters
unsigned long startup_purge_counter = 0; // Counter for how long the purge valve has been open for
unsigned long timer_start_time = 0;     // Counter for how long to stay in FC_STANDBY
int count = 0;                  // modulo-1000 -- counter for how long to stay in FC_INITIAL

// ----------------- FC STATE FUNCTIONS ----------------- //
void FCInitial() {
  if (Current_Time > 3000) // A timer to determine how long to be in this state.
    stateTransition(FC_INITIAL, FC_STANDBY);
}

void FCStandby() {
  // The stack is not consuming reactant or delivering power and all stack BOP actuators are in their safe state
  // The system remains in FC_STANDBY for STANDBY_DELAY_TIME

  if (!standby_timer_set) {
    timer_start_time = Current_Time;
    standby_timer_set = true;
  }
  
  //Default State
  fanControl(FAN_OFF);    //Fan speed
  setAllSafe();

  if (STANDBY_DELAY_TIME <= Current_Time - timer_start_time && fc_on) {
    standby_timer_set = false;
    stateTransition(FC_STANDBY, FC_STARTUP);
  }
}

void FCStartup() {
  // The stack goes from FC_STANDBY to a state where current can
  // safely be drawn from the stack
  
  switch (FC_SubState) {
    case (FC_STARTUP_STARTUP_PURGE):
      FCStartup_StartupPurge();
      break;

    case (FC_STARTUP_END):
      FCStartup_StartupEnd();
      break;
  }
}

void FCStartup_StartupPurge() {
  
  // for the start-up purge and the start-up resistor is applied**Resistor Control is nonexistant in test_bench**
  // across the stack to limit voltage
  setSupplyState(OPEN);// purge valve and supply valves are opened simultaneously
  setPurgeState(OPEN);
  setRelayState(CLOSED); // Open the state relay. 
  //setResistorState(CLOSED); // Close the resistor relay as we have reached a stage where we no longer need the start up resistor.
 
  
  if (!fc_fan_time_set) { // Timer Reused for PURGE
    startup_purge_counter = Current_Time;
    fc_fan_time_set = true;
  }

  if (STARTUP_PURGE_TIME <= Current_Time - startup_purge_counter) {
    fc_fan_time_set = false;
    subStateTransition(FC_SubState, FC_STARTUP_END);
    return;
  }
}

void FCStartup_StartupEnd() {
  setPurgeState(CLOSED);// close purge valve
  setSupplyState(CLOSED);// fan is minimum

  fc_fan_time_set = false;
  startup_purge_counter = 1;
  stateTransition(FC_State, FC_RUN);
  subStateTransition(FC_SubState, FC_STARTUP_STARTUP_PURGE); // switch back to startup purge

  //setResistorState(OPEN); // Open the resistor relay as we have reached a stage where we no longer need the start up resistor.
  setRelayState(CLOSED); // Close the system relay, start the damn thing.

  fanControl(FAN_MID_LOW);
}

void FCRun() {
  digitalWrite(STATE_LED_YELLOW,HIGH);
  setSupplyState(OPEN); // The supply value should always be open.
  setRelayState(CLOSED);
  AutomaticPurgeControl();
  AutomaticFanControl(fc_current, stack_temp); // fc_current, stack_temp are used and modified in CheckAlarms.ino

//  if (!fc_on)
//    stateTransition(FC_RUN, FC_SHUTDOWN);
}

void FCShutdown() {
  // The stack goes from FC_RUN to FC_STANDBY. The system remains in
  // FC_SHUTDOWN for SHUTDOWN_DELAY_TIME
  fanControl(FAN_MID_HIGH);
  digitalWrite(STATE_LED_BLUE,HIGH);

  if (!timer_time_set) {
    timer_start_time = Current_Time;
    timer_time_set = true;
  }
  
  //Set all Safe includes FAN_OFF this will which turns the fan off. We need it on here hence the new function
  //setAllSafeButFan
  setSupplyState(CLOSED);
  setPurgeState(CLOSED);
  setRelayState(OPEN);
  setResistorState(OPEN);

//3 minutes or 20 or ambient
  if ((SHUTDOWN_DELAY_TIME <= Current_Time - timer_start_time)|| stack_temp <= amb_temp || stack_temp <= 20) {
    fanControl(FAN_OFF);
    timer_time_set = false;
    stateTransition(FC_SHUTDOWN, FC_STANDBY);
  }
}

void FCAlarm() {
  // The stack is shut down because an alarm was triggered.
  // All actuators are in their safe states
  setAllSafe();
  digitalWrite(STATE_LED_RED,HIGH);
}

// ----------------- STATE TRANSITION & SUBSTATE TRANSITION -----------------
void stateTransition(int fromState, int toState) {
  FC_State = toState;
}

void subStateTransition(int fromState, int toState) {
  FC_SubState = toState;
}

void pinCheck(void){
  for(int i=2;i<=11;i++){
    digitalWrite(i,HIGH);
    delay(1000);
    for(int j=2;j<=11;j++){
      digitalWrite(j,LOW);
    }
  }
  delay(5000);
}
