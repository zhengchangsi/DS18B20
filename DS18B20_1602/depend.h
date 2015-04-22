#ifndef __basic_H__
#define __basic_H__


#define uchar unsigned char
#define uint unsigned int
#define exchange(m,n) m=m+n;n=m-n;m=m-n; 

#define EA_on   EA=1    
#define EA_off  EA=0

#define ET2_on  ET2=1  
#define ET2_off ET2=0

#define ES_on   ES=1   
#define ES_off  ES=0

#define ET1_on  ET1=1  
#define ET1_off ET1=0

#define EX1_on  EX1=1  
#define EX1_off EX1=0

#define ET0_on  ET0=1  
#define ET0_off ET0=0

#define EX0_on  EX0=1  
#define EX0_off EX0=0


#define EX0_int0   EA=1;IT0=0;EX0=1;  
#define EX0_int1   EA=1;IT0=1;EX0=1; 

#define EX1_int0   EA=1;IT1=0;EX1=1;  
#define EX1_int1   EA=1;IT1=1;EX1=1;  


#endif