#include "hd44780_driver.h"
#include "LCD.h"
#include "enc.h"
#include "stepmotor.h"

unsigned char Char_0[] =  {4,6,4,6,4,14,14,4};     // t
unsigned char Char_1[] =  {24,24,0,28,16,16,28,0}; // degree C
unsigned char Char_2[] = {0,14,21,21,0,14,21,21};  //mm
unsigned char Char_3[] = {20,28,20,20,3,5,3,6};    //Hg
unsigned char Char_4[] = {28,20,28,28,28,28,8,28}; // press
unsigned char Char_5[] ={4,4,14,31,31,31,14,0};    //moisture
unsigned char Char_6[] ={18,4,18,8,18,0,30,12};    //moisture V2

unsigned char DispString[17]={0};
int32_t temperature=0;
int32_t pressure=0;
         
void ConfigureLCD(void){
lcd_init(); //Display Init
lcd_set_user_char(0, Char_0); // Set char
lcd_set_user_char(1, Char_1); // Set char
lcd_set_user_char(2, Char_2); // Set char
lcd_set_user_char(3, Char_3); // Set char
lcd_set_user_char(4, Char_4); // Set char
lcd_set_user_char(5, Char_5); // Set char
lcd_set_user_char(6, Char_6); // Set char

lcd_clear(); // clear LCD
}

unsigned char* DisplayTemperature(int16_t Temperature){
unsigned char* pointerDisp = DispString;
 //temperature = bmp085_read_temperature();
 temperature = Temperature;

 DispString[0] = temperature/1000 + 0x30;
 DispString[1] = (temperature%1000)/100 + 0x30;
 DispString[2] = (temperature%100)/10 + 0x30;
 DispString[3] = 0x2E; //point
 DispString[4] = temperature%10 + 0x30;
 DispString[5] = 0x01; //degree
 if (*DispString == 0x30){ 
 pointerDisp++;
  
  DispString[6] = 0x20;
  DispString[7] = 0x00;
  
  if (DispString[1] == 0x30)
  {
    DispString[7] = 0x20;
    pointerDisp++;
    DispString[8] = 0x00;
  }
  
 }  
 else{
 DispString[5] = 0x00; 
 }

 if(temperature < 0){ 
   if(pointerDisp > DispString)pointerDisp--;
   *pointerDisp = 0x2D;
 }
    
 lcd_out(pointerDisp);

return pointerDisp;
}

void DisplayPressure(float Pressure){
 static unsigned char* pointerDisp = DispString;
 uint16_t PresInt = (uint16_t)(Pressure * 100.0); 
 
 DispString[0] = PresInt/10000 + 0x30;
 DispString[1] = (PresInt%10000)/1000 + 0x30;
 DispString[2] = (PresInt%1000)/100 + 0x30;
 DispString[3] = 0x2E; //point
 DispString[4] = (PresInt%100)/10 + 0x30;
 DispString[5] = PresInt%10 + 0x30;
 DispString[6] = 0x02; //degree
 DispString[7] = 0x03; //degree
 DispString[8] = 0x00; 
 lcd_out(pointerDisp);
 
return;
}

void DisplaySteps(void){
 lcd_set_xy(0,0);
 lcd_out("Stp+:");
 lcd_set_xy(0,1);
 lcd_out("Stp-:");
 lcd_set_xy(5,0);
 UInt32ToStr(DispString, StepsUp);
 lcd_out(DispString);
 lcd_set_xy(5,1);
 UInt32ToStr(DispString, StepsDown);
 lcd_out(DispString);
return;
};

void DisplayRevolutions(void){
 lcd_set_xy(0,0);
 lcd_out("Rev+:");
 lcd_set_xy(0,1);
 lcd_out("Rev-:");
 lcd_set_xy(5,0);
 UInt32ToStr(DispString, RevUp);
 lcd_out(DispString);
 lcd_set_xy(5,1);
 UInt32ToStr(DispString, RevDown);
 lcd_out(DispString);
return;
};

void UInt32ToStr(unsigned char * DispString, int32_t Numb){
 DispString[0] = (Numb%10000000000)/1000000000 + 0x30;
 DispString[1] = (Numb%1000000000)/100000000 + 0x30;
 DispString[2] = (Numb%100000000)/10000000 + 0x30;
 DispString[3] = (Numb%10000000)/1000000 + 0x30;
 DispString[4] = (Numb%1000000)/100000 + 0x30;
 DispString[5] = (Numb%100000)/10000 + 0x30;
 DispString[6] = (Numb%10000)/1000 + 0x30;
 DispString[7] = (Numb%1000)/100 + 0x30;
 DispString[8] = (Numb%100)/10 + 0x30;
 DispString[9] = Numb%10 + 0x30;
 DispString[10] = 0x00; 
}

void DisplayHumidity(float * Humidity){
unsigned char* pointerDisp = DispString;
static s16 HumI =0;
 HumI = (s16)(*Humidity*10);
 
 DispString[0] = HumI/1000 + 0x30;
 DispString[1] = (HumI%1000)/100 + 0x30;
 DispString[2] = (HumI%100)/10 + 0x30;
 DispString[3] = 0x2E; //point
 DispString[4] = HumI%10 + 0x30;
 DispString[5] = '%'; //degree
 if (*DispString == 0x30){ 
 pointerDisp++;
  
  DispString[6] = 0x20;
  DispString[7] = 0x00;
  
  if (DispString[1] == 0x30)
  {
    DispString[7] = 0x20;
    pointerDisp++;
    DispString[8] = 0x00;
  }
  
 }  
 else{
 DispString[5] = 0x00; 
 }
 
 lcd_out(pointerDisp);
 
return;
}