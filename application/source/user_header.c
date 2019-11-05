#include "user_header.h"

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

float   lv_flag_flt;		//2013-12-6 LVRT鏍囧織浣嶅欢鏃惰鏁板櫒

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

/*涓嬮潰鐨勭敤浣淪VPWM璁＄畻*/
Uint16 	SW_NPR,SW_MPR;
float   vdc;	 
float   m=0.0;
float   ua_m=0,ub_m=0,uc_m=0;  //璋冨埗娉�
float   u_alfa_NPR=0,u_beta_NPR=0;
float   u_alfa_MPR=0,u_beta_MPR=0;


float OCS_Trf;                          //涓绘帶缁欒繃鏉ョ殑杞煩鎸囦护

struct	TRANS_DATA TRS_NPR_I;   //缃戜晶鍙樻祦鍣ㄧ殑鐢垫祦锛堣繖閲孨PR浣滀负鍚庣紑锛屼笉鐢╣rd锛屼互鍖哄垎鐢电綉鐢垫祦杩樻槸缃戜晶鍙樻祦鍣ㄧ數娴侊級
struct	TRANS_DATA TRS_MPR_I;   //鏈轰晶鍙樻祦鍣ㄧ殑鐢垫祦
struct	TRANS_DATA TRS_MPR_U;   //鏈轰晶鍙樻祦鍣ㄧ畻鑴夊啿鐢�
struct	TRANS_DATA TRS_NPR_U;   //缃戜晶鍙樻祦鍣ㄧ畻鑴夊啿
struct	TRANS_DATA TRS_NGS_U;   //顗呭棢缂ゎ増缂拷
struct	TRANS_DATA TRS_STA_I;   //瀹氬瓙鐢垫祦
struct	TRANS_DATA TRS_STA_U;   //瀹氬瓙鐢靛帇
struct	TRANS_DATA TRS_GSTA_U;  //鐩爣瀹氬瓙鐢靛帇
struct	TRANS_DATA TRS_PSTA_U;  //鐢ㄤ簬缂栫爜鍣ㄤ綅缃娴嬬殑瀹氬瓙鐢靛帇
struct	TRANS_DATA TRS_PMPR_I;  //鐢ㄤ簬缂栫爜鍣ㄤ綅缃娴嬬殑杞瓙鐢垫祦
struct	TRANS_DATA DIP_NPR_U;  //鐢ㄤ簬鍔熺巼璁＄畻
struct	TRANS_DATA DIP_NPR_I;  //鐢ㄤ簬鍔熺巼璁＄畻
struct	TRANS_DATA DIP_STA_U;  //鐢ㄤ簬鍔熺巼璁＄畻
struct	TRANS_DATA DIP_STA_I;  //鐢ㄤ簬鍔熺巼璁＄畻
struct	TRANS_DATA DIP_MPR_I;  //鐢ㄤ簬鍔熺巼璁＄畻
struct	TRANS_DATA TRS_GAC_U;  //鐢ㄤ簬201011PLL
struct	TRANS_DATA TRS_SCR_I;   //鏈轰晶crowbar鐢垫祦BJTULVRT201204


struct PI_DATA PI_NPR_Id;				//缃戜晶鍙樻祦鍣╠杞寸數娴侀棴鐜�
struct PI_DATA PI_NPR_Iq;				//缃戜晶鍙樻祦鍣╭杞寸數娴侀棴鐜�
struct PI_DATA PI_MPR_Id;				//鏈轰晶鍙橀珜楸犺酱鐢垫祦闂幆
struct PI_DATA PI_MPR_Iq;				//鏈轰晶鍙樻祦鍣╭杞寸數娴侀棴鐜�
struct PI_DATA PI_NPR_U;				//缃戜晶鍙樻祦鍣ㄧ數鍘嬬幆
struct PI_DATA PI_MPR_U;				//杞苟缃戦棴鐜�
struct PI_DATA PI_STA_Id;				//鍔辩鎺у埗d
struct PI_DATA PI_STA_Iq;				//鍔辩鎺у埗q
struct PI_DATA PI_DATA_PLL;				//201011PLL
struct PI_PARA PI_PARA_DYMI;			//鍔ㄦ�瀹藉甫瀹絇I鎺у埗BJTULVRT201204

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


//鎱㈤�AD澶勭悊瀵勫瓨鍣�
Uint16 _OUT_AMUX1=0;  //鐢ㄤ簬鎱㈤�AD閫夐�淇″彿锛屾瘡娆¤閫夐�涓嬩竴涓狝D閫氶亾锛宊OUT_AMUX鍔�锛岀劧鍚庨�鍒癈PLD鍘诲鐞嗭紝閫夐�16閫�鑺墖
Uint16 _OUT_AMUX2;    //鐢ㄤ簬鎱㈤�AD閫夐�淇″彿锛屾瘡娆¤閫夐�涓嬩竴涓狝D閫氶亾锛宊OUT_AMUX鍔�锛岀劧鍚庨�鍒癈PLD鍘诲鐞嗭紝閫夐�16閫�鑺墖


