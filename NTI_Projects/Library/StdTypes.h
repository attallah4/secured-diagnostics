/*
* StdTypes.h
*
* Created: 17/10/2023 12:13:12
*  Author: Ali Attallah
*/


#ifndef STDTYPES_H_
#define STDTYPES_H_

typedef unsigned char u8;
typedef signed char s8;

typedef  char c8;

typedef unsigned short u16;
typedef signed short s16;

typedef unsigned long u32;
typedef signed long s32;

typedef unsigned long long u64;
typedef signed long long s64;


typedef enum {
	FALSE,
	TRUE
}Bool_t;

typedef enum {
	OK,
	NOK,
	NULLPTR,
	OUTOFRANGE
}Erorr_t ;

#define NULL_PTR ((void*)0)
#define  NULL ((char)0)

#define MAX_u8  ((u8)255)
#define MIN_u8  ((u8)0)

#define MAX_s8  ((s8)127)
#define MIN_s8  ((s8)-128)

#define ZERO_s8 ((s8)0)




#endif /* STDTYPES_H_ */