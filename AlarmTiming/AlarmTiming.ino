#include "DSRTC.h"

Set_LCD LCD(1, 2, 4, 5, 6, 7);


int mode_status = 0; // variable for set the time 
int alarm_min = 0;   // variables for set the alarm
int alarm_hour = 0;
int alarm_mode = 0;
int alarm_time = 0;
int alarm_stop = 0;

int IsEditingMode = 0;// variable for check the mode


void setup() {
  Set_LCD LCD(1, 2, 4, 5, 6, 7);
  DS3232Begin();
  setTime(12, 3, 3, 3, 13, 3, 21);
  pinMode(8, INPUT); pinMode(9, INPUT); pinMode(10, INPUT); pinMode(11, INPUT);

}

void loop() {

  byte seconds, minutes, hours, dayofweek, day, month, year;
  readTime(&seconds, &minutes, &hours, &dayofweek, &day, &month, &year );

  /////////////////////////////////////////////////////////////
  bool mode = digitalRead(8);               //// button inputs
  bool increment = digitalRead(9);
  bool decrement = digitalRead(10);
  bool set_button = digitalRead(11);
  bool alarm_button = digitalRead(12);
  /////////////////////////////////////////////////////////////
  //add mode button, this button chose the editing variable, minutes,ours or etc.
  ///////////////////////////////////////////////////////////////
  if (alarm_button == 1){
    alarm_mode = 1;
    alarm_stop = 1;
    }
  if (alarm_mode == 1){
    
    LCD.clear_all();
    alarm_disp(LCD,alarm_min,alarm_hour);

    if (mode==HIGH){
      alarm_time = not alarm_time;
    }

    if (increment == HIGH){
      if (alarm_time == 0){
        alarm_min += 1;
        if (alarm_min >59){
          alarm_min = 0;
        }
      }
      if (alarm_time==1){
        alarm_hour +=1;
        if (alarm_hour >23){
          alarm_hour = 0;
        }
      }
    }
    if (set_button == 1 and alarm_stop == 1){
      alarm_mode = 0;
      alarm_stop = 0;
    }
    delay(600);
  }
  //////////////////////////////////////////////////////////////////////
  else{
  if (alarm_min == minutes and alarm_hour == hours){
    digitalWrite(13,HIGH);delay(100);digitalWrite(13,LOW);delay(100);
  }
  if (alarm_button == 1){
    digitalWrite(13,LOW);
  }
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
      if (day > 31) {
        day = 1;
      }

      dayofweek +=1;
      if(dayofweek>6){
        dayofweek = 0;
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
        day = 31;
      }

      dayofweek +=1;
      if(dayofweek>6){
        dayofweek = 0;
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
  }
