

void TestEnTurn(void){
  
static u16 TimerEN = 32768; // edge touch screen;
static u16 TimerState = 0;


TimerState =  TIM1->CNT;

if(TimerState > TimerEN +8){
  EncTurnedDown = 1;
  TIM1->CNT = 32768;
}  
if(TimerState < TimerEN -8){
  EncTurnedUp = 1;
  TIM1->CNT = 32768;
} 