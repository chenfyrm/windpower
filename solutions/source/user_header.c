#include "DSP2833x_Device.h"     				// DSP2833x Headerfile Include File
#include "user_header.h"

Uint16 DEBUG_OPER;                                        //20100401at27

//电机参数设定2010atcpc
float  	MPR_Ls;	 	    				//定子自感	--单位H
float	MPR_Lr;	 	    				//转子自感	--单位H
float 	MPR_Lm;	 	    				//定转子互感--单位H
float 	MPR_Rs;	     					//定子电阻	--单位ohm
float 	MPR_Rr;	    					//转子电阻	--单位ohm
float 	SIGMA;							//(1-MPR_Lm*MPR_Lm/(MPR_Ls*MPR_Lr))
float	STAROTRTO;       				//定转子变比
float	STAROTRTO2;       				//定转子变比的平方
float	POLEPAIRES;       				//电机极对数

Uint16  BANK_RAMDATA_POS;						    					//存储变量的存储点位置[0,4999]
Uint16  ERROR_RAMDATA_POS;

Uint16   _OUT4_DATA;		//该标志位无用改为宏定义20130222//存储变量的存储点位置[0,4999]

//------------------------------------const定义--------------------------------------------

//eeprom位操作
const  Uint16 ONEBYTE[8]={0x0080,0x0040,0x0020,0x0010,0x0008,0x0004,0x0002,0x0001};

//AD1544通道选择
const  Uint16 AD1544[4]={0x0000,0x2000,0x4000,0x6000};
//--------------------------------------变量定义-------------------------------------------
Uint16	flag[16];													//标志位变量
//Uint16	disp[15];

struct MC_DATA MC_DATA;

float   MC_y_test;
float   MC_U_test;
float	Uns_ft;
Uint16	MC_N_test;
Uint32	MC_F_cnt;

Uint32	QEP_CNT1;
Uint32	QEP_CNT2;
int16	QEPPHE_N;


float   pll_theta; 				//201011PLL
float   ptheta;
float   ntheta;
float 	temp_pd;
float 	temp_pq;
float 	temp_nd;
float 	temp_nq;
float   NGS_Udq_lv;

float   NGS_Udq_p;
float   NGS_Udq_n;
float   NGS_Udq_epsilon;
float   NGS_Udq_p_ex;		//20130206
float   NGS_Udq_epsilon_lv;	//20130301
float   NGS_Udq_pflt;		//20130301

float   LV_A1;				//201011LVRT
float   LV_A2;
float   LV_T1;
float   LV_T2;

float   lv_flag_flt;		//2013-12-6 LVRT标志位延时计数器

//ModbusRS485
Uint16  length485;													//modbus
Uint16  longtx_num;													//modbus

float   RUN_mpridrf_exi;
Uint16  RUN_mpriq;
Uint16  _OUT3_TEST;
Uint16  _NQEPPCO;
Uint16  R_SCOUT;
float   Ud_lv;
float   temp_ud;

//float   NGS_Udq_p;
//float   NGS_Udq_epsilon;
float   NGS_Udq;
float   PHAI_d;
float   PHAI_q;
float   PHAI_dq;

int32   ET_SUM1;
int32   ET_SUM2;

/*下面的用作SVPWM计算*/
Uint16 SW_NPR,SW_MPR;
float   vdc;
float   m=0.0;
float   ua_m=0,ub_m=0,uc_m=0;  //调制波
float   u_alfa_NPR=0,u_beta_NPR=0;
float   u_alfa_MPR=0,u_beta_MPR=0;

struct	GIVE GIVE;
float OCS_Trf;                          //主控给过来的转矩指令

struct RUN RUN;

