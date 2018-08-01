/*
 * [tkim058]_lab[3]_part[1].c
 * Partner(s) Name & E-mail: MinHwan Oh
 * Lab Section: B01
 * Assignment: Lab #3  Exercise #1
 * Exercise Description: [Fuel Sensor]
 *
 * I acknowledge all content contained herein, excluding template or example
 * code, is my own original work.
 */

#include <avr/io.h>
enum States{Start, Init, Wait1, Pressed1, Wait2, Pressed2}state;
unsigned char tmpB;

void Tick()
{
	
switch(state)
{
	case Start: 
	state =Init;break;
	case Init:
	state = Wait1;break;
	case Wait1:
	state = (PINA & 0x01) ? Pressed1 : state; break;
	case Pressed1:
	state = (!(PINA & 0x01))? Wait2 : state; break;
	case Wait2:
	state = (PINA & 0x01) ? Pressed2 : state; break;
	case Pressed2:
	state = (!(PINA & 0x01))? Wait1 : state; break;
	default:
	state = Start;
	break;
}
switch(state)
{
	case Start: break;
	case Init:
	tmpB = 0x01;
	PORTB = tmpB;
	break;
	case Wait1: break;
	case Pressed1:
	tmpB = 0x02;
	PORTB = tmpB;
	case Wait2: break;
	case Pressed2:
	tmpB = 0x01;
	PORTB = tmpB;
	break;
	default: break;
}
}
int main(void)
{
 DDRA = 0x00; PORTA = 0xFF;	//set PORTA to inputs
 DDRB = 0xFF; PORTB = 0x00;	//set PORTB to outputs

 state = Start;              //initialize state var
 tmpB = 0x01;                   //initialize tmpB var

 while (1) {
	 Tick();                 //call tick()
 }
}




