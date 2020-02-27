#include "timers.h"
#include "LCD.h"
#include "hd44780_driver.h"
#include "uart.h"
#include "enc.h"
#include "nortos.h"

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

void TIM3_init(void)
{
  RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;   //��������� ������ �������� ��������� �� TIM2
  TIM3->CNT = 0;
  TIM3->SR = 0;
  TIM3->CR2=0x0;          //�������� �������
  TIM3->CR1=0x0;          //�������� �������
  
  TIM3->PSC = 79;          // ������������ ������� 3
  TIM3->ARR = 99;      //
  
  TIM3->CR1 &= ~TIM_CR1_DIR;      //������ ���� - 0 (�������� - 1) ������
  TIM3->CR1 &= ~TIM_CR1_UDIS;      //����.-1; ��������� ������� �� �������.������� -0
  TIM3->CR1 &= ~TIM_CR1_CKD;      //clock division
  TIM3->CR1 &= ~TIM_CR1_ARPE;      //��������� 0 - ����� �������� �� ���� ������ �������� ARR;���������=1 �����������
  TIM3->CR1 &= ~TIM_CR1_OPM;      //��������� ������ � ������ ���������� ��������
  TIM3->DIER |= TIM_DIER_UIE;      //&UPDATE INTERRPUT - ���������� �� ������������ &&&
  
  TIM3->CR1 |= TIM_CR1_URS;
  TIM3->EGR &= ~TIM_EGR_UG;      // ���������� 0 ;update enable  ARR � ��������� �������� �� ���������������� � ������� �������
  TIM3->CR1 |= TIM_CR1_CEN;       //��������� ������ 3
  NVIC_EnableIRQ (TIM3_IRQn);    //��������� ����������
}

