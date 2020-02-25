#ifndef _LCD_H
#define _LCD_H



extern unsigned char DispString[17];

void ConfigureLCD(void);
void DisplayPressure(float Pressure);
unsigned char* DisplayTemperature(int16_t Pressure);
void DisplayHumidity(float* Humidity);
void DisplaySteps(void);
void DisplayRevolutions(void);
void UInt32ToStr(unsigned char * DispString, int32_t Numb);
#endif