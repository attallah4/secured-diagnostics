


#ifndef SERVO_INTERFACE_H_
#define SERVO_INTERFACE_H_


void Servo_Init(void);

void Servo_getAngel(u8 angel);

#define SERVO_PWM_REG OCR1B


#endif /* SERVO_INTERFACE_H_ */