/****************************************Copyright (c)**************************************************
**                       		     北	京	交	通	大	学
**                                        电气工程学院
**                                         604实验室
**
**                              
** 
**--------------文件信息--------------------------------------------------------------------------------
**文   件   名: user_interface.c
**创   建   人:
**最后修改日期:
**描        述: 右玉1.5MW双馈风电机组并网变流器控制软件外设控制程序--201005atcpc-201007atbjtu
				包括对eeprom,sci,spi,ad,da的控制程序
**              
**--------------历史版本信息----------------------------------------------------------------------------
** 创建人:
** 版  本:
** 日　期:
** 描　述:
**
**--------------当前版本修订------------------------------------------------------------------------------
** 修改人:
** 日　期:
** 描　述:
**
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
#include "DSP2833x_Device.h"     // Headerfile Include File
#include "DSP2833x_Examples.h"   // Examples Include File
#include "math.h"				//20121103
//函数声明
#include "user_header.h"  						//变量常量定义
#include "user_macro.h"							//宏函数
#include "user_database.h"						//数据库
#include "user_interface.h"
/*********************************************************************************************************
** 函数名称: EeStart
** 功能描述: 开始对eeprom的操作
** 输　入:
** 输　出:
** 注  释: 	 时钟线高时数据线下降沿为开始
**-------------------------------------------------------------------------------------------------------
** 作　者:
** 日　期:
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
void EeStart(void)
{
	EALLOW;
    GpioDataRegs.GPBSET.bit.GPIO32 = 1;     	 //数据高
	GpioCtrlRegs.GPBDIR.bit.GPIO32 = 1;  		//数据线变为输出口
	EDIS;
	DELAY_US(DELAY_EE);
    GpioDataRegs.GPBSET.bit.GPIO33 = 1;     	//时钟高
	DELAY_US(DELAY_EE);
	GpioDataRegs.GPBCLEAR.bit.GPIO32 = 1;		 	//数据低
	DELAY_US(DELAY_EE);
   	GpioDataRegs.GPBCLEAR.bit.GPIO33 = 1;     	//时钟低
	DELAY_US(DELAY_EE);
}
/*********************************************************************************************************
** 函数名称: EeStop
** 功能描述: 结束对eeprom的操作
** 输　入:
** 输　出:
** 注  释: 	 时钟线高时数据线上升沿为结束
**-------------------------------------------------------------------------------------------------------
** 作　者:
** 日　期:
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
void EeStop(void)
{
	EALLOW;
    GpioDataRegs.GPBCLEAR.bit.GPIO32 = 1;     	 //数据低
	GpioCtrlRegs.GPBDIR.bit.GPIO32 = 1;  		//数据线变为输出口
	EDIS;
	DELAY_US(DELAY_EE);
    GpioDataRegs.GPBSET.bit.GPIO33 = 1;     	//时钟高
	DELAY_US(DELAY_EE);
    GpioDataRegs.GPBSET.bit.GPIO32 = 1;     	 //数据高
	DELAY_US(DELAY_EE);
   	GpioDataRegs.GPBCLEAR.bit.GPIO33 = 1;     	//时钟低
	EALLOW;
	GpioCtrlRegs.GPBDIR.bit.GPIO32= 0;			//数据线变为输入口
	EDIS;
	DELAY_US(DELAY_EE);
}

/*********************************************************************************************************
** 函数名称: EeWrite
** 功能描述: 将number个字节数据（不包括地址）连续写入到eeprom（一般要求在同一页面）
** 输　入: 	 number,表示要写的字节数
** 输　出:
** 注  释: 	 EEPROM.data[0]:写控制字;
**			 EEPROM.data[1-2]:待写数据地址;
**			 EEPROM.data[3-x]:待写数据;
**-------------------------------------------------------------------------------------------------------
** 作　者:
** 日　期:
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
void EeWrite(unsigned char number)
{
	int16 i,j;
//----------------------------------------------//发送起始位
	EeStart();
//----------------------------------------------//开始发送数据
	for(j=0;j<number+3;j++)						//先发低字节
	{
		for(i=0;i<8;i++)						//每个字节先发高字位
		{
			if((EEPROM.data[j] & ONEBYTE[i])==0)	//要发0
			{
				GpioDataRegs.GPBCLEAR.bit.GPIO32 =1;	//数据低
				DELAY_US(DELAY_EE);					
    			GpioDataRegs.GPBSET.bit.GPIO33 = 1; //时钟高
				DELAY_US(DELAY_EE);				
   	   		    GpioDataRegs.GPBCLEAR.bit.GPIO33 = 1;//时钟低
				DELAY_US(DELAY_EE);				
			}
			else									//要发1
			{
				GpioDataRegs.GPBSET.bit.GPIO32 =1;	//数据高
				DELAY_US(DELAY_EE);				
   				GpioDataRegs.GPBSET.bit.GPIO33 = 1;     	//时钟高
				DELAY_US(DELAY_EE);				
   	   		    GpioDataRegs.GPBCLEAR.bit.GPIO33 = 1;     	//时钟低
				DELAY_US(DELAY_EE);				
			}
		}
//----------------------------------------------//发完一个字节
		EALLOW;
		GpioCtrlRegs.GPBDIR.bit.GPIO32= 0;		//数据线变为输入口
		EDIS;
    	GpioDataRegs.GPBSET.bit.GPIO33 = 1;     	//时钟高
		DELAY_US(DELAY_EE);
		
		if(GpioDataRegs.GPBDAT.bit.GPIO32==1)	//如果数据线读到1表示没有应答
		{
			M_SetFlag(SL_EE_NOACK);				//置无应答标志
		}
		
   	    GpioDataRegs.GPBCLEAR.bit.GPIO33 = 1;     	//时钟低

		EALLOW;
		GpioDataRegs.GPBCLEAR.bit.GPIO32= 1;		//数据低
		GpioCtrlRegs.GPBDIR.bit.GPIO32= 1;		//数据线变为输出口
		EDIS;
		DELAY_US(DELAY_EE);
	}
//----------------------------------------------//发送停止位
	EeStop();
}

/*********************************************************************************************************
** 函数名称: EeRead
** 功能描述: 从eeprom连续读出number个字节数据
** 输　入: 	 number,表示要读的字节数
** 输　出:   EEPROM.data[0-1]:读出的数据
** 注  释: 	 先写写控制字,再写待读数据地址,再写读控制字,在读出数据
**-------------------------------------------------------------------------------------------------------
** 作　者:
** 日　期:
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
void EeRead(unsigned char number)
{
	int16 i,j;
	
//----------------------------------------------//发送起始位
	EeStart();
//----------------------------------------------//开始发送地址数据
	for(j=0;j<3;j++)							//先发低字节
	{
		for(i=0;i<8;i++)						//每个字节先发高字位
		{
			if((EEPROM.data[j] & ONEBYTE[i])==0)	//要发0
			{
				GpioDataRegs.GPBCLEAR.bit.GPIO32 =1;	//数据低
				DELAY_US(DELAY_EE);				
   				GpioDataRegs.GPBSET.bit.GPIO33 = 1;     	//时钟高
				DELAY_US(DELAY_EE);				
   	    		GpioDataRegs.GPBCLEAR.bit.GPIO33 = 1;     	//时钟低
				DELAY_US(DELAY_EE);				
			}
			else									//要发1
			{
				GpioDataRegs.GPBSET.bit.GPIO32 =1;	//数据高
				DELAY_US(DELAY_EE);				
    			GpioDataRegs.GPBSET.bit.GPIO33 = 1;     	//时钟高
				DELAY_US(DELAY_EE);				
   	   		    GpioDataRegs.GPBCLEAR.bit.GPIO33 = 1;     	//时钟低
				DELAY_US(DELAY_EE);				
			}
		}
//----------------------------------------------//发完一个字节
		EALLOW;
		GpioCtrlRegs.GPBDIR.bit.GPIO32= 0;		//数据线变为输入口
		EDIS;
   	    GpioDataRegs.GPBSET.bit.GPIO33 = 1;     	//时钟高
		DELAY_US(DELAY_EE);
		
		if(GpioDataRegs.GPBDAT.bit.GPIO32==1)	//如果数据线读到1表示没有应答
		{
			M_SetFlag(SL_EE_NOACK);				//置无应答标志
		}
		
   	    GpioDataRegs.GPBCLEAR.bit.GPIO33 = 1;     	//时
		
		EALLOW;
		GpioDataRegs.GPBCLEAR.bit.GPIO32 =1;		//数据低
		GpioCtrlRegs.GPBDIR.bit.GPIO32= 1;		//数据线变为输出口
		EDIS;
		
		DELAY_US(DELAY_EE);
	}
	
//----------------------------------------------//再次发送起始位
	EeStart();
//----------------------------------------------//再次发送起始位
	EEPROM.data[0] |= 0x01;						//改为读指令
	for(i=0;i<8;i++)							//先发高字位
	{
		if((EEPROM.data[0] & ONEBYTE[i])==0)		//要发0
		{
			GpioDataRegs.GPBCLEAR.bit.GPIO32 =1;		//数据低
			DELAY_US(DELAY_EE);					
   		    GpioDataRegs.GPBSET.bit.GPIO33 = 1;     	//时钟高
			DELAY_US(DELAY_EE);					
   	  	    GpioDataRegs.GPBCLEAR.bit.GPIO33 = 1;     	//时钟低
			DELAY_US(DELAY_EE);					
		}
		else										//要发1
		{
			GpioDataRegs.GPBSET.bit.GPIO32 =1;		//数据高
			DELAY_US(DELAY_EE);					
   		    GpioDataRegs.GPBSET.bit.GPIO33 = 1;     	//时钟高
			DELAY_US(DELAY_EE);					
   	        GpioDataRegs.GPBCLEAR.bit.GPIO33 = 1;     	//时钟低
			DELAY_US(DELAY_EE);					
		}
	}
//----------------------------------------------//发完一个字节
	EALLOW;
	GpioCtrlRegs.GPBDIR.bit.GPIO32 =0;			//数据线变为输入口
	EDIS;
    GpioDataRegs.GPBSET.bit.GPIO33 = 1;     	//时钟高
	DELAY_US(DELAY_EE);
	
	if(GpioDataRegs.GPBDAT.bit.GPIO32==1)		//如果数据线读到1表示没有应答
	{
		M_SetFlag(SL_EE_NOACK);					//置无应答标志
	}
	
   	GpioDataRegs.GPBCLEAR.bit.GPIO33 = 1;     	//时钟低
	DELAY_US(DELAY_EE);
//----------------------------------------------//开始读数据
	for(j=0;j<number;j++)						//先读低字节
	{
		EEPROM.data[j]=0;
		for(i=0;i<8;i++)						//每个字节先读高位
		{
   		    GpioDataRegs.GPBSET.bit.GPIO33 = 1;     	//时钟高
			DELAY_US(DELAY_EE);	
			if(GpioDataRegs.GPBDAT.bit.GPIO32==1)//数据为1
			{
				EEPROM.data[j] |= ONEBYTE[i];	//为零则不变
			}
   	   	    GpioDataRegs.GPBCLEAR.bit.GPIO33 = 1;     	//时钟低
			DELAY_US(DELAY_EE);
		}
//----------------------------------------------//收完一个字节
		if(j!=number-1)							//最后一个字节不发出应答
		{
			EALLOW;
			GpioDataRegs.GPBCLEAR.bit.GPIO32 =1;	//输出低来应答
			GpioCtrlRegs.GPBDIR.bit.GPIO32= 1;	//数据线为输出口
			EDIS;
			DELAY_US(DELAY_EE);
		}
   	    GpioDataRegs.GPBSET.bit.GPIO33 = 1;     	//时钟高
		DELAY_US(DELAY_EE);
   	    GpioDataRegs.GPBCLEAR.bit.GPIO33 = 1;     	//时钟低
		EALLOW;
		GpioCtrlRegs.GPBDIR.bit.GPIO32= 0;		//数据线为输入口
		EDIS;
		DELAY_US(DELAY_EE);		
	}
//----------------------------------------------//接收完毕,发送停止位
	EeStop();
}
/*********************************************************************************************************
** 函数名称: EeWpre
** 功能描述: 准备写入EEPROM的地址和数据
** 输　入: 	 index:待写入变量的序号
** 输　出:   EEPROM.data[0-4]:写控制字、待写数据的地址和待写数据
** 注  释:
**-------------------------------------------------------------------------------------------------------
** 作　者:
** 日　期:
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
void EeWpre(unsigned char index)
{
	EEPROM.data[0]=0xA0;									//Slave ADdress
	EEPROM.data[1]=((index<<1)&0xFF00)>>8;					//MSB ADdress
	EEPROM.data[2]=(index<<1)&0xFF;							//LSB ADdress
	EEPROM.data[3]=*(FUNC[index].para_add) & 0x00ff;		//低8位数据
	EEPROM.data[4]=(*(FUNC[index].para_add) & 0xff00)>>8;	//高8位数据
}
/*********************************************************************************************************
** 函数名称: EeRpre
** 功能描述: 准备读取EEPROM数据的地址
** 输　入: 	 index:待读取变量的序号
** 输　出:   EEPROM.data[0-2]:读控制字和待读取数据的地址
** 注  释:
**-------------------------------------------------------------------------------------------------------
** 作　者:
** 日　期:
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
void EeRpre(unsigned char index)
{
	EEPROM.data[0]=0xA0;							//Slave ADdress
	EEPROM.data[1]=((index<<1)&0xFF00)>>8;			//MSB ADdress
	EEPROM.data[2]=(index<<1)&0xFF;					//LSB ADdress
}
/*********************************************************************************************************
** 函数名称: EeWrword
** 功能描述: 写一个字的数据到EEPROM并读出来校验
** 输　入: 	 index:待写变量的序号
** 输　出:
** 注  释: 	 先将待写数据写入eeprom再读出来检验
**			 如果检验不对在置标志位SL_EE_FAIL
**-------------------------------------------------------------------------------------------------------
** 作　者:
** 日　期:
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
void EeWrword(unsigned char index)
{
	Uint16 data_rd;
	
	EeWpre(index);									
	EeWrite(2);											//写入2字节数据
	EeRead(2);											//将2字节数据读出
	
	data_rd=(EEPROM.data[1]<<8) | EEPROM.data[0];		//data_rd为读出的数据
	
	if(data_rd!=*(FUNC[index].para_add))
		M_SetFlag(SL_EE_FAIL);
}
/*********************************************************************************************************
** 函数名称: InitEeprom
** 功能描述: 初始化eeprom
** 输　入:
** 输　出:
** 注  释: 	 先将eeprom中的原有数据读出并进行检验
**			 如果出现数据错误则将eeprom中数据全部初始化
**			 检测在初始化过程中是否出现eeprom操作错误
**			 如果没有错误则置SL_CODEOK表示eeprom工作正常,否则清SL_CODEOK表示eeprom工作错误
**-------------------------------------------------------------------------------------------------------
** 作　者:
** 日　期:
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
void InitEeprom(void)
{
	Uint16 i,j;
//	Uint16 j;
	if(DEBUG_OPER==0)
	{
//----------------------------------------------//将eeprom的数据全部读入ram
		for(i=0;i<PARA_NUM;i++)					
		{
			EeRpre(i);								//控制字和地址填入EEPROM.data[]
			EeRead(2);
												//读出的数据放入RAM
			*FUNC[i].para_add=(EEPROM.data[1]<<8) | EEPROM.data[0];	
		
			if(CheckCode(i)==1)						//检查程序的返回值=1则表示有错误
			{
				for(j=0;j<PARA_NUM;j++)
				{
					*FUNC[j].para_add=FUNC[j].init;	//RAM数据恢复初值
					EeWrword(j);					//写入2字节数据
				}
				break;								//数据校验有错则跳出
			}
		}
	}
	else
	{
//-----------------------------------------//调试时直接将EEPROM初始化!!!
		for(j=0;j<PARA_NUM;j++)
		{
			*FUNC[j].para_add=FUNC[j].init;	//RAM数据恢复初值
			EeWrword(j);					//写入2字节数据
		}
	}
//-----------------------------------------	
	if(M_ChkFlag(SL_EE_FAIL)==0)					
		M_SetFlag(SL_CODEOK);					//EEPROM正常
	else
		M_ClrFlag(SL_CODEOK);					//EEPROM故障
}
/*********************************************************************************************************
** 函数名称: CheckCode
** 功能描述: 检验eeprom中数据是否正确
** 输　入: 	 index,待检验数据的序号
** 输　出:   j,j=1表示数据错误;j=0表示数据正确
** 注  释: 	 检验数据是否在指定的范围之内
**			 
**-------------------------------------------------------------------------------------------------------
** 作　者:
** 日　期:
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
Uint16 CheckCode(Uint16 index)						
{
	Uint16 j,data,max,min;
	int16  temp,max_temp,min_temp;
	
	data=*FUNC[index].para_add;
//----------------------------------------------//判断该数据的属性
	if((FUNC[index].attr & MAX_PT)==1)			//具有最大值指针属性
		max=*FUNC[index].max_add;
	else										//不具有最大值指针属性
		max=FUNC[index].max;					//读出这个量的最大值
//----------------------------------------------//具有最小值指针属性
	if((FUNC[index].attr & MIN_PT)==1)
		min=*FUNC[index].min_add;
	else 										//不具有最小值指针属性
		min=FUNC[index].min;					//读出这个量的最小值
//----------------------------------------------//开始校验
	j=0;										//置无故障标志
	if((FUNC[index].attr & SIG)==0)				//无符号数
	{
		if(data>max)				
			j=1;								//大于最大值，有错
		else if(data<min)						//小于最小值
		{
			if((FUNC[index].attr & VA0)==0)		
				j=1;							//又不具有VA0属性，有错
			else if(data!=0)					//具有VA0属性但又不为零，有错
				j=1;
		}
	}					
	else										//有符号数
	{
		temp=(int)data;							//全部转为有符号数
		max_temp=(int)max;
		min_temp=(int)min;
		if(temp>max_temp)						//大于最大值，有错
			j=1;
		else if(temp<min_temp)					//小于最小值，有错
			j=1;								//有符号数没有VA0属性
	}
//----------------------------------------------//返回值为j
	return j;
}
/*********************************************************************************************************
** 函数名称: EeCtrl
** 功能描述: 程序运行过程中对eeprom数据的操作
** 输　入:
** 输　出:
** 注  释: 	 在eeprom正确的前提下，检测标志位
**			 SL_INIEE:		是否需要进行初始化eeprom操作;
							如果是则置SL_EEBUSY_INIEE,全部初始化完以后再清SL_INIEE和SL_EEBUSY_INIEE
**			 SL_MCODE:		是否需要修改功能码值
							如果是则置SL_EEBUSY_MCODE,将EEPROM.mcode中指定的数据写入eeprom
							操作完成后再清SL_MCODE和SL_EEBUSY_MCODE
**			 SL_ERRSAVE:	是否需要保存故障信息
							如果是则置SL_EEBUSY_ERRSAVE,将TAB_ERR中的数据写入eeprom
							操作完成后再清SL_ERRSAVE和SL_EEBUSY_ERRSAVE
**			 SL_POFSAVE:	是否需要保存掉电信息
							如果是则置SL_EEBUSY_POFSAVE,将TAB_POF中的数据写入eeprom
							操作完成后再清SL_POFSAVE和SL_EEBUSY_POFSAVE
**-------------------------------------------------------------------------------------------------------
** 作　者:
** 日　期:
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
void EeCtrl(void)
{
	if(M_ChkFlag(SL_EE_FAIL)==0)					//EEPROM无故障?
	{
//----------------------------------------------//恢复出厂参数进行中
		if(M_ChkFlag(SL_EEBUSY_INI)!=0)			//RAM数据恢复初值
		{
			*FUNC[EEPROM.point].para_add=FUNC[EEPROM.point].init;	
			EeWrword(EEPROM.point);				//写入2字节数据
			EEPROM.point++;
			
			if(EEPROM.point>=PARA_NUM)			//操作完成?
			{
				EEPROM.point=0;
				M_ClrFlag(SL_EEBUSY_INI);
				M_ClrFlag(SL_EEASK_INI);
			}
		}
//----------------------------------------------//修改功能码进行中
		else if(M_ChkFlag(SL_EEBUSY_MCODE)!=0)
		{
			EeWrword(EEPROM.mcode);				//写入2字节数据
			M_ClrFlag(SL_EEBUSY_MCODE);
			M_ClrFlag(SL_EEASK_MCODE);
		}
//----------------------------------------------//保存故障信息进行中
		else if(M_ChkFlag(SL_EEBUSY_ERRSAVE)!=0)
		{
			EeWrword(TAB_ERR[EEPROM.point]);	//写入2字节数据
			EEPROM.point++;
			
			if(EEPROM.point>=ERRO_NUM)			//操作完成?
			{
				EEPROM.point=0;
				M_ClrFlag(SL_EEBUSY_ERRSAVE);
				M_ClrFlag(SL_EEASK_ERRSAVE);
			}
		}
//----------------------------------------------//是否存在保存掉电信息请求
/*
		else if(M_ChkFlag(SL_EEBUSY_POFSAVE)!=0)
		{
			EeWrword(TAB_POF[EEPROM.point]);	//写入2字节数据
			EEPROM.point++;
			
			if(EEPROM.point>=POFF_NUM)		//操作完成?
			{
				EEPROM.point=0;
				M_ClrFlag(SL_EEBUSY_POFSAVE);
				M_ClrFlag(SL_EEASK_POFSAVE);
			}
		}		
*/
//----------------------------------------------//EEPROM没有操作进行中
		else
		{
			EEPROM.point=0;
			if(M_ChkFlag(SL_EEASK_INI)!=0)			//是否存在恢复出厂参数请求
				M_SetFlag(SL_EEBUSY_INI);
			else if(M_ChkFlag(SL_EEASK_MCODE)!=0)	//是否存在修改功能码请求
				M_SetFlag(SL_EEBUSY_MCODE);
			else if(M_ChkFlag(SL_EEASK_ERRSAVE)!=0)	//是否存在保存故障信息请求
				{M_SetFlag(SL_EEBUSY_ERRSAVE);
//				     M_SetFlag(SL_PHASEA);          //测量Save占用时间,测量DSP板上T1端子 20090803
//    				*OUT3_ADDR = _OUT3_DATA;		//测量Save占用时间,测量DSP板上T1端子 20090803
				}
//			M_ClrFlag(SL_PHASEA);           //测量CPU占有率,测量DSP板上T1端子
//    		*OUT3_ADDR = _OUT3_DATA;		//测量Save占用时间,测量DSP板上T1端子 20090803



//			else if(M_ChkFlag(SL_EEASK_POFSAVE)!=0)	//是否存在保存掉电信息请求
//				M_SetFlag(SL_EEBUSY_POFSAVE);
		}
	}
}
/*********************************************************************************************************
** 函数名称: SetRtimer
** 功能描述: 实时时钟设定
** 输　入:
** 输　出:
** 注  释:
**-------------------------------------------------------------------------------------------------------
** 作　者:
** 日　期:
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
void SetRtimer(void)
{
	Uint16 temp;
	
//----------------------------------------------//写入时间值
	EEPROM.data[0]=0xDE;						//Slave ADdress
	EEPROM.data[1]=0;							//MSB ADdress
	EEPROM.data[2]=0x3F;						//LSB ADdress
	EEPROM.data[3]=0x02;						//STATUS register
	EeWrite(1);									//写允许
	
	EEPROM.data[0]=0xDE;						//Slave ADdress
	EEPROM.data[1]=0;							//MSB ADdress
	EEPROM.data[2]=0x3F;						//LSB ADdress
	EEPROM.data[3]=0x06;						//STATUS register
	EeWrite(1);									//写寄存器允许
	
	EEPROM.data[0]=0xDE;						//Slave ADdress
	EEPROM.data[1]=0;							//MSB ADdress
	EEPROM.data[2]=0x30;						//LSB ADdress
	
	temp=RTIMER.time[0]/10;
	EEPROM.data[3]=(RTIMER.time[0]-temp*10)|(temp<<4);	//秒
	
	
	temp=RTIMER.time[1]/10;
	EEPROM.data[4]=(RTIMER.time[1]-temp*10)|(temp<<4);	//分
	
	temp=RTIMER.time[2]/10;
	EEPROM.data[5]=0x80 | ((RTIMER.time[2]-temp*10)|(temp<<4));	//时
	
	temp=RTIMER.time[3]/10;
	EEPROM.data[6]=(RTIMER.time[3]-temp*10)|(temp<<4);	//日
	
	temp=RTIMER.time[4]/10;
	EEPROM.data[7]=(RTIMER.time[4]-temp*10)|(temp<<4);	//月
	
	temp=RTIMER.time[5]/10;
	EEPROM.data[8]=(RTIMER.time[5]-temp*10)|(temp<<4);	//年
	
	EEPROM.data[9]=0x05;						//星期
	EEPROM.data[10]=0x20;						//19/20
	EeWrite(8);									//写入时间值

	EEPROM.data[0]=0xDE;						//Slave ADdress
	EEPROM.data[1]=0;							//MSB ADdress
	EEPROM.data[2]=0x3F;						//LSB ADdress
	EEPROM.data[3]=0x0;							//STATUS register
	EeWrite(1);									//禁止写入
}
/*********************************************************************************************************
** 函数名称: RtRead
** 功能描述: 实时时钟读取
** 输　入:
** 输　出:   RTIMER.time[0~5]--[秒 分 时 日 月 年]
** 注  释:
**-------------------------------------------------------------------------------------------------------
** 作　者:
** 日　期:
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
void RtRead(void)
{
	Uint16 i;

	if(M_ChkFlag(SL_SETRTIMER)!=0)				//需要校正实时时钟?
	{
		SetRtimer();
		M_ClrFlag(SL_SETRTIMER);
	}
	else
	{
		//----------------------------------------------//读取时间值到data[0~7]
		EEPROM.data[0]=0xDE;						//Slave ADdress
		EEPROM.data[1]=0;							//MSB ADdress
		EEPROM.data[2]=0x30;						//LSB ADdress
		EeRead(8);
		//----------------------------------------------
		M_ClrBit(EEPROM.data[2],0x80);				//清除24小时设置位
	
		for(i=0;i<6;i++)
		{
			RTIMER.time[i]=((EEPROM.data[i] & 0xF0)>>4)*10+(EEPROM.data[i] & 0x0F);
		}
	}
}
/*********************************************************************************************************
** 函数名称: InitRtimer
** 功能描述: 实时时钟初始化
** 输　入:
** 输　出:
** 注  释: 	 只在实时时钟初始化的时候将需要设定的时间值设定到相应位置
**-------------------------------------------------------------------------------------------------------
** 作　者:
** 日　期:
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
void InitRtimer(void)
{
//----------------------------------------------//写入控制字
	EEPROM.data[0]=0xDE;						//Slave ADdress
	EEPROM.data[1]=0;							//MSB ADdress
	EEPROM.data[2]=0x3F;						//LSB ADdress
	EEPROM.data[3]=0x0;							//STATUS register
	EeWrite(1);									//禁止写入

	EEPROM.data[0]=0xDE;						//Slave ADdress
	EEPROM.data[1]=0;							//MSB ADdress
	EEPROM.data[2]=0x3F;						//LSB ADdress
	EEPROM.data[3]=0x02;						//STATUS register
	EeWrite(1);									//写允许

	EEPROM.data[0]=0xDE;						//Slave ADdress
	EEPROM.data[1]=0;							//MSB ADdress
	EEPROM.data[2]=0x3F;						//LSB ADdress
	EEPROM.data[3]=0x06;						//STATUS register
	EeWrite(1);									//写寄存器允许

	EEPROM.data[0]=0xDE;						//Slave ADdress
	EEPROM.data[1]=0;							//MSB ADdress
	EEPROM.data[2]=0x10;						//LSB ADdress
	EEPROM.data[3]=0x0;							//Control register 0
	EEPROM.data[4]=0x0;							//Control register 1
	EEPROM.data[5]=0x0;							//Control register 2
	EEPROM.data[6]=0x0;							//Control register 3
	EeWrite(4);									//写入4字节控制字
	
	DELAY_US(10000L);							//延时10ms

//----------------------------------------------//写入时间值
	EEPROM.data[0]=0xDE;						//Slave ADdress
	EEPROM.data[1]=0;							//MSB ADdress
	EEPROM.data[2]=0x3F;						//LSB ADdress
	EEPROM.data[3]=0x0;							//STATUS register
	EeWrite(1);									//禁止写入

	EEPROM.data[0]=0xDE;						//Slave ADdress
	EEPROM.data[1]=0;							//MSB ADdress
	EEPROM.data[2]=0x3F;						//LSB ADdress
	EEPROM.data[3]=0x02;						//STATUS register
	EeWrite(1);									//写允许
	
	EEPROM.data[0]=0xDE;						//Slave ADdress
	EEPROM.data[1]=0;							//MSB ADdress
	EEPROM.data[2]=0x3F;						//LSB ADdress
	EEPROM.data[3]=0x06;						//STATUS register
	EeWrite(1);									//写寄存器允许
	
	EEPROM.data[0]=0xDE;						//Slave ADdress
	EEPROM.data[1]=0;							//MSB ADdress
	EEPROM.data[2]=0x30;						//LSB ADdress
	EEPROM.data[3]=0;							//秒
	EEPROM.data[4]=0x00;						//分
	EEPROM.data[5]=0x80 | 0x00;					//时(0x80指的是24小时模式)
	EEPROM.data[6]=0x15;						//日
	EEPROM.data[7]=0x04;						//月
	EEPROM.data[8]=0x09;						//年
	EEPROM.data[9]=0x05;						//星期
	EEPROM.data[10]=0x20;						//19/20
	EeWrite(8);									//写入时间值

	EEPROM.data[0]=0xDE;						//Slave ADdress
	EEPROM.data[1]=0;							//MSB ADdress
	EEPROM.data[2]=0x3F;						//LSB ADdress
	EEPROM.data[3]=0x0;							//STATUS register
	EeWrite(1);									//禁止写入
	
//----------------------------------------------//读取时间值到data[0~7]
	EEPROM.data[0]=0xDE;						//Slave ADdress
	EEPROM.data[1]=0;							//MSB ADdress
	EEPROM.data[2]=0x30;						//LSB ADdress
	EeRead(8);
}

/*********************************************************************************************************
** 函数名称: CRC-16
** 功能描述:计算数据流* pData的16位CRC校验码，数据流长度为nLength
** 输　入:
** 输　出:
** 注  释:
**-------------------------------------------------------------------------------------------------------
** 作　者:
** 日　期:
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
const unsigned char auchCRCHi[] =
{
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,0x40, 0x01, 
	0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
	0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 
	0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 
	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 
	0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 
	0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 
	0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 
	0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 
	0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 
	0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 
	0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 
	0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
	0x40
} ;

const unsigned  char auchCRCLo[] = 
{
	0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 
	0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8, 0xD8, 0x18, 
	0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 
	0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3, 0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 
	0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 
	0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 
	0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 
	0x26, 0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 
	0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE, 0xAA, 
	0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 
	0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5, 0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 
	0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 
	0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 
	0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 
	0x4C, 0x8C, 0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,
	0x40
} ;

/*********************************************************************************************************
** 函数名称: CRC-16
** 功能描述:计算数据流* pData的16位CRC校验码，数据流长度为nLength
** 输　入:
** 输　出:
** 注  释:
**-------------------------------------------------------------------------------------------------------
** 作　者:
** 日　期:
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
unsigned short GetCrc_16(unsigned int *puchMsg , unsigned int usDataLen)
{
   unsigned char uchCRCHi = 0xFF ;    		/* high byte of CRC initialized */
   unsigned char uchCRCLo = 0xFF ;		 /* low byte of CRC initialized */
   unsigned uIndex ; 					/* will index into CRC lookup table */
   while (usDataLen--)				/* pass through message buffer */
   {
     uIndex = uchCRCHi ^ *puchMsg++ ; 				/* calculate the CRC */
     uchCRCHi = uchCRCLo ^ auchCRCHi[uIndex];
     uchCRCLo = auchCRCLo[uIndex] ;
   }
  return (uchCRCLo << 8 | uchCRCHi) ;
}

