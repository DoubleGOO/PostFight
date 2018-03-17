#include "pwm.h"
#include "delay.h"
u16 comp;
u8 command;

void TIM12_PWM_Init(u32 arr,u32 psc)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//(��ͨ���ģʽ)
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_TIM12);//GPIOF14����ӳ�䵽TIM12����ΪTIM12����������ţ�
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_TIM12);//GPIOF115����ӳ�䵽TIM12����ΪTIM12����������ţ�
	
	TIM_TimeBaseInitStructure.TIM_Period = arr;//Ԥװ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;//��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
	TIM_TimeBaseInitStructure.TIM_ClockDivision =TIM_CKD_DIV1;
	
	TIM_TimeBaseInit(TIM12,&TIM_TimeBaseInitStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//ģʽ1
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//�Ƚ��������(��Ч�ĵ�ƽ)
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//���ʹ��
	
	TIM_OC1Init(TIM12,&TIM_OCInitStructure);//TIM12ͨ��1��ʼ������
	TIM_OC2Init(TIM12,&TIM_OCInitStructure);//TIM12ͨ��2��ʼ������
	
	TIM_OC1PreloadConfig(TIM12, TIM_OCPreload_Enable);  //ʹ��TIM12��CCR1�ϵ�Ԥװ�ؼĴ���
	TIM_OC2PreloadConfig(TIM12, TIM_OCPreload_Enable);
 
	TIM_ARRPreloadConfig(TIM12,ENABLE);//ARPEʹ��Ԥװ��
	TIM_Cmd(TIM12,ENABLE);  //ʹ��TIM12
	
}


void Arm_Angle(double DU)
{
		comp = (u16)(10 * (DU / 9)) + 50;
		TIM_SetCompare1(TIM12,comp-1);//Ŀ��ռ�ձȻ����ת������
}

void Hand_Angle(double DU)
{
		comp = (u16)(10 * (DU / 9)) + 50;
		TIM_SetCompare2(TIM12,comp-1);//Ŀ��ռ�ձȻ����ת������
}

void AngleCtrl()
{
	switch(command){
		case 0x61://̧��
			Arm_Angle(0);
			break;
		case 0x62://����
			Arm_Angle(90);
		  break;
		case 0x63://�ſ�
			Hand_Angle(120);
			break;
		case 0x64://��£
			Hand_Angle(180);
			break;
		default://Ĭ����̬
			Arm_Angle(0);
			Hand_Angle(120);
			break;
	}
	delay_ms(200);
}