struct	TRANS_DATA TRS_NPR_I;   //网侧变流器的电流（这里NPR作为后缀，不用grd，以区分电网电流还是网侧变流器电流）
struct	TRANS_DATA TRS_MPR_I;   //机侧变流器的电流
struct	TRANS_DATA TRS_MPR_U;   //机侧变流器算脉冲用
struct	TRANS_DATA TRS_NPR_U;   //网侧变流器算脉冲
struct	TRANS_DATA TRS_NGS_U;   //嗟缤缪
struct	TRANS_DATA TRS_STA_I;   //定子电流
struct	TRANS_DATA TRS_STA_U;   //定子电压
struct	TRANS_DATA TRS_GSTA_U;  //目标定子电压
struct	TRANS_DATA TRS_PSTA_U;  //用于编码器位置检测的定子电压
struct	TRANS_DATA TRS_PMPR_I;  //用于编码器位置检测的转子电流
struct	TRANS_DATA DIP_NPR_U;  //用于功率计算
struct	TRANS_DATA DIP_NPR_I;  //用于功率计算
struct	TRANS_DATA DIP_STA_U;  //用于功率计算
struct	TRANS_DATA DIP_STA_I;  //用于功率计算
struct	TRANS_DATA DIP_MPR_I;  //用于功率计算
struct	TRANS_DATA TRS_GAC_U;  //用于201011PLL
struct	TRANS_DATA TRS_SCR_I;   //机侧crowbar电流BJTULVRT201204

struct I_DATA_PLL I_DATA_PLL;

struct PI_DATA PI_NPR_Id;				//网侧变流器d轴电流闭环
struct PI_DATA PI_NPR_Iq;				//网侧变流器q轴电流闭环
struct PI_DATA PI_MPR_Id;				//机侧变髌鱠轴电流闭环
struct PI_DATA PI_MPR_Iq;				//机侧变流器q轴电流闭环
struct PI_DATA PI_NPR_U;				//网侧变流器电压环
struct PI_DATA PI_MPR_U;				//软并网闭环
struct PI_DATA PI_STA_Id;				//励磁控制d
struct PI_DATA PI_STA_Iq;				//励磁控制q
struct PI_DATA PI_DATA_PLL;				//201011PLL
struct PI_PARA PI_PARA_DYMI;			//动态宽带宽PI控制BJTULVRT201204

struct PI_PARA PI_PARA_NPRU;
struct PI_PARA PI_PARA_NPRID;
struct PI_PARA PI_PARA_MPRU;
struct PI_PARA PI_PARA_MPRID;
struct PI_PARA PI_PARA_NPRIQ;
struct PI_PARA PI_PARA_MPRIQ;
struct PI_PARA PI_PARA_DYNU;
struct PI_PARA PI_PARA_DYNID;
struct PI_PARA PI_PARA_DYNIQ;
struct PI_PARA PI_PARA_MPRI;
struct PI_PARA PI_PARA_STAI;
struct PI_PARA PI_PARA_PLL;				//201011PLL

struct MAIN_LOOP MAIN_LOOP;

struct AMUX AMUX;
//慢速AD处理寄存器
Uint16 _OUT_AMUX1=0;  //用于慢速AD选通信号，每次要选通下一个AD通道，_OUT_AMUX加1，然后送到CPLD去处理，选通16选1芯片
Uint16 _OUT_AMUX2;    //用于慢速AD选通信号，每次要选通下一个AD通道，_OUT_AMUX加1，然后送到CPLD去处理，选通16选1芯片

struct AD AD;
struct ADFINAL ADFINAL;

struct AD_DATA AD_OUT_GRD_U;  //电网电压（主断前）
struct AD_DATA AD_OUT_STA_U;  //电机定子侧电压 大滤波通道
struct AD_DATA AD_OUT_NGS_U;  //电网电压（主断后）
struct AD_DATA AD_OUT_NPR_I;  //网侧变流器电流
struct AD_DATA AD_OUT_MPR_I;  //机侧变流器电流
struct AD_DATA AD_OUT_STA_I;  //定子侧电流
struct AD_DATA AD_OUT_NGF_U;  //电网电压（主断后）大滤波通道
struct AD_DATA AD_OUT_STAD_U;  //差值
struct AD_DATA AD_OUT_SCR_I;  //ACTIVECROWBAR电流
struct AD_DATA AD_OUT_DC_I;  //CHOPPER电流

float  AD_OUT_UDC; //AD计算后输出的直流电梗╒）

struct MEAN_DATA MEAN_DATA;
struct PRO PRO;
struct DISP DISP;

struct CAP_DATA CAP4,CAP5;

struct QEPDATA QEPDATA;
struct SCI SCI;
struct SCI_CANOPEN SCI_canopen;
struct SPI SPI;
struct EEPROM EEPROM;
struct RTIMER RTIMER;

