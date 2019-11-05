//-------------右玉1.5MW双馈风电机组并网变流器控制软件主程序----201005atcpc-201007atbjtu--------------------------------
#ifndef DCDC_database_H
#define DCDC_database_H

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------------//参数属性定义
#define	WR0		1						//write only
#define	RDO		2						//read only
#define WR1		4						//write enable when stop
#define	WR2		8						//write enable with password
#define	WR3		16						//write on RAM without eerom
#define	MAX_PT	32						//最大值为指针
#define	MIN_PT	64						//最小值为指针
#define	SIG		128						//有符号数
#define	VA0		256						//表示包含数值0(相当于禁止相应的功能)
#define	UNS		512						//禁止存储
#define	KEY		1024						//查看和修改需要制造商密码
#define	DOT1	2048					//操作器带1位小数点
#define	DOT2	4096					//操作器带2位小数点
#define	DOT3	8192					//操作器带3位小数点

//--------------------------------------//显示信息属性定义
#define	NONE	0						//无
#define	SOFT	1						//软停止
#define	SHUT	2						//急停
#define	N_RCVR	4						//不能恢复
#define	D_RCVR	8						//延时恢复
#define	I_RCVR	16						//立即恢复
#define	CNT		32						//计入故障次数
#define	OT_SER	64						//超时1min后变成严重故障
#define	SAVE	128						//信息需要保存
#define	OFFCB	256						//断主断
#define	WARNING	512						//报警

//--------------------------宏定义-----------------------------------------------
				
//-----------------------参数相关宏定义------------------------------------------
//功能码相关数量定义(增减功能码后只需要增减数据库内的数据和此处的相应数量定义即可)
#define NUM_GROUP1			29				//首组功能码的个数（'制造商用'）
#define	NUM_GROUP2			42				//第二组功能码的个数（'PI参数'）
#define NUM_GROUP3			43				//第三组功能码的个数（'保护阈值'）201005atcpc
#define NUM_GROUP4			14				//第四组功能码的个数（'运行模式')
#define NUM_TIME			6				//时间设定功能码的个数
#define NUM_WATCHLCD		53				//运行监控功能码的个数
#define NUM_ERRINF			42				//报警信息功能码的个数
#define NUM_ERROR			35				//历史最新故障信息

//操作器功能码数量
#define PARA_NUM			NUM_GROUP1+NUM_GROUP2+NUM_GROUP3+NUM_GROUP4+NUM_TIME+NUM_WATCHLCD+NUM_ERRINF+NUM_ERROR

//故障参数总数量
#define ERRO_NUM			NUM_ERROR+NUM_ERRINF

//故障参数表第一个参数的序号		
#define TAB_ERR_FIRST		NUM_GROUP1+NUM_GROUP2+NUM_GROUP3+NUM_GROUP4+NUM_TIME+NUM_WATCHLCD

//故障参数表最后参数的序号		
#define TAB_ERR_END			NUM_GROUP1+NUM_GROUP2+NUM_GROUP3+NUM_GROUP4+NUM_TIME+NUM_WATCHLCD+NUM_ERRINF+NUM_ERROR-1

//监控参数表第一个参数的序号(包括时间参数)
#define BANK_FIRST			NUM_GROUP1+NUM_GROUP2+NUM_GROUP3+NUM_GROUP4+NUM_TIME				

//监控参数表最后一个参数的序号
#define BANK_END			NUM_GROUP1+NUM_GROUP2+NUM_GROUP3+NUM_GROUP4+NUM_TIME+NUM_WATCHLCD-1				

//时间参数表第一个参数的序号
#define TIME_FIRST			NUM_GROUP1+NUM_GROUP2+NUM_GROUP3+NUM_GROUP4				

//时间参数表最后一个参数的序号
#define TIME_END			NUM_GROUP1+NUM_GROUP2+NUM_GROUP3+NUM_GROUP4+NUM_TIME-1	

//数字写指令参数表第一个参数的序号		
#define TAB_COMSTATE_FIRST		NUM_GROUP1+NUM_GROUP2+NUM_GROUP3

