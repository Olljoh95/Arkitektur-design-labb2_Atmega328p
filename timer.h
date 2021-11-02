#ifndef _TIMER_H_
#define _TIMER_H_

void timer_init(void);
ISR(TIMER0_OVF_vect);
void fadeLedUp(void);
void fadeLedDown(void);

#endif // _TIMER_H_
