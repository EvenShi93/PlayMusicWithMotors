/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Template/stm32f4xx_it.c
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    13-April-2012
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "stm32f4xx.h"
#include <ucos_ii.h>
#include "app_cfg.h"
#include <math.h>
#include "usart.h"
#include "timer.h"
#include "can.h"
#include "gpio.h"
#include "elmo.h"

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

void CAN1_RX0_IRQHandler(void)
{
	OS_CPU_SR cpu_sr;

	OS_ENTER_CRITICAL(); /* Tell uC/OS-II that we are starting an ISR          */
	OSIntNesting++;
	OS_EXIT_CRITICAL();

	CAN_ClearFlag(CAN1, CAN_FLAG_EWG);
	CAN_ClearFlag(CAN1, CAN_FLAG_EPV);
	CAN_ClearFlag(CAN1, CAN_FLAG_BOF);
	CAN_ClearFlag(CAN1, CAN_FLAG_LEC);
	CAN_ClearFlag(CAN1, CAN_FLAG_FMP0);
	CAN_ClearFlag(CAN1, CAN_FLAG_FF0);
	CAN_ClearFlag(CAN1, CAN_FLAG_FOV0);
	CAN_ClearFlag(CAN1, CAN_FLAG_FMP1);
	CAN_ClearFlag(CAN1, CAN_FLAG_FF1);
	CAN_ClearFlag(CAN1, CAN_FLAG_FOV1);
	OSIntExit();
}

/**
  * @brief  CAN2 receive FIFO0 interrupt request handler
  * @note
  * @param  None
  * @retval None
  */
void CAN2_RX0_IRQHandler(void)
{
	OS_CPU_SR cpu_sr;

	OS_ENTER_CRITICAL(); /* Tell uC/OS-II that we are starting an ISR          */
	OSIntNesting++;
	OS_EXIT_CRITICAL();

	CAN_ClearFlag(CAN2, CAN_FLAG_EWG);
	CAN_ClearFlag(CAN2, CAN_FLAG_EPV);
	CAN_ClearFlag(CAN2, CAN_FLAG_BOF);
	CAN_ClearFlag(CAN2, CAN_FLAG_LEC);
	CAN_ClearFlag(CAN2, CAN_FLAG_FMP0);
	CAN_ClearFlag(CAN2, CAN_FLAG_FF0);
	CAN_ClearFlag(CAN2, CAN_FLAG_FOV0);
	CAN_ClearFlag(CAN2, CAN_FLAG_FMP1);
	CAN_ClearFlag(CAN2, CAN_FLAG_FF1);
	CAN_ClearFlag(CAN2, CAN_FLAG_FOV1);
	OSIntExit();
}

/*************定时器2******start************/
//每1ms调用一次

extern OS_EVENT *PeriodSem;

void TIM2_IRQHandler(void)
{
#define PERIOD_COUNTER 10

	//用来计数10次，产生10ms的定时器
	static uint8_t periodCounter = PERIOD_COUNTER;

	OS_CPU_SR cpu_sr;
	OS_ENTER_CRITICAL(); /* Tell uC/OS-II that we are starting an ISR          */
	OSIntNesting++;
	OS_EXIT_CRITICAL();

	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{

		//实现10ms 发送1次信号量
		periodCounter--;
		if (periodCounter == 0)
		{
			OSSemPost(PeriodSem);
			periodCounter = PERIOD_COUNTER;
		}
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
	OSIntExit();
}

void TIM1_UP_TIM10_IRQHandler(void)
{
	OS_CPU_SR cpu_sr;
	OS_ENTER_CRITICAL(); /* Tell uC/OS-II that we are starting an ISR          */
	OSIntNesting++;
	OS_EXIT_CRITICAL();
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
	}
	OSIntExit();
}

void TIM8_UP_TIM13_IRQHandler(void)
{
	OS_CPU_SR cpu_sr;
	OS_ENTER_CRITICAL(); /* Tell uC/OS-II that we are starting an ISR          */
	OSIntNesting++;
	OS_EXIT_CRITICAL();
	if (TIM_GetITStatus(TIM8, TIM_IT_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM8, TIM_IT_Update);
	}
	OSIntExit();
}

void TIM5_IRQHandler(void)
{
	OS_CPU_SR cpu_sr;
	OS_ENTER_CRITICAL(); /* Tell uC/OS-II that we are starting an ISR          */
	OSIntNesting++;
	OS_EXIT_CRITICAL();
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
	}
	OSIntExit();
}

