#include "timers.h"
#include "LCD.h"
#include "hd44780_driver.h"
#include "uart.h"
#include "enc.h"
#include "nortos.h"
//////////////////////////////////////////////
u16 Hum;
u16 Temp;
u8 Crc;

float CalculatedHum;
float CalculatedTemp;
enum{TEMP=1,HUM};
extern uint8_t Direction;
//////////////////////////////////////////////////
void TIM1_init(void){

}

void TIM2_init(void)
{
  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;   //��������� ������ �������� ��������� �� TIM2
  TIM2->CNT = 0;
  TIM2->SR = 0;
  TIM2->CR2=0x0;          //�������� �������
  TIM2->CR1=0x0;          //�������� �������
  
  TIM2->PSC = 124;          // ������������ ������� 2
  TIM2->ARR = 4;      //
  
  TIM2->CR1 &= ~TIM_CR1_DIR;      //������ ���� - 0 (�������� - 1) ������
  TIM2->CR1 &= ~TIM_CR1_UDIS;      //����.-1; ��������� ������� �� �������.������� -0
  TIM2->CR1 &= ~TIM_CR1_CKD;      //clock division
  TIM2->CR1 &= ~TIM_CR1_ARPE;      //��������� 0 - ����� �������� �� ���� ������ �������� ARR;���������=1 �����������
  TIM2->CR1 &= ~TIM_CR1_OPM;      //��������� ������ � ������ ���������� ��������
  TIM2->DIER |= TIM_DIER_UIE;      //&UPDATE INTERRPUT - ���������� �� ������������ &&&
  
  TIM2->CR1 |= TIM_CR1_URS;
  TIM2->EGR &= ~TIM_EGR_UG;      // ���������� 0 ;update enable  ARR � ��������� �������� �� ���������������� � ������� �������
  TIM2->CR1 |= TIM_CR1_CEN;       //��������� ������2
  NVIC_EnableIRQ (TIM2_IRQn);    //��������� ����������
  
}

void TIM3_init(void) // make delays 
{
TIM_Cmd(TIM3, DISABLE);
  
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
  NVIC_InitTypeDef NVIC_InitStructure;
  
  
  RCC_APB2PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);


  TIM_TimeBaseInitStruct.TIM_Period = 65535;//encoderStepsPerRevolution - 1;
  TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Down | TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);

  TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);

//  TIM_ClearFlag(TIM3,TIM_FLAG_Update);
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
 // TIM_TimeBaseInitStruct. = 32768;
  TIM_Cmd(TIM3, ENABLE);
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  NVIC_EnableIRQ(TIM3_IRQn);
}

void TIM2_IRQHandler(void)
{
  static long long InsideCounter = 0;
  static uint8_t screen = 0;
  if (TIM2->SR & TIM_SR_UIF){
    TIM2->SR &= ~TIM_SR_UIF;        // ������� ���� ���������� 
  }
  
  if(InsideCounter%2){
    GPIOA->BSRR = GPIO_BSRR_BS8;
  }
  else {
    GPIOA->BSRR = GPIO_BSRR_BR8;
  }
  if(InsideCounter%12800 == 0){
    Direction++;
    Direction %=2;
    if(Direction){
      GPIOA->BSRR = GPIO_BSRR_BR15;
      F1_push(RevDecrease);
    }
    else{ 
      GPIOA->BSRR = GPIO_BSRR_BS15;
      F1_push(RevIncrease);
    }
    screen++;
    screen %=2;
    if(screen) F1_push(DisplaySteps);
    else F1_push(DisplayRevolutions);
  }
  
  InsideCounter++;
}

void TIM3_IRQHandler(void)
{
  static long long InsideCounter = 0;
  if (TIM3->SR & TIM_SR_UIF){
    TIM3->SR &= ~TIM_SR_UIF;        // ������� ���� ���������� 
  }
  
  
  InsideCounter++;
}