struct AD_DATA AD_OUT_GRD_U;  //鐢电綉鐢靛帇锛堜富鏂墠锛�
struct AD_DATA AD_OUT_STA_U;  //鐢垫満瀹氬瓙渚х數鍘�澶ф护娉㈤�閬�
struct AD_DATA AD_OUT_NGS_U;  //鐢电綉鐢靛帇锛堜富鏂悗锛�
struct AD_DATA AD_OUT_NPR_I;  //缃戜晶鍙樻祦鍣ㄧ數娴�
struct AD_DATA AD_OUT_MPR_I;  //鏈轰晶鍙樻祦鍣ㄧ數娴�
struct AD_DATA AD_OUT_STA_I;  //瀹氬瓙渚х數娴�
struct AD_DATA AD_OUT_NGF_U;  //鐢电綉鐢靛帇锛堜富鏂悗锛夊ぇ婊ゆ尝閫氶亾
struct AD_DATA AD_OUT_STAD_U;  //宸�
struct AD_DATA AD_OUT_SCR_I;  //ACTIVECROWBAR鐢垫祦
struct AD_DATA AD_OUT_DC_I;  //CHOPPER鐢垫祦

float  AD_OUT_UDC; //AD璁＄畻鍚庤緭鍑虹殑鐩存祦鐢垫鈺掞級

struct CAP_DATA CAP4,CAP5;

struct BS_DATA BS_MPR_Id;				//杞瓙渚х數娴乨杞�
struct BS_DATA BS_MPR_Iq;				//杞瓙渚х數娴乹杞�
struct BS_DATA BS_STA_Id;				//瀹氬瓙渚х數娴乨杞�
struct BS_DATA BS_STA_Iq;				//瀹氬瓙渚х數娴乹杞�
struct BS_DATA BS_NPR_Ud;				//缃戜晶鍙樻祦鍣╠杞�
struct BS_DATA BS_NPR_Uq;				//缃戜晶鍙樻祦鍣╠杞�
struct BS_DATA BS_NPR_Udn;				//缃戜晶鍙樻祦鍣╠杞�
struct BS_DATA BS_NPR_Uqn;				//缃戜晶鍙樻祦鍣╠杞�

struct BS_PARA BS_PARA_MPRI;
struct BS_PARA BS_PARA_STAI;
struct BS_PARA BS_PARA_NPRU;

//-----------------------------鍐呴儴鍙橀噺----------------------------------------------------------
Uint16  _NULL_VAL=0;
Uint16  _MSG_SCOUT1;												//SCOUT淇℃伅绾у埆(鍓嶆)
Uint16  _MSG_SCOUT2;												//SCOUT淇℃伅绾у埆(鏈)
Uint16  _SY_RTRN;
Uint32   POSCNT_TEST;
float   DM_imrd;   						//杞瓙鍔辩鐢垫祦
float   DM_imrq;   						//杞瓙鍔辩鐢垫祦
float   DM_Lr;							//褰撳墠閲嶈瘯娆℃暟
float   Te_feedback;                    //瀹為檯杞煩鍊煎弽棣�
float   Pnactive;    					//缃戜晶鏈夊姛鍔熺巼
float   Pnreactive;    					//缃戜晶鏃犲姛鍔熺巼
float   Pcreactive;    					//缃戜晶鐢靛鏃犲姛鍔熺巼201205LVRTatZB
//----------------------------鍙傛暟鍙橀噺------------------------------------------------------------
Uint16 _MC_TYPE;						//鏈哄瀷鍙傛暟
Uint16 _MC_REV;							//杞欢鐗堟湰
Uint16 _MC_DATE;						//鍑哄巶鏃ユ湡
Uint16 _MC_ID;							//浜у搧缂栧彿
Uint16 _SCIB_ADDR;						//485鑺傜偣鍦板潃
Uint16 _PROSTDBY1;						//
Uint16 _PROSTDBY2;						//

Uint16 _SW_FR;							//寮�叧棰戠巼(kHz)
Uint16 _DEADTIME;						//鑴夊啿鐨勬渶灏忓閫氭椂闂�us)
Uint16 _COMPTIME;						//鑴夊啿鐨勬渶灏忓閫氭椂闂�ms)
Uint16 _MINONTIME;						//鑴夊啿鐨勬渶灏忓閫氭椂闂�us)

Uint16 _RU_UDCT;						//鐢靛帇鎸囦护绉垎鏃堕棿(ms)
Uint16 _RU_IDT;							//鐢垫祦鎸囦护绉垎鏃堕棿(ms)
Uint16 _RU_IQT;							//鐢垫祦鎸囦护绉垎鏃堕棿(ms)
Uint16 _RU_TOQT;						//杞煩鎸囦护绉垎鍙�ms)
Uint16 _RU_AGLT;                        //鍔熺巼鍥犳暟瑙掓寚浠ょН鍒嗘椂闂�ms)
Uint16 _URF;							//鐩存祦鐢靛帇缁欏畾鍊�
Uint16 _MIDRF;							//d杞寸數娴佺粰瀹氬�
Uint16 _NIQRF;							//q杞寸數娴佺粰瀹氬�
Uint16 _MIQRF;							//q杞寸數娴佺粰瀹氬�
Uint16 _TOQRF;							//杞煩鎸囦护
Uint16 _AGLRF;							//鏈轰晶鍔熺巼鍥犳暟瑙�
Uint16 _EIDCO;							//鎵嬪姩 鏈轰晶鍔辩鐢垫祦璋冩暣绯绘暟
Uint16 _ENCODPOS;						//鎵嬪姩 缂栫爜鍣ㄥ垵濮嬩綅缃搴�

Uint16 _STDBY1;							//澶囩敤1
Uint16 _STDBY2;							//澶囩敤2
Uint16 _STDBY3;							//澶囩敤3
Uint16 _STDBY4;							//澶囩敤4
Uint16 _STDBY5;							//澶囩敤5
Uint16 _STDBY6;							//澶囩敤6
Uint16 _STDBY7;							//澶囩敤7
//Uint16 _STDBY8;							//澶囩敤8
Uint16 _MC_OK;							//澶囩敤8	 MagnetCurve2013-12-13
Uint16 _STDBY9;							//澶囩敤9
Uint16 _STDBY10;						//澶囩敤10
Uint16 _STDBY11;						//澶囩敤11
Uint16 _STDBY12;						//澶囩敤12
Uint16 _STDBY13;						//澶囩敤13
Uint16 _STDBY14;						//澶囩敤14
float _eidco;
float _encodpos;
float _sc_freq1;
float _sc_freq2;

//----'鏁板瓧閲忓彉閲�PC------
Uint16 _COMMAND1;
Uint16 _COMMAND2;
Uint16 _PCEROTRIG;					    //20100308
Uint16 _DISPLAY;
Uint16 _STATE1;
Uint16 _STATE2;
Uint16 _INPUT;
Uint16 _OUTPUT;
Uint16 _LVRT;

float _stdby01;							//澶囩敤缁忚繃灏忔暟鐐瑰鐞嗗悗鍊�
float _stdby02;							//澶囩敤缁忚繃灏忔暟鐐瑰鐞嗗悗鍊�
float _stdby03;							//璧ｇ粡杩囧皬鏁扮偣澶勭牀绗撅拷
float _stdby04;							//澶囩敤顒差惞鈭堫悶鎰︻湰鐮楃锟�
float _stdby05;							//澶囩敤缁忚繃灏忔暟澶勭悊鍚庡�
float _stdby06;							//澶囩敤缁忚繃灏忔暟鐐瑰鍊�
float _stdby07;							//澶囩敤缁忚繃灏忔暟鐐瑰鐞嗗悗鍊�
float _stdby08;							//澶囩敤缁忚繃灏忔暟鐐瑰鐞嗗悗鍊�
//------------------------杩愯妯″紡鍙橀噺-------------------------------------------------------------
Uint16 _ENSCR;							//

//-----------------------PI鐜弬鏁板彉閲�-------------------------------------------------------------
Uint16	_NPR_U_Kp;		  		//缃戜晶鍙樻祦鍣ㄧ數鍘嬮棴鐜瘮渚嬬郴鏁�
Uint16	_NPR_U_Ki;		   		//缃戜晶娣為珜闉吉璐℃爤鍧婎悹绐掑嚦锟�
Uint16	_NPR_U_Kd;		   		//缃戜晶婢夊櫒鐢靛帇闂偤鈷庣獟鍑筹拷
Uint16	_NPR_U_outmax;			//缃戜晶鍙樻祦鍣ㄧ吉璐℃爤鑲ユ稇楸胯柟锟�
Uint16	_NPR_U_errmax;		 	//缃戜晶鍙樻祦鍣ㄧ數鍘嬮棴鐜宸檺骞�
Uint16	_NPR_U_errmin;		   	//缃戜晶鍙樻祦闉吉璐℃爤鑲鸿煕閾戝厔锟�
Uint16	_NPR_U_incrementmax;	//缃戜晶鍙樻祦鍣ㄧ數鍘嬮棴鐜閲忛檺骞�

Uint16	_NPR_ID_Kp;				//缃戜晶鍙樻祦鍣ㄧ數娴侀棴鐜瘮渚嬬郴鏁�
Uint16	_NPR_ID_Ki;	   			//缃戜晶鍙樻祦鍣ㄧ數娴侀棴鐜Н鍒嗙郴鏁�
Uint16	_NPR_ID_Kd;	   			//缃戜晶鍙樻祦鍣ㄧ數娴侀棴鐜井鍒嗙郴鏁�
Uint16	_NPR_ID_outmax;			//缃戜晶鍙樻祦鍣ㄧ數娴侀棴鐜緭楸胯柟锟�
Uint16	_NPR_ID_errmax;	 		//缃戜晶鍙樻祦鍣ㄧ數娴侀棴鐜宸檺骞�
Uint16	_NPR_ID_errmin;	  		//缃戜晶鍙樻祦鍣ㄧ數娴侀棴鐜宸挌鈮堬拷
Uint16	_NPR_ID_incrementmax; 	//缃戜晶鍙樻祦鍣ㄧ數娴侀棴鐜毥鑲柟锟�

Uint16	_NPR_IQ_Kp;				//缃戜晶鍙樻祦鍣ㄧ數娴侀棴鐜瘮渚嬬郴鏁�
Uint16	_NPR_IQ_Ki;	   			//缃戜晶鍙橀珜闉紝闉呮爤鍧婎悹绐掑嚦锟�
Uint16	_NPR_IQ_Kd;	   			//缃戝暰娣為珜闉紝闉呮爤鑲衡拵绐掑嚦锟�
Uint16	_NPR_IQ_outmax;			//缃戜晶鍙樻祦鍣ㄧ數娴侀棴鐜緭鍑洪檺骞�
Uint16	_NPR_IQ_errmax;	 		//缃戜晶鍙樻祦鍣ㄧ數娴侀棴鐜宸檺骞�
Uint16	_NPR_IQ_errmin;	  		//缃戝暰娣為珜闉紝闉呯幆璇樊鏈�皬鍊�
Uint16	_NPR_IQ_incrementmax; 	//缃戜晶鍙樻祦鍣ㄧ數娴侀棴鐜閲忛檺骞�

Uint16	_MPR_U_Kp;	   			//鏈轰晶鍙樻祦鍣ㄧ數鍘嬮棴鐜瘮渚嬬郴鏁�
Uint16	_MPR_U_Ki;	  			//鏈轰晶鍙樻祦鍣ㄧ數鍘嬮棴鐜Н鍒嗙郴鏁�
Uint16	_MPR_U_Kd;	  			//鏈轰晶鍙樻祦鍣ㄧ數鍘嬮棴鐜井鍒嗙郴鏁�
Uint16	_MPR_U_outmax;	 		//鏈轰晶鍙樻祦鍣ㄧ數鍘嬮棴鐜緭鍑洪檺骞�
Uint16	_MPR_U_errmax;	  		//鏈轰晶鍙樻祦鍣ㄧ數鍘嬮棴鐜宸檺锟�
Uint16	_MPR_U_errmin;		 	//鏈轰晶鍙樻祦鍣ㄧ數鍘嬮棴鐜宸渶灏忓�
Uint16	_MPR_U_incrementmax; 	//鏈轰晶鍙樻祦鍣ㄧ數鍘嬮棴鐜閲忛檺骞�

Uint16 _MPR_ID_Kp;				//鏈轰晶鍙樻祦鍣ㄧ數娴侀棴鐜瘮渚嬬郴鏁�
Uint16 _MPR_ID_Ki;				//鏈轰晶鍙樻祦鍣ㄧ數娴侀棴鐜Н鍒嗙郴鏁�
Uint16 _MPR_ID_Kd;				//鏈轰晶鍙樻祦鍣ㄧ數娴侀棴鐜井鍒嗙郴鏁�
Uint16 _MPR_ID_outmax;			//鏈轰晶鍙樻祦鍣ㄧ數娴侀棴鐜緭鍑洪檺骞�
Uint16 _MPR_ID_errmax;			//鏈轰晶娣為珜闉紝闉呮爤鑲鸿煕閽曡柟锟�
Uint16 _MPR_ID_errmin;			//鏈轰晶鍙樻祦鍣ㄧ數娴侀棴鐜宸渶灏忓�
Uint16 _MPR_ID_incrementmax;		//鏈轰晶鍙樻祦鍣ㄧ數娴侀棴鐜閲忛檺骞�

Uint16 _MPR_IQ_Kp;				//鏈轰晶鍙樻祦鍣ㄧ數娴侀棴鐜瘮渚嬬郴鏁�
Uint16 _MPR_IQ_Ki;				//鏈轰晶鍙樻祦鍣ㄧ數娴侀棴鐜Н鍒嗙郴鏁�
Uint16 _MPR_IQ_Kd;				//鏈轰晶鍙樻祦鍣ㄧ數娴侀棴鐜井鍒嗙郴鏁�
Uint16 _MPR_IQ_outmax;			//鏈轰晶鍙樻祦鍣ㄧ數娴侀棴鐜緭鍑洪檺骞�
Uint16 _MPR_IQ_errmax;			//鏈轰晶鍙樻祦鍣ㄧ數娴侀棴鐜宸檺骞�
Uint16 _MPR_IQ_errmin;			//鏈轰晶鍙樻祦鍣ㄧ數娴侀棴鐜宸渶灏忓�
Uint16 _MPR_IQ_incrementmax;	//鏈轰晶鍙樻祦鍣ㄧ數娴侀棴鐜閲忛檺骞�


Uint16	_DYN_U_Kp;	   			//鏈轰晶鍙樻祦鍣ㄧ數鍘嬮棴鐜瘮渚嬬郴鏁�
Uint16	_DYN_U_Ki;	  			//鏈轰晶鍙樻祦鍣ㄧ數鍘嬮棴鐜Н鍒嗙郴鏁�
Uint16	_DYN_U_Kd;	  			//鏈轰晶鍙樻祦鍣ㄧ數鍘嬮棴鐜井鍒嗙郴鏁�
Uint16	_DYN_U_outmax;	 		//鏈轰晶鍙樻祦鍣ㄧ數鍘嬮棴鐜緭鍑洪檺骞�
Uint16	_DYN_U_errmax;	  		//鏈轰晶鍙樻祦鍣ㄧ數璐＄幆璇樊闄愬箙
Uint16	_DYN_U_errmin;		 	//鏈轰晶鍙樻祦鍣ㄧ數鍘嬮棴鐜宸渶灏忓�
Uint16	_DYN_U_incrementmax; 	//鏈轰晶鍙樻祦鍣ㄧ數璐℃爤鍚╅毥鑲柟锟�


Uint16 _SC_RTRN;													//鏁呴殰鏈�ぇ閲嶈瘯娆℃暟
Uint16 _SC_RTRT;													//涓ゆ鏁呴殰閲嶈瘯闂撮殧鏃堕棿(ms)

