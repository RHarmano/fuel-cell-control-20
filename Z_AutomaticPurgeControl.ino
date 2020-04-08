// Z_ in file name due to an error with global variables due to the order of files compiled
#define RESET_TIME 3000 // ms (3s)

unsigned long purgeLastCallTime = 0;  // AKA LastCallTime
double AmpSecSincePurge = 0;
long PurgeOpenCounter = 0;
boolean purgeIsOpen = false;

// ----------------- PURGE CONTROL -----------------
void AutomaticPurgeControl() {
  // If function hasn’t been called in RESET_TIME, Reset Local Static Variables
  // This happens if we transition into this state a while after starting
  // or leave the run state and then re-enter it later.
  if (Current_Time - purgeLastCallTime >= RESET_TIME) {
    AmpSecSincePurge = 0;
    PurgeOpenCounter = 0;
  }
  purgeLastCallTime = Current_Time;

  // If Purge Valve is open, reset the counter.
  // If the Purge Valve is closed, add A*s to the AmpSecSincePurge counter.
  if (purgeIsOpen) {
    AmpSecSincePurge = 0;
  } else {
    AmpSecSincePurge += fc_current * LOOP_TIME/1000; //Loop time is in milliseconds. //Purge Duration in AmpSecs
  }

  // If PURGE_INTERVAL is exceeded, open the Purge Valve and set the counter
  // to keep it open for the number of loops
  if (AmpSecSincePurge > PURGE_INTERVAL) { 
    setPurgeState(OPEN);
    purgeIsOpen = true;
    PurgeOpenCounter = PURGE_DURATION;
  } else {
    // If the counter is greater than 0 (i.e. we have not yet waited PURGE_DURATION),
    // keep the Purge Valve open and decrement the counter.
    // Once the counter is 0 or goes negative, close the purge valve.
    if (PurgeOpenCounter > 0) {
      setPurgeState(OPEN);
      purgeIsOpen = true;
      PurgeOpenCounter -= LOOP_TIME;
    } else {
      // Done purging
      setPurgeState(CLOSED);
      purgeIsOpen = false;
    }
  }
}
