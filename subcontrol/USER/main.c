#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "pwm.h"

extern u8 command;
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(115200);//��ʼ�����ڲ�����Ϊ115200
 	TIM12_PWM_Init((2000-1),840-1);	//84M/84=1Mhz�ļ���Ƶ��,��װ��ֵ500������PWMƵ��Ϊ 1M/500=2Khz.     
	while(1)
	{
		AngleCtrl();//��е�ۿ��ƣ�ͨ������1����ָ��
	}
}