void TIM3_IRQHandler(void)
{
	OS_CPU_SR cpu_sr;
	OS_ENTER_CRITICAL(); /* Tell uC/OS-II that we are starting an ISR          */
	OSIntNesting++;
	OS_EXIT_CRITICAL();
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
	OSIntExit();
}

void TIM4_IRQHandler(void)
{
	OS_CPU_SR cpu_sr;
	OS_ENTER_CRITICAL(); /* Tell uC/OS-II that we are starting an ISR          */
	OSIntNesting++;
	OS_EXIT_CRITICAL();
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
	OSIntExit();
}

void UART4_IRQHandler(void)
{

	OS_CPU_SR cpu_sr;
	OS_ENTER_CRITICAL(); /* Tell uC/OS-II that we are starting an ISR*/
	OSIntNesting++;
	OS_EXIT_CRITICAL();

	if (USART_GetITStatus(UART4, USART_IT_RXNE) == SET)
	{

		USART_ClearITPendingBit(UART4, USART_IT_RXNE);
	}
	OSIntExit();
}
/***************************试场调参数用蓝牙串口中断*****************************************************/
#include "string.h"
char buffer[20];
int bufferI=0; 
extern int actualNote;
extern int musicControlFlag;
/*************/
void bufferInit(void){
  bufferI=0;
  for(int i=0;i<20;i++)
    buffer[i]=0;
}
void AT_CMD_Handle(char *buffer,uint8_t bufferI)
{
 if((bufferI == 4) && strncmp(buffer, "AT\r\n", 4)==0)//检测    
  {
    USART_OUT(USART2,(uint8_t*)"OK\r\n");
  }else if((bufferI == 7) && strncmp(buffer, "AT+do", 5)==0)
	{
		actualNote = DO;
		musicControlFlag = 1;
		USART_OUT(USART2,(uint8_t*)"DO\r\n");
	}
	else if((bufferI == 7) && strncmp(buffer, "AT+ri", 5)==0)
	{
		actualNote = RI;
		musicControlFlag = 1;		
		USART_OUT(USART2,(uint8_t*)"RI\r\n");
	}
	else if((bufferI == 7) && strncmp(buffer, "AT+mi", 5)==0)
	{
				musicControlFlag = 1;
		actualNote = MI;
		USART_OUT(USART2,(uint8_t*)"MI\r\n");
	}
	else if((bufferI == 7) && strncmp(buffer, "AT+fa", 5)==0)
	{
				musicControlFlag = 1;
		actualNote = FA;
		USART_OUT(USART2,(uint8_t*)"FA\r\n");
	}
	else if((bufferI == 7) && strncmp(buffer, "AT+so", 5)==0)
	{
				musicControlFlag = 1;
		actualNote = SO;
		USART_OUT(USART2,(uint8_t*)"SO\r\n");
	}
	else if((bufferI == 7) && strncmp(buffer, "AT+la", 5)==0)
	{
				musicControlFlag = 1;
		actualNote = LA;
		USART_OUT(USART2,(uint8_t*)"LA\r\n");
	}
	else if((bufferI == 7) && strncmp(buffer, "AT+si", 5)==0)
	{
				musicControlFlag = 1;
		actualNote = SI;
		USART_OUT(USART2,(uint8_t*)"SI\r\n");
	}
	else if((bufferI == 8) && strncmp(buffer, "AT+hdo", 6)==0)
	{
				musicControlFlag = 1;
		actualNote = HDO;
		USART_OUT(USART2,(uint8_t*)"HDO\r\n");
	}
	bufferInit();
}

void USART1_IRQHandler(void)
{

	OS_CPU_SR cpu_sr;
	OS_ENTER_CRITICAL(); /* Tell uC/OS-II that we are starting an ISR*/
	OSIntNesting++;
	OS_EXIT_CRITICAL();

	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{

		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
	OSIntExit();
}

void USART2_IRQHandler(void)
{
	OS_CPU_SR cpu_sr;
	OS_ENTER_CRITICAL(); /* Tell uC/OS-II that we are starting an ISR*/
	OSIntNesting++;
	OS_EXIT_CRITICAL();
	
	uint8_t ch = 0;
	if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET)
	{
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
		ch = USART_ReceiveData(USART2);
		buffer[bufferI] = ch;
		bufferI++;
		if(buffer[bufferI-1] == '\n' && buffer[bufferI-2] == '\r')
		{
			AT_CMD_Handle(buffer,bufferI);
		}
		else if(bufferI > 10)
		{
			bufferInit();
		}
	}
	else
	{
		USART_ClearITPendingBit(USART2, USART_IT_PE);
		USART_ClearITPendingBit(USART2, USART_IT_TXE);
		USART_ClearITPendingBit(USART2, USART_IT_TC);
		USART_ClearITPendingBit(USART2, USART_IT_ORE_RX);
		USART_ClearITPendingBit(USART2, USART_IT_IDLE);
		USART_ClearITPendingBit(USART2, USART_IT_LBD);
		USART_ClearITPendingBit(USART2, USART_IT_CTS);
		USART_ClearITPendingBit(USART2, USART_IT_ERR);
		USART_ClearITPendingBit(USART2, USART_IT_ORE_ER);
		USART_ClearITPendingBit(USART2, USART_IT_NE);
		USART_ClearITPendingBit(USART2, USART_IT_FE);
		USART_ReceiveData(USART2);
	}
		
	OSIntExit();
}

