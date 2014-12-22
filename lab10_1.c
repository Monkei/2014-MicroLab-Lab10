#include <REG_MPC82G516.h>

//Global variables and definition
#define PWMPIN P22
#define C1 P00
#define C2 P01
#define C3 P02
#define Num P1

unsigned char pwm_width;
bit pwm_flag = 0;

void delay_ms(int t);
void pwm_setup(unsigned char speed){
	TMOD = 0;
	pwm_width = speed;
	EA = 1;
	ET0 = 1;
	TR0 = 1;
}

void timer0() interrupt 1 {
	if(!pwm_flag) {	//Start of High level
		pwm_flag = 1;	//Set flag
		PWMPIN = 1;	//Set PWM o/p pin
		TH0 = 255 - pwm_width;	//Load timer
		TF0 = 0;		//Clear interrupt flag
		return;		//Return
	}
	else {	//Start of Low level
		pwm_flag = 0;	//Clear flag
		PWMPIN = 0;	//Clear PWM o/p pin
		TH0 = pwm_width;	//Load timer
		TF0 = 0;	//Clear Interrupt flag
		return;		//return
	}
}

void btn1() interrupt 0 {
	if(pwm_width < 128)//if(pwm_width < 256)
		++pwm_width;
}

void btn2() interrupt 2 {
	if(pwm_width > 0)
		--pwm_width;
}

void show_num(){
	C2 = C3 = 1;
	C1 = 0;
	Num = pwm_width % 10;
	delay_ms(10);
	
	C1 = 1;
	C2 = 0;
	Num = (pwm_width/10) % 10;
	delay_ms(10);
	
	C2 = 1;
	C3 = 0;
	Num = pwm_width/100;
	delay_ms(10);
	
	C3 = 1;
}
void main()
{
	pwm_setup(30);
	P2 = 0x01;
	while(1)
	{
	}

}

void delay_ms(int t){
	int i;
	while(t--)
		for(i=0;i<1000;++i);
}
