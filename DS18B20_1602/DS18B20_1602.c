#include <reg52.h>
#include "depend.h"
#include  <math.h>  
#include  <stdio.h>
#include  <INTRINS.H>
#define uchar unsigned char
#define uint unsigned int

#define RS_CLR RS=0 
#define RS_SET RS=1
#define RW_CLR RW=0 
#define RW_SET RW=1 
#define EN_CLR EN=0
#define EN_SET EN=1

sbit RS = P2^0;
sbit RW = P2^1;
sbit EN = P2^2;
sbit DQ=P3^4; 

uchar  m,n,w;
uint  temp;
uchar xdata buf[3]={0,0,0};
uchar code *NUM[]={"0","1","2","3","4","5","6","7","8","9","."};

void delay_us(unsigned int n);
void delay_ms(unsigned char i);
void LCD_write_com(unsigned char com);
void LCD_write_Data(unsigned char Data);
void LCD_clear(void);
void LCD_write_str(unsigned char x,unsigned char y,unsigned char *s);
void LCD_write_char(unsigned char x,unsigned char y,unsigned char Data);
void LCD_init(void);
void delay(uint i);
void Init_DS18B20() ;
uchar ReadOneChar();
uchar WriteOneChar(unsigned char dat);
void tmpchange();
void tmp();
void Data_Process();

void main(void) 
{ 
unsigned char i; 
delay_ms(100); 
LCD_init(); 
LCD_clear(); 
while (1) 
{ 
     tmpchange();  
     tmp(); 
	 Data_Process(); 
		for(i=0;i<2;i++)
		{
			LCD_write_char(i,1,*NUM[buf[i]]);
		}  

}
}

void delay_us(unsigned int n) 
{ 
 if (n == 0) 
  {  
  return ;  
  } 
  while (--n);
 }
 void delay_ms(unsigned char i) 
 { 
 unsigned char a, b; 
 for (a = 1; a < i; a++) 
 {
   for (b = 1; b; b++) 
   {   ;   } 
    }
 }
/****************************
命令写入函数
****************************/
void LCD_write_com(unsigned char com) 
{  
	RS_CLR; 
	RW_CLR; 
	EN_SET; 
	P0 = com; 
	delay_us(5); 
	EN_CLR;
}

/*****************************
显示屏数据写入函数
****************************/
void LCD_write_Data(unsigned char Data) 
{ 
	RS_SET; 
	RW_CLR; 
	EN_SET; 
	P0 = Data; 
	delay_us(5); 
	EN_CLR;
}

/***************************
清空显示屏
****************************/
void LCD_clear(void) 
{ 
	LCD_write_com(0x01); 
	delay_ms(5);
}

/****************************
字符串写入
*****************************/
void LCD_write_str(unsigned char x,unsigned char y,unsigned char *s) 
{     
	if (y == 0) 
	{     
		LCD_write_com(0x80 + x);     
	}
	else 
	{     
		LCD_write_com(0xC0 + x);     
	}        
	while (*s) 
	{     
		LCD_write_Data( *s);     
		s ++;     
	}
}

/*****************************
字符写入
*****************************/
void LCD_write_char(unsigned char x,unsigned char y,unsigned char Data) 
{     
	if (y == 0) 
	{     
		LCD_write_com(0x80 + x);     
	}    
	else 
	{     
		LCD_write_com(0xC0 + x);     
	}        
	LCD_write_Data( Data);  
}

/*******************************
显示屏初始化
********************************/
void LCD_init(void) 
{
	LCD_write_com(0x38);   
	delay_ms(5); 
	LCD_write_com(0x38); 
	delay_ms(5); 
	LCD_write_com(0x38); 
	delay_ms(5); 
	LCD_write_com(0x38);  
	LCD_write_com(0x08);    
	LCD_write_com(0x01);    
	LCD_write_com(0x06);   
	delay_ms(5);
	LCD_write_com(0x0C);
} 

/*********************************
延时函数
**********************************/ 
void delay(uint i)     
{ 
	while(i--); 
}  
/*********************************
初始化DS18B20
*********************************/
void Init_DS18B20() 
{ 
	uchar x=0; 
	DQ = 1;              
	delay(8);            
	DQ = 0;              
	delay(80);          
	DQ = 1;              
	delay(14); 
	x=DQ;                 
	delay(20); 
} 
/*********************************
读取字节函数
*********************************/
uchar ReadOneChar() 
{ 
	uchar i = 0; 
	uchar dat = 0; 
	for (i=8;i>0;i--) 
	{ 
		DQ = 0;             
		dat>>=1;            
		DQ = 1;             
		if(DQ)              
		dat|=0x80;         
		delay(4);          
	} 
	return(dat); 
} 

/***********************************
写入字节
*********************************/
uchar WriteOneChar(unsigned char dat) 
{ 
	uchar i = 0; 
	for (i=8; i>0; i--) 
	{ 
		DQ = 0; 
		DQ = dat&0x01;  
		delay(5); 
		DQ = 1; 
		dat>>=1;       
	} 
	return(dat);
} 
/*************************************
温度转换
**************************************/
void tmpchange()            
{ 
  Init_DS18B20();            
  delay(200);                 
  WriteOneChar(0xcc);         
  WriteOneChar(0x44);         
} 
/*************************************
读出温度
************************************/
void tmp()                   
{ 
	Init_DS18B20();            
	delay(1); 
	WriteOneChar(0xcc);         
	WriteOneChar(0xbe);     
	m=ReadOneChar(); 
	n=ReadOneChar(); 
	temp=n; 
	temp<<=8;                                                
	temp=temp|m;    
	temp=temp>>4;
} 
void Data_Process()			
{
	buf[0] = temp/10;
	buf[1] = temp%10;
}