/*********************************************************************************************************
** 函数名称: Sci485_TxInit
** 功能描述: 485发送初始化
** 输　入:
** 输　出:
** 注  释:
**-------------------------------------------------------------------------------------------------------
** 作　者:
** 日　期:
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
void Sci485_TxInit(void)
{
	Uint32 temp32;
	Uint16 temp16;
	
	M_EN485TXD();
	M_EnTxb();
	temp32=LSPCLK/8;
	temp16=temp32/_SCIB_BAUD-1;				// LSPCLK/(8*BAUD)-1
//----------------------------------------------------------------------------
	ScibRegs.SCIFFTX.all=0xC000;			// Reset TX FIFO's
	ScibRegs.SCICCR.all = 0x0007;			// 1 stop bit, No parity, 8-bit character, No loopback
	
	ScibRegs.SCIHBAUD = (temp16&0xFF00)>>8;	// BAUDRATE
	ScibRegs.SCILBAUD = temp16&0x00FF;
	
	ScibRegs.SCIFFTX.bit.TXFIFOXRESET=1;	// Re-enable TX FIFO operation
	
	ScibRegs.SCICTL1.all =0x0022;     		// Relinquish SCI from Reset
//----------------------------------------------------------------------------
}
/*********************************************************************************************************
** 函数名称: Sci485_RxInit
** 功能描述: 485接收初始化
** 输　入:
** 输　出:
** 注  释:
**-------------------------------------------------------------------------------------------------------
** 作　者:
** 日　期:
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
void Sci485_RxInit(void)
{
	Uint16 temp16;			//20100727加入波特率设定
	Uint32 temp32;

//----------------------------------------------------------------------------
	M_EN485RXD();
	M_EnRxb();
	
	temp32=LSPCLK/8;
	temp16=temp32/_SCIB_BAUD-1;				// LSPCLK/(8*BAUD)-1	
	ScibRegs.SCIHBAUD = (temp16&0xFF00)>>8;	// BAUDRATE
	ScibRegs.SCILBAUD = temp16&0x00FF;
//----------------------------------------------------------------------------

	ScibRegs.SCIFFRX.all=0x000A;			//   different!!!Reset RX FIFO's//RXFFIL4--0: Receive FIFO interrupt level ==10	
	ScibRegs.SCIFFRX.bit.RXFIFORESET=1;		// Receive FIFO reset :Re-enable RX FIFO operation
	
	M_ClrRxFifoOvr();
	
	ScibRegs.SCICTL1.all =0x0021;     		// Relinquish SCI from Reset //bit5:SCI software reset
//----------------------------------------------------------------------------
}


/*********************************************************************************************************
** 函数名称: READSTATE
** 功能描述: 读取变流器状态-开关量
** 输　入:
** 输　出:
** 注  释:
**-------------------------------------------------------------------------------------------------------
** 作　者:
** 日　期:
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
void READSTATE(void)
{
//----------------------------------------------------------------------------
//----COMMAND1------------------------------------------------------------------
	if(M_ChkFlag(SL_ENPCOPER)!=0)	  	_COMMAND1 |= 0x0001;	//0 PC控制使能   0-CAN控制
	else								_COMMAND1 &= 0xFFFE;
	if(M_ChkFlag(SL_OPERATION)!=0)	  	_COMMAND1 |= 0x0002;	//1 运行模式选择 0-背靠背运行
	else								_COMMAND1 &= 0xFFFD;
	if(M_ChkFlag(SL_OCS_EIN)!=0)	  	_COMMAND1 |= 0x0004;	//2 主断路器控制指令CAN模式下使用
	else								_COMMAND1 &= 0xFFFB;
	if(M_ChkFlag(SL_OCS_SYSRUN)!=0)	  	_COMMAND1 |= 0x0008;	//3 同步并网指令CAN模式下使用
	else								_COMMAND1 &= 0xFFF7;
	if(M_ChkFlag(SL_OCS_PREC)!=0)	  	_COMMAND1 |= 0x0010;	//4 预充电指令PC模式下使用
	else								_COMMAND1 &= 0xFFEF;
	if(M_ChkFlag(SL_OCS_NPRSTART)!=0)	_COMMAND1 |= 0x0020;	//5 网侧变流器启动PC模式下使用
	else								_COMMAND1 &= 0xFFDF;
	if(M_ChkFlag(SL_OCS_MPRSTART)!=0)	_COMMAND1 |= 0x0040;	//6 机侧变流器启动PC模式下使用
	else								_COMMAND1 &= 0xFFBF;
	if(M_ChkFlag(SL_OCS_OPENSTAC)!=0)	_COMMAND1 |= 0x0080;	//7 定子接触器控制指令PC模式下使用
	else								_COMMAND1 &= 0xFF7F;
	if(M_ChkFlag(SL_OCS_RESET)!=0)		_COMMAND1 |= 0x0100;	//8 变流器故障复位指令CAN/PC模式下使用
	else								_COMMAND1 &= 0xFEFF;
	if(M_ChkFlag(SL_PC_ERRDATASAVE)!=0)	_COMMAND1 |= 0x0200;	//9 外部RAM锁存故障数据指令
	else								_COMMAND1 &= 0xFDFF;
	if(M_ChkFlag(SL_PC_ERRDATACLR)!=0)	_COMMAND1 |= 0x0400;	//10 外部RAM释放故障数据指令
	else								_COMMAND1 &= 0xFBFF;
	if(M_ChkFlag(SL_PC_BANKDATASAVE)!=0)_COMMAND1 |= 0x0800;	//11 外部RAM锁存显示数据指令
	else								_COMMAND1 &= 0xF7FF;
	if(M_ChkFlag(SL_PCOCS_CBOFF)!=0)	_COMMAND1 |= 0x1000;	//12 指令PC模式下使用 PC控制手动断开CB 1=断开 2010atcpc
	else								_COMMAND1 &= 0xEFFF;

	
//----STATE1------------------------------------------------------------------
	if(M_ChkFlag(SL_RUN)!=0)	  		_STATE1 |= 0x0001;	//变流器发脉冲运行
	else								_STATE1 &= 0xFFFE;
	if(M_ChkFlag(SL_ERROR)!=0)	  		_STATE1 |= 0x0002;	//变流器处于故障
	else								_STATE1 &= 0xFFFD;
	if(M_ChkFlag(SL_CBCLOSED)!=0)	  	_STATE1 |= 0x0004;	//主断路器闭合完成
	else								_STATE1 &= 0xFFFB;
	if(M_ChkFlag(SL_CHARGEOK)!=0)	  	_STATE1 |= 0x0008;	//预充电完成
	else								_STATE1 &= 0xFFF7;
	if(M_ChkFlag(SL_NPR_PWMOUT)!=0)	  	_STATE1 |= 0x0010;	//网侧变流器运行
	else								_STATE1 &= 0xFFEF;
	if(M_ChkFlag(SL_STEADYFB)!=0)	  	_STATE1 |= 0x0020;	//中间直流电压稳定
	else								_STATE1 &= 0xFFDF;
	if(M_ChkFlag(SL_MPR_PWMOUT)!=0)	  	_STATE1 |= 0x0040;	//机侧变流器运行
	else								_STATE1 &= 0xFFBF;
	if(M_ChkFlag(SL_MPR_SYNOK)!=0)	  	_STATE1 |= 0x0080;	//定子侧同步并网完成
	else								_STATE1 &= 0xFF7F;
	if(M_ChkFlag(SL_SPEED_IN_RANGE)!=0)	_STATE1 |= 0x0100;	//电机转速在运行范围内
	else								_STATE1 &= 0xFEFF;
	if(M_ChkFlag(SL_RAMERRORSAVE)!=0)	_STATE1 |= 0x0200;	//外部RAM故障信息完成存储标志
	else								_STATE1 &= 0xFDFF;
	if(M_ChkFlag(SL_RAMBANKSAVE)!=0)	_STATE1 |= 0x0400;	//外部RAM显示信息锁存标志
	else								_STATE1 &= 0xFBFF;
//----MagnetCurve2013-12-13
	if(M_ChkFlag(SL_MC_OK)!=0)			_STATE1 |= 0x0800;	//励磁曲线MagnetCurve200909
	else								_STATE1 &= 0xF7FF;
	if(M_ChkFlag(SL_MC_FAIL)!=0)		_STATE1 |= 0x1000;	//励磁曲线MagnetCurve200909
	else								_STATE1 &= 0xEFFF;

//----DISPLAY------------------------------------------------------------------
	if(M_ChkFlag(SL_DISPLAY0)!=0)	  	_DISPLAY |= 0x0001;	//网侧变流器运行
	else								_DISPLAY &= 0xFFFE;
	if(M_ChkFlag(SL_DISPLAY1)!=0)	  	_DISPLAY |= 0x0002;	//机侧变流器运行
	else								_DISPLAY &= 0xFFFD;
	if(M_ChkFlag(SL_DISPLAY2)!=0)	  	_DISPLAY |= 0x0004;	//中间直流电压稳定
	else								_DISPLAY &= 0xFFFB;
	if(M_ChkFlag(SL_DISPLAY3)!=0)	  	_DISPLAY |= 0x0008;	//严重故障
	else								_DISPLAY &= 0xFFF7;
	if(M_ChkFlag(SL_DISPLAY4)!=0)	  	_DISPLAY |= 0x0010;	//定子侧达到同步并网条件
	else								_DISPLAY &= 0xFFEF;
	if(M_ChkFlag(SL_DISPLAY5)!=0)	  	_DISPLAY |= 0x0020;	//故障
	else								_DISPLAY &= 0xFFDF;
	if(M_ChkFlag(SL_DISPLAY6)!=0)	  	_DISPLAY |= 0x0040;	//LVRT晶闸管开通指示
	else								_DISPLAY &= 0xFFBF;
	if(M_ChkFlag(SL_DISPLAY7)!=0)	  	_DISPLAY |= 0x0080;	//等待预充电指令指示
	else								_DISPLAY &= 0xFF7F;
			
//----IO/INPUT------------------------------------------------------------------
	if(M_ChkFlag(SL_IN1_CBSTS)!=0)	  	_INPUT |= 0x0001;	//P4.1主断路器状态反馈：	1=闭合；0=断开
	else								_INPUT &= 0xFFFE;
	if(M_ChkFlag(SL_IN1_CBRESET)!=0)	_INPUT |= 0x0002;	//P4.2主控正在复位主断路器：1=复位；0=未复位
	else								_INPUT &= 0xFFFD;
	if(M_ChkFlag(SL_IN1_STATORK)!=0)	_INPUT |= 0x0004;	//P4.3定子接触器状态反馈：	1=闭合；0=断开
	else								_INPUT &= 0xFFFB;
	if(M_ChkFlag(SL_IN1_MIANK)!=0)	  	_INPUT |= 0x0008;	//P4.4主接触器状态反馈：	1=闭合；0=断开
	else								_INPUT &= 0xFFF7;
	if(M_ChkFlag(SL_IN1_MIANFILTER)!=0)	_INPUT |= 0x0010;	//P4.5主滤波器状态反馈：	1=闭合；0=断开
	else								_INPUT &= 0xFFEF;
	if(M_ChkFlag(SL_IN1_EXFAULTOK)!=0)	_INPUT |= 0x0020;	//P4.6外部故障链状态反馈：	1=正常，0=故障
	else								_INPUT &= 0xFFDF;
	if(M_ChkFlag(SL_IN1_MIANFAN)!=0)	_INPUT |= 0x0040;	//P4.7功率风机状态反馈：	1=正常，0=故障
	else								_INPUT &= 0xFFBF;
	if(M_ChkFlag(SL_IN1_EXESTOP)!=0)	_INPUT |= 0x0080;	//P4.8外部急停故障反馈： 	1=急停按钮按下，0=急停按钮拔起
	else								_INPUT &= 0xFF7F;
	if(M_ChkFlag(SL_IN3_CBTRIP)!=0)		_INPUT |= 0x0100;	//P4.9主断过流脱扣故障反馈：1=故障；0=正常
	else								_INPUT &= 0xFEFF;

//----IO/OUTPUT------------------------------------------------------------------
	if(M_ChkFlag(CL_CBLVC)!=0)	  		_OUTPUT |= 0x0001;	//P5.5主断路器欠压链开关指令：	1=闭合；0=断开
	else								_OUTPUT &= 0xFFFE;
	if(M_ChkFlag(CL_CBON)!=0)	  		_OUTPUT |= 0x0002;	//P5.6主断路器合闸指令：		1=合闸
	else								_OUTPUT &= 0xFFFD;
	if(M_ChkFlag(CL_PRE)!=0)	  		_OUTPUT |= 0x0004;	//P5.7预充电指令：				1=预充电；0=禁止预充电
	else								_OUTPUT &= 0xFFFB;
	if(M_ChkFlag(CL_MAINK)!=0)	  		_OUTPUT |= 0x0008;	//P5.8主接触器和滤波器器指令：	1=闭合；0=断开
	else								_OUTPUT &= 0xFFF7;
	if(M_ChkFlag(CL_STATORK)!=0)	  	_OUTPUT |= 0x0010;	//P5.9定子接触器指令：			1=闭合；0=断开
	else								_OUTPUT &= 0xFFEF;
	if(M_ChkFlag(CL_CBFCON)!=0)	  		_OUTPUT |= 0x0020;	//P5.10主断路器欠压链控制，		1=闭合；0=断开
	else								_OUTPUT &= 0xFFDF;
	if(M_ChkFlag(CL_FANWORK)!=0)	  	_OUTPUT |= 0x0040;	//P5.11功率风扇控制：			1=运行；0=停止
	else								_OUTPUT &= 0xFFBF;

//----LVRT------------------------------------------------------------------
	if(M_ChkFlag(SL_LV_MSTOP)!=0)	  	_LVRT |= 0x0001;	//
	else								_LVRT &= 0xFFFE;
	if(M_ChkFlag(SL_LV_NSTOP)!=0)	  	_LVRT |= 0x0002;	//
	else								_LVRT &= 0xFFFD;
	if(M_ChkFlag(SL_LV_SCRON)!=0)	  	_LVRT |= 0x0004;	//
	else								_LVRT &= 0xFFFB;
	if(M_ChkFlag(SL_LV_SCRRUNING)!=0)	_LVRT |= 0x0008;	//
	else								_LVRT &= 0xFFF7;
	if(M_ChkFlag(SL_LV_SCRIZERO)!=0)	_LVRT |= 0x0010;	//
	else								_LVRT &= 0xFFEF;
	if(M_ChkFlag(SL_LV_MPWMOUT)!=0)	    _LVRT |= 0x0020;	//
	else								_LVRT &= 0xFFDF;
	if(M_ChkFlag(SL_LV_STATE)!=0)	  	_LVRT |= 0x0040;	//
	else								_LVRT &= 0xFFBF;
//----------------------------------------------------------------------------
}

/*********************************************************************************************************
** 函数名称: WRCOMMAND
** 功能描述: 写入变流器指令-开关量
** 输　入:
** 输　出:
** 注  释:
**-------------------------------------------------------------------------------------------------------
** 作　者:
** 日　期:
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
void WRCOMMAND(void)
{
//----------------------------------------------------------------------------
 	if(M_ChkFlag(SL_ENPCOPER)!=0)		
 	{
		if((_COMMAND1&0x0002)!=0)	M_SetFlag(SL_OPERATION);
		else						M_ClrFlag(SL_OPERATION);
		if(((_COMMAND1&0x0004)!=0) && (M_ChkFlag(SL_ERROR)==0))	//201005atcpc
		{
	 		if(M_ChkCounter(MAIN_LOOP.cnt_ein,DELAY_EIN)>0)	M_SetFlag(SL_OCS_EIN);     		//延时1s，防止误操作
		}
		else 	
		{
			M_ClrFlag(SL_OCS_EIN);              
			MAIN_LOOP.cnt_ein=0;		
    	}
     
		if(((_COMMAND1&0x0008)!=0) && (M_ChkFlag(SL_ERROR)==0))		//201005atcpc					
		{ 
	  		if(M_ChkCounter(MAIN_LOOP.cnt_sysrun,DELAY_SYSRUN)>0)	 M_SetFlag(SL_OCS_SYSRUN); //延时1s，防止误操作
		}				
		else 	
		{
			M_ClrFlag(SL_OCS_SYSRUN);
			MAIN_LOOP.cnt_sysrun=0;		
    	}
	
		if(((_COMMAND1&0x0010)!=0) && (M_ChkFlag(SL_ERROR)==0))		//201005atcpc					
		{ 
	  		if(M_ChkCounter(MAIN_LOOP.cnt_prec,DELAY_PREC)>0)	 M_SetFlag(SL_OCS_PREC); //延时1s，防止误操作
		}				
		else 	
		{
			M_ClrFlag(SL_OCS_PREC);
			MAIN_LOOP.cnt_prec=0;		
   		} 

		if(((_COMMAND1&0x0020)!=0) && (M_ChkFlag(SL_ERROR)==0))		//201005atcpc					
		{ 
	  		if(M_ChkCounter(MAIN_LOOP.cnt_nprcmd,DELAY_NPRCMD)>0)	 M_SetFlag(SL_OCS_NPRSTART); //延时1s，防止误操作
		}				
		else 	
		{
			M_ClrFlag(SL_OCS_NPRSTART);
			MAIN_LOOP.cnt_nprcmd=0;		
    	} 

		if(((_COMMAND1&0x0040)!=0) && (M_ChkFlag(SL_ERROR)==0))		//201005atcpc					
		{ 
	  		if(M_ChkCounter(MAIN_LOOP.cnt_mprcmd,DELAY_MPRCMD)>0)	 M_SetFlag(SL_OCS_MPRSTART); //延时1s，防止误操作
		}				
		else 	
		{
			M_ClrFlag(SL_OCS_MPRSTART);
			MAIN_LOOP.cnt_mprcmd=0;		
    	} 

		if((_COMMAND1&0x0080)!=0)							
		{ 
	  		if(M_ChkCounter(MAIN_LOOP.cnt_clostacmd,DELAY_CLOSTACMD)>0)	 M_SetFlag(SL_OCS_OPENSTAC); //延时1s，防止误操作
		}				
		else 	
		{
			M_ClrFlag(SL_OCS_OPENSTAC);
			MAIN_LOOP.cnt_clostacmd=0;		
    	} 

		if((_COMMAND1&0x0100)!=0)																	//上位机要求复位故障,由外部I/O给定
		{ 
	  		if(M_ChkCounter(MAIN_LOOP.cnt_reset,DELAY_RESET)>0)	 M_SetFlag(SL_OCS_RESET);     		//延时2s，防止误操作
		}				
		else 	
		{
			M_ClrFlag(SL_OCS_RESET);
			MAIN_LOOP.cnt_reset=0;		
    	}	
    	
		if((_COMMAND1&0x1000)!=0)	M_SetFlag(SL_PCOCS_CBOFF);	 //12 指令PC模式下使用 PC控制手动断开CB 1=断开 2010atcpc
		else						M_ClrFlag(SL_PCOCS_CBOFF);
   	}

	if((_COMMAND1&0x0200)!=0)	M_SetFlag(SL_PC_ERRDATASAVE);	 //9 外部RAM锁存故障数据指令PC/CAN模式下都可使用
	else						M_ClrFlag(SL_PC_ERRDATASAVE);	
	if((_COMMAND1&0x0400)!=0)	M_SetFlag(SL_PC_ERRDATACLR);	 //10 外部RAM释放故障数据指令PC/CAN模式下都可使用
//	else						M_ClrFlag(SL_PC_ERRDATACLR);
	else if(M_ChkFlag(SL_LV_CLRERRAM)==0)			M_ClrFlag(SL_PC_ERRDATACLR);		//20130306
//	if((_COMMAND1&0x0800)!=0)	M_SetFlag(SL_PC_BANKDATASAVE);	 //11 外部RAM锁存显示数据指令PC/CAN模式下都可使用
//	else						M_ClrFlag(SL_PC_BANKDATASAVE);

//20130724
	if((_COMMAND1&0x0800)!=0)
	{
		M_SetFlag(SL_PC_BANKDATASAVE);
		M_SetFlag(SL_TRIG_ERRDSAVE);	 //11 外部RAM锁存显示数据指令PC/CAN模式下都可使用
	}
	else						M_ClrFlag(SL_PC_BANKDATASAVE);

//----------------------------------------------------------------------------
}

/*********************************************************************************************************
** 函数名称: ScibDatpro
** 功能描述: 对sci接收到的数据进行解析校验
** 输　入:
** 输　出:   response=0表示需要不需要回复;response=1表示需要立即回复;response=2表示不立即回复,进程完后再回复(如恢复出厂参数)
** 注  释: 	 通信协议说明如下
				SCI.rxb[0]:报头(0x7E)
				SCI.rxb[1]:下位机地址
				SCI.rxb[2]:命令字(低字节)
				SCI.rxb[3]:命令字(高字节)
				SCI.rxb[4]:功能码序号
				SCI.rxb[5]:功能码数值(低字节)
				SCI.rxb[6]:功能码数值(高字节)
				SCI.rxb[7]:状态字(低字节)
				SCI.rxb[8]:状态字(高字节)
				SCI.rxb[9]:异或校验
**-------------------------------------------------------------------------------------------------------
** 作　者:
** 日　期:
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
Uint16 ScibDatpro(void)
{
	Uint16 response,i,j;
	Uint16 rx_command,rx_startnum,rx_opernum,rx_crc,cRc_16;
	Uint16 rx_ramwavenum,rx_ramsegstart,error_pos,bank_pos;
	
	
//------------------------------------------------------------------------------------------------		
		if(SCI.rxb[0]!=_SCIB_ADDR)	//上位机&节点地址不符,并非操作器发的数据
			response=0;				//不进行处理回复,等待下一帧数据
		
		else							//操作器控制或上位机控制且节点地址相符
		{
			SCI.txb[0] = SCI.rxb[0];								//下位机地址字节
			SCI.txb[1] = SCI.rxb[1];
			
			rx_crc=SCI.rxb[7];										//保存校验和1个字16位
			rx_crc=((rx_crc<<8)&0xFF00)|SCI.rxb[6];					//[6][7]two words

			length485=SCI485NUM_RX-2;
            cRc_16=GetCrc_16(&SCI.rxb[0],length485);				//CRC校验
           
            if(rx_crc!=cRc_16)
              response=0;	
           
            else
            {
                response=1;
				
				//接收数据转存
				rx_command=SCI.rxb[1];							//保存命令字
				
				rx_startnum=SCI.rxb[2];							//保存功能码序号
				rx_startnum=((rx_startnum<<8)&0xFF00)|SCI.rxb[3];
			    
				rx_opernum=SCI.rxb[4];							//保存功能码值
				rx_opernum=((rx_opernum<<8)&0xFF00)|SCI.rxb[5];
				
				//命令字�

				switch (rx_command&0xFFFF)					//命令解析???跟FFFF做与运算没有作用啊？？？
				{
//--------------------NO.1--READ------
					case COM_RDAO:		//读模拟量
					{
						 if((rx_startnum+rx_opernum)>PARA_NUM)
                              response=0;
						 
						 else
						 {
						    
						    j=0; 
							READSTATE();							    
							for(i=rx_startnum;i<(rx_startnum+rx_opernum);i++)
                            {
								SCI.txb[3+j]=(*FUNC[i].para_add&0xFF00)>>8; //201005atcpc 保证能与CAN同时通讯
								SCI.txb[4+j]=(*FUNC[i].para_add)&0x00FF;	//直接将RAM中的数据发送
								j++;
								j++; 
							}

							SCI.txb[2]=rx_opernum * 2;
							length485=SCI.txb[2]+3;
						
						    cRc_16=GetCrc_16(&SCI.txb[0],length485);
						
							SCI.txb[length485+1]=(cRc_16&0xFF00)>>8;  //-------------------------
							SCI.txb[length485]=cRc_16&0x00FF;
						   
						    length485=length485+2;
						}	
							
					break;
					}

//---------------------NO.3--WRITE A--------
					case COM_WRAO:			//写模拟量
					{		
							 if(rx_startnum>PARA_NUM)
                               response=0;
						     
						     else
					         {
					        	if((((FUNC[rx_startnum].attr&WR1)==0)&&((FUNC[rx_startnum].attr&WR0)==0)&&((FUNC[rx_startnum].attr&WR3)==0))||(((FUNC[rx_startnum].attr&WR1)==WR1)&&(M_ChkFlag(SL_RUN)!=0)))//非写操作或运行中不可修
									response=0;						//置操作失败标志

								else
								{
					        		if((FUNC[rx_startnum].attr&WR3)==WR3)//属于只修改RAM数据的写类型
					        		{
								   		*FUNC[rx_startnum].para_add=rx_opernum;	//修改RAM里的值

					        			if(M_ChkFlag(SL_RUN)==0)			//运行中不允许修改控制模式201005atcpc
										{
					        				if((_COMMAND1&0x0001)!=0)	M_SetFlag(SL_ENPCOPER);
											else						M_ClrFlag(SL_ENPCOPER);	
										}
					        			
					        			WRCOMMAND();	//只有使能了PCOPER之后才允许修改其它量
					        		}
					        		else
					        		{
								   		*FUNC[rx_startnum].para_add=rx_opernum;	//修改RAM和EEROM
								
										EEPROM.mcode=rx_startnum;			//写入2字节数据
										M_SetFlag(SL_EEASK_MCODE);			//设EEPROM修改功能码请求标志
					        		}   
																	
									if((rx_startnum>=TIME_FIRST)&&(rx_startnum<=TIME_END))
										M_SetFlag(SL_SETRTIMER);			//置实时时钟需要重新设定标志
								
									SCI.txb[2]=SCI.rxb[2];					//准备发送数据(操作成功)
									SCI.txb[3]=SCI.rxb[3];
									SCI.txb[4]=SCI.rxb[4];
									SCI.txb[5]=SCI.rxb[5];
							   		
							    	length485=6;
									cRc_16=GetCrc_16(&SCI.txb[0],length485);
								
									SCI.txb[7]=(cRc_16&0xFF00)>>8;  
					        		SCI.txb[6]=cRc_16&0x00FF;
                                
                               	 	length485=length485+2;
								}
							}	
					break;
					}

//--------------------NO.3--READ exRAM------
					case COM_RDRAM:		//读exRAM
						   
						 if((rx_startnum+rx_opernum)>PARA_NUM)
                              response=0;
						 
						 else
						 {						    
						    j=0; 
						    i=0;
							rx_ramwavenum = rx_startnum;									//0-49代表数据波形,50为故障时刻数据 201005atcpc
							rx_ramsegstart = rx_opernum * RAM_SEGMENT;						//本次波形段传输开始数据地址 0-(n-1)
							 
							if(rx_ramwavenum<25)											//BANK_RAM:0-24
							{
								bank_pos = BANK_RAMDATA_POS + rx_ramsegstart;				//本次波形段传输开始数据地址+该波形的初始地址
								if(bank_pos >= RAM_BIAS)  bank_pos=bank_pos-RAM_BIAS;		//error_pos=0-3999
								
								for(i=0;i<RAM_SEGMENT;i++)
								{
									SCI.txb[8+j]=(*(BANK_RAMSTART+((Uint32)RAM_BIAS * rx_ramwavenum + bank_pos))&0xFF00)>>8;
									SCI.txb[9+j]=(*(BANK_RAMSTART+((Uint32)RAM_BIAS * rx_ramwavenum + bank_pos)))&0x00FF;				
									j++;
									j++; 									
									bank_pos++;
									if(bank_pos >= RAM_BIAS)  bank_pos=0;					//bank_pos=0-3999
								}								
							}
							else if(rx_ramwavenum<50)										//ERROR_RAM:25-49 2010atcpc
							{								
								error_pos = ERROR_RAMDATA_POS + rx_ramsegstart;				//本次波形段传输开始数据地址+该波形的初始地址
								if(error_pos >= RAM_BIAS)  error_pos=error_pos-RAM_BIAS;	//error_pos=0-3999
								
								for(i=0;i<RAM_SEGMENT;i++)
								{
									SCI.txb[8+j]=(*(ERROR_RAMSTART+((Uint32)RAM_BIAS * (rx_ramwavenum-25) + error_pos))&0xFF00)>>8;
									SCI.txb[9+j]=(*(ERROR_RAMSTART+((Uint32)RAM_BIAS * (rx_ramwavenum-25) + error_pos)))&0x00FF;				
									j++;
									j++; 									
									error_pos++;
									if(error_pos >= RAM_BIAS)  error_pos=0;					//error_pos=0-3999
								}																
							}

							SCI.txb[2]=SCI.rxb[2];
							SCI.txb[3]=SCI.rxb[3];
							SCI.txb[4]=SCI.rxb[4];
							SCI.txb[5]=SCI.rxb[5];
							
//							SCI.txb[6]=((RAM_SEGMENT * 2)&0xFF00)>>8;
//							SCI.txb[7]=(RAM_SEGMENT * 2)&0x00FF;
							SCI.txb[6]=(j&0xFF00)>>8;
							SCI.txb[7]=j&0x00FF;
						
							length485=j+8;						
//							length485=RAM_SEGMENT * 2+8;						
						    cRc_16=GetCrc_16(&SCI.txb[0],length485);
						
							SCI.txb[length485+1]=(cRc_16&0xFF00)>>8;  
							SCI.txb[length485]=cRc_16&0x00FF;
						   
						    length485=length485+2;						//+CRC_16 2bits
						}								
					break;

					default:
					response=0;
				}
		    }
		}
	return response; 

}

/*********************************************************************************************************
** 函数名称: Sci485Ctrl
** 功能描述: 对sci的接收发送进行综合控制
** 输　入:
** 输　出:
** 注  释:
**-------------------------------------------------------------------------------------------------------
** 作　者:
** 日　期:
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
void Sci485Ctrl(void)
{
	Uint16 i,j,response;

	if(M_ChkCounter(SCI.cnt_sciover,DELAY_SCIOVER)>=0)				//发送/接收超时?
	{
		SCI.cnt_sciover=0;
		M_ClrFlag(SL_TX);
		M_ClrFlag(SL_RX);
		Sci485_RxInit();											//485接收初始化
	}
	else if(M_ChkFlag(SL_TX)!=0)									//发送?
	{
		if(M_ChkFlag(SL_TXLONGDATA)==0)								//发送数据完成?
		{
			if(ScibRegs.SCIFFTX.bit.TXFFST == 0)						//发送完成?Transmit FIFO is empty.
			{
				SCI.cnt_sciover=0;										//清除发送/接收超时定时器
				if(ScibRegs.SCICTL2.bit.TXEMPTY==1)						//发送寄存器为空?Transmitter buffer and shift registers are both empty
		 		{
					M_ClrFlag(SL_TX);
					Sci485_RxInit();									//485接收初始化
				}
			}
		}
	}
	else															//接收
	{
		if(ScibRegs.SCIFFRX.bit.RXFFST == 0)						//未开始接收或接收完成?
		{
			SCI.cnt_sciover=0;										//清除发送/接收超时定时器
			M_ClrRxFifoOvr();
			
			if(M_ChkFlag(SL_RX)!=0)									//接收完成?
			{
				if(M_ChkCounter(SCI.cnt_scispace,DELAY_SCISPACE)>=0)//接收到发送间隔到时?
	    		{
					if(M_ChkFlag(SL_RESUME)!=0)						//恢复出厂参数进行中?
					{
						if(M_ChkFlag(SL_EEASK_INI)==0)				//EEPROM修改功能码操作完成?
						{
							M_ClrFlag(SL_RESUME);					//清恢复出厂参数进行中标志
							M_SetFlag(SL_TX);						//置发挝癖曛疚�
							M_ClrFlag(SL_RX);
							
							Sci485_TxInit();						//485发送初始化
							
//							for(i=0;i<length485;i++)				//different here!!!change
//							ScibRegs.SCITXBUF=SCI.txb[i];
							j=0;
							for(i=0;i<length485;i=j)				//have corected
							{                               
								if(ScibRegs.SCICTL2.bit.TXRDY==1)
								{
//									DELAY_US(150);
									ScibRegs.SCITXBUF=SCI.txb[i];
									j++;
								}
							}												
						}
					}
					else
					{
						response=ScibDatpro();						//调用数据解析程序
						
						if(response==1)								//表示要立即回复
						{
//							M_SetFlag(SL_TX);						//置发送任务标志位
							M_ClrFlag(SL_RX);
							
							Sci485_TxInit();						//485发送初始化
							
							if(length485<=16)
							{
								for(i=0;i<length485;i++)
									ScibRegs.SCITXBUF=SCI.txb[i];	//201005atcpc
							}
							else
							{
								for(i=0;i<15;i++)
									ScibRegs.SCITXBUF=SCI.txb[i];	//201005atcpc

								M_SetFlag(SL_TXLONGDATA);							
							}																					
							M_SetFlag(SL_TX);						//置发送任务标志位120625
						}
						else if(response==0)						//不需要回复
						{
							M_ClrFlag(SL_RX);
							Sci485_RxInit();						//485接收初始化
						}
					}
				}
			}
		}
		else if((ScibRegs.SCIFFRX.bit.RXFFST >= 1)&&(M_ChkFlag(SL_HEADOK)==0))	//开始接收且还没有收到报头?
		{
			SCI.rxb[0]=ScibRegs.SCIRXBUF.all&0x00FF;
			if(SCI.rxb[0]==_SCIB_ADDR)								//different!!! 
				M_SetFlag(SL_HEADOK);
			else
				Sci485_RxInit();									//485接收初始化
		}
		else if(ScibRegs.SCIFFRX.bit.RXFFST >= SCI485NUM_RX-1)		//change接收完成?SCIFFRX.bit.RXFFST：Receive FIFO has x words
		{
			SCI.cnt_sciover=0;										//清除发送/接收超时定时器
			M_DisTxRxb();
			M_ClrRxFifoOvr();
			
			for(i=1;i<SCI485NUM_RX;i++)								//读出接收缓存(不包括报头) 9位数据
				SCI.rxb[i]=ScibRegs.SCIRXBUF.all&0x00FF;
			
			M_ClrFlag(SL_HEADOK);
			M_SetFlag(SL_RX);										//置接收完成标志位
			SCI.cnt_scispace=0;										//清除接收到发送间隔定时器
		}
	}
}

/*********************************************************************************************************
** 函数名称: Sci_canopenrx
** 功能描述: sci_CANOPEN初始化
** 输　入:
** 输　出:
** 注  释:
**-------------------------------------------------------------------------------------------------------
** 作　者:
** 日　期:
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
void Scicanopen_Init(void)
{
//----------------------------------------------------------------------------
	SciaRegs.SCICCR.all =0x0007;   			// 1 stop bit,No loopback 
                                  			// no parity,8 char bits
	SciaRegs.SCICTL1.all =0x0003;  			// Disable TX, RX, internal SCICLK, 
                                  			// Disable RX_ERR, SLEEP, TXWAKE
	SciaRegs.SCICTL2.all =0;		 		// fifo mode,they are ignored 

   	SciaRegs.SCIFFTX.all=0xC000;			// disable tx232_int,reset scia_fifo 
    SciaRegs.SCIFFRX.all=0x000A;			// disable rx232_int 
    SciaRegs.SCIFFCT.all=0x00;
    
	SciaRegs.SCICTL1.all =0x0023;     		// Relinquish SCI from Reset 

	SciaRegs.SCIFFTX.bit.TXFIFOXRESET=1;
	SciaRegs.SCIFFRX.bit.RXFIFORESET=1;
//-----------------------------------------------------------------------------
}  
/*********************************************************************************************************
** 函数名称: Sci_canopenrx
** 功能描述: 对sci_CANOPEN的接收发送进行综合控制
** 输　入:
** 输　出:
** 注  释:
**-------------------------------------------------------------------------------------------------------
** 作　者:
** 日　期:
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
void Sci_canopenrx(void)
{
	Uint16 i,heartbeat,xor_data,temp;
	
	if(M_ChkCounter(SCI_canopen.cnt_sciover,DELAY_SCICANOPENOVER)>=0)				//接收超时?
	{
		SCI_canopen.cnt_sciover=0;
		Scicanopen_Init();
		M_ClrFlag(SL_CANOPENHEAD);			//20130801
		M_ClrFlag(SL_CANOPENHEADOK);		//20130801
	}
	else
	{
/*120507		if((SciaRegs.SCIFFRX.bit.RXFFST >= 1)&&(M_ChkFlag(SL_CANOPENHEADOK)==0))	//开始接收且还没有收到报头?
		{
			SCI_canopen.cnt_sciover=0;

			SCI_canopen.rxb[0]=SciaRegs.SCIRXBUF.all&0x00FF;
			if(SCI_canopen.rxb[0]==CANOPENCOM_HEAD)
				M_SetFlag(SL_CANOPENHEADOK);
			else
			{	
				SciaRegs.SCIFFRX.bit.RXFIFORESET=1;		// Re-enable RX FIFO operation
				SciaRegs.SCIFFRX.bit.RXFFOVRCLR=1;
			}
		}
		else if(SciaRegs.SCIFFRX.bit.RXFFST >= SCICANOPENRXNUM-1)			//接收完成?
		{
			
			//	SciaRegs.SCICTL1.bit.RXENA =0;
				for(i=1;i<SCICANOPENRXNUM;i++)								//读出接收缓存(不包括报头)
					SCI_canopen.rxb[i]=SciaRegs.SCIRXBUF.all&0x00FF;
				M_ClrFlag(SL_CANOPENHEADOK);
				
				heartbeat= SCI_canopen.rxb[2] & ONEBYTE[0];
				if(heartbeat!=SCI_canopen.heartbeat)
					SCI_canopen.cnt_heartbeat=0;
				
				SCI_canopen.heartbeat = heartbeat;

				xor_data=SCI_canopen.rxb[0];								//异或校验
				for(i=1;i<(SCICANOPENRXNUM-1);i++)
					xor_data ^= SCI_canopen.rxb[i];
			
				if(xor_data == SCI_canopen.rxb[SCICANOPENRXNUM-1])							//异或校验符合?
				{
					if((SCI_canopen.rxb[1]|SCI_canopen.rxb[2]|SCI_canopen.rxb[3]|SCI_canopen.rxb[4]|SCI_canopen.rxb[5]|SCI_canopen.rxb[6]|SCI_canopen.rxb[7]|SCI_canopen.rxb[8])!=0) //剔出数据都等于0的坏包20090817
					{			
					//数据转存
					SCI_canopen.rx_controlword=(SCI_canopen.rxb[2]<<8)|SCI_canopen.rxb[1];							//controlword
				
					SCI_canopen.rx_torque=(SCI_canopen.rxb[4]<<8)|SCI_canopen.rxb[3];							//torque_ref
				
					SCI_canopen.rx_angle=(SCI_canopen.rxb[6]<<8)|SCI_canopen.rxb[5];							//angle_ref
					}		
				}

		//		SciaRegs.SCICTL1.bit.RXENA =1;
				SciaRegs.SCIFFRX.bit.RXFIFORESET=1;		// Re-enable RX FIFO operation
				SciaRegs.SCIFFRX.bit.RXFFOVRCLR=1;
				SCI_canopen.cnt_sciover=0;

		}
*/
/*		if((SciaRegs.SCIFFRX.bit.RXFFST >= 2)&&(M_ChkFlag(SL_CANOPENHEADOK)==0))	//开始接收且还没有收到报头?
		{
			SCI_canopen.cnt_sciover=0;
	
			for(i=0;i<2;i++)								//校验接收包括报头的前5位信息
				SCI_canopen.rxb[i]=SciaRegs.SCIRXBUF.all&0x00FF;
			
			if(SCI_canopen.rxb[0]==CANOPENCOM_HEAD && SCI_canopen.rxb[1]==0x11)
				M_SetFlag(SL_CANOPENHEADOK);	//[0]=0x7E,[1]=命令码0x11,[2]=数据长度9个字节,[3]=特定参数0x11,[4]=地址偏移0x00

			else
			{	
				SciaRegs.SCIFFRX.bit.RXFIFORESET=1;		// Re-enable RX FIFO operation
				SciaRegs.SCIFFRX.bit.RXFFOVRCLR=1;
			}
		}
*/
//---------20130801----------
		if((SciaRegs.SCIFFRX.bit.RXFFST >= 1)&&(M_ChkFlag(SL_CANOPENHEADOK)==0))	//开始接收且还没有收到报头?	20121215
		{
			SCI_canopen.cnt_sciover=0;

			if(M_ChkFlag(SL_CANOPENHEAD)==0)
			{
				SCI_canopen.rxb[0]=SciaRegs.SCIRXBUF.all&0x00FF;

				if(SCI_canopen.rxb[0]==CANOPENCOM_HEAD)
					M_SetFlag(SL_CANOPENHEAD);
				else
				{
					SciaRegs.SCIFFRX.bit.RXFIFORESET=1;		// Re-enable RX FIFO operation
					SciaRegs.SCIFFRX.bit.RXFFOVRCLR=1;

					temp = SciaRegs.SCIFFRX.bit.RXFFST;
					for(i=0;i<temp;i++)								//校验接收包括报头的前5位信息
						SCI_canopen.rxb[0]=SciaRegs.SCIRXBUF.all&0x00FF;
					
				}
			}
			else
			{
				SCI_canopen.rxb[1]=SciaRegs.SCIRXBUF.all&0x00FF;

				if(SCI_canopen.rxb[1]==0x11)
					M_SetFlag(SL_CANOPENHEADOK);
				else
				{
					SciaRegs.SCIFFRX.bit.RXFIFORESET=1;		// Re-enable RX FIFO operation
					SciaRegs.SCIFFRX.bit.RXFFOVRCLR=1;
					M_ClrFlag(SL_CANOPENHEAD);

					temp = SciaRegs.SCIFFRX.bit.RXFFST;
					for(i=0;i<temp;i++)								//校验接收包括报头的前5位信息
						SCI_canopen.rxb[0]=SciaRegs.SCIRXBUF.all&0x00FF;
				}
				
			}
		}