/*定位系统数据接收串口*/
void USART3_IRQHandler(void)
{

	OS_CPU_SR cpu_sr;
	OS_ENTER_CRITICAL(); /* Tell uC/OS-II that we are starting an ISR*/
	OSIntNesting++;
	OS_EXIT_CRITICAL();

	if (USART_GetITStatus(USART3, USART_IT_RXNE) == SET)
	{
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
	}
	OSIntExit();
}

void USART6_IRQHandler(void) //更新频率200Hz
{

	OS_CPU_SR cpu_sr;
	OS_ENTER_CRITICAL(); /* Tell uC/OS-II that we are starting an ISR*/
	OSIntNesting++;
	OS_EXIT_CRITICAL();

	if (USART_GetITStatus(USART6, USART_IT_RXNE) == SET)
	{
		USART_ClearITPendingBit(USART6, USART_IT_RXNE);
	}
	else
	{
		USART_ClearITPendingBit(USART6, USART_IT_PE);
		USART_ClearITPendingBit(USART6, USART_IT_TXE);
		USART_ClearITPendingBit(USART6, USART_IT_TC);
		USART_ClearITPendingBit(USART6, USART_IT_ORE_RX);
		USART_ClearITPendingBit(USART6, USART_IT_IDLE);
		USART_ClearITPendingBit(USART6, USART_IT_LBD);
		USART_ClearITPendingBit(USART6, USART_IT_CTS);
		USART_ClearITPendingBit(USART6, USART_IT_ERR);
		USART_ClearITPendingBit(USART6, USART_IT_ORE_ER);
		USART_ClearITPendingBit(USART6, USART_IT_NE);
		USART_ClearITPendingBit(USART6, USART_IT_FE);
		USART_ReceiveData(USART6);
	}
	OSIntExit();
}



void UART5_IRQHandler(void)
{
	OS_CPU_SR cpu_sr;
	OS_ENTER_CRITICAL(); /* Tell uC/OS-II that we are starting an ISR*/
	OSIntNesting++;
	OS_EXIT_CRITICAL();

	if (USART_GetITStatus(UART5, USART_IT_RXNE) == SET)
	{

		USART_ClearITPendingBit(UART5, USART_IT_RXNE);
	}
	else
	{
		USART_ClearITPendingBit(UART5, USART_IT_PE);
		USART_ClearITPendingBit(UART5, USART_IT_TXE);
		USART_ClearITPendingBit(UART5, USART_IT_TC);
		USART_ClearITPendingBit(UART5, USART_IT_ORE_RX);
		USART_ClearITPendingBit(UART5, USART_IT_IDLE);
		USART_ClearITPendingBit(UART5, USART_IT_LBD);
		USART_ClearITPendingBit(UART5, USART_IT_CTS);
		USART_ClearITPendingBit(UART5, USART_IT_ERR);
		USART_ClearITPendingBit(UART5, USART_IT_ORE_ER);
		USART_ClearITPendingBit(UART5, USART_IT_NE);
		USART_ClearITPendingBit(UART5, USART_IT_FE);
		USART_ReceiveData(UART5);
	}
	OSIntExit();
}

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
	while (1)
	{
	}
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{

	/* Go to infinite loop when Hard Fault exception occurs */
	while (1)
	{
	}
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
	/* Go to infinite loop when Memory Manage exception occurs */
	while (1)
	{
	}
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{

	/* Go to infinite loop when Bus Fault exception occurs */
	while (1)
	{
	}
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{

	/* Go to infinite loop when Usage Fault exception occurs */
	while (1)
	{
	}
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}
