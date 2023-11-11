



#ifndef SEV_SEG_INTERFACE_H_
#define SEV_SEG_INTERFACE_H_

#define SEVSEG PORTB


typedef enum 
{
	SEG1 ,
	SEG10 ,
	SEG100 ,
	SEG1000,
	}SEG_PIN;

 void Segment_display(u16 num);
 
 void Enable_7seg(SEG_PIN seg);



#endif /* SEV_SEG_INTERFACE_H_ */