struct PHI_DATA PHI_DATA_M;

struct BS_DATA BS_MPR_Id;				//转子侧电流d轴
struct BS_DATA BS_MPR_Iq;				//转子侧电流q轴
struct BS_DATA BS_STA_Id;				//定子侧电流d轴
struct BS_DATA BS_STA_Iq;				//定子侧电流q轴
struct BS_DATA BS_NPR_Ud;				//网侧变流器d轴
struct BS_DATA BS_NPR_Uq;				//网侧变流器d轴
struct BS_DATA BS_NPR_Udn;				//网侧变流器d轴
struct BS_DATA BS_NPR_Uqn;				//网侧变流器d轴

struct BS_PARA BS_PARA_MPRI;
struct BS_PARA BS_PARA_STAI;
struct BS_PARA BS_PARA_NPRU;

//-----------------------------内部变量----------------------------------------------------------
Uint16  _NULL_VAL = 0;
Uint16  _MSG_SCOUT1;												//SCOUT信息级别(前次)
Uint16  _MSG_SCOUT2;												//SCOUT信息级别(本次)
Uint16  _SY_RTRN;
Uint32   POSCNT_TEST;
float   DM_imrd;   						//转子励磁电流
float   DM_imrq;   						//转子励磁电流
float   DM_Lr;							//当前重试次数
float   Te_feedback;                    //实际转矩值反馈
float   Pnactive;    					//网侧有功功率
float   Pnreactive;    					//网侧无功功率
float   Pcreactive;    					//网侧电容无功功率201205LVRTatZB

//----------------------------参数变量------------------------------------------------------------
Uint16 _MC_TYPE;						//机型参数
Uint16 _MC_REV;							//软件版本
Uint16 _MC_DATE;						//出厂日期
Uint16 _MC_ID;							//产品编号
Uint16 _SCIB_ADDR;						//485节点地址
Uint16 _PROSTDBY1;						//
Uint16 _PROSTDBY2;						//

Uint16 _SW_FR;							//开关频率(kHz)
Uint16 _DEADTIME;						//脉冲的最小导通时间(us)
Uint16 _COMPTIME;						//脉冲的最小导通时间(ms)
Uint16 _MINONTIME;						//脉冲的最小导通时间(us)

Uint16 _RU_UDCT;						//电压指令积分时间(ms)
Uint16 _RU_IDT;							//电流指令积分时间(ms)
Uint16 _RU_IQT;							//电流指令积分时间(ms)
Uint16 _RU_TOQT;						//转矩指令积分变(ms)
Uint16 _RU_AGLT;                        //功率因数角指令积分时间(ms)
Uint16 _URF;							//直流电压给定值
Uint16 _MIDRF;							//d轴电流给定值
Uint16 _NIQRF;							//q轴电流给定值
Uint16 _MIQRF;							//q轴电流给定值
Uint16 _TOQRF;							//转矩指令
Uint16 _AGLRF;							//机侧功率因数角
Uint16 _EIDCO;							//手动 机侧励磁电流调整系数
Uint16 _ENCODPOS;						//手动 编码器初始位置角度

Uint16 _STDBY1;							//备用1
Uint16 _STDBY2;							//备用2
Uint16 _STDBY3;							//备用3
Uint16 _STDBY4;							//备用4
Uint16 _STDBY5;							//备用5
Uint16 _STDBY6;							//备用6
Uint16 _STDBY7;							//备用7
//Uint16 _STDBY8;							//备用8
Uint16 _MC_OK;							//备用8	 MagnetCurve2013-12-13
Uint16 _STDBY9;							//备用9
Uint16 _STDBY10;						//备用10
Uint16 _STDBY11;						//备用11
Uint16 _STDBY12;						//备用12
Uint16 _STDBY13;						//备用13
Uint16 _STDBY14;						//备用14
float _eidco;
float _encodpos;
float _sc_freq1;
float _sc_freq2;

//----'数字量变量'PC------
Uint16 _COMMAND1;
Uint16 _COMMAND2;
Uint16 _PCEROTRIG;					    //20100308
Uint16 _DISPLAY;
Uint16 _STATE1;
Uint16 _STATE2;
Uint16 _INPUT;
Uint16 _OUTPUT;
Uint16 _LVRT;