//---------20130801----------
		else if(SciaRegs.SCIFFRX.bit.RXFFST >= SCICANOPENRXNUM-2)			//接收完成?
		{
//				M_NotFlag(SL_PHASEA);            							//2014-05-06临时测试CANopen
//				*OUT3_ADDR = _OUT3_DATA;
			
				for(i=2;i<SCICANOPENRXNUM;i++)								//读出接收缓存(不包括报头)
					SCI_canopen.rxb[i]=SciaRegs.SCIRXBUF.all&0x00FF;	//[5]-[12]是4个字的指令数据,[13]是校验位
				M_ClrFlag(SL_CANOPENHEADOK);
				M_ClrFlag(SL_CANOPENHEAD);
				
				heartbeat= SCI_canopen.rxb[6] & ONEBYTE[0];  //201105CPC 常牵通讯"心跳位"是Bit15
				if(heartbeat!=SCI_canopen.heartbeat)
				{
					SCI_canopen.cnt_heartbeat=0;
//    				M_NotFlag(SL_PHASEB);								//2014-05-06临时测试CANopen
//    				*OUT3_ADDR = _OUT3_DATA;
				}
				SCI_canopen.heartbeat = heartbeat;

				xor_data=SCI_canopen.rxb[0];								//异或校验
				for(i=1;i<(SCICANOPENRXNUM-1);i++)
					xor_data ^= SCI_canopen.rxb[i];
			
				if(xor_data == SCI_canopen.rxb[SCICANOPENRXNUM-1])							//异或校验符合?
				{
//					if((SCI_canopen.rxb[5]|SCI_canopen.rxb[6]|SCI_canopen.rxb[7]|SCI_canopen.rxb[8]|SCI_canopen.rxb[9]|SCI_canopen.rxb[10]|SCI_canopen.rxb[11]|SCI_canopen.rxb[12])!=0) //剔出数据都等于0的坏包20090817
//					{			
					//数据转存
					SCI_canopen.rx_controlword=(SCI_canopen.rxb[6]<<8)|SCI_canopen.rxb[5];						//controlword
				
					SCI_canopen.rx_torque=(SCI_canopen.rxb[8]<<8)|SCI_canopen.rxb[7];							//torque_ref
				
					SCI_canopen.rx_angle=(SCI_canopen.rxb[10]<<8)|SCI_canopen.rxb[9];							//angle_ref
//					}
//					else
//					{
//						temp=1;		//201105Xgate_testing
//					}		
				}

/*				if(M_ChkFlag(SL_CANOPENOVER)!=0)	//201101NR
				{
			   		 SCI_canopen.rx_controlword=0;
					 SCI_canopen.rx_torque=0;
					 SCI_canopen.rx_angle=0; 
				}
*/
		//		SciaRegs.SCICTL1.bit.RXENA =1;
				SciaRegs.SCIFFRX.bit.RXFIFORESET=1;		// Re-enable RX FIFO operation
				SciaRegs.SCIFFRX.bit.RXFFOVRCLR=1;
				SCI_canopen.cnt_sciover=0;

		}
	}
} 
/*********************************************************************************************************
** 函数名称: Sci_canopentx_read
** 功能描述: 对G-Gate网关下发读取数据指令
** 输　入:
** 输　出:
** 注  释:
**-------------------------------------------------------------------------------------------------------
** 作　者:
** 日　期:
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:120507
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
void Sci_canopentx_read(void)
{
	Uint16 i,xor_data;

	SCI_canopen.txb[0]= CANOPENCOM_HEAD;						//报头
	SCI_canopen.txb[1]= 0x0011;									//读命令字
	SCI_canopen.txb[2]= 0x0002;									//命令信息长度=地址偏移量+数据字节数量
	SCI_canopen.txb[3]= 0x0011;									//特定参数 恒为0x11
	SCI_canopen.txb[4]= 0x0000;									//地址偏移量 设为0
	SCI_canopen.txb[5]=	0x0008;									//数据量8个字节

	xor_data=SCI_canopen.txb[0];								//异或校验
	for(i=1;i<SCICANOPENREADNUM-1;i++)
		xor_data ^= SCI_canopen.txb[i];
				
	SCI_canopen.txb[SCICANOPENREADNUM-1] = xor_data;
		
	for(i=0;i<SCICANOPENREADNUM;i++)							//2011XGate
		SciaRegs.SCITXBUF=SCI_canopen.txb[i];
			
}  

/*********************************************************************************************************
** 函数名称: Sci_canopentx
** 功能描述: 对sci_CANOPEN的接收发送进行综合控制
** 输　入:
** 输　出:
** 注  释:
**-------------------------------------------------------------------------------------------------------
** 作　者:
** 日　期:
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
void Sci_canopentx(void)
{
	Uint16 i,xor_data;

//if(SCI_canopen.tx_state1!=0)  SCI_canopen.tx_state1=0x0000;   //cantest
//else SCI_canopen.tx_state1=0xFFFF;                            //cantest
/*120507	
		SCI_canopen.txb[0] = CANOPENCOM_HEAD;
//		SCI_canopen.txb[1] = CANOPENCOM_TX1;
		SCI_canopen.txb[1]=SCI_canopen.tx_torque&0x00FF;
		SCI_canopen.txb[2]=(SCI_canopen.tx_torque&0xFF00)>>8;
		SCI_canopen.txb[3]=SCI_canopen.tx_speed&0x00FF;
		SCI_canopen.txb[4]=(SCI_canopen.tx_speed&0xFF00)>>8;
		SCI_canopen.txb[5]=SCI_canopen.tx_state1&0x00FF;
		SCI_canopen.txb[6]=(SCI_canopen.tx_state1&0xFF00)>>8;
		SCI_canopen.txb[7]=SCI_canopen.tx_state2&0x00FF;
		SCI_canopen.txb[8]=(SCI_canopen.tx_state2&0xFF00)>>8;
		SCI_canopen.txb[9]=SCI_canopen.tx_watertempin&0x00FF;
		SCI_canopen.txb[10]=(SCI_canopen.tx_watertempin&0xFF00)>>8;
		SCI_canopen.txb[11]=SCI_canopen.tx_watertempout&0x00FF;
		SCI_canopen.txb[12]=(SCI_canopen.tx_watertempout&0xFF00)>>8;
		SCI_canopen.txb[13]=SCI_canopen.tx_skiiptempmax&0x00FF;
		SCI_canopen.txb[14]=(SCI_canopen.tx_skiiptempmax&0xFF00)>>8;
		SCI_canopen.txb[15]=SCI_canopen.tx_demand&0x00FF;
		SCI_canopen.txb[16]=(SCI_canopen.tx_demand&0xFF00)>>8;

		xor_data=SCI_canopen.txb[0];									//异或校验
		for(i=1;i<SCICANOPENTXNUM-1;i++)
			xor_data ^= SCI_canopen.txb[i];
				
		SCI_canopen.txb[SCICANOPENTXNUM-1] = xor_data;
		
		for(i=0;i<SCICANOPENTXNUM-2;i++)
			SciaRegs.SCITXBUF=SCI_canopen.txb[i];
*/		
//CPC通讯协议120507
		SCI_canopen.txb[0]= CANOPENCOM_HEAD;						//报头
		SCI_canopen.txb[1]= 0x0010;									//写命令字
		SCI_canopen.txb[2]= 17;										//命令信息长度=地址偏移量+数据字节数量
		SCI_canopen.txb[3]= 0x0011;									//特定参数 恒为0x11
		SCI_canopen.txb[4]= 0x0000;									//地址偏移量 设为0

		SCI_canopen.txb[5]=SCI_canopen.tx_torque&0x00FF;
		SCI_canopen.txb[6]=(SCI_canopen.tx_torque&0xFF00)>>8;
		SCI_canopen.txb[7]=SCI_canopen.tx_speed&0x00FF;
		SCI_canopen.txb[8]=(SCI_canopen.tx_speed&0xFF00)>>8;
		SCI_canopen.txb[9]=SCI_canopen.tx_state1&0x00FF;
		SCI_canopen.txb[10]=(SCI_canopen.tx_state1&0xFF00)>>8;
		SCI_canopen.txb[11]=SCI_canopen.tx_state2&0x00FF;
		SCI_canopen.txb[12]=(SCI_canopen.tx_state2&0xFF00)>>8;
		SCI_canopen.txb[13]=SCI_canopen.tx_watertempin&0x00FF;
		SCI_canopen.txb[14]=(SCI_canopen.tx_watertempin&0xFF00)>>8;
		SCI_canopen.txb[15]=SCI_canopen.tx_watertempout&0x00FF;
		SCI_canopen.txb[16]=(SCI_canopen.tx_watertempout&0xFF00)>>8;
		SCI_canopen.txb[17]=SCI_canopen.tx_skiiptempmax&0x00FF;
		SCI_canopen.txb[18]=(SCI_canopen.tx_skiiptempmax&0xFF00)>>8;
		SCI_canopen.txb[19]=SCI_canopen.tx_demand&0x00FF;
		SCI_canopen.txb[20]=(SCI_canopen.tx_demand&0xFF00)>>8;

		xor_data=SCI_canopen.txb[0];								//异或校验
		for(i=1;i<SCICANOPENTXNUM-1;i++)
			xor_data ^= SCI_canopen.txb[i];
				
		SCI_canopen.txb[SCICANOPENTXNUM-1] = xor_data;
		
		for(i=0;i<SCICANOPENTXNUM-6;i++)							//2011XGate
			SciaRegs.SCITXBUF=SCI_canopen.txb[i];
} 
/*********************************************************************************************************
** 函数名称: DataFilter
** 功能描述: 数据滤波
** 输　入: 	Y(k-1)为上次滤波结果琗(k)虏裳怠！�
** 输　出: ：Y(k)为本次滤波结果。
** 注  释: 	 滤波公式为：Y(k)=cY(k-1)+(1-c)X(k),其中，c=1/(1+2*PAI*fh/fs),fh为低通滤波器的截止频率，fs为采样频率.
			在一阶低通滤ㄖ校琗(k)次猋(k)。
			直流量误差1％为稳定时间。
**-------------------------------------------------------------------------------------------------------
** 作　者:
** 日　期:
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
void DataFilter( float c,float *out,float in)
{
   *out = c * *out + (1 - c) * in;
} 

/*********************************************************************************************************
** 函数名称: Bandstop filter
** 功能描述: 陷波器
** 输　入:   w0 中心频率
			 wb 半个带阻频率
			 Ts=2e-4
			 
** 输　出:
** 注  释: 201110bjtu
**-------------------------------------------------------------------------------------------------------
** 作　者:
** 日　期:
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日期:   201110 BJTULVRT201204
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
void BS_Loop(struct BS_DATA *var,struct BS_PARA BS_var)
{

	float outtemp,w0,wb,w2,W;
//test
//	w0 = _stdby07 * TWOPAI;  
//test
	w0 = BS_var.f0 * TWOPAI;
	wb = BS_var.fb * TWOPAI;
	w2 = 4 * tan(0.0001 * w0) * tan(0.0001 * w0);                   //w0^2中心频率平方
	W  = 4 * (tan(0.0001 * (w0 + wb)) - tan(0.0001 * (w0 - wb)));   //W带宽
    	
    outtemp = ((4+w2) * var->in + (2* w2-8) * var->inp + (4+w2) * var->infp - (2* w2-8) * var->outp - (4-W+w2) * var->outfp) /(4+W+w2);     //输出函数，由（5）式得。

	if     (outtemp >  BS_var.outmax)  outtemp =  BS_var.outmax;		//输出限幅
	else if(outtemp < -BS_var.outmax)  outtemp = -BS_var.outmax;		//输出限幅

	var->out  = outtemp;		

	var->infp  = var->inp;      //in(k-1)-->in(k-2)
	var->inp   = var->in;       //in(k)-->in(k-1)
	var->outfp = var->outp;     //out(k-1)-->out(k-2)
	var->outp  = var->out;      //out(k)-->out(k-1)				
} 

/***************************************************************
** 函数名称: Bandstop filter without pre-warped
** 功能描述: 陷波器-无预畸变
** 输　入:   w0 中心频率
			 wb 半个带阻频率
			 Ts=2e-4
			 
** 输　出:
** 注  释: 201110bjtu
**-------------------------------------------------------------------------------------------------------
** 作　者:
** 日　期:
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日期:   201110 BJTULVRT201204
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
void BS_Loop_S(struct BS_DATA *var,struct BS_PARA BS_var)
{

	float outtemp,w0,wb,w2,W;

	w0 = BS_var.f0 * TWOPAI;
	wb = BS_var.fb * TWOPAI;
	w2 = 4e-8 * w0 * w0;            //w0^2中心频率平方 无预畸变
	W  = 8e-4  * wb;   				//W带宽
    	
    outtemp = ((4+w2) * var->in + (2* w2-8) * var->inp + (4+w2) * var->infp - (2* w2-8) * var->outp - (4-W+w2) * var->outfp) /(4+W+w2);     //输出函数，由（5）式得。

	if     (outtemp >  BS_var.outmax)  outtemp =  BS_var.outmax;		//输出限幅
	else if(outtemp < -BS_var.outmax)  outtemp = -BS_var.outmax;		//输出限幅

	var->out  = outtemp;		

	var->infp  = var->inp;      //in(k-1)-->in(k-2)
	var->inp   = var->in;       //in(k)-->in(k-1)
	var->outfp = var->outp;     //out(k-1)-->out(k-2)
	var->outp  = var->out;      //out(k)-->out(k-1)				
} 

/*********************************************************************************************************
** 函数名称: 100Hz Bandstop filter
** 功能描述: 陷波器
** 输　入:   w0=100 中心频率
			 wb=+-50Hz 半个带阻频率
			 Ts=2e-4
			 
** 输　出:
** 注  释: 201110bjtu
**-------------------------------------------------------------------------------------------------------
** 作　者:
** 日　期:
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日期:   201110 BJTULVRT201204
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
void BS_Loop100(struct BS_DATA *var,struct BS_PARA BS_var)
{
	float outtemp;
    	
    outtemp = 0.9409 * var->in - 1.8669 * var->inp + 0.9409 * var->infp + 1.8669 * var->outp - 0.8817 * var->outfp;     //输出函数，由（5）式得。

	if     (outtemp >  BS_var.outmax)  outtemp =  BS_var.outmax;		//输出限幅
	else if(outtemp < -BS_var.outmax)  outtemp = -BS_var.outmax;		//输出限幅

	var->out  = outtemp;		

	var->infp  = var->inp;      //in(k-1)-->in(k-2)
	var->inp   = var->in;       //in(k)-->in(k-1)
	var->outfp = var->outp;     //out(k-1)-->out(k-2)
	var->outp  = var->out;      //out(k)-->out(k-1)				
} 


/*********************************************************************************************************
** 函数名称: Ad8364Ctrl
** 功能描述: 读取并处理前一蔚淖唤峁逼舳乱淮蜛D转换
** 洹∪�
** 输　出:
** 注  释: 	 每次都运行
**-------------------------------------------------------------------------------------------------------
** 作　者:
** 日　期:
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
void Ad8364Ctrl(void)
{
	float tempa,tempb,tempc,temp;

//------------------------------数据读取(共18路)---------------------------------
//该组AD数据是100us之前的结果
	AD.dat[0] = *AD_ASTART;	       // STA.Ubc 电机定子侧电压Ubc
	AD.dat[1] = *(AD_ASTART+1);    // AMUX，慢速信号，16选1过来的信号
//	AD.dat[2] = *(AD_ASTART+2);    // GRD.Ubc 主断前Ubc
	AD.dat[2] = *(AD_ASTART+2);    // chopper电流idc	20130805
//	AD.dat[3] = *(AD_ASTART+3);    // Ic 备用SKIIP电流反馈
//	AD.dat[4] = *(AD_ASTART+4);    // GRD.Uab 主断前Uab
	AD.dat[5] = *(AD_ASTART+5);    // MPR.ic, 机侧变流器MPR的电流

	AD.dat[6]  = *AD_BSTART;       // NGS.Uab 网侧电压Ubc大滤波通道
	AD.dat[7]  = *(AD_BSTART+1);   // MPR.ib，机侧变流器NPR
	AD.dat[8]  = *(AD_BSTART+2);   // NGS.Ubc 网侧电压Ubc大滤波通道
	AD.dat[9]  = *(AD_BSTART+3);   // MPR.ia，机侧变流器NPR的电流
	AD.dat[10] = *(AD_BSTART+4);   // Udc 中间直流电压
	AD.dat[11] = *(AD_BSTART+5);   // NPR.ic，网侧变流器NPR的电流

//	AD.dat[12] = *AD_CSTART;       // Vdc2 
	AD.dat[13] = *(AD_CSTART+1);   // NPR.ib，网侧变流器NPR的电流
	AD.dat[14] = *(AD_CSTART+2);   // NGS.Uab 网侧电压Uab
	AD.dat[15] = *(AD_CSTART+3);   // NPR.ia，网侧变流器NPR的电流
	AD.dat[16] = *(AD_CSTART+4);   // STA.Uab 电机定子侧电压Uab
	AD.dat[17] = *(AD_CSTART+5);   // NGS.Ubc 网侧电压Ubc

//----------------------------数据读取结束------------------------------
	
	ADFINAL.ia1  = AD.dat[15];		// NPR.ia，网侧变流器NPR的电流
	ADFINAL.ib1  = AD.dat[13];	    // NPR.ib，网侧变流器NPR的电流
	ADFINAL.ic1  = AD.dat[11];	    // NPR.ic，网侧变流器NPR的电流

	ADFINAL.ia2  = AD.dat[9];	    // MPR.ia，机侧变流器MPR的电流
	ADFINAL.ib2  = AD.dat[7];		// MPR.ib，机侧变流器MPR的电流
	ADFINAL.ic2  = AD.dat[5];		// MPR.ic, 机侧变流器MPR的电流

//	ADFINAL.uab   = AD.dat[4];       // GRD.Uab 主断前Uab
//	ADFINAL.ubc   = AD.dat[2];		 // GRD.Ubc 主断前Ubc
//	ADFINAL.isa  = AD.dat[2];		// 定子电流A相 以流出电机为正
//	ADFINAL.isc  = AD.dat[4];	    // 定子电流C相 BJTULVRT201204
	ADFINAL.idc  = AD.dat[2];		//chopper电流idc	20130805

	ADFINAL.uab1 = AD.dat[14];		// Uab 网侧电压
	ADFINAL.ubc1 = AD.dat[17];		// Ubc 网侧电压
	
	ADFINAL.uab2 = AD.dat[16];		// Uab 电机定子侧电压
	ADFINAL.ubc2 = AD.dat[0];		// Ubc 电机定子侧电压

	ADFINAL.uab3 = AD.dat[6];		// Uab 网侧电压 大滤波通道
	ADFINAL.ubc3 = AD.dat[8];		// Ubc 网侧电压 大滤波通道


	ADFINAL.udc  = AD.dat[10];		//中间直流电压检测

    if(ADFINAL.udc < 0) ADFINAL.udc=0;

	ADFINAL.AMUX = AD.dat[1];       //慢速AD输入

//-----------------------------------------------------------	     
	switch(_OUT4_DATA)
	{
		case(8): {AMUX.NPR_tempa=ADFINAL.AMUX   * 0.0030517 + 20;   break; }	//NPR的A相温度，Skiip反馈,=10V*10/(32768) +20
		case(10):{AMUX.NPR_tempb=ADFINAL.AMUX   * 0.0030517 + 20;   break; }	//NPR的B相温度，Skiip反馈,=10V*10/(32768) +20
		case(12):{AMUX.NPR_tempc=ADFINAL.AMUX   * 0.0030517 + 20;   break; }	//NPR的C相温度，Skiip反馈,=10V*10/(32768) +20
		case(11):{AMUX.MPR_tempa=ADFINAL.AMUX   * 0.0030517 + 20;   break; }	//MPR的A相温度，Skiip反馈,=10V*10/(32768) +20
		case(9): {AMUX.MPR_tempb=ADFINAL.AMUX   * 0.0030517 + 20;   break; }	//MPR的B相温度，Skiip反馈,=10V*10/(32768) +20
		case(2): {AMUX.MPR_tempc=ADFINAL.AMUX   * 0.0030517 + 20;   break; }	//MPR的C相温度，Skiip反馈,=10V*10/(32768) +20
        case(1): {
                  AMUX.Lac_R=(ADFINAL.AMUX+49152) /(491.52- 0.001* ADFINAL.AMUX);//new PCB PT100(Rt=100R+0.39*T)
             	  AMUX.Lac_temp=2.5641 * (AMUX.Lac_R - 100);
             	  break; 
             	 }
        case(0): {
                  AMUX.Ldudt_R=(ADFINAL.AMUX+49152) /(491.52- 0.001* ADFINAL.AMUX);//new PCB PT100(Rt=100R+0.39*T)
             	  AMUX.Ldudt_temp=2.5641 * (AMUX.Ldudt_R - 100);
             	  break; 
             	 }
//---------------中间直流斩波器-IGBT电流BJTULVRT201204---------------------------
/*		case(5): {
					ADFINAL.idc = ADFINAL.AMUX ;
					AD_OUT_DC_I.b = ADFINAL.idc * 7.6294e-2 * 1.0000000;  //20欧采用电阻,700A对应140mA(1:5000) =10V*700A/(32768*20R*140mA)
					break;
				 }
*///		case(5): {AD_OUT_STA_I.ac=ADFINAL.AMUX  * 0.0732422;		break; }	//电机定子侧A相线电流，互感器1200A:1A,Rt=5R,=1200A*10V/(5R*1A*32768)
//		case(4): {AD_OUT_STA_I.ba=ADFINAL.AMUX  * 0.0732422;		break; }	//电机定子侧B相线电流，互感器
//20130805
		case(5): {AD_OUT_STA_I.ac=ADFINAL.AMUX  * 0.0732422;		break; }	//电机定子侧A相线电流，互感器1200A:1A,Rt=5R,=1200A*10V/(5R*1A*32768)
		case(4): {AD_OUT_STA_I.ba=ADFINAL.AMUX  * 0.0732422;		break; }	//电机定子侧B相线电流，互感器