Uint16 _SC_IACOV1;													//鍩哄噯鐢垫祦鐨勭櫨鍒嗗�)
Uint16 _SC_UDCOV;													//涓棿鐩存祦鐢靛帇杩囧帇鍊�V)
Uint16 _SC_UDCOVH;													//涓棿鐩存祦鐢靛帇杩囧帇鍊硷紙缃戝帇璺岃惤锛�V)
Uint16 _SC_IDCOV;													//鏀逛负dc-chopper鐢垫祦淇濇姢BJTULVRT201204
//Uint16 _SC_UDCLV;													//涓棿鐩存祦鐢靛帇娆犲帇鍊�V)
Uint16 _SC_VDCON;													//涓婄數鐢靛帇
Uint16 _SC_UACOV1;													//缃戝帇浜ゆ祦鐢靛帇杩囧帇鍔ㄤ綔鍊�V)
Uint16 _SC_UACLV1;													//浜ゆ祦鐢靛帇缂虹浉鍔ㄤ綔鍊�V)
Uint16 _SC_IACOV2;													//鍩哄噯鐢垫祦鐨勭櫨鍒嗗�)
Uint16 _SC_PGOV;													//
Uint16 _SC_QGOV;													//
Uint16 _SC_IACOVST;                                                 //瀹氬瓙鐢垫祦杩囨祦淇濇姢

Uint16 _SC_Rs;														//瀹氬瓙鐢甸樆(mohm)
Uint16 _SC_Lls;														//瀹氬瓙婕忔姉(mH)
Uint16 _SC_Rr;														//杞瓙鐢甸樆(mohm)
Uint16 _SC_Llr;														//杞瓙婕忔姉(mH)
Uint16 _SC_Lm;														//鍔辩鐢碉拷mH)
Uint16 _SC_POLES;													//鏋佸鏁�
Uint16 _SC_Usn;														//瀹氬瓙棰濆畾鐢靛帇(V)
Uint16 _SC_Uro;                                                		//杞瓙寮�矾鐢靛帇(V)
Uint16 _SC_PLSPRVL;													//缂栫爜鍣ㄦ瘡鍦堝厜鏍呮暟閲�
Uint16 _SC_MSTDBY;                                               	//鐢垫満鍙傛暟澶囩敤
Uint16 _SC_EXISTY1;                                               	//鐢垫満鍔辩璋冭妭澶囩敤1
Uint16 _SC_EXISTY2;                                               	//鐢垫満鍔辩璋冭妭澶囩敤2
Uint16 _SC_EXISTY3;                                               	//鐢垫満鍔辩璋冭妭澶囩敤3
Uint16 _SC_EXISTY4;                                               	//鐢垫満鍔辩璋冭妭澶囩敤4
Uint16 _SC_EXISTY5;                                               	//鐢垫満鍔辩璋冭妭澶囩敤5