float _stdby01;							//备用经过小数点处理后值
float _stdby02;							//备用经过小数点处理后值
float _stdby03;							//赣经过小数点处砗笾
float _stdby04;							//备用∈愦砗笾
float _stdby05;							//备用经过小数处理后值
float _stdby06;							//备用经过小数点处值
float _stdby07;							//备用经过小数点处理后值
float _stdby08;							//备用经过小数点处理后值
//------------------------运行模式变量-------------------------------------------------------------
Uint16 _ENSCR;							//

//-----------------------PI环参数变量--------------------------------------------------------------
Uint16	_NPR_U_Kp;		  		//网侧变流器电压闭环比例系数
Uint16	_NPR_U_Ki;		   		//网侧淞髌鞯缪贡栈坊窒凳
Uint16	_NPR_U_Kd;		   		//网侧澉器电压闭肺⒎窒凳
Uint16	_NPR_U_outmax;			//网侧变流器缪贡栈肥涑鱿薹
Uint16	_NPR_U_errmax;		 	//网侧变流器电压闭环误差限幅
Uint16	_NPR_U_errmin;		   	//网侧变流鞯缪贡栈肺蟛铑兄
Uint16	_NPR_U_incrementmax;	//网侧变流器电压闭环增量限幅

Uint16	_NPR_ID_Kp;				//网侧变流器电流闭环比例系数
Uint16	_NPR_ID_Ki;	   			//网侧变流器电流闭环积分系数
Uint16	_NPR_ID_Kd;	   			//网侧变流器电流闭环微分系数
Uint16	_NPR_ID_outmax;			//网侧变流器电流闭环输鱿薹
Uint16	_NPR_ID_errmax;	 		//网侧变流器电流闭环误差限幅
Uint16	_NPR_ID_errmin;	  		//网侧变流器电流闭环误差钚≈
Uint16	_NPR_ID_incrementmax; 	//网侧变流器电流闭环隽肯薹

Uint16	_NPR_IQ_Kp;				//网侧变流器电流闭环比例系数
Uint16	_NPR_IQ_Ki;	   			//网侧变髌鞯缌鞅栈坊窒凳
Uint16	_NPR_IQ_Kd;	   			//网啾淞髌鞯缌鞅栈肺⒎窒凳
Uint16	_NPR_IQ_outmax;			//网侧变流器电流闭环输出限幅
Uint16	_NPR_IQ_errmax;	 		//网侧变流器电流闭环误差限幅
Uint16	_NPR_IQ_errmin;	  		//网啾淞髌鞯缌鞅环误差最小值
Uint16	_NPR_IQ_incrementmax; 	//网侧变流器电流闭环增量限幅

Uint16	_MPR_U_Kp;	   			//机侧变流器电压闭环比例系数
Uint16	_MPR_U_Ki;	  			//机侧变流器电压闭环积分系数
Uint16	_MPR_U_Kd;	  			//机侧变流器电压闭环微分系数
Uint16	_MPR_U_outmax;	 		//机侧变流器电压闭环输出限幅
Uint16	_MPR_U_errmax;	  		//机侧变流器电压闭环误差限
Uint16	_MPR_U_errmin;		 	//机侧变流器电压闭环误差最小值
Uint16	_MPR_U_incrementmax; 	//机侧变流器电压闭环增量限幅

Uint16 _MPR_ID_Kp;				//机侧变流器电流闭环比例系数
Uint16 _MPR_ID_Ki;				//机侧变流器电流闭环积分系数
Uint16 _MPR_ID_Kd;				//机侧变流器电流闭环微分系数
Uint16 _MPR_ID_outmax;			//机侧变流器电流闭环输出限幅
Uint16 _MPR_ID_errmax;			//机侧淞髌鞯缌鞅栈肺蟛钕薹
Uint16 _MPR_ID_errmin;			//机侧变流器电流闭环误差最小值
Uint16 _MPR_ID_incrementmax;		//机侧变流器电流闭环增量限幅