//--------
		case(7): {AD_OUT_SCR_I.a =ADFINAL.AMUX  * 0.0305176;		break; }	//ActiveCROWBAR中A相SCR电流，电流LEM/电压型反馈4A--400V =10V*400A/(32768*4V)
		case(6): {AD_OUT_SCR_I.b =ADFINAL.AMUX  * 0.0305176;		break; }	//ActiveCROWBAR中B相SCR电流，电流LEM/电压型反馈4A--400V =10V*400A/(32768*4V)
		default: break; 			      
	}

	if(M_ChkCounter(MAIN_LOOP.cnt_AMUX,DELAY_AMUX)>=0)
	{
	    MAIN_LOOP.cnt_AMUX=0;                         							//5ms读一次慢速AD
	     _OUT_AMUX1++;
		 if(_OUT_AMUX1 >= 12) _OUT_AMUX1=0;
		 _OUT4_DATA = _OUT_AMUX1;
		 *OUT4_ADDR = _OUT4_DATA;
    }
	else
	{
		_OUT_AMUX2++;
		if((_OUT_AMUX2 > 7) || (_OUT_AMUX2 < 4)) _OUT_AMUX2=4; 
		_OUT4_DATA = _OUT_AMUX2;
		*OUT4_ADDR = _OUT4_DATA;	
	}

