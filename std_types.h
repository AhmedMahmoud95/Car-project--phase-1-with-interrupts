/*
 * std_types.h
 *
 *  Created on: Oct 21, 2019
 *      Author: Sprints
 */

#ifndef STD_TYPES_H_
#define STD_TYPES_H_


/************************************************************************/
/*                   typedefs for standard types                        */
/************************************************************************/

#define NULL	((void *)0)

typedef unsigned char uint8;
typedef unsigned int uint16;
typedef unsigned long int uint32;
typedef unsigned long long uint64;
typedef signed char sint8;
typedef signed int sint16;
typedef signed long int sint32;
typedef signed long long sint64;
typedef volatile uint8* const reg_type8;
typedef volatile uint16* const reg_type16;


/************************************************************************/
/*				 		defining boolean values                         */
/************************************************************************/
#define FALSE 	0	// defines boolean false
#define TRUE 	1	// defines boolean true


/************************************************************************/
/*						 LOW/HIGH defines                               */
/************************************************************************/
#define LOW  0		// defines LOW value for a bit
#define HIGH 0xFF	// defines HIGH value for a bit


/************************************************************************/
/*						 BIT_MATH defines                               */
/************************************************************************/

/* Set VARiable's Certin BIT High */
#define SET_BIT(VAR,BIT_NB) 		(VAR)|=(BIT_NB)
/* Set VARiable's Certin BIT Low */
#define CLR_BIT(VAR,BIT_NB) 		(VAR)&=~(BIT_NB)
/* Toggle VARiable's Certin BIT */
#define TOGGLE_BIT(VAR,BIT_NB) 		(VAR)^=(BIT_NB)
/* Assign VARiable's Certin BIT by a Certin VALue */
#define ASSIGN_BIT(VAR,BIT_NB,VAL)  (VAR)=((VAR&(~(BIT_NB)))|(VAL<<BIT_NB))
/* Get VARiable's Certin BIT Value */
#define GET_BIT(VAR,BIT_NB) 		(((VAR)&(BIT_NB))/(BIT_NB))


#endif /* STD_TYPES_H_ */
