// For all state function declarations see StateFuncs

// ----------------- FC -----------------
void FC() {
  if (fc_alarm)
    stateTransition(FC_State, FC_ALARM);

  // Finite State Machine Starts Here
  switch (FC_State) {
    case (FC_INITIAL):
      FCInitial();
      break;

    case (FC_STANDBY):
      FCStandby();
      break;

    case (FC_STARTUP):
      FCStartup();
      break;

    case (FC_RUN):
      FCRun();
      break;

    case (FC_SHUTDOWN):
      FCShutdown();
      break;

    case (FC_ALARM):
      FCAlarm();
      break;

    default:
      fc_alarm = true; //If we somehow enter an invalid state something is wrong so we should transfer to the FC_Alarm
      break;
  }
}