//数字写指令参数表最后参数的序号		
#define TAB_COMSTATE_END			NUM_GROUP1+NUM_GROUP2+NUM_GROUP3+NUM_GROUP4-1


//运行给定的位置//
#define NO_URF				NUM_GROUP1-16	
#define NO_MIDRF			NUM_GROUP1-15
#define NO_NIQRF			NUM_GROUP1-14
#define NO_MIQRF			NUM_GROUP1-13
#define NO_TOQRF            NUM_GROUP1-12
#define NO_AGLRF			NUM_GROUP1-11



//---------------------------故障信息序号-systest----------------------------------------------
#define MSG_NUM				45				//故障信息数量

#define	MSG_NONE			0				//空信息
#define	MSG_CODEOK			1				//EEPROM正常
#define	MSG_EE_FAIL			2				//EEPROM故障
#define	MSG_ESTOP			3				//急停故障
#define	MSG_CBTRIP			4				//主断脱扣故障
#define	MSG_EXFAULT 		5				//变流器外部硬件故障
#define	MSG_CAN_FAIL		6				//CAN通讯故障
#define	MSG_ENCODFAULT		7				//编码器故障
#define	MSG_CBERROR 		8				//主断合闸故障
#define	MSG_PREERROR 		9				//预充电故障
#define	MSG_MAINKERROR 		10				//主接触器闭合故障
#define	MSG_MAINFERROR 		11				//主滤波器闭合故障
#define	MSG_STACERROR 		12				//定子接触器闭合故障
#define	MSG_HIA1			13				//网侧,A相硬件过流
#define	MSG_HIB1			14				//网侧,B相硬件过流
#define	MSG_HIC1			15				//网侧,C相硬件过流
#define	MSG_HIA2			16				//电机侧,A相硬件过流
#define	MSG_HIB2			17  			//电机侧,B相硬件过流
#define	MSG_HIC2			18				//电机侧,C相硬件过流
#define	MSG_UDCOV           19	            //硬件检测中间直流电压过压
#define	MSG_HIAC1			20				//网侧硬件过流
#define	MSG_HIAC2			21				//电机侧硬件过流
#define MSG_PDPASERIES      22            	//网侧严重故障
#define MSG_PDPBSERIES      23            	//电机侧严重故障
#define	MSG_MSPEEDOUT 		24				//转速超出范围故障
#define	MSG_SIAC1			25				//网侧软件过流
#define	MSG_SIAC2			26				//电机侧软件过流
#define	MSG_FE1				27				//电网频率错误
#define	MSG_SUDCOV			28				//软件中间直流电压过压
#define	MSG_SUACOV1			29				//软件网压交流过压
#define	MSG_SIDCOV			30				//改为dc-chopper电流保护BJTULVRT201204
//#define	MSG_SUDCLV			30				//软件中间直流电压欠压
#define	MSG_SUACLV1			31				//软件网压交流欠压或失电
#define	MSG_UDCWAVE			32				//中间电压波动故障
#define	MSG_SIOVST	    	33				//定子电流过流故障
#define	MSG_GFAULT1			34				//网侧接地故障
#define	MSG_GFAULT2		   	35				//机侧接地故障
#define	MSG_TOV1			36				//网侧SKIIP超温
#define	MSG_TOV2			37  			//电机侧SKIIP超温
#define	MSG_SKTOV			38  			//软件判断SKIIP超温
#define	MSG_TLOV1			39				//网侧电感超温
#define MSG_TLOV2           40            	//机侧电感超温
#define	MSG_PGOV			41				//并网有功超限
#define MSG_QGOV            42            	//并网无功超限
#define	MSG_STASYNFAIL 		43				//定子同步并网失败故障
#define	MSG_PHORDE			44				//电网相序错误

//--------------------------------------//数据总表
extern const struct PARA FUNC[PARA_NUM];

extern const Uint16 TAB_ERR[ERRO_NUM];
extern const float TAB_EXI[128];
extern const float TAB_IQEXI[128];
extern const Uint16 TAB_ET2[256];
extern const Uint16 TAB_ET1[256];

extern const struct MESSAGE TAB_MSG[MSG_NUM];

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif
//===========================================================================
// No more.
//===========================================================================