Uint16 _BA_ERR4;													//绗洓娆℃晠闅滀俊鎭�
Uint16 _BA_ERR3;													//绗笁娆℃晠闅滀俊鎭�
Uint16 _BA_ERR2;													//绗簩娆℃晠闅滀俊鎭�
Uint16 _BA_ERR1;													//绗竴娆℃晠闅滀俊鎭�
Uint16 _BA_ERR5;													//绀烘尝鍣ㄦ晠闅滀俊鎭�
//--------------------------------鎶ヨ淇℃伅鍙橈拷----------------------------------------------------
Uint16 _BA_EMIDRF;													//鏈�柊鏁呴殰鏃跺埢 d杞寸數娴佹寚浠�A)
Uint16 _BA_ENIQRF;													//鏈�柊鏁呴殰鏃跺埢 q杞寸數娴佹寚浠�A)
Uint16 _BA_EMIQRF;													//鏈�箍闅滄椂鍒�q杞寸數娴佹寚浠�A)
Uint16 _BA_ETOQRF;													//鏈�柊鏁呴殰鏃跺埢 杞煩鎸囦护(NM)
Uint16 _BA_EURF;													//鏈�柊鏁呴殰鏃跺埢 涓棿鐩存祦鐢靛帇缁欙拷V)
Uint16 _BA_EUDC;													//鏈�柊鏁呴殰鏃跺埢 涓棿鐩存祦鐢靛帇(V)
Uint16 _BA_EAGLRF;													//鏈�柊鏁呴殰鏃跺埢 鏃犲姛瑙掑害鎸囦护()
Uint16 _BA_EIA1;													//鏈�柊鏁呴殰鏃跺埢 缃戜晶A鐩哥數娴佹湁鏁堝�(A)
Uint16 _BA_EIB1;													//鏈�柊鏁呴殰鏃跺埢 缃戜晶B鐩哥數娴佹湁鏁堝�(A)
Uint16 _BA_EIC1;													//鏈�柊鏁呴殰鏃跺埢 缃戜晶C鐩哥數娴佹湁鏁堝�(A)
Uint16 _BA_EIA2;													//鏈�柊鏁呴殰鏃跺埢 缂侇寔閮冪浉鐢垫祦鏈夋晥鍊�A)
Uint16 _BA_EIB2;													//鏈�柊鏁呴殰鏃跺埢 鐢垫満渚鐩哥數娴佹湁鏁堝�(A)
Uint16 _BA_EIC2;													//鏈�柊鏁呴殰鏃跺埢 鐢垫満渚鐩哥數娴佹湁鏁堝�(A)
Uint16 _BA_EUAB1;													//鏈�柊鏁呴殰鏃跺埢 缃戜晶A鐩哥數鍘嬫湁鏁堝�(V)
Uint16 _BA_EUBC1;													//鏈�柊鏁呴殰鏃跺埢 缃戜晶B鐩哥數鍘嬫湁鏁堝�(V)
Uint16 _BA_EUAB2;													//鏈�柊鏁呴殰鏃跺埢 缃戜晶鐩哥數鍘嬫湁鏁堝�(V)
Uint16 _BA_EUBC2;													//鏈�柊鏁呴殰鏃跺埢 鐢垫満渚鐩哥數娴佹湁鏁堝�(V)
Uint16 _BA_EUAB0;													//鏈�柊鏁呴殰鏃跺埢 涓绘柇鍓岮B绾跨數鍘嬫湁鏁堝�(V)
Uint16 _BA_EUBC0;													//鏈�柊鏁呴殰鏃跺埢 涓婚敤鐧嘋绾跨數鍘嬫湁鏁堝�(V)
Uint16 _BA_EFREQ;													//鏈�柊鏁呴殰鏃跺埢 鐢电綉棰戠巼(hz)
Uint16 _BA_ESPEED;													//鏈�柊鏁呴殰鏃跺埢 鐢垫満杞�(rpm)
Uint16 _BA_ENPRUD;              			//d杞翠富鏂悗缃戝帇鍙嶉20091026atzy
Uint16 _BA_ENPRUQ;          				//q杞翠富鏂悗缃戝帇鍙嶉20091026atzy
Uint16 _BA_ENPRUD2;          				//d杞翠富鏂悗缃戝帇鍙嶉 婊ゆ尝鍚�0091026atzy
Uint16 _BA_ENPRUQ2;          				//q杞翠富鏂悗缃戝帇鍙嶉 婊ゆ尝鍚�0091026atzy
Uint16 _BA_ENUDOUT;          				//顗呴兛宀吉鏁呮稇锟�091026atzy
Uint16 _BA_ENUQOUT;          				//缃戜晶q杞寸數鍘嬭緭鍑�0091026atzy
Uint16 _BA_ETA1;													//鏈�柊鏁呴殰鏃跺埢 缃戜晶鍙樻祦鍣ˋ妗ヨ噦娓╁害
Uint16 _BA_ETB1;													//鏈�柊鏁呴殰鏃跺埢 缃戜晶鍙樻祦鍣˙妗ヨ噦娓╁害
Uint16 _BA_ETC1;													//鏈�柊鏁呴殰鏃跺埢 缃戜晶鍙樻祦鍣–妗ヨ噦娓╁害
Uint16 _BA_ETA2;													//鏈�柊鏁呴殰鏃跺埢 鐢垫満渚у彉娴佸櫒A鐤熺暁闇诧拷
Uint16 _BA_ETB2;													//鏈�柊鏁呴殰鏃跺埢 鐢垫満渚ф窞楂岄熬妗ヨ噦娓╋拷
Uint16 _BA_ETC2;													//鏈�箍鏀堕矞绗拷鐢垫満渚у彉娴佸櫒C妗ヨ噦娓╁害
Uint16 _BA_EPIONU;													//鏈�柊鏁呴殰鏃跺埢 缃戜晶鐢靛帇鐜緭鍑�
Uint16 _BA_EPIONID;													//鏈�柊鏁呴殰鏃跺埢 缃戜晶d杞寸數娴佺幆杈撳嚭
Uint16 _BA_EPIONIQ;													//鏈�柊鏁呴殰鏃跺埢 缃戜晶q杞寸數娴佺幆杈撳嚭
Uint16 _BA_EMEXI;													//鏈�柊鏁呴殰鏃跺埢 鏈轰晶鍔辩鐞嗚璁＄畻鍊兼樉绀�
Uint16 _BA_EPIOMID;													//鏈�柊鏁呴殰鏃跺埢 鏈轰晶d杞寸數娴佺幆杈擄拷
Uint16 _BA_EPIOMIQ;													//鏈�柊鏁呴殰鏃跺埢 鏈轰晶q杞寸數娴佺幆杈撳嚭
Uint16 _BA_ETLAC;													//鏈�柊鏁呴殰鏃跺埢 缃戜晶鐢垫劅娓╁害
Uint16 _BA_ETLDUDT;													//鏈�柊鏁呴殰鏃跺埢 鏈轰晶鐢垫劅娓╁害
Uint16 _BA_ETSKIIP;													//鏈�柊鏁呴殰鏃跺埢 SKIIP娓╋拷
Uint16 _BA_ESTAIAC;	
Uint16 _BA_ESTAIBA;	
Uint16 _BA_ETOQFB;	
Uint16 _BA_EPSTA;	
Uint16 _BA_EPNPR;	
Uint16 _BA_EPGRID;	

Uint16 _BA_TIME4_0;													//鏈�柊鏁呴殰鏃堕棿(绉�
Uint16 _BA_TIME4_1;													//鏈�柊鏁呴殰鏃堕棿(锟�
Uint16 _BA_TIME4_2;													//鏈�柊鏁呴殰鏃堕棿(鏃�
Uint16 _BA_TIME4_3;													//鏈�柊鏁呴殰鏃堕棿(鏃�
Uint16 _BA_TIME4_4;													//鏈�柊鏁呴矞濂旓拷鏈�
Uint16 _BA_TIME4_5;													//鏈�柊鏁呴殰鏃堕棿(骞�

Uint16 _BA_TIME3_0;													//绗笁娆℃晠闅滄椂闂�绉�
Uint16 _BA_TIME3_1;													//绗笁娆℃晠闅滄椂闂�鍒�
Uint16 _BA_TIME3_2;													//绗笁娆℃晠闅滄椂闂�鏃�
Uint16 _BA_TIME3_3;													//绗笁娆℃晠闅滄椂闂�鏃�
Uint16 _BA_TIME3_4;													//绗笁娆℃晠闅滄椂闂�鏈�
Uint16 _BA_TIME3_5;													//绗笁娆℃晠椴滃锟藉勾)

