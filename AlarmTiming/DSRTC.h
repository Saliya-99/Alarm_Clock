#include <Wire.h>
#include<LiquidCrystal.h>
LiquidCrystal *object;

class Set_LCD{
  private:
  int RS;
  int E;
  int pin_1;
  int pin_2;
  int pin_3;
  int pin_4;
  int check=0;
  
  public:
    Set_LCD(int RS_pin, int enable, int p1, int p2, int p3, int p4){
      RS = RS_pin;
      E = enable;
      pin_1 = p1;
      pin_2 = p2;
      pin_3 = p3;
      pin_4 = p4; 
      
      LiquidCrystal LCD(RS,E,pin_1,pin_2,pin_3,pin_4);
      object = &LCD;
      LCD.begin(16,2);
    }

    void DISP(char word[]){
      
      LiquidCrystal LCD = *object;
      LCD.print(word);
      check += 1;
    }

    void DISP(int value){
      
      LiquidCrystal LCD = *object;
      LCD.print(value);
      check += 1;
    }

    void clear_all(){
      LiquidCrystal LCD = *object;
      LCD.clear();
      
    }
    void set_pos(int col,int row){
      LiquidCrystal LCD = *object;
      LCD.setCursor(col,row);
    
    }
    
};
