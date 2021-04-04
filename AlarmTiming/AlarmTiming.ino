#include "DSRTC.h"

Set_LCD LCD(1, 2, 4, 5, 6, 7);


int mode_status = 0;
int inc_min = 0;
int inc_hours = 0;
int inc_days = 0;
int inc_months = 0;
int inc_years = 0;
int IsEditingMode = 0;


void setup() {
  Set_LCD LCD(1, 2, 4, 5, 6, 7);
  DS3232Begin();
  setTime(12, 10, 16, 3, 13, 3, 21);
  pinMode(8, INPUT); pinMode(9, INPUT); pinMode(10, INPUT); pinMode(11, INPUT);

}

void loop() {

  byte seconds, minutes, hours, dayofweek, day, month, year;
  readTime(&seconds, &minutes, &hours, &dayofweek, &day, &month, &year );

  /////////////////////////////////////////////////////////////
  bool mode = digitalRead(8);
  bool increment = digitalRead(9);
  bool decrement = digitalRead(10);
  bool set_button = digitalRead(11);
  /////////////////////////////////////////////////////////////
  //add mode button, this button chose the editing variable, minutes,ours or etc.
  if (mode == HIGH) {
    IsEditingMode = 1;
    if (mode_status == 5) {
      mode_status = 0;
    }
    mode_status += 1;// selected minute or hours
  }

  //add increment button
  if (increment == HIGH) {
    if (mode_status == 1) {

      minutes += 1;
      if (minutes >= 60) {
        minutes = 0;
      }
    }
    if (mode_status == 2) {

      hours += 1;
      if (hours >= 24) {
        hours = 0;
      }
    }
    if (mode_status == 3) {

      day += 1;
      if (day > 30) {
        day = 1;
      }
    }

    if (mode_status == 4) {

      month += 1;
      if (month > 12) {
        month = 1;
      }
    }

    if (mode_status == 5) {
      year += 1;
    }
  
  DisplayTimeBlink(LCD, seconds, minutes, hours, dayofweek, day, month, year );
  setTime(seconds, minutes, hours, dayofweek, day, month, year);
  }

  //add decrement button

  if (decrement == HIGH) {
    if (mode_status == 1) {

      minutes -= 1;
      if (minutes < 0) {
        minutes = 59;
      }
    }
    if (mode_status == 2) {

      hours -= 1;
      if (hours < 0) {
        hours = 23;
      }
    }
    if (mode_status == 3) {

      day -= 1;
      if (day < 1) {
        day = 30;
      }
    }

    if (mode_status == 4) {

      month -= 1;
      if (month < 1) {
        month = 12;
      }
    }

    if (mode_status == 5) {
      year += 1;
    }
  DisplayTimeBlink(LCD, seconds, minutes, hours, dayofweek, day, month, year );
  setTime(seconds, minutes, hours, dayofweek, day, month, year);
  }

  //set the new time in normal mode
  if (set_button == HIGH) {
    setTime(00, minutes, hours, dayofweek, day, month, year);

    IsEditingMode = 0;
    readTime(&seconds, &minutes, &hours, &dayofweek, &day, &month, &year );

  }

  if (IsEditingMode == 0) {
    DisplayTime(LCD, seconds, minutes, hours, dayofweek, day, month, year);
  }

  else {
    DisplayTimeBlink(LCD, seconds, minutes, hours, dayofweek, day, month, year );
  }
  }