Uint16 _MPR_IQ_Kp;				//机侧变流器电流闭环比例系数
Uint16 _MPR_IQ_Ki;				//机侧变流器电流闭环积分系数
Uint16 _MPR_IQ_Kd;				//机侧变流器电流闭环微分系数
Uint16 _MPR_IQ_outmax;			//机侧变流器电流闭环输出限幅
Uint16 _MPR_IQ_errmax;			//机侧变流器电流闭环误差限幅
Uint16 _MPR_IQ_errmin;			//机侧变流器电流闭环误差最小值
Uint16 _MPR_IQ_incrementmax;	//机侧变流器电流闭环增量限幅


Uint16	_DYN_U_Kp;	   			//机侧变流器电压闭环比例系数
Uint16	_DYN_U_Ki;	  			//机侧变流器电压闭环积分系数
Uint16	_DYN_U_Kd;	  			//机侧变流器电压闭环微分系数
Uint16	_DYN_U_outmax;	 		//机侧变流器电压闭环输出限幅
Uint16	_DYN_U_errmax;	  		//机侧变流器电贡环误差限幅
Uint16	_DYN_U_errmin;		 	//机侧变流器电压闭环误差最小值
Uint16	_DYN_U_incrementmax; 	//机侧变流器电贡栈吩隽肯薹


Uint16 _SC_RTRN;													//故障最大重试次数
Uint16 _SC_RTRT;													//两次故障重试间隔时间(ms)

Uint16 _SC_IACOV1;													//基准电流的百分值)
Uint16 _SC_UDCOV;													//中间直流电压过压值(V)
Uint16 _SC_UDCOVH;													//中间直流电压过压值（网压跌落）(V)
Uint16 _SC_IDCOV;													//改为dc-chopper电流保护BJTULVRT201204
//Uint16 _SC_UDCLV;													//中间直流电压欠压值(V)
Uint16 _SC_VDCON;													//上电电压
Uint16 _SC_UACOV1;													//网压交流电压过压动作值(V)
Uint16 _SC_UACLV1;													//交流电压缺相动作值(V)
Uint16 _SC_IACOV2;													//基准电流的百分值)
Uint16 _SC_PGOV;													//
Uint16 _SC_QGOV;													//
Uint16 _SC_IACOVST;                                                 //定子电流过流保护

Uint16 _SC_Rs;														//定子电阻(mohm)
Uint16 _SC_Lls;														//定子漏抗(mH)
Uint16 _SC_Rr;														//转子电阻(mohm)
Uint16 _SC_Llr;														//转子漏抗(mH)
Uint16 _SC_Lm;														//励磁电 mH)
Uint16 _SC_POLES;													//极对数
Uint16 _SC_Usn;														//定子额定电压(V)
Uint16 _SC_Uro;                                                		//转子开路电压(V)
Uint16 _SC_PLSPRVL;													//编码器每圈光栅数量
Uint16 _SC_MSTDBY;                                               	//电机参数备用
Uint16 _SC_EXISTY1;                                               	//电机励磁调节备用1
Uint16 _SC_EXISTY2;                                               	//电机励磁调节备用2
Uint16 _SC_EXISTY3;                                               	//电机励磁调节备用3
Uint16 _SC_EXISTY4;                                               	//电机励磁调节备用4
Uint16 _SC_EXISTY5;                                               	//电机励磁调节备用5

