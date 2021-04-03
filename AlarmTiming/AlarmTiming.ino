#include "DSRTC.h"

Set_LCD LCD(1,2,4,5,6,7);

void setup() {
   Set_LCD LCD(1,2,4,5,6,7);
  //LCD.DISP(1);
}

void loop() {
  LCD.DISP(1);
  LCD.DISP(2);
  delay(1000);
  LCD.clear_all();
  delay(1000);
  
  for(int i=0;i<10;i++){
    LCD.set_pos(1,2);
    LCD.DISP("Saliya");
    delay(100);
    LCD.clear_all();
    delay(100);
    }
    
  LCD.clear_all();
  delay(1000);

}