//----20130805----
	AD_OUT_STA_I.cb = - AD_OUT_STA_I.ac - AD_OUT_STA_I.ba;
	AD_OUT_DC_I.b = ADFINAL.idc * 7.6294e-2 * 1.0000000;  //20欧采用电阻,700A对应140mA(1:5000) =10V*700A/(32768*20R*140mA)
//----------------

//-------------------定子电流（单位A）-------------------------------------------------------------
/*	AD_OUT_STA_I.a  =  (AD_OUT_STA_I.ac - AD_OUT_STA_I.ba) * 0.3333333;
	AD_OUT_STA_I.b  =   AD_OUT_STA_I.a  + AD_OUT_STA_I.ba;	
    AD_OUT_STA_I.c  = - AD_OUT_STA_I.a  - AD_OUT_STA_I.b; 
*/
//-------------------定子电流（单位A）-BJTULVRT201204------------------------------------------------------------
/*	AD_OUT_STA_I.ac =   ADFINAL.isa  * 0.114441;	//LEM2000A电机定子侧A相线电流，1500A-4V;==(1500/4*10)/32768  20111128
	AD_OUT_STA_I.cb =   ADFINAL.isc  * 0.114441;	//LEM2000A电机定子侧B相线电流，200A-100mA;50.0ohm采样,==10V*200A*D/(100mA*50R*32768*1) INA114反相 20111128
	AD_OUT_STA_I.ba = - AD_OUT_STA_I.ac - AD_OUT_STA_I.cb;
*/
	AD_OUT_STA_I.a  =  (AD_OUT_STA_I.ac - AD_OUT_STA_I.ba) * 0.3333333;	//201112fluxObs
	AD_OUT_STA_I.b  =   AD_OUT_STA_I.a  + AD_OUT_STA_I.ba;
    AD_OUT_STA_I.c  = - AD_OUT_STA_I.a  - AD_OUT_STA_I.b;
	tempa = abs(AD_OUT_STA_I.ac);
	tempb = abs(AD_OUT_STA_I.cb);
	DataFilter(0.9999,&MEAN_DATA.iac3,tempa); //定子侧电流	平均值滤波10S
	DataFilter(0.9999,&MEAN_DATA.icb3,tempb); //定子侧电流	平均值滤波10S

	tempa = abs(AD_OUT_STA_I.a);
	tempb = abs(AD_OUT_STA_I.b);
	tempc = abs(AD_OUT_STA_I.c);
	DataFilter(0.9999,&MEAN_DATA.ia3,tempa); //定子侧电流	平均值滤波10S
	DataFilter(0.9999,&MEAN_DATA.ib3,tempb); //定子侧电流	平均值滤波10S
	DataFilter(0.9999,&MEAN_DATA.ic3,tempc); //定子侧电流	平均值滤波10S

//------------------网侧变流器电流------------------------------------------------------------------
    AD_OUT_NPR_I.a = - (ADFINAL.ia1 * 0.0572204);  // SKIIP反馈电流(流出桥臂为正),底板有一个反向，10V=1875A,=10V*1875A/(32768*10V)
	AD_OUT_NPR_I.b = - (ADFINAL.ib1 * 0.0572204);  // SKIIP反馈电流(流出桥臂为正)，控制算法以流出SKIIP�
	AD_OUT_NPR_I.c = - (ADFINAL.ic1 * 0.0572204);  // SKIIP反馈电流(流出桥臂为正)
//---20121103-----------------并网电流瞬时值保护-201011LVRT--------------------------
	if(abs(AD_OUT_NPR_I.a)>abs( AD_OUT_NPR_I.b))
	{
		if(abs( AD_OUT_NPR_I.a)>abs( AD_OUT_NPR_I.c))	temp=abs(AD_OUT_NPR_I.a);
		else										    temp=abs(AD_OUT_NPR_I.c);
	}
	else
	{
		if(abs( AD_OUT_NPR_I.b)>abs( AD_OUT_NPR_I.c))	temp=abs(AD_OUT_NPR_I.b);
		else										    temp=abs(AD_OUT_NPR_I.c);
	}

	PRO.NPR_iac = temp * 100 / NPR_IACN;			//并网电流瞬时最大值，基准电流的百分值

//-------------------机侧变流器电流转为实际值-201005atcpc-----------------------------------------------------
	if(R_PHORDE==1)		//反相序控制201005atcpc
	{
    	AD_OUT_MPR_I.b =  (ADFINAL.ia2 * 0.0572204);  // SKIIP反馈电流(流出桥臂为正),底板有一个反向，10V=1875A,=10V*1875A/(32768*10V)
		AD_OUT_MPR_I.a =  (ADFINAL.ib2 * 0.0572204);  // SKIIP反馈电流(流出桥臂为正)，控制算法以流出SKIIP为�
		AD_OUT_MPR_I.c =  (ADFINAL.ic2 * 0.0572204);  // SKIIP反馈电流(流出桥臂为正)
	}
	else
	{
	    AD_OUT_MPR_I.a =  (ADFINAL.ia2 * 0.0572204);  // SKIIP反馈电流(流出桥臂为正),底板有一个反向，10V=1875A,=10V*1875A/(32768*10V)
		AD_OUT_MPR_I.b =  (ADFINAL.ib2 * 0.0572204);  // SKIIP反馈电流(流出桥臂为正)，控制算法以流出SKIIP为正
		AD_OUT_MPR_I.c =  (ADFINAL.ic2 * 0.0572204);  // SKIIP反馈电流(流出桥臂为正)
	}
//----20121103----------------转子电流瞬时值保护-----201011LVRT----------------------
	if(abs(AD_OUT_MPR_I.a)>abs(AD_OUT_MPR_I.b))
	{
		if(abs(AD_OUT_MPR_I.a)>abs(AD_OUT_MPR_I.c))		temp=abs(AD_OUT_MPR_I.a);
		else											temp=abs(AD_OUT_MPR_I.c);
	}
	else
	{
		if(abs(AD_OUT_MPR_I.b)>abs(AD_OUT_MPR_I.c))		temp=abs(AD_OUT_MPR_I.b);
		else											temp=abs(AD_OUT_MPR_I.c);
	}

	PRO.MPR_iac = temp * 100 / MPR_IACN;		//转子电鞔笾担嫉琪的百分值

//---------------------直流电压----------------------------------------------------------------------
    AD_OUT_UDC      = ADFINAL.udc * 0.0448788;   // LEM(40mA=1500V),Rt=255R,=10V*1500V/(32768*255R*40mA)
	DataFilter(0.44,&MEAN_DATA.udc,AD_OUT_UDC);  //Vdc直流滤波，fh=1kHz
//	DataFilter(0.7,&MEAN_DATA.udc,AD_OUT_UDC);   //Vdc直流滤波，fh=340Hz 201005atcpc
    AD_OUT_UDC      = MEAN_DATA.udc;
//    AD_OUT_UDC      = 1100;	//controltest
//----20121103------------中间直流电压保护值计算-201011LVRT----------------------------

	PRO.udc  = AD_OUT_UDC;	                                 //单位V
						
//---------------------主断前电网电压---------------------------------------------------------------------
//	AD_OUT_GRD_U.ab = ADFINAL.uab * 0.0448788;   // LEM(40mA=1500V),Rt=255R,=10V*1500V/(32768*255R*40mA)
//	AD_OUT_GRD_U.bc = ADFINAL.ubc * 0.0448788;   // LEM(40mA=1500V),Rt=255R,=10V*1500V/(32768*255R*40mA) 

//---------------------主断后电网电压---------------------------------------------------------------------
	AD_OUT_NGS_U.ab = ADFINAL.uab1 * 0.0448788;   // LEM(40mA=1500V),Rt=255R,=10V*1500V/(32768*255R*40mA)
	AD_OUT_NGS_U.bc = ADFINAL.ubc1 * 0.0448788;   // LEM(40mA=1500V),Rt=255R,=10V*1500V/(32768*255R*40mA)

//-------------------电机定子侧线电压---------------------------------------------
	AD_OUT_STA_U.ab  = ADFINAL.uab2 * 0.0448788;  // LEM(40mA=1500V),Rt=255R,=10V*1500V/(32768*255R*40mA)
	AD_OUT_STA_U.bc  = ADFINAL.ubc2 * 0.0448788;  // LEM(40mA=1500V),Rt=255R,=10V*1500V/(32768*255R*40mA)

//-------------------主断后电网电压,大滤波通道---------------------------------------------
	AD_OUT_NGF_U.ab  = ADFINAL.uab3 * 0.0448788;  // LEM(40mA=1500V),Rt=255R,=10V*1500V/(32768*255R*40mA)
	AD_OUT_NGF_U.bc  = ADFINAL.ubc3 * 0.0448788;  // LEM(40mA=1500V),Rt=255R,=10V*1500V/(32768*255R*40mA)
/* 
//---------------------零漂滤波201005atcpc-------------------------------------------------------------------
	DataFilter(0.999985,&MEAN_DATA.zfia1,AD_OUT_NPR_I.a); //网侧电流传感器	零漂滤波60S
	DataFilter(0.999985,&MEAN_DATA.zfib1,AD_OUT_NPR_I.b); //网侧电流传感器	零漂滤波60S
	DataFilter(0.999985,&MEAN_DATA.zfic1,AD_OUT_NPR_I.c); //网侧电流传感器	零漂滤波60S

	DataFilter(0.999985,&MEAN_DATA.zfia3,AD_OUT_STA_I.a); //定子侧电流传感器	零漂滤波60S
	DataFilter(0.999985,&MEAN_DATA.zfib3,AD_OUT_STA_I.b); //定子侧电流传感器	零漂瞬�0S
	DataFilter(0.999985,&MEAN_DATA.zfic3,AD_OUT_STA_I.c); //定子侧电流传感器	零漂滤波60S

	DataFilter(0.999985,&MEAN_DATA.zfuab,AD_OUT_GRD_U.ab); //主断前网压电压传感器	零漂滤波60S
	DataFilter(0.999985,&MEAN_DATA.zfubc,AD_OUT_GRD_U.bc); //主断前网压电压传感器	零漂滤波60S

	DataFilter(0.999985,&MEAN_DATA.zfuab1,AD_OUT_NGS_U.ab); //网压电压传感器	零漂滤波60S
	DataFilter(0.999985,&MEAN_DATA.zfubc1,AD_OUT_NGS_U.bc); //网压电压传感器	零漂滤波60S


//------------------除チ漂--电机试验不允许对机侧电流进行零漂滤波！201005atcpc-------------------------------------------------------------------
	if(M_ChkFlag(SL_SENSZFSTDY)!=0)
	{
		AD_OUT_NPR_I.a = AD_OUT_NPR_I.a - MEAN_DATA.zfia1;  //网侧电流
		AD_OUT_NPR_I.b = AD_OUT_NPR_I.b - MEAN_DATA.zfib1;
		AD_OUT_NPR_I.c = AD_OUT_NPR_I.c - MEAN_DATA.zfic1;

		AD_OUT_STA_I.a = AD_OUT_STA_I.a - MEAN_DATA.zfia3;  //定子侧电流
		AD_OUT_STA_I.b = AD_OUT_STA_I.b - MEAN_DATA.zfib3; 
		AD_OUT_STA_I.c = AD_OUT_STA_I.c - MEAN_DATA.zfic3; 

		AD_OUT_GRD_U.ab = AD_OUT_GRD_U.ab - MEAN_DATA.zfuab; //主断前网压电压
		AD_OUT_GRD_U.bc = AD_OUT_GRD_U.bc - MEAN_DATA.zfubc; 

		AD_OUT_NGS_U.ab = AD_OUT_NGS_U.ab - MEAN_DATA.zfuab1; //网压电压
		AD_OUT_NGS_U.bc = AD_OUT_NGS_U.bc - MEAN_DATA.zfubc1;	
	}
*/
//-------------------主断前电网电压，由哐棺嘌�-----------------------------------------------------
//	AD_OUT_GRD_U.b  = (AD_OUT_GRD_U.bc - AD_OUT_GRD_U.ab) * 0.3333333;
//	AD_OUT_GRD_U.a  = AD_OUT_GRD_U.b + AD_OUT_GRD_U.ab;	
//	AD_OUT_GRD_U.c  = - AD_OUT_GRD_U.a - AD_OUT_GRD_U.b; 

//-------------------电网电压，由线压转为相压------------------------------------------------------
	AD_OUT_NGS_U.b  = (AD_OUT_NGS_U.bc - AD_OUT_NGS_U.ab) * 0.3333333;
	AD_OUT_NGS_U.a  = AD_OUT_NGS_U.b + AD_OUT_NGS_U.ab;	
	AD_OUT_NGS_U.c  = - AD_OUT_NGS_U.a - AD_OUT_NGS_U.b;

//-------------------电机ㄗ硬嗟缪梗上哐顾阆嘌�-----------------------------------------------------
	AD_OUT_STA_U.b  = (AD_OUT_STA_U.bc - AD_OUT_STA_U.ab) * 0.3333333;
	AD_OUT_STA_U.a  = AD_OUT_STA_U.b + AD_OUT_STA_U.ab;	
    AD_OUT_STA_U.c  = - AD_OUT_STA_U.a - AD_OUT_STA_U.b;

//---------------------平均值滤波------------------------------------------------------------------
	tempa = abs(AD_OUT_NPR_I.a);
	tempb = abs(AD_OUT_NPR_I.b);
	tempc = abs(AD_OUT_NPR_I.c);
	DataFilter(0.9999,&MEAN_DATA.ia1,tempa); //网侧电流	平均值滤波10S
	DataFilter(0.9999,&MEAN_DATA.ib1,tempb); //网侧电流	平均值滤波10S
	DataFilter(0.9999,&MEAN_DATA.ic1,tempc); //网侧电流	平均值滤波10S

	tempa = abs(AD_OUT_MPR_I.a);
	tempb = abs(AD_OUT_MPR_I.b);
	tempc = abs(AD_OUT_MPR_I.c);
	DataFilter(0.9999,&MEAN_DATA.ia2,tempa); //机侧电流	平均值滤波10S
	DataFilter(0.9999,&MEAN_DATA.ib2,tempb); //机侧电流	平均值滤波10S
	DataFilter(0.9999,&MEAN_DATA.ic2,tempc); //机侧电流	平均值滤波10S

//	tempa = abs(AD_OUT_GRD_U.ab);
//	tempb = abs(AD_OUT_GRD_U.bc);
//	DataFilter(0.9999,&MEAN_DATA.uab,tempa); //主断前网侧电压	平均值滤波10S
//	DataFilter(0.9999,&MEAN_DATA.ubc,tempb); //主断前网侧电压	平均值滤波10S

	tempa = abs(AD_OUT_NGS_U.ab);
	tempb = abs(AD_OUT_NGS_U.bc);
	DataFilter(0.9999,&MEAN_DATA.uab1,tempa); //网侧电压	平均值滤波10S
	DataFilter(0.9999,&MEAN_DATA.ubc1,tempb); //网侧电压	平均值滤波10S

	tempa = abs(AD_OUT_STA_U.ab);
	tempb = abs(AD_OUT_STA_U.bc);
	DataFilter(0.9999,&MEAN_DATA.uab2,tempa); //定子侧电压	平均值滤波10S
	DataFilter(0.9999,&MEAN_DATA.ubc2,tempb); //定子侧电压	平均值滤波10S


	tempa = abs(AD_OUT_NGS_U.a);
	tempb = abs(AD_OUT_NGS_U.b);
	tempc = abs(AD_OUT_NGS_U.c);
	DataFilter(0.9999,&MEAN_DATA.ua1,tempa); //网侧电压	平均值滤波10S
	DataFilter(0.9999,&MEAN_DATA.ub1,tempb); //网侧电压	平均值滤波10S
	DataFilter(0.9999,&MEAN_DATA.uc1,tempc); //网侧电压	平均值滤波10S

	tempa = abs(AD_OUT_NGF_U.ab);			  //MagnetCurve2013-12-13
	tempb = abs(AD_OUT_NGF_U.bc);
	DataFilter(0.9999,&MEAN_DATA.uab3,tempa); //主断后电网电压,大滤波通道	平均值滤波10S
	DataFilter(0.9999,&MEAN_DATA.ubc3,tempb); //主断后电网电压,大滤波通道	平均值滤波10S

//	tempa = abs(AD_OUT_NGF_U.ab);			  //MagnetCurve200909
//	tempb = abs(AD_OUT_NGF_U.bc);
//	DataFilter(0.9999,&MEAN_DATA.uab3,tempa); //主断后电网电压,大滤波通道	平均值滤波10S
//	DataFilter(0.9999,&MEAN_DATA.ubc3,tempb); //主断后电网电压,大滤波通道	平均值滤波10S

//--------------求网压和定子电压差值平均值------------------------------------------
    AD_OUT_STAD_U.ab = AD_OUT_NGF_U.ab - AD_OUT_STA_U.ab;
    AD_OUT_STAD_U.bc = AD_OUT_NGF_U.bc - AD_OUT_STA_U.bc;

	tempa = abs(AD_OUT_STAD_U.ab);
	tempb = abs(AD_OUT_STAD_U.bc);
	DataFilter(0.9999,&MEAN_DATA.uab_d,tempa);  //差值平均值    平均值滤波10S
	DataFilter(0.9999,&MEAN_DATA.ubc_d,tempb);  //差值平均值	平均值滤波10S
	DataFilter(0.997,&MEAN_DATA.ubc_t,tempb);  //差值平均值	平均值滤波1S	//20130801
//----------------------------------------------------------------------------------
/*	//201204
	tempa = abs(AD_OUT_STA_I.ac);
	tempb = abs(AD_OUT_STA_I.ba);
	DataFilter(0.9999,&MEAN_DATA.iac3,tempa); //定子侧电流	平均值滤波10S
	DataFilter(0.9999,&MEAN_DATA.iba3,tempb); //定子侧电流	平均值滤波10S

	tempa = abs(AD_OUT_STA_I.a);
	tempb = abs(AD_OUT_STA_I.b);
	tempc = abs(AD_OUT_STA_I.c);
	DataFilter(0.9999,&MEAN_DATA.ia3,tempa); //定子侧电流	平均值滤波10S
	DataFilter(0.9999,&MEAN_DATA.ib3,tempb); //定子侧电流	平均值滤波10S
	DataFilter(0.9999,&MEAN_DATA.ic3,tempc); //定子侧电流	平均值滤波10S
*/

//--------------------------------------------------------------------------------------------------
//----------------------网侧和机侧电感温度滤波---------------------------------------------------------------------
	tempa = abs(AMUX.Lac_temp);
	tempb = abs(AMUX.Ldudt_temp);
	DataFilter(0.9999,&MEAN_DATA.Lac_temp,tempa); 	//网侧电感温度	平均值滤波10S
	DataFilter(0.9999,&MEAN_DATA.Ldudt_temp,tempb); //机侧电感温度	平均值滤波10S

//--------------------励磁参数辨识MagnetCurve2013-12-13--ZZJ--------------------------------------------------------------
//BJTULVRT201204计算比率Uns_ft移到input里节约T0资源
//	Uns_ft = 0.5 * ((MEAN_DATA.uab3/MEAN_DATA.uab1)+(MEAN_DATA.ubc3/MEAN_DATA.ubc1));//大滤波幅值衰减比例
//	Uns_ft = 0.848;		//R=20k,C=0.1uF,fh=80Hz,理论衰减比例Avh=0.848,实际采用上式测量计算值为0.83左右！2010-10-2

//--------20121011--------

	if(_SC_MSTDBY==1)	 //Us=50%
	{
		MC_U_test = (float)_SC_Usn * 0.5 * Uns_ft - (0.5 * 1.110721 * (MEAN_DATA.uab2+MEAN_DATA.ubc2));
		MC_DATA.temp[1] = _SC_EXISTY1 * 0.001;
		MAIN_LOOP.cnt_mc_ack=0;	
		MC_F_cnt = 0;
		MC_N_test= 0;
	}
	else if(_SC_MSTDBY==2)//Us=75%
	{
		MC_U_test =  (float)_SC_Usn * 0.75 * Uns_ft - (0.5 * 1.110721 * (MEAN_DATA.uab2+MEAN_DATA.ubc2));
		MC_DATA.temp[2] = _SC_EXISTY2 * 0.001;	
		MAIN_LOOP.cnt_mc_ack=0;	
		MC_F_cnt = 0;
		MC_N_test= 0;
	}
	else if(_SC_MSTDBY==3)//Us=90%
	{
		MC_U_test =  (float)_SC_Usn * 0.9 * Uns_ft - (0.5 * 1.110721 * (MEAN_DATA.uab2+MEAN_DATA.ubc2));
		MC_DATA.temp[3] = _SC_EXISTY3 * 0.001;	
		MAIN_LOOP.cnt_mc_ack=0;	
		MC_F_cnt = 0;
		MC_N_test= 0;
	}
	else if(_SC_MSTDBY==4)//Us=100%
	{
		MC_U_test =  (float)_SC_Usn * 1.0 * Uns_ft - (0.5 * 1.110721 * (MEAN_DATA.uab2+MEAN_DATA.ubc2));
		MC_DATA.temp[4] = _SC_EXISTY4 * 0.001;
		MAIN_LOOP.cnt_mc_ack=0;	
		MC_F_cnt = 0;
		MC_N_test= 0;
	}
	else if(_SC_MSTDBY==5)//Us=110% 
	{
		MC_U_test =  (float)_SC_Usn * 1.1 * Uns_ft - (0.5 * 1.110721 * (MEAN_DATA.uab2+MEAN_DATA.ubc2));
		MC_DATA.temp[5] = _SC_EXISTY5 * 0.001;
		MAIN_LOOP.cnt_mc_ack=0;	
		MC_F_cnt = 0;
		MC_N_test= 0;
	}
	else if(_SC_MSTDBY==99)//确定励磁参数辨识完成
	{
		if(M_ChkFlag(SL_MC_FAIL)!=0)
		{
			_MC_OK = 0;
			MC_DATA.y[0] = 1;
			MC_DATA.y[1] = 1;
			MC_DATA.y[2] = 1;
			MC_DATA.y[3] = 1;
			MC_DATA.y[4] = 1;
			MC_DATA.y[5] = 1;			
		} 
		else if(M_ChkFlag(SL_MC_OK)==0)
		{
	    	MC_DATA.y[0] = _SC_EXISTY1 * 0.001;
 	   		MC_DATA.y[1] = _SC_EXISTY1 * 0.001;
			MC_DATA.y[2] = _SC_EXISTY2 * 0.001;
			MC_DATA.y[3] = _SC_EXISTY3 * 0.001;
			MC_DATA.y[4] = _SC_EXISTY4 * 0.001;
			MC_DATA.y[5] = _SC_EXISTY5 * 0.001; 
			
			MC_U_test =  (float)_SC_Usn * (0.5 + MC_N_test * 0.1) * Uns_ft - (0.5 * 1.110721 * (MEAN_DATA.uab2+MEAN_DATA.ubc2));
			MC_F_cnt++;

//			if(MC_F_cnt>32766) MC_F_cnt=32766;//test

			if(abs(MC_U_test) < 25)
			{
				if(M_ChkCounter(MAIN_LOOP.cnt_mc_ack,DELAY_MC_ACK)>=0)	//0.5s
				{
					MC_F_cnt = 0;
					MAIN_LOOP.cnt_mc_ack=0;
					if(MC_N_test < 6)	 MC_N_test++;	//0-6			
					else
					{
						M_SetFlag(SL_MC_OK);
						MC_N_test = 0;
					}					
				}
			}		
			else if(MC_F_cnt > 5e4)		//超时达到10s,认为励磁曲线测绘失败,需要重新测量
			{
				M_SetFlag(SL_MC_FAIL);
				MC_F_cnt = 0;
				MC_N_test= 0;
				MAIN_LOOP.cnt_mc_ack=0;
			}
			else	MAIN_LOOP.cnt_mc_ack=0;		
		}
		else
		{
			_MC_OK = 1;
		}
					
	}
	else if(_SC_MSTDBY==100)		//用户要求重新测绘励磁曲线
	{
		M_ClrFlag(SL_MC_OK);
		M_ClrFlag(SL_MC_FAIL);
		MC_F_cnt  = 0;
		MC_N_test = 0;
		_MC_OK 	  = 0;	
		MAIN_LOOP.cnt_mc_ack=0;	
	}
	else
	{
		MC_U_test = MEAN_DATA.uab3 + MEAN_DATA.ubc3 - (MEAN_DATA.uab2+MEAN_DATA.ubc2);		//BJTULVRT_201011
		MC_F_cnt  = 0;
		MC_N_test = 0;
		MAIN_LOOP.cnt_mc_ack=0;		
	}