Uint16 _BA_ERR4;													//第四次故障信息
Uint16 _BA_ERR3;													//第三次故障信息
Uint16 _BA_ERR2;													//第二次故障信息
Uint16 _BA_ERR1;													//第一次故障信息
Uint16 _BA_ERR5;													//示波器故障信息
//--------------------------------报警信息变 ----------------------------------------------------
Uint16 _BA_EMIDRF;													//最新故障时刻 d轴电流指令(A)
Uint16 _BA_ENIQRF;													//最新故障时刻 q轴电流指令(A)
Uint16 _BA_EMIQRF;													//最鹿障时刻 q轴电流指令(A)
Uint16 _BA_ETOQRF;													//最新故障时刻 转矩指令(NM)
Uint16 _BA_EURF;													//最新故障时刻 中间直流电压给 V)
Uint16 _BA_EUDC;													//最新故障时刻 中间直流电压(V)
Uint16 _BA_EAGLRF;													//最新故障时刻 无功角度指令()
Uint16 _BA_EIA1;													//最新故障时刻 网侧A相电流有效值(A)
Uint16 _BA_EIB1;													//最新故障时刻 网侧B相电流有效值(A)
Uint16 _BA_EIC1;													//最新故障时刻 网侧C相电流有效值(A)
Uint16 _BA_EIA2;													//最新故障时刻 缁郃相电流有效值(A)
Uint16 _BA_EIB2;													//最新故障时刻 电机侧B相电流有效值(A)
Uint16 _BA_EIC2;													//最新故障时刻 电机侧C相电流有效值(A)
Uint16 _BA_EUAB1;													//最新故障时刻 网侧A相电压有效值(V)
Uint16 _BA_EUBC1;													//最新故障时刻 网侧B相电压有效值(V)
Uint16 _BA_EUAB2;													//最新故障时刻 网侧相电压有效值(V)
Uint16 _BA_EUBC2;													//最新故障时刻 电机侧A相电流有效值(V)
Uint16 _BA_EUAB0;													//最新故障时刻 主断前AB线电压有效值(V)
Uint16 _BA_EUBC0;													//最新故障时刻 主锨癇C线电压有效值(V)
Uint16 _BA_EFREQ;													//最新故障时刻 电网频率(hz)
Uint16 _BA_ESPEED;													//最新故障时刻 电机转速(rpm)
Uint16 _BA_ENPRUD;              			//d轴主断后网压反馈20091026atzy
Uint16 _BA_ENPRUQ;          				//q轴主断后网压反馈20091026atzy
Uint16 _BA_ENPRUD2;          				//d轴主断后网压反馈 滤波后20091026atzy
Uint16 _BA_ENPRUQ2;          				//q轴主断后网压反馈 滤波后20091026atzy
Uint16 _BA_ENUDOUT;          				//郿岬缪故涑 0091026atzy
Uint16 _BA_ENUQOUT;          				//网侧q轴电压输出20091026atzy
Uint16 _BA_ETA1;													//最新故障时刻 网侧变流器A桥臂温度
Uint16 _BA_ETB1;													//最新故障时刻 网侧变流器B桥臂温度
Uint16 _BA_ETC1;													//最新故障时刻 网侧变流器C桥臂温度
Uint16 _BA_ETA2;													//最新故障时刻 电机侧变流器A疟畚露
Uint16 _BA_ETB2;													//最新故障时刻 电机侧淞髌鰾桥臂温
Uint16 _BA_ETC2;													//最鹿收鲜笨 电机侧变流器C桥臂温度
Uint16 _BA_EPIONU;													//最新故障时刻 网侧电压环输出
Uint16 _BA_EPIONID;													//最新故障时刻 网侧d轴电流环输出
Uint16 _BA_EPIONIQ;													//最新故障时刻 网侧q轴电流环输出
Uint16 _BA_EMEXI;													//最新故障时刻 机侧励磁理论计算值显示
Uint16 _BA_EPIOMID;													//最新故障时刻 机侧d轴电流环输
Uint16 _BA_EPIOMIQ;													//最新故障时刻 机侧q轴电流环输出
Uint16 _BA_ETLAC;													//最新故障时刻 网侧电感温度
Uint16 _BA_ETLDUDT;													//最新故障时刻 机侧电感温度
Uint16 _BA_ETSKIIP;													//最新故障时刻 SKIIP温
Uint16 _BA_ESTAIAC;
Uint16 _BA_ESTAIBA;
Uint16 _BA_ETOQFB;
Uint16 _BA_EPSTA;
Uint16 _BA_EPNPR;
Uint16 _BA_EPGRID;

Uint16 _BA_TIME4_0;													//最新故障时间(秒)
Uint16 _BA_TIME4_1;													//最新故障时间(
Uint16 _BA_TIME4_2;													//最新故障时间(时)
Uint16 _BA_TIME4_3;													//最新故障时间(日)
Uint16 _BA_TIME4_4;													//最新故鲜奔 月)
Uint16 _BA_TIME4_5;													//最新故障时间(年)

Uint16 _BA_TIME3_0;													//第三次故障时间(秒)
Uint16 _BA_TIME3_1;													//第三次故障时间(分)
Uint16 _BA_TIME3_2;													//第三次故障时间(时)
Uint16 _BA_TIME3_3;													//第三次故障时间(日)
Uint16 _BA_TIME3_4;													//第三次故障时间(月)
Uint16 _BA_TIME3_5;													//第三次故鲜奔 年)

