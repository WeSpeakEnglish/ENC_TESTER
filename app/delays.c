#include "delays.h"
#include "nortos.h"

#define Del40 5750*4
#define Del_ms 145*4

void delay_40ms(void){
  u32 delay=0;
for(delay=Del40;delay;delay--);
  return;
}
void delay_1s(void){
   u32 delay=0;
for(delay=25;delay>0;delay--)delay_40ms(); 
}

void delay_ms(int Ms){
u32 delay=0;
  while(Ms--){
   for(delay=Del_ms;delay;delay--);
  };

}
void delay_times(int times){
  for(;times;times--);
}