//---------2013-12-13---ZZJ--------

//-------------------------------------------------------------------------------------------------
	*AD_DA_CTRL     = AD8364_CONVERT;	               	  	//启动下籄D转换
    CAP4.adsmptsctr = ECap4Regs.TSCTR;						//保存网压定向时间
	QEPDATA.adsmposcnt=EQep2Regs.QPOSCNT;					//保存编码器位置信息

}

/*********************************************************************************************************
** 函数名称: Da5344Manage
** 功能描述：The value of 4 da channels are chosen.
** 输　入:
** 输　出:
** 注  释: 	The da output is used to help debug or display
**-------------------------------------------------------------------------------------------------------
** 作　者:
** 日　期:
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:2012.4
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
void Da5344Manage(void)
{ 
	Uint16 i;

	for(i=0;i<=3;i++)
	{
		switch(daindex[i])
		{												//4096-(10V),0-(-10V)

			case 0: {if(M_ChkFlag(SL_LV_STATE)==0)		zys[i] = 2048;
				     else   							zys[i] = 4095;	break;} 
			case 1: {if(M_ChkFlag(SL_LV_SCRON)==0)		zys[i] = 2048;
				     else   							zys[i] = 4095;	break;}  
			case 2: {if(M_ChkFlag(SL_LV_SCRRUNING)==0)	zys[i] = 2048;
				     else   							zys[i] = 4095;	break;}  
			case 3: {if(M_ChkFlag(SL_LV_SCRIZERO)==0)	zys[i] = 2048;
				     else   							zys[i] = 4095;	break;} 
			case 4: {if(M_ChkFlag(SL_UNBALANCE)==0)		zys[i] = 2048;
				     else   							zys[i] = 4095;	break;}  
			case 5: {if(M_ChkFlag(SL_LV_MSTOP)==0)		zys[i] = 2048;
				     else   							zys[i] = 4095;	break;}  
			case 6: {if(M_ChkFlag(SL_LV_NSTOP)==0)		zys[i] = 2048;
				     else   							zys[i] = 4095;	break;}  
			case 7: {if(M_ChkFlag(SL_LV_QWORKING)==0)	zys[i] = 2048;
				     else   							zys[i] = 4095;	break;}  
			case 8: {if(M_ChkFlag(SL_ERROR)==0)			zys[i] = 2048;
					 else   							zys[i] = 4095;	break;}  
//			case 9: {if(M_ChkFlag(SL_LV_PHICON)==0)		zys[i] = 2048;
//				     else   							zys[i] = 4095;	break;}  //=1LV机侧动态磁链控制标志位
			case 10:{if(M_ChkFlag(SL_LV_SYNCON)==0)		zys[i] = 2048;				
				     else   							zys[i] = 4095;	break;}  //=1LV机侧动态调节标志位
			case 11: {if(M_ChkFlag(SL_QCAPSPDIN)==0)			zys[i] = 2048;
					 else   							zys[i] = 4095;	break;}  
			case 12: {if(M_ChkFlag(SL_QCAPDISTURB)==0)		zys[i] = 2048;
				     else   							zys[i] = 4095;	break;}  //=1LV机侧动态磁链控制标志位
			case 13:{if(M_ChkFlag(SL_QEPPCO)==0)		zys[i] = 2048;				
				     else   							zys[i] = 4095;	break;}  //=1LV机侧动态调节标志位
//			case 14:{if(M_ChkFlag(SL_QEPPHE)==0)		zys[i] = 2048;				
//				     else   							zys[i] = 4095;	break;}  //=1LV机侧动态调节标志位
			case 15:{if(M_ChkFlag(SL_IN1_CBSTS)==0)		zys[i] = 2048;				
				     else   							zys[i] = 4095;	break;}  //=1LV机侧动态调节标志位
			case 16:{if(M_ChkFlag(SL_GRDFQE)==0)		zys[i] = 2048;				
				     else   							zys[i] = 4095;	break;}  //=1LV机侧动态调节标志位
			case 17:{if(M_ChkFlag(SL_HIDCOV)==0)		zys[i] = 2048;				
				     else   							zys[i] = 4095;	break;}  //=1
			case 18:{if(M_ChkFlag(SL_IDCOV)==0)			zys[i] = 2048;				
				     else   							zys[i] = 4095;	break;}  //=1
			case 19:{if(M_ChkFlag(SL_LV_SCRKEEPON)==0)	zys[i] = 2048;				
				     else   							zys[i] = 4095;	break;}  //=1


//------------------------------------------------------------------/放大倍数 magnify times----------------------
 			//----------------------AD OUT variables---------------------------------------------------
 			case 20:	{zys[i] = (int16)((AD_OUT_NGF_U.bc			* 0.005) * 204.8) + 2048; 	break;}//AD OUT variables 
 			case 21:	{zys[i] = (int16)((AD_OUT_STA_U.ab			* 0.005) * 204.8) + 2048;	break;}  
 			case 22:	{zys[i] = (int16)((AD_OUT_STA_U.bc			* 0.005) * 204.8) + 2048;	break;} 

 			case 23:	{zys[i] = (int16)((AD_OUT_SCR_I.a			* 0.01) * 204.8) + 2048;	break;}//
			case 24:	{zys[i] = (int16)((AD_OUT_SCR_I.b			* 0.01) * 204.8) + 2048;	break;}//
 		 
   			case 25:	{zys[i] = (int16)((AD_OUT_DC_I.b			* 0.01) * 204.8) + 2048; 	break;}  
   			case 26:	{zys[i] = (int16)((AD_OUT_NGS_U.bc			* 0.005) * 204.8) + 2048; 	break;}  

			case 27:	{zys[i] = (int16)((AD_OUT_UDC				* 0.005) * 204.8) + 2048;	break;}//AD OUT variables 

			case 28:	{zys[i] = (int16)((QEPDATA.omigamec			* 0.01) * 204.8) + 2048;break;}  
 			case 29:	{zys[i] = (int16)((CAP4.omigaslp			*  0.1) * 204.8) + 2048;break;} 
			case 30:	{zys[i] = (int16)((CAP4.omigasyn			* 0.01) * 204.8) + 2048;break;}  
			case 31:	{zys[i] = (int16)((QEPDATA.omigarote		* 0.01) * 204.8) + 2048;break;} 

			case 32:	{zys[i] = (int16)((AD_OUT_STA_I.a			* 0.01) * 204.8) + 2048;break;} 
			case 33:	{zys[i] = (int16)((AD_OUT_STA_I.b			* 0.01) * 204.8) + 2048;break;} 
			case 34:	{zys[i] = (int16)((AD_OUT_STA_I.c			* 0.01) * 204.8) + 2048;break;} 
			case 35:	{zys[i] = (int16)((AD_OUT_STA_I.ac			* 0.005) * 204.8) + 2048;break;} 
			case 36:	{zys[i] = (int16)((AD_OUT_STA_I.cb			* 0.005) * 204.8) + 2048;break;} 

			case 37:	{zys[i] = (int16)((TRS_MPR_I.a				* 0.01) * 204.8) + 2048;break;} 
			case 38:	{zys[i] = (int16)((TRS_MPR_I.b				* 0.01) * 204.8) + 2048;break;}  
			case 39:	{zys[i] = (int16)((TRS_MPR_I.c				* 0.01) * 204.8) + 2048;break;}

 			case 40:	{zys[i] = (int16)((TRS_MPR_I.d				* 0.01) * 204.8) + 2048;break;} 
 			case 41:	{zys[i] = (int16)((TRS_MPR_I.q				* 0.01) * 204.8) + 2048;break;}  

//---------------------------------MPR pi loop variables------------------------------------------------------------
 			case 42:	{zys[i] = (int16)((RUN.mpridrf				* 0.01) * 204.8) + 2048;break;}//
			case 43:	{zys[i] = (int16)((RUN.mpriqrf				* 0.01) * 204.8) + 2048;break;} 
			case 44:	{zys[i] = (int16)((CAP4.mprtrstheta			*    1) * 204.8) + 2048;break;}  
			case 45:	{zys[i] = (int16)((QEPDATA.rotposdisp		*    1) * 204.8) + 2048;break;}// 

			case 46:	{zys[i] = (int16)((PI_MPR_Id.reference		* 0.01) * 204.8) + 2048;break;}//MPR pi loop variables 
			case 47:	{zys[i] = (int16)((PI_MPR_Id.feedback		* 0.01) * 204.8) + 2048;break;} 
			case 48:	{zys[i] = (int16)((PI_MPR_Id.out			*  0.1) * 204.8) + 2048;break;} 

			case 49:	{zys[i] = (int16)((PI_MPR_Iq.reference		* 0.01) * 204.8) + 2048;break;}//MPR pi loop variables 
			case 50:	{zys[i] = (int16)((PI_MPR_Iq.feedback		* 0.01) * 204.8) + 2048;break;} 
			case 51:	{zys[i] = (int16)((PI_MPR_Iq.out			*  0.1) * 204.8) + 2048;break;}  

			case 52:	{zys[i] = (int16)((CAP4.omigaslp * MPR_Lr * DM_imrd		* 0.01) * 204.8) + 2048;	break;}//MPR pi loop variables 
			case 53:	{zys[i] = (int16)((SIGMA * CAP4.omigaslp * MPR_Lr * PI_MPR_Id.feedback	* 0.01) * 204.8) + 2048;	break;} 

			case 54:	{zys[i] = (int16)((DM_imrd					* 0.01) * 204.8) + 2048;break;}  

			case 55:	{zys[i] = (int16)((TRS_MPR_U.d				* 0.01) * 204.8) + 2048;break;} 
			case 56:	{zys[i] = (int16)((TRS_MPR_U.q				* 0.01) * 204.8) + 2048;break;} 

			case 57:	{zys[i] = (int16)((RUN.mpridrf_g			* 0.01) * 204.8) + 2048;break;} 
			case 58:	{zys[i] = (int16)((RUN.mpridrf_exi			* 0.01) * 204.8) + 2048;break;} 
			case 59:	{zys[i] = (int16)((RUN.mpridrf_var			* 0.01) * 204.8) + 2048;break;} 

			case 60:	{zys[i] = (int16)((QEPDATA.adsmposcnt		* 0.001) * 204.8) + 2048;break;}// 

//---------------------------------NPR pi loop variables------------------------------------------------------------
 			case 61:	{zys[i] = (int16)((TRS_NGS_U.d				* 0.01) * 204.8) + 2048;break;} 
			case 62:	{zys[i] = (int16)((TRS_NGS_U.q				* 0.01) * 204.8) + 2048;break;} 
			case 63:	{zys[i] = (int16)((TRS_NGS_U.dflt			* 0.01) * 204.8) + 2048;break;}
			case 64:	{zys[i] = (int16)((TRS_NGS_U.qflt			* 0.01) * 204.8) + 2048;break;}  

			case 65:	{zys[i] = (int16)((NGS_Udq_p				* 0.01) * 204.8) + 2048;break;} 
			case 66:	{zys[i] = (int16)((NGS_Udq_n				* 0.01) * 204.8) + 2048;break;}
	
			case 67:	{zys[i] = (int16)((TRS_NPR_U.sintheta		* 	 1)  * 204.8) + 2048;break;} 
			case 68:	{zys[i] = (int16)((TRS_NPR_U.costheta		*    1)  * 204.8) + 2048;break;}  
		 
 			case 69:	{zys[i] = (int16)((PI_NPR_U.reference		* 0.005) * 204.8) + 2048;break;}//NPR pi loop variables 
			case 70:	{zys[i] = (int16)((PI_NPR_U.feedback		* 0.005) * 204.8) + 2048;break;} 
 			case 71:	{zys[i] = (int16)((PI_NPR_U.out				* 0.01) * 204.8) + 2048;break;} 

			case 72:	{zys[i] = (int16)((TRS_NPR_I.a				* 0.01) * 204.8) + 2048;break;} 
			case 73:	{zys[i] = (int16)((TRS_NPR_I.b				* 0.01) * 204.8) + 2048;break;} 
			case 74:	{zys[i] = (int16)((TRS_NPR_I.c				* 0.01) * 204.8) + 2048;break;} 

	 	  	case 75:	{zys[i] = (int16)((TRS_NPR_I.d				* 0.01) * 204.8) + 2048;break;} 
 			case 76:	{zys[i] = (int16)((TRS_NPR_I.q				* 0.01) * 204.8) + 2048;break;}  

		 	case 77:	{zys[i] = (int16)((TRS_NPR_I.dflt			* 0.01) * 204.8) + 2048;break;} 
		  	case 78:	{zys[i] = (int16)((TRS_NPR_I.qflt			* 0.01) * 204.8) + 2048;break;}  

			case 79:	{zys[i] = (int16)((NGS_Udq_epsilon			*  0.1) * 204.8) + 2048;break;}

//-----------------------------NPR pi loop variables------------------------------------------------------------------
			case 80:	{zys[i] = (int16)((PI_NPR_Id.reference		* 0.01) * 204.8) + 2048;break;}//NPR pi loop variables  *200
			case 81:	{zys[i] = (int16)((PI_NPR_Id.feedback		* 0.01) * 204.8) + 2048;break;} 
			case 82:	{zys[i] = (int16)((PI_NPR_Id.out			* 0.01) * 204.8) + 2048;break;}  

			case 83:	{zys[i] = (int16)((PI_NPR_Iq.reference		* 0.01) * 204.8) + 2048;break;}//NPR pi loop variables 
			case 84:	{zys[i] = (int16)((PI_NPR_Iq.feedback		* 0.01) * 204.8) + 2048;break;} 
			case 85:	{zys[i] = (int16)((PI_NPR_Iq.out			* 0.01) * 204.8) + 2048;break;}   
	 		
			case 86:	{zys[i] = (int16)((TRS_NPR_U.d				* 0.01) * 204.8) + 2048;break;}  		 
 			case 87:	{zys[i] = (int16)((TRS_NPR_U.q				* 0.01) * 204.8) + 2048;break;} 

			case 88:	{zys[i] = (int16)((CAP4.nprtrstheta			*    1)  * 204.8) + 2048;break;} 
			case 89:	{zys[i] = (int16)((CAP4.nprtrstheta_lv		*    1)  * 204.8) + 2048;break;}

			case 91:	{zys[i] = (int16)((CAP4.omigasyn * NPR_L * PI_NPR_Iq.feedback	* 0.01)  * 204.8) + 2048;	break;}
			case 92:	{zys[i] = (int16)((CAP4.omigasyn * NPR_L * PI_NPR_Id.feedback	* 0.01)  * 204.8) + 2048;	break;}

 			case 93:	{zys[i] = (int16)((AD_OUT_SCR_I.a			* 0.01) * 204.8) + 2048;	break;}//
			case 94:	{zys[i] = (int16)((AD_OUT_SCR_I.b			* 0.01) * 204.8) + 2048;	break;}//

//------------------------------LVRT----------------------------------------------------------------------------------
			case 95:	{zys[i] = (int16)((NGS_Udq				    * 0.01) * 204.8) + 2048;break;}

			case 96:	{zys[i] = (int16)((PRO.Pnactive 	* 0.001	*  0.005) * 204.8) + 2048;break;}
			case 97:	{zys[i] = (int16)((PRO.Pnreactive 	* 0.001	*  0.01) * 204.8) + 2048;break;}
			case 98:	{zys[i] = (int16)((PRO.Pgactive 	* 0.001	*  0.005) * 204.8) + 2048;break;}
			case 99:	{zys[i] = (int16)((PRO.Pgreactive 	* 0.001	*  0.01) * 204.8) + 2048;break;}
			case 100:	{zys[i] = (int16)((PRO.Psactive 	* 0.001	*  0.005) * 204.8) + 2048;break;}
			case 101:	{zys[i] = (int16)((PRO.Psreactive 	* 0.001	*  0.01) * 204.8) + 2048;break;}
			case 102:	{zys[i] = (int16)((PRO.Pgactive 	* 0.001	*  0.005) * 204.8) + 2048;break;}

			case 103:	{zys[i] = (int16)(((DIP_NPR_I.qflt+DIP_STA_I.qflt)* 0.05) * 204.8) + 2048;break;}
			case 104:	{zys[i] = (int16)((DIP_STA_I.qflt				* 0.005) * 204.8) + 2048;break;}
			case 105:	{zys[i] = (int16)((DIP_NPR_I.qflt				* 0.05) * 204.8) + 2048;break;}

 			case 106:	{zys[i] = (int16)((AD_OUT_NGS_U.a			* 0.01) * 204.8) + 2048;	break;}//
			case 107:	{zys[i] = (int16)((AD_OUT_NGS_U.b 			* 0.01) * 204.8) + 2048;	break;}//
 			case 108:	{zys[i] = (int16)((AD_OUT_NGS_U.c			* 0.01) * 204.8) + 2048;	break;}//
			case 109:	{zys[i] = (int16)((AD_OUT_NGS_U.ab			* 0.01) * 204.8) + 2048;	break;}//

			case 110:	{zys[i] = (int16)((0				      	   ) * 204.8) + 2048;break;}

			case 111:	{zys[i] = (int16)((kq						* 1) * 204.8) + 2048;break;}
			case 112:	{zys[i] = (int16)((Pcreactive 	    * 0.001	*  0.1) * 204.8) + 2048;break;}
			case 113:	{zys[i] = (int16)((1				* 0.01) * 204.8) + 2048;break;}
			case 114:	{zys[i] = (int16)((1				*    1) * 204.8) + 2048;break;}
			case 115:	{zys[i] = (int16)((1				*    1) * 204.8) + 2048;break;}
			case 116:	{zys[i] = (int16)((1				*    1) * 204.8) + 2048;break;}
			case 117:	{zys[i] = (int16)((1				*    1) * 204.8) + 2048;break;}
			case 118:	{zys[i] = (int16)((1				*    1) * 204.8) + 2048;break;}
			case 119:	{zys[i] = (int16)((1				*    1) * 204.8) + 2048;break;}
			case 120:	{zys[i] = (int16)((1				*    1) * 204.8) + 2048;break;}
			case 121:	{zys[i] = (int16)((1				*    1) * 204.8) + 2048;break;}

//-------------------20111208磁链观测------------------------------------------
//-----------theta Phisdq 补偿idq
/*			case 122:	{zys[i] = (int16)((PHI_DATA_M.theta				*    1) * 204.8) + 2048;break;}

			case 123:	{zys[i] = (int16)((PHI_DATA_M.PHId				*    1) * 204.8) + 2048;break;}
			case 124:	{zys[i] = (int16)((PHI_DATA_M.PHIq				*    1) * 204.8) + 2048;break;}
			case 125:	{zys[i] = (int16)((PHI_DATA_M.PHIdflt			*    1) * 204.8) + 2048;break;}
			case 126:	{zys[i] = (int16)((PHI_DATA_M.PHIqflt			*    1) * 204.8) + 2048;break;}
			case 127:	{zys[i] = (int16)((PHI_DATA_M.PHIdflt2			*    1) * 204.8) + 2048;break;}
			case 128:	{zys[i] = (int16)((PHI_DATA_M.PHIqflt2			*    1) * 204.8) + 2048;break;}
			case 129:	{zys[i] = (int16)((PHI_DATA_M.Id				* 0.01) * 204.8) + 2048;break;}
			case 130:	{zys[i] = (int16)((PHI_DATA_M.Iq				* 0.01) * 204.8) + 2048;break;}

//-----------Rs*IsDQ
			case 131:	{zys[i] = (int16)((MPR_Rs * PHI_DATA_M.ISD		* 0.01) * 204.8) + 2048;break;}
			case 132:	{zys[i] = (int16)((MPR_Rs * PHI_DATA_M.ISQ		* 0.01) * 204.8) + 2048;break;}
//-----------LP input PhisDQ		
			case 133:	{zys[i] = (int16)((PHI_DATA_M.ISD				* 0.01) * 204.8) + 2048;break;}
			case 134:	{zys[i] = (int16)((PHI_DATA_M.ISQ				* 0.01) * 204.8) + 2048;break;}
			case 135:	{zys[i] = (int16)((1				* 0.01) * 204.8) + 2048;break;}
			case 136:	{zys[i] = (int16)((1				* 0.01) * 204.8) + 2048;break;}

			case 137:	{zys[i] = (int16)((PHI_DATA_M.PHIMd				*    1) * 204.8) + 2048;break;}
			case 138:	{zys[i] = (int16)((PHI_DATA_M.PHIMq				*    1) * 204.8) + 2048;break;}
			case 139:	{zys[i] = (int16)((PHI_DATA_M.PHIMdflt			*    1) * 204.8) + 2048;break;}
			case 140:	{zys[i] = (int16)((PHI_DATA_M.PHIMqflt			*    1) * 204.8) + 2048;break;}
			case 141:	{zys[i] = (int16)((MPR_Rs / MPR_Ls * PHI_DATA_M.PHIMdflt*    0.1) * 204.8) + 2048;break;}
			case 142:	{zys[i] = (int16)((MPR_Rs / MPR_Ls * PHI_DATA_M.PHIMqflt*    0.1) * 204.8) + 2048;break;}
			case 143:	{zys[i] = (int16)((QEPDATA.omigarote * PHI_DATA_M.PHIMdflt*    0.01) * 204.8) + 2048;break;}
			case 144:	{zys[i] = (int16)((QEPDATA.omigarote * PHI_DATA_M.PHIMqflt*    0.01) * 204.8) + 2048;break;}
*/
			case 145:	{zys[i] = (int16)((TRS_NGS_U.dflt * SQRT3		* 0.01) * 204.8) + 2048;break;}
/*	
			case 146:	{zys[i] = (int16)((RS_phid                      *    0.1) * 204.8) + 2048;break;}
			case 147:	{zys[i] = (int16)((RS_phiq                      *    0.1) * 204.8) + 2048;break;}
			case 148:	{zys[i] = (int16)((CM_vrd                       *   0.01) * 204.8) + 2048;break;}
			case 149:	{zys[i] = (int16)((CM_vrq                       *   0.01) * 204.8) + 2048;break;}
*/
//			case 150:	{zys[i] = (int16)((TRS_MPR_U.ab                 *   0.01) * 204.8) + 2048;break;}
//			case 151:	{zys[i] = (int16)((TRS_MPR_U.bc                 *   0.01) * 204.8) + 2048;break;}
			case 152:	{zys[i] = (int16)((TRS_MPR_U.a                  *   0.01) * 204.8) + 2048;break;}
			case 153:	{zys[i] = (int16)((TRS_MPR_U.b                  *   0.01) * 204.8) + 2048;break;}
			case 154:	{zys[i] = (int16)((TRS_MPR_U.c                  *   0.01) * 204.8) + 2048;break;}