Uint16 _BA_TIME2_0;													//绗簩闂殰鏃堕棿(绉�
Uint16 _BA_TIME2_1;													//绗簩娆℃晠闅滄椂闂�鍒�
Uint16 _BA_TIME2_2;													//绗簩娆℃晠闅滃?鏃�
Uint16 _BA_TIME2_3;													//绗簩娆℃晠闅滄椂闂�鏃�
Uint16 _BA_TIME2_4;													//绗簩娆℃晠闅滄椂闂�鏈�
Uint16 _BA_TIME2_5;													//绗簩娆℃晠闅滄椂?骞�

Uint16 _BA_TIME1_0;													//绗竴娆℃晠闅滄椂闂�绉�
Uint16 _BA_TIME1_1;													//绗竴娆℃晠闅滄椂闂�鍒�
Uint16 _BA_TIME1_2;													//绗竴娆℃晠闅滄椂闂�鏃�
Uint16 _BA_TIME1_3;													//绗竴娆℃晠闅滄椂闂�鏃�
Uint16 _BA_TIME1_4;													//绗竴娆℃晠闅滄椂闂�鏈�
Uint16 _BA_TIME1_5;													//绗竴娆℃晠闅滄椂闂�骞�

Uint16 _BA_TIME5_0;													//绀烘尝鍣ㄦ晠闅滄椂闂�绉�
Uint16 _BA_TIME5_1;													//绀烘尝鍣ㄦ晠闅滄椂闂�鍒�
Uint16 _BA_TIME5_2;													//绀烘尝鍣ㄦ晠闅滄椂闂�鏃�
Uint16 _BA_TIME5_3;													//绀烘尝鍣ㄦ晠闅滄椂闂�鏃�
Uint16 _BA_TIME5_4;													//绀烘尝鍣ㄦ晠闅滄椂闂�鏈�
Uint16 _BA_TIME5_5;													//绀烘尝鍣ㄦ晠闅滄椂闂�骞�

//-------------------------------------杩愯鐩戞帶鍙橀噺-----------------------------------------------
Uint16 _BA_MIDRF;													//d杞寸數娴佹寚浠�A)
Uint16 _BA_NIQRF;													//q杞寸數娴佹寚浠�A)
Uint16 _BA_MIQRF;													//q杞寸數娴佹寚浠�A)
Uint16 _BA_TOQRF;													//杞煩鎸囦护(NM)
Uint16 _BA_AGLRF;													//鏃犲姛瑙掑害鎸囦护(NM)
Uint16 _BA_TOQFB;													//杞煩鍙嶉(NM)
Uint16 _BA_URF;														//涓棿鐩存祦鐢靛帇缁欏畾(V)
Uint16 _BA_UDC;														//涓棿鐩存祦鐢靛帇(V)
Uint16 _BA_IA1;														//缃戦儍鐩哥數娴佹湁鏁堝�(A)
Uint16 _BA_IB1;														//缃戜晶B鐩哥數娴佹湁械?A)
Uint16 _BA_IC1;														//缃戜晶C鐩哥數娴佹湁鏁堝�(A)
Uint16 _BA_IA2;														//鐢垫満渚鐩哥數娴佹湁鏁堝�(A)
Uint16 _BA_IB2;														//鐢垫満渚鐩哥數楗旇械锟紸)
Uint16 _BA_IC2;														//鐢垫満渚鐩哥數娴佹湁鏁堝�(A)
Uint16 _BA_UAB1;													//缃戜晶AB绾跨數鍘嬫湁鏁堝�(V)
Uint16 _BA_UBC1;													//缃戜晶BC绾跨數鍘嬭械锟絍)
Uint16 _BA_UAB2;													//鐢垫満渚B绾跨數鍘嬫湁鏁堝�(V)
Uint16 _BA_UBC2;													//鐢垫満渚C绾跨數娴佹湁鏁堝�(V)
Uint16 _BA_UAB0;												    	//涓绘柇鍓岮B绾跨數鍘嬫湁鏁堝�(V)
Uint16 _BA_UBC0;												    	//涓绘柇鍓岯C绾跨數娴佹湁鏁堝�(V)
Uint16 _BA_FREQ;													//鐢电綉棰戯拷hz)
Uint16 _BA_SPEED;													//鐢垫満杞�(rpm)
Uint16 _BA_TA1;														//缃戜晶鍙樻祦鍣ˋ妗ョ暁闇�
Uint16 _BA_TB1;														//缃戜晶鍙樻祦榘炬ˉ鑷傛俯搴�
Uint16 _BA_TC1;														//缃戜晶鍙樻祦鍣–妗ヨ噦娓╁害
Uint16 _BA_TA2;														//鐢垫満渚у彉娴佸櫒A妗ヨ噦娓╁害
Uint16 _BA_TB2;														//鐢垫満渚у彉娴佸櫒B妗ヨ噦娓╁害
Uint16 _BA_TC2;														//鐢垫満渚у彉娴佸櫒C妗ヨ噦娓╁害
Uint16 _BA_PIONU;													//缃戜晶鐢靛帇鐜緭鍑�
Uint16 _BA_PIONID;													//缃戜晶d杞寸數娴佺幆杈撳嚭
Uint16 _BA_PIONIQ;													//缃戜晶q杞寸數娴佺幆杈撳嚭
Uint16 _BA_MEXI;													//
Uint16 _BA_PIOMID;													//鏈轰晶d杞寸數娴佺幆杈撳嚭
Uint16 _BA_PIOMIQ;													//鏈轰晶q杞寸數娴佺幆杈撳嚭
Uint16 _BA_GRDUD;													//浼犳劅鍣ㄦ祴閲忕綉鍘媎
Uint16 _BA_GRDUQ;													//浼犳劅鍣ㄦ祴閲忕綉鍘媞