Uint16 _BA_TIME2_0;													//第二问障时间(秒)
Uint16 _BA_TIME2_1;													//第二次故障时间(分)
Uint16 _BA_TIME2_2;													//第二次故障奔?时)
Uint16 _BA_TIME2_3;													//第二次故障时间(日)
Uint16 _BA_TIME2_4;													//第二次故障时间(月)
Uint16 _BA_TIME2_5;													//第二次故障时?年)

Uint16 _BA_TIME1_0;													//第一次故障时间(秒)
Uint16 _BA_TIME1_1;													//第一次故障时间(分)
Uint16 _BA_TIME1_2;													//第一次故障时间(时)
Uint16 _BA_TIME1_3;													//第一次故障时间(日)
Uint16 _BA_TIME1_4;													//第一次故障时间(月)
Uint16 _BA_TIME1_5;													//第一次故障时间(年)

Uint16 _BA_TIME5_0;													//示波器故障时间(秒)
Uint16 _BA_TIME5_1;													//示波器故障时间(分)
Uint16 _BA_TIME5_2;													//示波器故障时间(时)
Uint16 _BA_TIME5_3;													//示波器故障时间(日)
Uint16 _BA_TIME5_4;													//示波器故障时间(月)
Uint16 _BA_TIME5_5;													//示波器故障时间(年)

//-------------------------------------运行监控变量-----------------------------------------------
Uint16 _BA_MIDRF;													//d轴电流指令(A)
Uint16 _BA_NIQRF;													//q轴电流指令(A)
Uint16 _BA_MIQRF;													//q轴电流指令(A)
Uint16 _BA_TOQRF;													//转矩指令(NM)
Uint16 _BA_AGLRF;													//无功角度指令(NM)
Uint16 _BA_TOQFB;													//转矩反馈(NM)
Uint16 _BA_URF;														//中间直流电压给定(V)
Uint16 _BA_UDC;														//中间直流电压(V)
Uint16 _BA_IA1;														//网郃相电流有效值(A)
Uint16 _BA_IB1;														//网侧B相电流有е?A)
Uint16 _BA_IC1;														//网侧C相电流有效值(A)
Uint16 _BA_IA2;														//电机侧A相电流有效值(A)
Uint16 _BA_IB2;														//电机侧B相电饔行е A)
Uint16 _BA_IC2;														//电机侧C相电流有效值(A)
Uint16 _BA_UAB1;													//网侧AB线电压有效值(V)
Uint16 _BA_UBC1;													//网侧BC线电压行е V)
Uint16 _BA_UAB2;													//电机侧AB线电压有效值(V)
Uint16 _BA_UBC2;													//电机侧BC线电流有效值(V)
Uint16 _BA_UAB0;												    	//主断前AB线电压有效值(V)
Uint16 _BA_UBC0;												    	//主断前BC线电流有效值(V)
Uint16 _BA_FREQ;													//电网频 hz)
Uint16 _BA_SPEED;													//电机转速(rpm)
Uint16 _BA_TA1;														//网侧变流器A桥畚露
Uint16 _BA_TB1;														//网侧变流鰾桥臂温度
Uint16 _BA_TC1;														//网侧变流器C桥臂温度
Uint16 _BA_TA2;														//电机侧变流器A桥臂温度
Uint16 _BA_TB2;														//电机侧变流器B桥臂温度
Uint16 _BA_TC2;														//电机侧变流器C桥臂温度
Uint16 _BA_PIONU;													//网侧电压环输出
Uint16 _BA_PIONID;													//网侧d轴电流环输出
Uint16 _BA_PIONIQ;													//网侧q轴电流环输出
Uint16 _BA_MEXI;													//
Uint16 _BA_PIOMID;													//机侧d轴电流环输出
Uint16 _BA_PIOMIQ;													//机侧q轴电流环输出
Uint16 _BA_GRDUD;													//传感器测量网压d
Uint16 _BA_GRDUQ;													//传感器测量网压q

