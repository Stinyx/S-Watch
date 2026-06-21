#pragma once

#pragma once

// Watch state enum with all the possible states (state machine)
enum WatchState {
  NTPSYNCING,
  CLOCK,
  SETTINGS,
  IMAGE,
  NAVIGATION,
  TIMER,
  ALARM,
  ABOUT,
};

// global state variables
extern WatchState currentState;
extern WatchState lastState;
extern int state;

// If watchstate changes, do something only once
void onStateEnter(WatchState state);

void set_current_state(WatchState newState);