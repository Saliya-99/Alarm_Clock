#include "DSRTC.h"

Set_LCD LCD(1, 2, 4, 5, 6, 7);


int mode_status = 0;
int inc_min = 0;
int inc_hours = 0;
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

  if (mode == HIGH) {
    IsEditingMode = 1;
    if (mode_status == 2) {
      mode_status = 0;
    }
    mode_status += 1;// selected minute or hours

 /*  if (mode_status == 1) {
      LCD.clear_all();
      while (1) {
        LCD.DISP("MIN: "); LCD.DISP(minutes+inc_min);delay(1000); LCD.clear_all(); delay(1000);
        if (mode or set_button){
          break;
        }
      }
      

  }

  if (mode_status == 2) {
      LCD.clear_all();
      while (1) {
        LCD.DISP("HOURS:"); LCD.DISP(hours+inc_hours);delay(100); LCD.clear_all(); delay(100);
        if (mode or set_button){
          break;
        }
      }
    }*/
  
  }
  if (increment == HIGH) {
    if (mode_status == 1) {
      inc_min += 1;
    }
    if (mode_status == 2) {
      inc_hours += 1;
    }
    DisplayTimeBlink(LCD, seconds, minutes+inc_min, hours+inc_hours, dayofweek, day, month, year );
  }
  
  if (set_button == HIGH) {
    setTime(00, minutes + inc_min, hours + inc_hours, 0, 13, 3, 21);
    inc_min = 0;
    inc_hours = 0;
    IsEditingMode = 0;
  }

  if(IsEditingMode ==0){
  DisplayTime(LCD, seconds, minutes+inc_hours, hours+inc_hours, dayofweek, day, month, year );}
  
  else{
    DisplayTimeBlink(LCD, seconds, minutes+inc_min, hours+inc_hours, dayofweek, day, month, year );
  }



  /////////////////////////////////////////////////////////




}