//Uint16 _BA_STAUD;													//定子电压d MagnetCurve2013-12-13
Uint16 _BA_MC_IN;													//励磁校正输入 MagnetCurve2013-12-13
Uint16 _BA_MC_K;													//励磁校正输出 MagnetCurve2013-12-13
//Uint16 _BA_STAUQ;													//定子电压q MagnetCurve2013-12-13

Uint16 _BA_NPRID;													//传感器测量网压d
Uint16 _BA_NPRIQ;													//传感器测量网压q
//Uint16 _BA_EXCID;													//传感器测量网压d
//Uint16 _BA_EXCIQ;
Uint16 _BA_SCRIA;													//SCR电流a	20110906
Uint16 _BA_SCRIB;													//SCR电流b	20110906
Uint16 _BA_TLAC;
Uint16 _BA_TLDUDT;
Uint16 _BA_TNSKIIP;
Uint16 _BA_TMSKIIP;
Uint16 _BA_STAUABD;													//定子同步并网前定子前后电压差
Uint16 _BA_STAUBCD;													//定子同步并网前定子前后电压差
Uint16 _BA_STAIAC;													//定子线电流有效值显示
Uint16 _BA_STAIBA;													//定子线电流有效值显示
Uint16 _BA_PSTA;
Uint16 _BA_PNPR;
Uint16 _BA_PGRID;
Uint16 _BA_QSTA;
Uint16 _BA_QNPR;
Uint16 _BA_QGRID;
Uint16 _BA_SSTA;
Uint16 _BA_SNPR;
Uint16 _BA_SGRID;

Uint16 _SC_NPR_TLOV;
Uint16 _SC_MPR_TLOV;
Uint16 _SC_LVUDC1;
Uint16 _SC_LVUDC2;
Uint16 _SC_LVIAC2;
Uint16 _SC_TSCRON;
Uint16 _SC_MPR_UD;
Uint16 _SC_MPR_UQ;
Uint16 _SC_MSPEED1;
Uint16 _SC_MSPEED2;
Uint16 _SC_UDSTAC;
Uint16 _SCIB_BAUD;													//485波特率
Uint16 _SC_SKPTOV;
Uint16 _SC_FREQ1;
Uint16 _SC_FREQ2;

//-----------------------测试用变量-----------------------------------------------------------
int16 	zys[4];			//DA变量
Uint16 	daindex[4]; 	//BJTULVRT201204


//int32 	zys = 0;
//int16 	zys1,zys2,zys3,zys4;
Uint32 	i_cnt1=0;  //用于CCS波形显示
Uint32 	i_cnt2=0;  //用于CCS波形显示
Uint32 	i_cnt3=0;  //用于CCS波形显示
float   draw1[150]={0.0},draw2[150]={0.0},draw3[150]={0.0},draw4[150]={0.0},draw5[150]={0.0};
float   draw6[150]={0.0};//,draw7[100]={0.0},draw8[100]={0.0},draw9[100]={0.0},draw10[100]={0.0};
Uint16 zsector = 0;
float testtheta;

Uint16 temp_flag3;		//120507
Uint16 TX_SPEED;		//120507

Uint16	state_n=0;		//110818
Uint16	state_m=0;		//110818
Uint16	action1=0;		//110818
Uint16	action2=0;		//110818

//----------20121103新添加变量--------------
float   GRD_Ut;
float   GRD_Utlv;		//201205LVRTatZB
float   kq;
Uint16	CNT_SCRON;		//20120602
float   Te_instant;
float   Te_instant2;
float   Te_instant3;

//---------20121210----------
float   lv_ctrl1=0;
float   lv_ctrl2=0;
float   lv_ctrl3=0;
float   lv_ctrl4=0;
float   lv_ctrl5=0;
float   lv_ctrl6=0;

//----20130225atsp----
float   kq_lv;
float   NGS_Udq_p_lv;
float   Te_feedback_lv;                    //实际转矩值反馈
Uint16	scrdone=0;		//20130222
Uint16	scrhold=0;		//20130223
Uint16	scroff1=0;		//20130303
Uint16	cnt_lv_clrerram=0;		//20130303

//--------------------
//---------20130801---------
Uint16	ecpostep1 = 0;
Uint16	ecpostep2 = 0;
Uint16	ecpostep3 = 0;



//===========================================================================
// No more.
//===========================================================================