//---------PHIObs-I_model_201201
/*			case 155:	{zys[i] = (int16)((PHI_DATA_M.Isd               *   0.01) * 204.8) + 2048;break;}
			case 156:	{zys[i] = (int16)((PHI_DATA_M.Isq               *   0.01) * 204.8) + 2048;break;}
			case 157:	{zys[i] = (int16)((PHI_DATA_M.Isdflt            *   0.01) * 204.8) + 2048;break;}
			case 158:	{zys[i] = (int16)((PHI_DATA_M.Isqflt            *   0.01) * 204.8) + 2048;break;}
			case 159:	{zys[i] = (int16)((TRS_SCR_I.dflt               *   0.01) * 204.8) + 2048;break;}
			case 160:	{zys[i] = (int16)((TRS_SCR_I.qflt               *   0.01) * 204.8) + 2048;break;}
			case 161:	{zys[i] = (int16)((PHI_DATA_M.Ird               *   0.01) * 204.8) + 2048;break;}
			case 162:	{zys[i] = (int16)((PHI_DATA_M.Irq               *   0.01) * 204.8) + 2048;break;}
			case 163:	{zys[i] = (int16)((PHI_DATA_M.PHId              *      1) * 204.8) + 2048;break;}
			case 164:	{zys[i] = (int16)((PHI_DATA_M.PHIq              *      1) * 204.8) + 2048;break;}
			case 165:	{zys[i] = (int16)((PHI_DATA_M.PHId0             *      1) * 204.8) + 2048;break;}
			case 166:	{zys[i] = (int16)((PHI_DATA_M.PHIdflt2          *      1) * 204.8) + 2048;break;}
			case 167:	{zys[i] = (int16)((TRS_SCR_I.a               	*   0.01) * 204.8) + 2048;break;}
			case 168:	{zys[i] = (int16)((TRS_SCR_I.b               	*   0.01) * 204.8) + 2048;break;}
*/
			case 169:	{zys[i] = (int16)((PI_DATA_PLL.outflt        *      0.01) * 204.8) + 2048;break;}
			case 170:	{zys[i] = (int16)((CAP4.freqtmp		         *      0.01) * 204.8) + 2048;break;}
			case 171:	{zys[i] = (int16)((1           *      1) * 204.8) + 2048;break;}
			case 172:	{zys[i] = (int16)((1           *      1) * 204.8) + 2048;break;}

//			case 173:	{zys[i] = (int16)((MC_DATA.k		            *      1) * 204.8) + 2048;break;}
//			case 174:	{zys[i] = (int16)((PHI_DATA_M.k		            *      1) * 204.8) + 2048;break;}

			case 175:	{zys[i] = (int16)((1		        *      0.01) * 204.8) + 2048;break;}
			case 176:	{zys[i] = (int16)((1		        *      0.01) * 204.8) + 2048;break;}
			case 177:	{zys[i] = (int16)((TRS_STA_I.d		      		*      0.01) * 204.8) + 2048;break;}
			case 178:	{zys[i] = (int16)((TRS_STA_I.q			        *      0.01) * 204.8) + 2048;break;}
//			case 179:	{zys[i] = (int16)((PHI_DATA_M.PHIq0             *      1) * 204.8) + 2048;break;}

//------------Te and Isdq feedback
			case 184:	{zys[i] = (int16)((Te_feedback		    		*      0.001) * 204.8) + 2048;break;}

			case 185:	{zys[i] = (int16)((Te_instant			        *      0.001) * 204.8) + 2048;break;}
/*			case 186:	{zys[i] = (int16)((Te_instant2			        *      0.001) * 204.8) + 2048;break;}
			case 187:	{zys[i] = (int16)((Te_instant3			        *      0.001) * 204.8) + 2048;break;}
			case 188:	{zys[i] = (int16)((Isd_feedback		    		*      0.005) * 204.8) + 2048;break;}
			case 189:	{zys[i] = (int16)((Isq_feedback			        *      0.005) * 204.8) + 2048;break;}
*/

			case 200:	{zys[i] = (int16)((GIVE.toqrf			    	*      0.001) * 204.8) + 2048;break;}
			case 201:	{zys[i] = (int16)((GIVE.toqrfflt			    *      0.001) * 204.8) + 2048;break;}
			case 202:	{zys[i] = (int16)((GIVE.toqrfrun			    *      0.001) * 204.8) + 2048;break;}
			case 203:	{zys[i] = (int16)((RUN.toqrf			    	*      0.001) * 204.8) + 2048;break;}
			case 204:	{zys[i] = (int16)((RUN.mpriqrf_g		   		*      0.01) * 204.8) + 2048;break;}

			case 205:	{zys[i] = (int16)((DIP_STA_U.dflt			    *      0.01) * 204.8) + 2048;break;}
			case 206:	{zys[i] = (int16)((DIP_STA_U.qflt			    *      0.01) * 204.8) + 2048;break;}
			case 207:	{zys[i] = (int16)((DIP_STA_I.dflt			    *      0.005) * 204.8) + 2048;break;}
			case 208:	{zys[i] = (int16)((DIP_STA_I.qflt		   		*      0.005) * 204.8) + 2048;break;}
			case 209:	{zys[i] = (int16)((DIP_NPR_U.dflt			    *      0.01) * 204.8) + 2048;break;}
			case 210:	{zys[i] = (int16)((DIP_NPR_U.qflt			    *      0.01) * 204.8) + 2048;break;}
			case 211:	{zys[i] = (int16)((DIP_NPR_I.dflt			    *      0.01) * 204.8) + 2048;break;}
			case 212:	{zys[i] = (int16)((DIP_NPR_I.qflt		   		*      0.01) * 204.8) + 2048;break;}

			case 213:	{zys[i] = (int16)((TRS_MPR_I.qflt		   		*      0.01) * 204.8) + 2048;break;}
			case 214:	{zys[i] = (int16)((DIP_MPR_I.qflt		   		*      0.01) * 204.8) + 2048;break;}

			case 215:	{zys[i] = (int16)((PRO.Pnactive2 	* 0.001	*  0.005) * 204.8) + 2048;break;}
			case 216:	{zys[i] = (int16)((PRO.Pnreactive2 	* 0.001	*  0.01) * 204.8) + 2048;break;}
			case 217:	{zys[i] = (int16)((PRO.Pgactive2 	* 0.001	*  0.005) * 204.8) + 2048;break;}
			case 218:	{zys[i] = (int16)((PRO.Pgreactive2 	* 0.001	*  0.01) * 204.8) + 2048;break;}
			case 219:	{zys[i] = (int16)((PRO.Psactive2 	* 0.001	*  0.005) * 204.8) + 2048;break;}
			case 220:	{zys[i] = (int16)((PRO.Psreactive2 	* 0.001	*  0.01) * 204.8) + 2048;break;}

			case 221:	{zys[i] = (int16)((CNT_SCRON				*  1) * 204.8) + 2048;break;}
			case 222:	{zys[i] = (int16)((NGS_Udq_pflt				*  0.01) * 204.8) + 2048;break;}


//------------不平衡 陷波器
/*			case 200:	{zys[i] = (int16)((TRS_NGS_U.dflt			    *      0.01) * 204.8) + 2048;break;}
			case 201:	{zys[i] = (int16)((TRS_NGS_U.qflt			    *      0.01) * 204.8) + 2048;break;}
			case 202:	{zys[i] = (int16)((TRS_NGS_U.dnflt			    *      0.01) * 204.8) + 2048;break;}
			case 203:	{zys[i] = (int16)((TRS_NGS_U.qnflt		   		*      0.01) * 204.8) + 2048;break;}
			case 204:	{zys[i] = (int16)((TRS_NGS_U.dbsf			    *      0.01) * 204.8) + 2048;break;}
			case 205:	{zys[i] = (int16)((TRS_NGS_U.qbsf			    *      0.01) * 204.8) + 2048;break;}
			case 206:	{zys[i] = (int16)((TRS_NGS_U.dnbsf		    	*      0.01) * 204.8) + 2048;break;}
			case 207:	{zys[i] = (int16)((TRS_NGS_U.qnbsf			    *      0.01) * 204.8) + 2048;break;}
			case 208:	{zys[i] = (int16)((NGS_Udq_p2			        *      0.01) * 204.8) + 2048;break;}
			case 209:	{zys[i] = (int16)((NGS_Udq_n2		    		*      0.01) * 204.8) + 2048;break;}
			case 210:	{zys[i] = (int16)((NGS_Udq_epsilon2			    *      0.1)  * 204.8) + 2048;break;}
*/
           default:   break;	
		}
	}

//------------------DA channel adjust----------------------------------------------------------
		zys[0] = zys[0] - 0;	//adjusst ad channel  201205LVRTatZB
		zys[1] = zys[1] + 0;	//adjusst ad channel
		zys[2] = zys[2] + 0;	//adjusst ad channel
		zys[3] = zys[3] - 0;	//adjusst ad channel

		if		(zys[0]>=4095)  	zys[0] = 4095;
		else if	(zys[0]<=0)			zys[0] = 0; 

		if		(zys[1]>=4095)  	zys[1] = 4095;
		else if	(zys[1]<=0)			zys[1] = 0;  

		if		(zys[2]>=4095)  	zys[2] = 4095;
		else if	(zys[2]<=0)			zys[2] = 0;  

		if		(zys[3]>=4095)  	zys[3] = 4095;
		else if	(zys[3]<=0)			zys[3] = 0;  
		 
	*DA_ADD0 =	zys[0];
	*DA_ADD1 =	zys[1];
	*DA_ADD2 =	zys[2];
	*DA_ADD3 =	zys[3];

}


/*********************************************************************************************************
** 函数名称: Output
** 功能描� 10路信号输出; 8路LED显示输出
** 输　入:
** 输　出:
** 注  释:
**-------------------------------------------------------------------------------------------------------
** 作　者:
** 日　期:
**-------------------------------------------------------------------------------------------------------
** 修�
** 日　期:
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
void Output(void)
{
//------------------------------数据输出-----------------------------------

   *OUT1_ADDR = _OUT1_DATA;
   *OUT2_ADDR = _OUT2_DATA;

//-----------------------------启动开关意外动作检测110818-------------------------

	if(state_n==0)
	{
		action1 = (_OUT1_DATA & 0x003F);
		state_n=1;
	}
	else
	{
		action2 = (_OUT1_DATA & 0x003F);
		state_n=0;
	}

	if(action1 != action2)
	{
		M_ClrFlag(SL_SWITCHDETECT);									//处于正常动作检测
		state_m=0;
		MAIN_LOOP.cnt_detectdelay = 0;
	}

	if(state_m==0)
	{
 	    if(M_ChkCounter(MAIN_LOOP.cnt_detectdelay,DELAY_DETECT)>=0)		//从正常检测转换至意外检测之间延时_STDBY4 ms
 	    {
 	    	state_m=1;

			MAIN_LOOP.cnt_cberror=0;								//清定时器
			MAIN_LOOP.cnt_mainkerror=0;								//清定时器
			MAIN_LOOP.cnt_mainferror=0;								//清定时器
			MAIN_LOOP.cnt_stacerror=0;								//清定时器
		}

	}

	else if((action1 == action2) && (state_m==1))
	{
	    M_SetFlag(SL_SWITCHDETECT);									//处于意外动作检测

	}

//---------20121107----------testCL_ZKLVRT--------
	if((_STDBY9&0x0002)!=0)		M_SetFlag(CL_ZKLVRT);	//116.1	atsp

//---------20121107----------testCL_ZKLVRT--------

//-----------------------------功率散热风机控制----------------------------------
	if(M_ChkFlag(SL_FAN_WORK)!=0) 	M_SetFlag(CL_FANWORK);
	else							M_ClrFlag(CL_FANWORK); 
/*
//-----------------------------功率散热风机控制--20100429systest--------------------------------
	if(M_ChkFlag(SL_FAN_WORK)!=0) 	
	{
		if(AMUX.skiiptempmax>35.0)	 	M_SetFlag(CL_FANWORK);          //启动功率组件风机
		else if(AMUX.skiiptempmax<15.0)	M_ClrFlag(CL_FANWORK);          //关闭功率组件风机
	}
	else
	{
//		if(AMUX.skiiptempmax<50.0)	 M_ClrFlag(CL_FANWORK);          	//关闭功率组件风机
		M_ClrFlag(CL_FANWORK); 
	}							
*/
//---------------------CANOPEN反馈主控的状态变量---------------------------------------------------
//-----------------------------------tx_state1----------------------------------------	
	if(M_ChkFlag(SL_CBCLOSED)!=0)	  		SCI_canopen.tx_state1 |= COM_NPRREADY;
	else									SCI_canopen.tx_state1 &= COM_NPRREADY_NOT;

	if(M_ChkFlag(SL_NPR_PWMOUT)!=0)	  		SCI_canopen.tx_state1 |= COM_NPRON;		//201005atcpc
	else 									SCI_canopen.tx_state1 &= COM_NPRON_NOT;

	if(M_ChkFlag(SL_MPR_SYNOK)!=0)	  		SCI_canopen.tx_state1 |= COM_READYGENERATION;
	else 									SCI_canopen.tx_state1 &= COM_READYGENERATION_NOT;

	if(M_ChkFlag(SL_SPEED_IN_RANGE)!=0)	  	SCI_canopen.tx_state1 |= COM_SPEEDINRANGE;
	else 									SCI_canopen.tx_state1 &= COM_SPEEDINRANGE_NOT;

	if((M_ChkFlag(SL_SERIESTOP)!=0)||(M_ChkFlag(SL_ERRSTOP)!=0))	  	  SCI_canopen.tx_state1 |= COM_FAILURE;
	else  if((M_ChkFlag(SL_SERIESTOP)==0)&&(M_ChkFlag(SL_ERRSTOP)==0))	  SCI_canopen.tx_state1 &= COM_FAILURE_NOT;

	if(M_ChkFlag(SL_SERIESTOP)!=0)	  		SCI_canopen.tx_state1 |= COM_FAILUREA;
	else 									SCI_canopen.tx_state1 &= COM_FAILUREA_NOT;

	if(M_ChkFlag(SL_ERRSTOP)!=0)	  		SCI_canopen.tx_state1 |= COM_FAILUREB;
	else 									SCI_canopen.tx_state1 &= COM_FAILUREB_NOT;

	if(M_ChkFlag(SL_PGOV_COM)!=0)	  		SCI_canopen.tx_state1 |= COM_PLIM;
    else 									SCI_canopen.tx_state1 &= COM_PLIM_NOT;

	if(M_ChkFlag(SL_QGOV_COM)!=0)	  		SCI_canopen.tx_state1 |= COM_QLIM;
	else 									SCI_canopen.tx_state1 &= COM_QLIM_NOT;
	

	SCI_canopen.tx_state1 &= 0x7FFF;
	SCI_canopen.tx_state1 |= (SCI_canopen.heartbeat <<8);

//-----------------------------------tx_state2----------------------------------------	

//	if(((PRO.STA_iac* 1.05)>_SC_IACOVST)||((PRO.STA_iba* 1.05)>_SC_IACOVST))	  	SCI_canopen.tx_state2 |= COM_ILIM;
//	else																			SCI_canopen.tx_state2 &= COM_ILIM_NOT;

	if(M_ChkFlag(SL_IN1_EXESTOP)!=0)	  	SCI_canopen.tx_state2 |= COM_ESTOP;     //20090815
	else 									SCI_canopen.tx_state2 &= COM_ESTOP_NOT;

	if(M_ChkFlag(SL_CBTRIP)!=0)	  			SCI_canopen.tx_state2 |= COM_CBTRIP;
	else 									SCI_canopen.tx_state2 &= COM_CBTRIP_NOT;

	if(M_ChkFlag(SL_IN1_CBSTS)!=0)	  		SCI_canopen.tx_state2 |= COM_CBCLOSED;			//1=CB closed 0=CB open
	else 									SCI_canopen.tx_state2 &= COM_CBCLOSED_NOT;

//	if(PRO.Pg>1.8e6)	  					SCI_canopen.tx_state2 |= COM_POWLIM;
//    else if(PRO.Pg<1.75e6)					SCI_canopen.tx_state2 &= COM_POWLIM_NOT;	

//--------120507---------
/*	if(temp_flag3==0)	
	{
		if(M_ChkFlag(SL_LV_QWORKING)!=0)	 //20130225
			SCI_canopen.tx_torque= (int16)(Te_feedback_lv * 16383.0 / CAN_TEN);
		else
			SCI_canopen.tx_torque= (int16)(Te_feedback * 16383.0 / CAN_TEN);
//		SCI_canopen.tx_torque= (int16)(DISP.toqfb * 16383.0 / CAN_TEN);
//		SCI_canopen.tx_torque= (int16)(5 * 16383.0 / CAN_TEN);
		SCI_canopen.tx_skiiptempmax = (int16)(AMUX.skiiptempmax * 16383.0 / CAN_TEMP);
//		SCI_canopen.tx_skiiptempmax = (int16)(50 * 16383.0 / CAN_TEMP);
		temp_flag3 =1;
	}
	else
	{
		if(M_ChkFlag(SL_LV_QWORKING)!=0)	 //20130225
			SCI_canopen.tx_torque= (int16)(Te_feedback_lv * 16383.0 / CAN_TEN);
		else
			SCI_canopen.tx_torque= (int16)(Te_feedback * 16383.0 / CAN_TEN);
//		SCI_canopen.tx_torque= (int16)(DISP.toqfb * 16383.0 / CAN_TEN) + 1;
//		SCI_canopen.tx_torque= (int16)(5 * 16383.0 / CAN_TEN) + 1;
		SCI_canopen.tx_skiiptempmax = (int16)(AMUX.skiiptempmax * 16383.0 / CAN_TEMP) + 1;
//		SCI_canopen.tx_skiiptempmax = (int16)(50 * 16383.0 / CAN_TEMP) + 1;
		temp_flag3 =0;
	}
*/
//--------20130308--------
		if(M_ChkFlag(SL_IN1_STATORK)!=0)
		{
			if(M_ChkFlag(SL_LV_QWORKING)!=0)	 //20130225
				SCI_canopen.tx_torque= (int16)(Te_feedback_lv * 16383.0 / CAN_TEN);
			else
				SCI_canopen.tx_torque= (int16)(Te_feedback * 16383.0 / CAN_TEN);
		}
		else	SCI_canopen.tx_torque= 0;

		if(temp_flag3==0)
		{
			SCI_canopen.tx_skiiptempmax = (int16)(AMUX.skiiptempmax * 16383.0 / CAN_TEMP);
			temp_flag3 =1;
		}
		else
		{
			SCI_canopen.tx_skiiptempmax = (int16)(AMUX.skiiptempmax * 16383.0 / CAN_TEMP) + 1;
			temp_flag3 =0;
		}



//-----------------------------显示灯输出----------------------------------
	if(M_ChkFlag(SL_DISPLAY0)!=0) 	GpioDataRegs.GPBCLEAR.bit.GPIO56 = 1;
	else							GpioDataRegs.GPBSET.bit.GPIO56 = 1;

	if(M_ChkFlag(SL_DISPLAY1)!=0)  	GpioDataRegs.GPBCLEAR.bit.GPIO57 = 1;
	else							GpioDataRegs.GPBSET.bit.GPIO57 = 1;
	
	if(M_ChkFlag(SL_DISPLAY2)!=0) 	GpioDataRegs.GPBCLEAR.bit.GPIO58 = 1;
	else							GpioDataRegs.GPBSET.bit.GPIO58 = 1;

	if(M_ChkFlag(SL_DISPLAY3)!=0)  	GpioDataRegs.GPBCLEAR.bit.GPIO59 = 1;
	else							GpioDataRegs.GPBSET.bit.GPIO59 = 1;

	if(M_ChkFlag(SL_DISPLAY4)!=0) 	GpioDataRegs.GPBCLEAR.bit.GPIO60 = 1;
	else							GpioDataRegs.GPBSET.bit.GPIO60 = 1;

	if(M_ChkFlag(SL_DISPLAY5)!=0)  	GpioDataRegs.GPBCLEAR.bit.GPIO61 = 1;
	else							GpioDataRegs.GPBSET.bit.GPIO61 = 1;

	if(M_ChkFlag(SL_DISPLAY6)!=0) 	GpioDataRegs.GPBCLEAR.bit.GPIO62 = 1;
	else							GpioDataRegs.GPBSET.bit.GPIO62 = 1;

	if(M_ChkFlag(SL_DISPLAY7)!=0)  	GpioDataRegs.GPBCLEAR.bit.GPIO63 = 1;
	else							GpioDataRegs.GPBSET.bit.GPIO63 = 1;

} 
/*********************************************************************************************************
** 函数名称: Input
** 功能描述: 16路信号输入;
** 输　入:
** 输　出:
** 注  释:
**-------------------------------------------------------------------------------------------------------
** 作　者:
** 日　期:
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
void Input(void)
{
	Uint16 tempa,tempb,tempc,tempda,tempdb,tempdc;
	float temp_Usn,temp_Uro;
//--------------------------------数据输入----------------------------------
	tempa = *IN1_ADDR; 
	tempb = *IN2_ADDR;
	tempc = *IN3_ADDR;

	DELAY_US(100L);        //100us延时，IO输入防抖

	tempda = *IN1_ADDR;    
	tempdb = *IN2_ADDR;
	tempdc = *IN3_ADDR;

//--------------------------------数据输入----------------------------------
	if((tempa==tempda)&&(tempb==tempdb))	
		_IN12_DATA = (tempa & 0x00FF) | ((tempb<<8) & 0xFF00);

	if(tempc==tempdc)		
		_IN34_DATA = (tempc & 0x00FF);

//---------------------CANOPEN指令控制------------------------------------------------------

if(M_ChkFlag(SL_ENPCOPER)==0)
{ 
	if((SCI_canopen.rx_controlword & COM_EIN)==COM_EIN)	    
	{
		if(M_ChkCounter(MAIN_LOOP.cnt_ocsein1,DELAY_OCSEIN1)>0)		M_SetFlag(SL_OCS_EIN);	//20090817 250ms
		MAIN_LOOP.cnt_ocsein2=0;	
	}								
	else 		  											
	{
		if(M_ChkCounter(MAIN_LOOP.cnt_ocsein2,DELAY_OCSEIN2)>0)		M_ClrFlag(SL_OCS_EIN);	//20090817 250ms 
		MAIN_LOOP.cnt_ocsein1=0;
	}

/*//----------20120321--------------
	if(((SCI_canopen.rx_controlword & COM_EIN)==COM_EIN) && (M_ChkFlag(SL_SYSOFF)==0))	    
	{
		if(M_ChkCounter(MAIN_LOOP.cnt_ocsein1,DELAY_OCSEIN1)>0)		
		{
			M_SetFlag(SL_OCS_EIN);		//20090817 250ms
			M_SetFlag(SL_OCS_SYSRUN);	//20110707符合华创通讯,原2个指令合二为一
		}
		MAIN_LOOP.cnt_ocsein2=0;	
	}
	else
	{
		if(M_ChkFlag(SL_SYSOFF)!=0)
		{
			M_ClrFlag(SL_OCS_EIN);
			M_ClrFlag(SL_OCS_SYSRUN);
		}
		
		if(M_ChkCounter(MAIN_LOOP.cnt_ocsein2,DELAY_OCSEIN2)>0)		
		{
			M_ClrFlag(SL_OCS_EIN);		//20090817 250ms 
			M_ClrFlag(SL_OCS_SYSRUN); 	//20110707符合华创通讯,原2个指令合�
		}
		MAIN_LOOP.cnt_ocsein1=0;
	}