//Uint16 _BA_STAUD;													//瀹氬瓙鐢靛帇d MagnetCurve2013-12-13
Uint16 _BA_MC_IN;													//鍔辩鏍℃杈撳叆 MagnetCurve2013-12-13
Uint16 _BA_MC_K;													//鍔辩鏍℃杈撳嚭 MagnetCurve2013-12-13
//Uint16 _BA_STAUQ;													//瀹氬瓙鐢靛帇q MagnetCurve2013-12-13

Uint16 _BA_NPRID;													//浼犳劅鍣ㄦ祴閲忕綉鍘媎
Uint16 _BA_NPRIQ;													//浼犳劅鍣ㄦ祴閲忕綉鍘媞
//Uint16 _BA_EXCID;													//浼犳劅鍣ㄦ祴閲忕綉鍘媎
//Uint16 _BA_EXCIQ;
Uint16 _BA_SCRIA;													//SCR鐢垫祦a	20110906
Uint16 _BA_SCRIB;													//SCR鐢垫祦b	20110906
Uint16 _BA_TLAC;
Uint16 _BA_TLDUDT;
Uint16 _BA_TNSKIIP;
Uint16 _BA_TMSKIIP;
Uint16 _BA_STAUABD;													//瀹氬瓙鍚屾骞剁綉鍓嶅畾瀛愬墠鍚庣數鍘嬪樊
Uint16 _BA_STAUBCD;													//瀹氬瓙鍚屾骞剁綉鍓嶅畾瀛愬墠鍚庣數鍘嬪樊
Uint16 _BA_STAIAC;													//瀹氬瓙绾跨數娴佹湁鏁堝�鏄剧ず
Uint16 _BA_STAIBA;													//瀹氬瓙绾跨數娴佹湁鏁堝�鏄剧ず
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
Uint16 _SCIB_BAUD;													//485娉㈢壒鐜�
Uint16 _SC_SKPTOV;
Uint16 _SC_FREQ1;
Uint16 _SC_FREQ2;
 
//-----------------------娴嬭瘯鐢ㄥ彉閲�----------------------------------------------------------
int16 	zys[4];			//DA鍙橀噺
Uint16 	daindex[4]; 	//BJTULVRT201204


//int32 	zys = 0;
//int16 	zys1,zys2,zys3,zys4;
Uint32 	i_cnt1=0;  //鐢ㄤ簬CCS娉㈠舰鏄剧ず
Uint32 	i_cnt2=0;  //鐢ㄤ簬CCS娉㈠舰鏄剧ず
Uint32 	i_cnt3=0;  //鐢ㄤ簬CCS娉㈠舰鏄剧ず
float   draw1[150]={0.0};
float	draw2[150]={0.0};
float	draw3[150]={0.0};
float	draw4[150]={0.0};
float	draw5[150]={0.0};
float   draw6[150]={0.0};//,draw7[100]={0.0},draw8[100]={0.0},draw9[100]={0.0},draw10[100]={0.0};
Uint16 zsector = 0;
float testtheta;

Uint16 temp_flag3;		//120507
Uint16 TX_SPEED;		//120507

Uint16	state_n=0;		//110818
Uint16	state_m=0;		//110818
Uint16	action1=0;		//110818
Uint16	action2=0;		//110818

//----------20121103鏂版坊鍔犲彉閲�-------------
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
float   Te_feedback_lv;                    //瀹為檯杞煩鍊煎弽棣�
Uint16	scrdone=0;		//20130222
Uint16	scrhold=0;		//20130223
Uint16	scroff1=0;		//20130303
Uint16	cnt_lv_clrerram=0;		//20130303

//--------------------
//---------20130801---------
Uint16	ecpostep1 = 0;
Uint16	ecpostep2 = 0;
Uint16	ecpostep3 = 0;

//------------------------------------const瀹氫箟--------------------------------------------
//eeprom浣嶆搷浣�
const  Uint16 ONEBYTE[8]={0x0080,0x0040,0x0020,0x0010,0x0008,0x0004,0x0002,0x0001};

//AD1544閫氶亾閫夋嫨
const  Uint16 AD1544[4]={0x0000,0x2000,0x4000,0x6000};

//--------------------------------------鍙橀噺瀹氫箟-------------------------------------------
Uint16	flag[16];													//鏍囧織浣嶅彉閲�
//Uint16	disp[15];													//鏍囧織鍙橀噺

//---2013-12-13--ZZJ澧炲姞鐢垫満鍔辩
//------------------------鐢垫満鍔辩鍙傛暟璇嗗埆MagnetCurve200909------------------------------------
float   MC_y_test;
float   MC_U_test;
float	Uns_ft;
Uint16	MC_N_test;
Uint32	MC_F_cnt;
//---2013-12-13--ZZJ澧炲姞鐢垫満鍔辩


//===========================================================================
// No more.
//===========================================================================