//-----------------------------
*/

//---------------------上位机要求复位故障------------------------------------------------------
	if((SCI_canopen.rx_controlword & COM_OCSRESET)==COM_OCSRESET)	M_SetFlag(SL_OCS_RESET);									
	else 	   														M_ClrFlag(SL_OCS_RESET);													

/*	
//---------------------上位机要求变流器启动------------------------------------------------------
	if((SCI_canopen.rx_controlword & COM_SYSRUN)==COM_SYSRUN)
	{
		if(M_ChkCounter(MAIN_LOOP.cnt_ocssysrun1,DELAY_OCSSYSRUN1)>0)	M_SetFlag(SL_OCS_SYSRUN);	//20090817 250ms
		MAIN_LOOP.cnt_ocssysrun2=0;	
	}									
	else 		  											
	{
		if(M_ChkCounter(MAIN_LOOP.cnt_ocssysrun2,DELAY_OCSSYSRUN2)>0)	M_ClrFlag(SL_OCS_SYSRUN);	//20090817  250ms
		MAIN_LOOP.cnt_ocssysrun1=0;
	}
*/
//---------------------上位机要求变流器启动-------20121206---------------------------------------
	if(((SCI_canopen.rx_controlword & COM_SYSRUN)==COM_SYSRUN) && (M_ChkFlag(SL_SYSOFF)==0) && (PRO.speedflt>950))
	{
		if(M_ChkCounter(MAIN_LOOP.cnt_ocssysrun1,DELAY_OCSSYSRUN1)>0)	M_SetFlag(SL_OCS_SYSRUN);	//20090817 250ms
		MAIN_LOOP.cnt_ocssysrun2=0;	
	}
	else
	{
		if(M_ChkFlag(SL_SYSOFF)!=0)			M_ClrFlag(SL_OCS_SYSRUN);

		if(M_ChkCounter(MAIN_LOOP.cnt_ocssysrun2,DELAY_OCSSYSRUN2)>0)	M_ClrFlag(SL_OCS_SYSRUN);	//20090817  250ms
		MAIN_LOOP.cnt_ocssysrun1=0;
	}

//---------20130306--------
	if(M_ChkFlag(SL_LV_CLRERRAM)!=0)
	{
		cnt_lv_clrerram ++ ;		//20130309
		M_SetFlag(SL_PC_ERRDATACLR);
		if(cnt_lv_clrerram>=10)		//20130309
		{
			M_ClrFlag(SL_LV_CLRERRAM);
			cnt_lv_clrerram = 0;
		}
	}
//-------------------------

//---------------------上位机要求网侧变流器单涝诵形薰Σ⑼�-----------------------------------------------------
//	if((SCI_canopen.rx_controlword & COM_NPREIN)==COM_NPREIN)	M_SetFlag(SL_OCS_NPREIN);  //暂时屏蔽
//	else 		  												M_ClrFlag(SL_OCS_NPREIN); 
}	 
//---------------------------接收操作器来的PI环参数-------------------------------------------------
	PI_PARA_NPRU.kp           = _NPR_U_Kp/100.00;			//DOT2属性
    PI_PARA_NPRU.ki           = _NPR_U_Ki/10.00;			//DOT1属性
//	PI_PARA_NPRU.kd           = _NPR_U_Kd/1000.00;			//DOT3属性
	PI_PARA_NPRU.outmax       = _NPR_U_outmax;
	PI_PARA_NPRU.errmax       = _NPR_U_errmax/10.00;		//DOT1粜�	//NPR电压环参数
	PI_PARA_NPRU.errmin       = _NPR_U_errmin/1000.00;	    //DOT3属性
	PI_PARA_NPRU.incrementmax = _NPR_U_incrementmax/10.00;  //DOT1属性
/*
	PI_PARA_NPRID.kp           = _NPR_ID_Kp/100.00;			//DOT2属性
    PI_PARA_NPRID.ki           = _NPR_ID_Ki/10.00;			//DOT1属性
//    PI_PARA_NPRID.kd           = _NPR_ID_Kd/1000.00;			//DOT3属性
	PI_PARA_NPRID.outmax       = _NPR_ID_outmax;		 					    //NPR电流环参数
	PI_PARA_NPRID.errmax       = _NPR_ID_errmax/10.00;		//DOT1属性
	PI_PARA_NPRID.errmin       = _NPR_ID_errmin/1000.00;		//DOT3属性
	PI_PARA_NPRID.incrementmax = _NPR_ID_incrementmax/10.00;	//DOT1属性
*/
//--------20121210--------
	lv_ctrl1           = _NPR_ID_Kp/100.00;			//DOT2属性
    lv_ctrl2           = _NPR_ID_Ki/10.00;			//DOT1属性
	lv_ctrl3	       = _NPR_ID_outmax;		 					    //NPR电流环参数
	lv_ctrl4 			= _NPR_ID_errmax/10.00;		//DOT1属性
	lv_ctrl5			= _NPR_ID_errmin/1000.00;		//DOT3属性
	lv_ctrl6			= _NPR_ID_incrementmax/10.00;	//DOT1属性

	PI_PARA_NPRID.kp           = 0.4;			//DOT2属性
    PI_PARA_NPRID.ki           = 167;			//DOT1属性
	PI_PARA_NPRID.outmax       = 200;		    //NPR电流环参数
	PI_PARA_NPRID.errmax       = 50;			//DOT1属性
	PI_PARA_NPRID.errmin       = 0;				//DOT3属性
	PI_PARA_NPRID.incrementmax = 55;			//DOT1属性
//--------20121210--------

	PI_PARA_NPRIQ.kp           = _NPR_IQ_Kp/100.00;			//DOT2属性
    PI_PARA_NPRIQ.ki           = _NPR_IQ_Ki/10.00;			//DOT1属性
//    PI_PARA_NPRIQ.kd           = _NPR_IQ_Kd/1000.00;			//DOT3属性
	PI_PARA_NPRIQ.outmax       = _NPR_IQ_outmax;		 					    //NPR电流环参数
	PI_PARA_NPRIQ.errmax       = _NPR_IQ_errmax/10.00;		//DOT1属性
	PI_PARA_NPRIQ.errmin       = _NPR_IQ_errmin/1000.00;		//DOT3属性
	PI_PARA_NPRIQ.incrementmax = _NPR_IQ_incrementmax/10.00;	//DOT1属性

	PI_PARA_MPRID.kp           = _MPR_ID_Kp/100.00;			//DOT2属性
    PI_PARA_MPRID.ki           = _MPR_ID_Ki/10.00;			//DOT1属性
 //   PI_PARA_MPRID.kd           = _MPR_ID_Kd/1000.00;			//DOT3属性
	PI_PARA_MPRID.outmax       = _MPR_ID_outmax;   							//MPR电流环参数
	PI_PARA_MPRID.errmax       = _MPR_ID_errmax/10.00;		//DOT1属性
	PI_PARA_MPRID.errmin       = _MPR_ID_errmin/1000.00;		//DOT3属性
	PI_PARA_MPRID.incrementmax = _MPR_ID_incrementmax/10.00;	//DOT1属性

	PI_PARA_MPRIQ.kp           = _MPR_IQ_Kp/100.00;			//DOT2属性
    PI_PARA_MPRIQ.ki           = _MPR_IQ_Ki/10.00;			//DOT1属性
//    PI_PARA_MPRIQ.kd           = _MPR_IQ_Kd/1000.00;			//DOT3属性
	PI_PARA_MPRIQ.outmax       = _MPR_IQ_outmax;   							//MPR电流环参数
	PI_PARA_MPRIQ.errmax       = _MPR_IQ_errmax/10.00;		//DOT1属�
	PI_PARA_MPRIQ.errmin       = _MPR_IQ_errmin/1000.00;		//DOT3属性
	PI_PARA_MPRIQ.incrementmax = _MPR_IQ_incrementmax/10.00;	//DOT1属性
/*
	PI_PARA_MPRU.kp           = _MPR_U_Kp/100.00;			//DOT2属性
    PI_PARA_MPRU.ki           = _MPR_U_Ki/10.00;			//DOT1属性
    PI_PARA_MPRU.kd           = _MPR_U_Kd/1000.00;			//DOT3属性
	PI_PARA_MPRU.outmax       = _MPR_U_outmax;   							//MPR电压环参数
	PI_PARA_MPRU.errmax       = _MPR_U_errmax/10.00;		//DOT1属性
	PI_PARA_MPRU.errmin       = _MPR_U_errmin/1000.00;		//DOT3属性
	PI_PARA_MPRU.incrementmax = _MPR_U_incrementmax/10.00;  //DOT1属性

	PI_PARA_DYNU.kp           = _DYN_U_Kp/100.00;			//DOT2属性
    PI_PARA_DYNU.ki           = _DYN_U_Ki/10.00;			//DOT1属性
    PI_PARA_DYNU.kd           = _DYN_U_Kd/1000.00;			//DOT3属性
	PI_PARA_DYNU.outmax       = _DYN_U_outmax;   							//动态电压环参数
	PI_PARA_DYNU.errmax       = _DYN_U_errmax/10.00;		//DOT1属性
	PI_PARA_DYNU.errmin       = _DYN_U_errmin/1000.00;		//DOT3属性
	PI_PARA_DYNU.incrementmax = _DYN_U_incrementmax/10.00;  //DOT1属性
*/
//----网侧电压环启动动态PI给固定值BJTULVRT201204
	PI_PARA_DYNU.kp           = 0.15;						//DOT2属性
    PI_PARA_DYNU.ki           = 3;							//DOT1属性
    PI_PARA_DYNU.kd           = 0;							//DOT3属性
	PI_PARA_DYNU.outmax       = 600;   						//动态电压环参数
	PI_PARA_DYNU.errmax       = 100;						//DOT1属性
	PI_PARA_DYNU.errmin       = 0;							//DOT3属性
	PI_PARA_DYNU.incrementmax = 100;  						//DOT1属性
//-----机侧动态PI参数BJTULVRT201204	_MPR_U_Kp在调试界面里没有 暂时不用,首选PR
	PI_PARA_DYMI.kp           = _DYN_U_Kp/100.00;			//DOT2属性
    PI_PARA_DYMI.ki           = _DYN_U_Ki/10.00;			//DOT1属性
    PI_PARA_DYMI.kd           = _DYN_U_Kd/1000.00;			//DOT3属性
	PI_PARA_DYMI.outmax       = _DYN_U_outmax;   							//MPR电压环参数
	PI_PARA_DYMI.errmax       = _DYN_U_errmax/10.00;		//DOT1属性
	PI_PARA_DYMI.errmin       = _DYN_U_errmin/1000.00;		//DOT3属性
	PI_PARA_DYMI.incrementmax = _DYN_U_incrementmax/10.00;  //DOT1属性
//----同时用作动态PI和PR参数设定

	_eidco   = _EIDCO/1000.00;
	_encodpos= _ENCODPOS/1000.00;
	_sc_freq1= _SC_FREQ1/10.00;
	_sc_freq2= _SC_FREQ2/10.00;
	_stdby01 = _STDBY1/1000.00;								//备用经过小数愦砗笾�
	_stdby02 = _STDBY2/100.00;								//备用经过小数点处理后值
	_stdby03 = _STDBY3/10.00;								//备用经过小数点处理后值
    _stdby04 = _STDBY4;			        					//备用
	_stdby05 = _STDBY5;			        					//备用
    _stdby06 = _STDBY6;			        					//备用
	_stdby07 = _STDBY7;			        					//备用
//    _stdby08 = _STDBY8;			        					//备用
//计算定子电压AD大滤波比率2013-12-13--ZZJ
	Uns_ft = 0.5 * ((MEAN_DATA.uab3/MEAN_DATA.uab1)+(MEAN_DATA.ubc3/MEAN_DATA.ubc1));//大滤波幅值衰减比例

	daindex[0] = (Uint16)_NPR_U_Kd;	//da output select BJTULVRT201204
	daindex[1] = (Uint16)_NPR_ID_Kd;
	daindex[2] = (Uint16)_NPR_IQ_Kd;
	daindex[3] = (Uint16)_MPR_ID_Kd;

//转子电流带阻滤波参数 BJTULVRT201204
	BS_PARA_MPRI.f0 = 300;
	BS_PARA_MPRI.fb = 50;
	BS_PARA_MPRI.outmax = 1800;//201205LVRTatZB
//定子电流带阻滤波参数 BJTULVRT201204
	BS_PARA_STAI.f0 = 50;
	BS_PARA_STAI.fb = 40;
	BS_PARA_STAI.outmax = 8000; //201205LVRTatZB

//电机参数设定201005atcpc

	MPR_Ls = (_SC_Lls * 1e-6)+(_SC_Lm * 1e-6);				//定子自感	--单位H
	MPR_Lr = (_SC_Llr * 1e-6)+(_SC_Lm * 1e-6);				//转子自感	--单位H
	MPR_Lm = _SC_Lm * 1e-6;									//定转子互感--单位H
	MPR_Rs = _SC_Rs * 1e-6;									//定子电阻	--单位ohm
	MPR_Rr = _SC_Rr * 1e-6;									//转子电阻	--单位ohm
	SIGMA  = 1- (MPR_Lm * MPR_Lm /(MPR_Ls * MPR_Lr));		//(1-MPR_Lm*MPR_Lm/(MPR_Ls*MPR_Lr))	
	
	temp_Usn  = (float)_SC_Usn;								//定子额定电压(V)
	temp_Uro  = (float)_SC_Uro;								//转子开路电压(V)
	STAROTRTO = temp_Usn * SQRT3 / temp_Uro;				//定转子变比 只适用定子角接转子星接的电机
	STAROTRTO2= STAROTRTO * STAROTRTO;						//定转子变比的平方
	POLEPAIRES= (float)_SC_POLES;							//极对数

 	if(_SC_PLSPRVL != 2048)									//201007BJTULVRT 如果不是缺省值2048,则重新赋值
	{
		if(EQep2Regs.QPOSMAX != (4 * _SC_PLSPRVL))
		{
			EALLOW;			
 			EQep2Regs.QPOSMAX   = 4 * _SC_PLSPRVL;			// 位置计数器最大值
			EDIS;	
		}
	}
   
} 
/*********************************************************************************************************
** 函数名称: Disepwmio_NPR
** 功能描述:
** 输　入:
** 输　出:
** 注  释:
**-------------------------------------------------------------------------------------------------------
** 作　�
** 日　期:
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
void Disepwmio_NPR(void)
{
	EALLOW;
	
	EPwm1Regs.AQCSFRC.bit.CSFA = 1;		//force low  AQCSFRC = Action Qualifier Continuous S/W force Register Set
	EPwm1Regs.AQCSFRC.bit.CSFB = 2;		//force high
	EPwm2Regs.AQCSFRC.bit.CSFA = 1;		//force low
	EPwm2Regs.AQCSFRC.bit.CSFB = 2;		//force high
	EPwm3Regs.AQCSFRC.bit.CSFA = 1;		//force low
	EPwm3Regs.AQCSFRC.bit.CSFB = 2;		//force high

	EPwm1Regs.TBCTR = 0x0000;           // Clear counter  TBCTR = Time-base Counter Register
    EPwm2Regs.TBCTR = 0x0000;           // Clear counter
    EPwm3Regs.TBCTR = 0x0000;           // Clear counter

	EDIS;
}  
/*********************************************************************************************************
** 函数名称: Disepwmio_MPR
** 功能描述:
** 输∪?
** 输　出:
** 注  释:
**-------------------------------------------------------------------------------------------------------
** 作　者:
** 日　期:
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
void Disepwmio_MPR(void)
{
	EALLOW;
	
	EPwm4Regs.AQCSFRC.bit.CSFA = 1;		//force low  AQCSFRC = Action Qualifier Continuous S/W force Register Set
	EPwm4Regs.AQCSFRC.bit.CSFB = 2;		//force high
	EPwm5Regs.AQCSFRC.bit.CSFA = 1;		//force low
	EPwm5Regs.AQCSFRC.bit.CSFB = 2;		//force high
	EPwm6Regs.AQCSFRC.bit.CSFA = 1;		//force low
	EPwm6Regs.AQCSFRC.bit.CSFB = 2;		//force high 
  
    EPwm4Regs.TBCTR = 0x0000;           // Clear counter  TBCTR = Time-base Counter Register
    EPwm5Regs.TBCTR = 0x0000;           // Clear counter
    EPwm6Regs.TBCTR = 0x0000;           // Clear counter 

	EDIS;
}  
/*********************************************************************************************************
** 函数名称： DisPwm
** 功能描述：脉冲禁止
** 输　入:
** 输　出:
** 注  释:
**-------------------------------------------------------------------------------------------------------
** 作　者:
** 日　期:
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
void DisPwm(void)
{
	Disepwmio_NPR();
	Disepwmio_MPR();
} 


/*********************************************************************************************************
** 函数名称: Enepwmio_NPR
** 功能描述:
** 输　入:
** 输　出:
** 注  释:
**-------------------------------------------------------------------------------------------------------
** 作　者:
** 日　期:
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日∑?
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
void Enepwmio_NPR(void)
{
	EALLOW;

	EPwm1Regs.AQCSFRC.bit.CSFA = 3;		//forcing disabled  AQCSFRC = Action Qualifier Continuous S/W force Register Set
	EPwm1Regs.AQCSFRC.bit.CSFB = 3;		//forcing disabled
	EPwm2Regs.AQCSFRC.bit.CSFA = 3;		//forcing disabled
	EPwm2Regs.AQCSFRC.bit.CSFB = 3;		//forcing disabled
	EPwm3Regs.AQCSFRC.bit.CSFA = 3;		//forcing disabled
	EPwm3Regs.AQCSFRC.bit.CSFB = 3;		//forcing disabled

	EDIS;
}  
/*********************************************************************************************************
** 函数名称：Enepwmio_MPR
** 功能描述:
** 输　入:
** 输　出:
** 注  释:
**-------------------------------------------------------------------------------------------------------
** 作　者:
** 日　期:
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
void Enepwmio_MPR(void)
{
	EALLOW;
	
	EPwm4Regs.AQCSFRC.bit.CSFA = 3;		//forcing disabled
	EPwm4Regs.AQCSFRC.bit.CSFB = 3;		//forcing disabled
	EPwm5Regs.AQCSFRC.bit.CSFA = 3;		//forcing disabled
	EPwm5Regs.AQCSFRC.bit.CSFB = 3;		//forcing disabled
	EPwm6Regs.AQCSFRC.bit.CSFA = 3;		//forcing disabled
	EPwm6Regs.AQCSFRC.bit.CSFB = 3;		//forcing disabled

	EDIS;
}    
/*********************************************************************************************************
** 函数名称: ConfigPwm
** 功能描述: 进行PWM开关频率和死区时间的设置
** 输　入:
** 输　出:
** 注  释:
**-------------------------------------------------------------------------------------------------------
** 作　者:
** 日　期:
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
void ConfigPwm(void)						
{
	Disepwmio_NPR();
	Disepwmio_MPR();
	EALLOW;
//----------NPR的PWM1-PWM6设置---------------//
    EPwm1Regs.TBPRD = 3750000/_SW_FR;           // 开关频率为作给�_SW_FR=200对应2kHz
    EPwm2Regs.TBPRD = 3750000/_SW_FR;           // PWM时钟为75MHz
	EPwm3Regs.TBPRD = 3750000/_SW_FR;           // TBPRD = Time-base Period Register
    SW_NPR=3750000.0/_SW_FR;

    EPwm1Regs.DBRED = 75 * _DEADTIME;              //死区，_DEADTIME单位为us
    EPwm1Regs.DBFED = 75 * _DEADTIME;              //
    EPwm2Regs.DBRED = 75 * _DEADTIME;              //DBRED = Dead-Band Generator Rising Edge Delay Count Register
    EPwm2Regs.DBFED = 75 * _DEADTIME;              //DBFED = Dead-Band Generator Falling Edge Delay Count Register
    EPwm3Regs.DBRED = 75 * _DEADTIME;
    EPwm3Regs.DBFED = 75 * _DEADTIME;   

//----------MPR的PWM7-PWM12设置---------------//
	EPwm4Regs.TBPRD = 3750000/_SW_FR;           // 
    EPwm5Regs.TBPRD = 3750000/_SW_FR;           // 
    EPwm6Regs.TBPRD = 3750000/_SW_FR;           // 
    SW_MPR=3750000.0/_SW_FR;

    EPwm4Regs.DBRED = 75 * _DEADTIME;
    EPwm4Regs.DBFED = 75 * _DEADTIME;
    EPwm5Regs.DBRED = 75 * _DEADTIME;
    EPwm5Regs.DBFED = 75 * _DEADTIME;
    EPwm6Regs.DBRED = 75 * _DEADTIME;
    EPwm6Regs.DBFED = 75 * _DEADTIME; 

   GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;  // GPIO0 = PWM1A
   GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;  // GPIO1 = PWM1B
   GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;  // GPIO2 = PWM2A
   GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;  // GPIO3 = PWM2B
   GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;  // GPIO4 = PWM3A
   GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;  // GPIO5 = PWM3B 
   GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1;  // GPIO6 = PWM4A
   GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 1;  // GPIO7 = PWM4B
   GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 1;  // GPIO8 = PWM5A
   GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 1;  // GPIO9 = PWM5B
   GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 1;  // GPIO10 = PWM6A
   GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 1;  // GPIO11 = PWM6B  
    
	EDIS; 
}

/*********************************************************************************************************
** 函数名称: EnPdpint
** 功能描述:
** 输　入:
** 输　出:
** 注  释:
**-------------------------------------------------------------------------------------------------------
** 作　者:
** 日　?
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
void EnPdpint(void)
{
	EALLOW;
	
   // Enable TZ interrupt
    EPwm1Regs.TZEINT.bit.OST = 1;
    EPwm2Regs.TZEINT.bit.OST = 1;
    EPwm3Regs.TZEINT.bit.OST = 1;
	EPwm4Regs.TZEINT.bit.OST = 1;
    EPwm5Regs.TZEINT.bit.OST = 1;
    EPwm6Regs.TZEINT.bit.OST = 1;

	EDIS;
}
/*********************************************************************************************************
** 函数名称: DisPdpint
** 功能描述:
** 输　入:
** 输　:
** 注  释:
**-------------------------------------------------------------------------------------------------------
** 鳌≌�
** 日　期:
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
void DisPdpint(void)
{
	EALLOW;
	
   // disable TZ interrupt
    EPwm1Regs.TZEINT.bit.OST = 0;
    EPwm2Regs.TZEINT.bit.OST = 0;
    EPwm3Regs.TZEINT.bit.OST = 0;
	EPwm4Regs.TZEINT.bit.OST = 0;
    EPwm5Regs.TZEINT.bit.OST = 0;
    EPwm6Regs.TZEINT.bit.OST = 0;

	EDIS;
} 
/*********************************************************************************************************
** 函数名称: ClrPdpint
** 功能描述:
** 输　入:
** 输〕?
** 注  释:
**-------------------------------------------------------------------------------------------------------
** 作　者:
** 日　期:
**-------------------------------------------------------------------------------------------------------
** 修改人:
** 日　期:
**------------------------------------------------------------------------------------------------------
***********************************************************************************************/
void ClrPdpint(void)
{
	EALLOW;
	
    EPwm1Regs.TZCLR.bit.OST = 1;   
    EPwm1Regs.TZCLR.bit.INT = 1;
	EPwm2Regs.TZCLR.bit.OST = 1;   
    EPwm2Regs.TZCLR.bit.INT = 1;
	EPwm3Regs.TZCLR.bit.OST = 1;   
    EPwm3Regs.TZCLR.bit.INT = 1;
	EPwm4Regs.TZCLR.bit.OST = 1;   
    EPwm4Regs.TZCLR.bit.INT = 1;
	EPwm5Regs.TZCLR.bit.OST = 1;   
    EPwm5Regs.TZCLR.bit.INT = 1;
	EPwm6Regs.TZCLR.bit.OST = 1;   
    EPwm6Regs.TZCLR.bit.INT = 1;

	EDIS;
}   

//===========================================================================
// No more.
//===========================================================================
