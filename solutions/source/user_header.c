#include "DSP2833x_Device.h"     				// DSP2833x Headerfile Include File
#include "user_header.h"

Uint16 DEBUG_OPER;                                        //20100401at27

//��������趨2010atcpc
float  	MPR_Ls;	 	    				//�����Ը�	--��λH
float	MPR_Lr;	 	    				//ת���Ը�	--��λH
float 	MPR_Lm;	 	    				//��ת�ӻ���--��λH
float 	MPR_Rs;	     					//���ӵ���	--��λohm
float 	MPR_Rr;	    					//ת�ӵ���	--��λohm
float 	SIGMA;							//(1-MPR_Lm*MPR_Lm/(MPR_Ls*MPR_Lr))
float	STAROTRTO;       				//��ת�ӱ��
float	STAROTRTO2;       				//��ת�ӱ�ȵ�ƽ��
float	POLEPAIRES;       				//���������

Uint16  BANK_RAMDATA_POS;						    					//�洢�����Ĵ洢��λ��[0,4999]
Uint16  ERROR_RAMDATA_POS;

Uint16   _OUT4_DATA;		//�ñ�־λ���ø�Ϊ�궨��20130222//�洢�����Ĵ洢��λ��[0,4999]

//------------------------------------const����--------------------------------------------

//eepromλ����
const  Uint16 ONEBYTE[8]={0x0080,0x0040,0x0020,0x0010,0x0008,0x0004,0x0002,0x0001};

//AD1544ͨ��ѡ��
const  Uint16 AD1544[4]={0x0000,0x2000,0x4000,0x6000};
//--------------------------------------��������-------------------------------------------
Uint16	flag[16];													//��־λ����
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

float   lv_flag_flt;		//2013-12-6 LVRT��־λ��ʱ������

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

/*���������SVPWM����*/
Uint16 SW_NPR,SW_MPR;
float   vdc;
float   m=0.0;
float   ua_m=0,ub_m=0,uc_m=0;  //���Ʋ�
float   u_alfa_NPR=0,u_beta_NPR=0;
float   u_alfa_MPR=0,u_beta_MPR=0;

struct	GIVE GIVE;
float OCS_Trf;                          //���ظ�������ת��ָ��

struct RUN RUN;

struct	TRANS_DATA TRS_NPR_I;   //����������ĵ���������NPR��Ϊ��׺������grd�������ֵ��������������������������
struct	TRANS_DATA TRS_MPR_I;   //����������ĵ���
struct	TRANS_DATA TRS_MPR_U;   //�����������������
struct	TRANS_DATA TRS_NPR_U;   //���������������
struct	TRANS_DATA TRS_NGS_U;   //���������
struct	TRANS_DATA TRS_STA_I;   //���ӵ���
struct	TRANS_DATA TRS_STA_U;   //���ӵ�ѹ
struct	TRANS_DATA TRS_GSTA_U;  //Ŀ�궨�ӵ�ѹ
struct	TRANS_DATA TRS_PSTA_U;  //���ڱ�����λ�ü��Ķ��ӵ�ѹ
struct	TRANS_DATA TRS_PMPR_I;  //���ڱ�����λ�ü���ת�ӵ���
struct	TRANS_DATA DIP_NPR_U;  //���ڹ��ʼ���
struct	TRANS_DATA DIP_NPR_I;  //���ڹ��ʼ���
struct	TRANS_DATA DIP_STA_U;  //���ڹ��ʼ���
struct	TRANS_DATA DIP_STA_I;  //���ڹ��ʼ���
struct	TRANS_DATA DIP_MPR_I;  //���ڹ��ʼ���
struct	TRANS_DATA TRS_GAC_U;  //����201011PLL
struct	TRANS_DATA TRS_SCR_I;   //����crowbar����BJTULVRT201204

struct I_DATA_PLL I_DATA_PLL;

struct PI_DATA PI_NPR_Id;				//���������d������ջ�
struct PI_DATA PI_NPR_Iq;				//���������q������ջ�
struct PI_DATA PI_MPR_Id;				//��������d������ջ�
struct PI_DATA PI_MPR_Iq;				//���������q������ջ�
struct PI_DATA PI_NPR_U;				//�����������ѹ��
struct PI_DATA PI_MPR_U;				//�����ջ�
struct PI_DATA PI_STA_Id;				//���ſ���d
struct PI_DATA PI_STA_Iq;				//���ſ���q
struct PI_DATA PI_DATA_PLL;				//201011PLL
struct PI_PARA PI_PARA_DYMI;			//��̬�����PI����BJTULVRT201204

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
//����AD����Ĵ���
Uint16 _OUT_AMUX1=0;  //��������ADѡͨ�źţ�ÿ��Ҫѡͨ��һ��ADͨ����_OUT_AMUX��1��Ȼ���͵�CPLDȥ����ѡͨ16ѡ1оƬ
Uint16 _OUT_AMUX2;    //��������ADѡͨ�źţ�ÿ��Ҫѡͨ��һ��ADͨ����_OUT_AMUX��1��Ȼ���͵�CPLDȥ����ѡͨ16ѡ1оƬ

struct AD AD;
struct ADFINAL ADFINAL;

struct AD_DATA AD_OUT_GRD_U;  //������ѹ������ǰ��
struct AD_DATA AD_OUT_STA_U;  //������Ӳ��ѹ ���˲�ͨ��
struct AD_DATA AD_OUT_NGS_U;  //������ѹ�����Ϻ�
struct AD_DATA AD_OUT_NPR_I;  //�������������
struct AD_DATA AD_OUT_MPR_I;  //�������������
struct AD_DATA AD_OUT_STA_I;  //���Ӳ����
struct AD_DATA AD_OUT_NGF_U;  //������ѹ�����Ϻ󣩴��˲�ͨ��
struct AD_DATA AD_OUT_STAD_U;  //��ֵ
struct AD_DATA AD_OUT_SCR_I;  //ACTIVECROWBAR����
struct AD_DATA AD_OUT_DC_I;  //CHOPPER����

float  AD_OUT_UDC; //AD����������ֱ���繣�V��

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

struct BS_DATA BS_MPR_Id;				//ת�Ӳ����d��
struct BS_DATA BS_MPR_Iq;				//ת�Ӳ����q��
struct BS_DATA BS_STA_Id;				//���Ӳ����d��
struct BS_DATA BS_STA_Iq;				//���Ӳ����q��
struct BS_DATA BS_NPR_Ud;				//���������d��
struct BS_DATA BS_NPR_Uq;				//���������d��
struct BS_DATA BS_NPR_Udn;				//���������d��
struct BS_DATA BS_NPR_Uqn;				//���������d��

struct BS_PARA BS_PARA_MPRI;
struct BS_PARA BS_PARA_STAI;
struct BS_PARA BS_PARA_NPRU;

//-----------------------------�ڲ�����----------------------------------------------------------
Uint16  _NULL_VAL = 0;
Uint16  _MSG_SCOUT1;												//SCOUT��Ϣ����(ǰ��)
Uint16  _MSG_SCOUT2;												//SCOUT��Ϣ����(����)
Uint16  _SY_RTRN;
Uint32   POSCNT_TEST;
float   DM_imrd;   						//ת�����ŵ���
float   DM_imrq;   						//ת�����ŵ���
float   DM_Lr;							//��ǰ���Դ���
float   Te_feedback;                    //ʵ��ת��ֵ����
float   Pnactive;    					//�����й�����
float   Pnreactive;    					//�����޹�����
float   Pcreactive;    					//��������޹�����201205LVRTatZB

//----------------------------��������------------------------------------------------------------
Uint16 _MC_TYPE;						//���Ͳ���
Uint16 _MC_REV;							//����汾
Uint16 _MC_DATE;						//��������
Uint16 _MC_ID;							//��Ʒ���
Uint16 _SCIB_ADDR;						//485�ڵ��ַ
Uint16 _PROSTDBY1;						//
Uint16 _PROSTDBY2;						//

Uint16 _SW_FR;							//����Ƶ��(kHz)
Uint16 _DEADTIME;						//�������С��ͨʱ��(us)
Uint16 _COMPTIME;						//�������С��ͨʱ��(ms)
Uint16 _MINONTIME;						//�������С��ͨʱ��(us)

Uint16 _RU_UDCT;						//��ѹָ�����ʱ��(ms)
Uint16 _RU_IDT;							//����ָ�����ʱ��(ms)
Uint16 _RU_IQT;							//����ָ�����ʱ��(ms)
Uint16 _RU_TOQT;						//ת��ָ����ֱ�(ms)
Uint16 _RU_AGLT;                        //����������ָ�����ʱ��(ms)
Uint16 _URF;							//ֱ����ѹ����ֵ
Uint16 _MIDRF;							//d���������ֵ
Uint16 _NIQRF;							//q���������ֵ
Uint16 _MIQRF;							//q���������ֵ
Uint16 _TOQRF;							//ת��ָ��
Uint16 _AGLRF;							//���๦��������
Uint16 _EIDCO;							//�ֶ� �������ŵ�������ϵ��
Uint16 _ENCODPOS;						//�ֶ� ��������ʼλ�ýǶ�

Uint16 _STDBY1;							//����1
Uint16 _STDBY2;							//����2
Uint16 _STDBY3;							//����3
Uint16 _STDBY4;							//����4
Uint16 _STDBY5;							//����5
Uint16 _STDBY6;							//����6
Uint16 _STDBY7;							//����7
//Uint16 _STDBY8;							//����8
Uint16 _MC_OK;							//����8	 MagnetCurve2013-12-13
Uint16 _STDBY9;							//����9
Uint16 _STDBY10;						//����10
Uint16 _STDBY11;						//����11
Uint16 _STDBY12;						//����12
Uint16 _STDBY13;						//����13
Uint16 _STDBY14;						//����14
float _eidco;
float _encodpos;
float _sc_freq1;
float _sc_freq2;

//----'����������'PC------
Uint16 _COMMAND1;
Uint16 _COMMAND2;
Uint16 _PCEROTRIG;					    //20100308
Uint16 _DISPLAY;
Uint16 _STATE1;
Uint16 _STATE2;
Uint16 _INPUT;
Uint16 _OUTPUT;
Uint16 _LVRT;

float _stdby01;							//���þ���С���㴦���ֵ
float _stdby02;							//���þ���С���㴦���ֵ
float _stdby03;							//�Ӿ���С���㴦���
float _stdby04;							//���í��С���㴦����
float _stdby05;							//���þ���С�������ֵ
float _stdby06;							//���þ���С���㴦ֵ
float _stdby07;							//���þ���С���㴦���ֵ
float _stdby08;							//���þ���С���㴦���ֵ
//------------------------����ģʽ����-------------------------------------------------------------
Uint16 _ENSCR;							//

//-----------------------PI����������--------------------------------------------------------------
Uint16	_NPR_U_Kp;		  		//�����������ѹ�ջ�����ϵ��
Uint16	_NPR_U_Ki;		   		//�����������ѹ�ջ�����ϵ�
Uint16	_NPR_U_Kd;		   		//����������ѹ�շ΢��ϵ�
Uint16	_NPR_U_outmax;			//����������ѹ�ջ�����޷
Uint16	_NPR_U_errmax;		 	//�����������ѹ�ջ�����޷�
Uint16	_NPR_U_errmin;		   	//����������ѹ�ջ�������
Uint16	_NPR_U_incrementmax;	//�����������ѹ�ջ������޷�

Uint16	_NPR_ID_Kp;				//��������������ջ�����ϵ��
Uint16	_NPR_ID_Ki;	   			//��������������ջ�����ϵ��
Uint16	_NPR_ID_Kd;	   			//��������������ջ�΢��ϵ��
Uint16	_NPR_ID_outmax;			//��������������ջ�����޷
Uint16	_NPR_ID_errmax;	 		//��������������ջ�����޷�
Uint16	_NPR_ID_errmin;	  		//��������������ջ�����С�
Uint16	_NPR_ID_incrementmax; 	//��������������ջ�����޷

Uint16	_NPR_IQ_Kp;				//��������������ջ�����ϵ��
Uint16	_NPR_IQ_Ki;	   			//�������������ջ�����ϵ�
Uint16	_NPR_IQ_Kd;	   			//�������������ջ�΢��ϵ�
Uint16	_NPR_IQ_outmax;			//��������������ջ�����޷�
Uint16	_NPR_IQ_errmax;	 		//��������������ջ�����޷�
Uint16	_NPR_IQ_errmin;	  		//��������������������Сֵ
Uint16	_NPR_IQ_incrementmax; 	//��������������ջ������޷�

Uint16	_MPR_U_Kp;	   			//�����������ѹ�ջ�����ϵ��
Uint16	_MPR_U_Ki;	  			//�����������ѹ�ջ�����ϵ��
Uint16	_MPR_U_Kd;	  			//�����������ѹ�ջ�΢��ϵ��
Uint16	_MPR_U_outmax;	 		//�����������ѹ�ջ�����޷�
Uint16	_MPR_U_errmax;	  		//�����������ѹ�ջ������
Uint16	_MPR_U_errmin;		 	//�����������ѹ�ջ������Сֵ
Uint16	_MPR_U_incrementmax; 	//�����������ѹ�ջ������޷�

Uint16 _MPR_ID_Kp;				//��������������ջ�����ϵ��
Uint16 _MPR_ID_Ki;				//��������������ջ�����ϵ��
Uint16 _MPR_ID_Kd;				//��������������ջ�΢��ϵ��
Uint16 _MPR_ID_outmax;			//��������������ջ�����޷�
Uint16 _MPR_ID_errmax;			//��������������ջ�����޷
Uint16 _MPR_ID_errmin;			//��������������ջ������Сֵ
Uint16 _MPR_ID_incrementmax;		//��������������ջ������޷�

Uint16 _MPR_IQ_Kp;				//��������������ջ�����ϵ��
Uint16 _MPR_IQ_Ki;				//��������������ջ�����ϵ��
Uint16 _MPR_IQ_Kd;				//��������������ջ�΢��ϵ��
Uint16 _MPR_IQ_outmax;			//��������������ջ�����޷�
Uint16 _MPR_IQ_errmax;			//��������������ջ�����޷�
Uint16 _MPR_IQ_errmin;			//��������������ջ������Сֵ
Uint16 _MPR_IQ_incrementmax;	//��������������ջ������޷�


Uint16	_DYN_U_Kp;	   			//�����������ѹ�ջ�����ϵ��
Uint16	_DYN_U_Ki;	  			//�����������ѹ�ջ�����ϵ��
Uint16	_DYN_U_Kd;	  			//�����������ѹ�ջ�΢��ϵ��
Uint16	_DYN_U_outmax;	 		//�����������ѹ�ջ�����޷�
Uint16	_DYN_U_errmax;	  		//����������繱������޷�
Uint16	_DYN_U_errmin;		 	//�����������ѹ�ջ������Сֵ
Uint16	_DYN_U_incrementmax; 	//����������繱ջ������޷


Uint16 _SC_RTRN;													//����������Դ���
Uint16 _SC_RTRT;													//���ι������Լ��ʱ��(ms)

Uint16 _SC_IACOV1;													//��׼�����İٷ�ֵ)
Uint16 _SC_UDCOV;													//�м�ֱ����ѹ��ѹֵ(V)
Uint16 _SC_UDCOVH;													//�м�ֱ����ѹ��ѹֵ����ѹ���䣩(V)
Uint16 _SC_IDCOV;													//��Ϊdc-chopper��������BJTULVRT201204
//Uint16 _SC_UDCLV;													//�м�ֱ����ѹǷѹֵ(V)
Uint16 _SC_VDCON;													//�ϵ��ѹ
Uint16 _SC_UACOV1;													//��ѹ������ѹ��ѹ����ֵ(V)
Uint16 _SC_UACLV1;													//������ѹȱ�ද��ֵ(V)
Uint16 _SC_IACOV2;													//��׼�����İٷ�ֵ)
Uint16 _SC_PGOV;													//
Uint16 _SC_QGOV;													//
Uint16 _SC_IACOVST;                                                 //���ӵ�����������

Uint16 _SC_Rs;														//���ӵ���(mohm)
Uint16 _SC_Lls;														//����©��(mH)
Uint16 _SC_Rr;														//ת�ӵ���(mohm)
Uint16 _SC_Llr;														//ת��©��(mH)
Uint16 _SC_Lm;														//���ŵ� mH)
Uint16 _SC_POLES;													//������
Uint16 _SC_Usn;														//���Ӷ��ѹ(V)
Uint16 _SC_Uro;                                                		//ת�ӿ�·��ѹ(V)
Uint16 _SC_PLSPRVL;													//������ÿȦ��դ����
Uint16 _SC_MSTDBY;                                               	//�����������
Uint16 _SC_EXISTY1;                                               	//������ŵ��ڱ���1
Uint16 _SC_EXISTY2;                                               	//������ŵ��ڱ���2
Uint16 _SC_EXISTY3;                                               	//������ŵ��ڱ���3
Uint16 _SC_EXISTY4;                                               	//������ŵ��ڱ���4
Uint16 _SC_EXISTY5;                                               	//������ŵ��ڱ���5

Uint16 _BA_ERR4;													//���Ĵι�����Ϣ
Uint16 _BA_ERR3;													//�����ι�����Ϣ
Uint16 _BA_ERR2;													//�ڶ��ι�����Ϣ
Uint16 _BA_ERR1;													//��һ�ι�����Ϣ
Uint16 _BA_ERR5;													//ʾ����������Ϣ
//--------------------------------������Ϣ�� ----------------------------------------------------
Uint16 _BA_EMIDRF;													//���¹���ʱ�� d�����ָ��(A)
Uint16 _BA_ENIQRF;													//���¹���ʱ�� q�����ָ��(A)
Uint16 _BA_EMIQRF;													//��¹��ʱ�� q�����ָ��(A)
Uint16 _BA_ETOQRF;													//���¹���ʱ�� ת��ָ��(NM)
Uint16 _BA_EURF;													//���¹���ʱ�� �м�ֱ����ѹ�� V)
Uint16 _BA_EUDC;													//���¹���ʱ�� �м�ֱ����ѹ(V)
Uint16 _BA_EAGLRF;													//���¹���ʱ�� �޹��Ƕ�ָ��()
Uint16 _BA_EIA1;													//���¹���ʱ�� ����A�������Чֵ(A)
Uint16 _BA_EIB1;													//���¹���ʱ�� ����B�������Чֵ(A)
Uint16 _BA_EIC1;													//���¹���ʱ�� ����C�������Чֵ(A)
Uint16 _BA_EIA2;													//���¹���ʱ�� ����A�������Чֵ(A)
Uint16 _BA_EIB2;													//���¹���ʱ�� �����B�������Чֵ(A)
Uint16 _BA_EIC2;													//���¹���ʱ�� �����C�������Чֵ(A)
Uint16 _BA_EUAB1;													//���¹���ʱ�� ����A���ѹ��Чֵ(V)
Uint16 _BA_EUBC1;													//���¹���ʱ�� ����B���ѹ��Чֵ(V)
Uint16 _BA_EUAB2;													//���¹���ʱ�� �������ѹ��Чֵ(V)
Uint16 _BA_EUBC2;													//���¹���ʱ�� �����A�������Чֵ(V)
Uint16 _BA_EUAB0;													//���¹���ʱ�� ����ǰAB�ߵ�ѹ��Чֵ(V)
Uint16 _BA_EUBC0;													//���¹���ʱ�� ���ǰBC�ߵ�ѹ��Чֵ(V)
Uint16 _BA_EFREQ;													//���¹���ʱ�� ����Ƶ��(hz)
Uint16 _BA_ESPEED;													//���¹���ʱ�� ���ת��(rpm)
Uint16 _BA_ENPRUD;              			//d�����Ϻ���ѹ����20091026atzy
Uint16 _BA_ENPRUQ;          				//q�����Ϻ���ѹ����20091026atzy
Uint16 _BA_ENPRUD2;          				//d�����Ϻ���ѹ���� �˲���20091026atzy
Uint16 _BA_ENPRUQ2;          				//q�����Ϻ���ѹ���� �˲���20091026atzy
Uint16 _BA_ENUDOUT;          				//���d��ѹ�� 0091026atzy
Uint16 _BA_ENUQOUT;          				//����q���ѹ���20091026atzy
Uint16 _BA_ETA1;													//���¹���ʱ�� ���������A�ű��¶�
Uint16 _BA_ETB1;													//���¹���ʱ�� ���������B�ű��¶�
Uint16 _BA_ETC1;													//���¹���ʱ�� ���������C�ű��¶�
Uint16 _BA_ETA2;													//���¹���ʱ�� ����������Aű��¶
Uint16 _BA_ETB2;													//���¹���ʱ�� ����������B�ű���
Uint16 _BA_ETC2;													//��¹���ʱ� ����������C�ű��¶�
Uint16 _BA_EPIONU;													//���¹���ʱ�� �����ѹ�����
Uint16 _BA_EPIONID;													//���¹���ʱ�� ����d����������
Uint16 _BA_EPIONIQ;													//���¹���ʱ�� ����q����������
Uint16 _BA_EMEXI;													//���¹���ʱ�� �����������ۼ���ֵ��ʾ
Uint16 _BA_EPIOMID;													//���¹���ʱ�� ����d���������
Uint16 _BA_EPIOMIQ;													//���¹���ʱ�� ����q����������
Uint16 _BA_ETLAC;													//���¹���ʱ�� �������¶�
Uint16 _BA_ETLDUDT;													//���¹���ʱ�� �������¶�
Uint16 _BA_ETSKIIP;													//���¹���ʱ�� SKIIP��
Uint16 _BA_ESTAIAC;
Uint16 _BA_ESTAIBA;
Uint16 _BA_ETOQFB;
Uint16 _BA_EPSTA;
Uint16 _BA_EPNPR;
Uint16 _BA_EPGRID;

Uint16 _BA_TIME4_0;													//���¹���ʱ��(��)
Uint16 _BA_TIME4_1;													//���¹���ʱ��(
Uint16 _BA_TIME4_2;													//���¹���ʱ��(ʱ)
Uint16 _BA_TIME4_3;													//���¹���ʱ��(��)
Uint16 _BA_TIME4_4;													//���¹��ʱ� ��)
Uint16 _BA_TIME4_5;													//���¹���ʱ��(��)

Uint16 _BA_TIME3_0;													//�����ι���ʱ��(��)
Uint16 _BA_TIME3_1;													//�����ι���ʱ��(��)
Uint16 _BA_TIME3_2;													//�����ι���ʱ��(ʱ)
Uint16 _BA_TIME3_3;													//�����ι���ʱ��(��)
Uint16 _BA_TIME3_4;													//�����ι���ʱ��(��)
Uint16 _BA_TIME3_5;													//�����ι��ʱ� ��)

Uint16 _BA_TIME2_0;													//�ڶ�����ʱ��(��)
Uint16 _BA_TIME2_1;													//�ڶ��ι���ʱ��(��)
Uint16 _BA_TIME2_2;													//�ڶ��ι��ϱ�?ʱ)
Uint16 _BA_TIME2_3;													//�ڶ��ι���ʱ��(��)
Uint16 _BA_TIME2_4;													//�ڶ��ι���ʱ��(��)
Uint16 _BA_TIME2_5;													//�ڶ��ι���ʱ?��)

Uint16 _BA_TIME1_0;													//��һ�ι���ʱ��(��)
Uint16 _BA_TIME1_1;													//��һ�ι���ʱ��(��)
Uint16 _BA_TIME1_2;													//��һ�ι���ʱ��(ʱ)
Uint16 _BA_TIME1_3;													//��һ�ι���ʱ��(��)
Uint16 _BA_TIME1_4;													//��һ�ι���ʱ��(��)
Uint16 _BA_TIME1_5;													//��һ�ι���ʱ��(��)

Uint16 _BA_TIME5_0;													//ʾ��������ʱ��(��)
Uint16 _BA_TIME5_1;													//ʾ��������ʱ��(��)
Uint16 _BA_TIME5_2;													//ʾ��������ʱ��(ʱ)
Uint16 _BA_TIME5_3;													//ʾ��������ʱ��(��)
Uint16 _BA_TIME5_4;													//ʾ��������ʱ��(��)
Uint16 _BA_TIME5_5;													//ʾ��������ʱ��(��)

//-------------------------------------���м�ر���-----------------------------------------------
Uint16 _BA_MIDRF;													//d�����ָ��(A)
Uint16 _BA_NIQRF;													//q�����ָ��(A)
Uint16 _BA_MIQRF;													//q�����ָ��(A)
Uint16 _BA_TOQRF;													//ת��ָ��(NM)
Uint16 _BA_AGLRF;													//�޹��Ƕ�ָ��(NM)
Uint16 _BA_TOQFB;													//ת�ط���(NM)
Uint16 _BA_URF;														//�м�ֱ����ѹ����(V)
Uint16 _BA_UDC;														//�м�ֱ����ѹ(V)
Uint16 _BA_IA1;														//���A�������Чֵ(A)
Uint16 _BA_IB1;														//����B������Ч�?A)
Uint16 _BA_IC1;														//����C�������Чֵ(A)
Uint16 _BA_IA2;														//�����A�������Чֵ(A)
Uint16 _BA_IB2;														//�����B������Ч� A)
Uint16 _BA_IC2;														//�����C�������Чֵ(A)
Uint16 _BA_UAB1;													//����AB�ߵ�ѹ��Чֵ(V)
Uint16 _BA_UBC1;													//����BC�ߵ�ѹ�Ч� V)
Uint16 _BA_UAB2;													//�����AB�ߵ�ѹ��Чֵ(V)
Uint16 _BA_UBC2;													//�����BC�ߵ�����Чֵ(V)
Uint16 _BA_UAB0;												    	//����ǰAB�ߵ�ѹ��Чֵ(V)
Uint16 _BA_UBC0;												    	//����ǰBC�ߵ�����Чֵ(V)
Uint16 _BA_FREQ;													//����Ƶ hz)
Uint16 _BA_SPEED;													//���ת��(rpm)
Uint16 _BA_TA1;														//���������A����¶
Uint16 _BA_TB1;														//��������B�ű��¶�
Uint16 _BA_TC1;														//���������C�ű��¶�
Uint16 _BA_TA2;														//����������A�ű��¶�
Uint16 _BA_TB2;														//����������B�ű��¶�
Uint16 _BA_TC2;														//����������C�ű��¶�
Uint16 _BA_PIONU;													//�����ѹ�����
Uint16 _BA_PIONID;													//����d����������
Uint16 _BA_PIONIQ;													//����q����������
Uint16 _BA_MEXI;													//
Uint16 _BA_PIOMID;													//����d����������
Uint16 _BA_PIOMIQ;													//����q����������
Uint16 _BA_GRDUD;													//������������ѹd
Uint16 _BA_GRDUQ;													//������������ѹq

//Uint16 _BA_STAUD;													//���ӵ�ѹd MagnetCurve2013-12-13
Uint16 _BA_MC_IN;													//����У������ MagnetCurve2013-12-13
Uint16 _BA_MC_K;													//����У����� MagnetCurve2013-12-13
//Uint16 _BA_STAUQ;													//���ӵ�ѹq MagnetCurve2013-12-13

Uint16 _BA_NPRID;													//������������ѹd
Uint16 _BA_NPRIQ;													//������������ѹq
//Uint16 _BA_EXCID;													//������������ѹd
//Uint16 _BA_EXCIQ;
Uint16 _BA_SCRIA;													//SCR����a	20110906
Uint16 _BA_SCRIB;													//SCR����b	20110906
Uint16 _BA_TLAC;
Uint16 _BA_TLDUDT;
Uint16 _BA_TNSKIIP;
Uint16 _BA_TMSKIIP;
Uint16 _BA_STAUABD;													//����ͬ������ǰ����ǰ���ѹ��
Uint16 _BA_STAUBCD;													//����ͬ������ǰ����ǰ���ѹ��
Uint16 _BA_STAIAC;													//�����ߵ�����Чֵ��ʾ
Uint16 _BA_STAIBA;													//�����ߵ�����Чֵ��ʾ
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
Uint16 _SCIB_BAUD;													//485������
Uint16 _SC_SKPTOV;
Uint16 _SC_FREQ1;
Uint16 _SC_FREQ2;

//-----------------------�����ñ���-----------------------------------------------------------
int16 	zys[4];			//DA����
Uint16 	daindex[4]; 	//BJTULVRT201204


//int32 	zys = 0;
//int16 	zys1,zys2,zys3,zys4;
Uint32 	i_cnt1=0;  //����CCS������ʾ
Uint32 	i_cnt2=0;  //����CCS������ʾ
Uint32 	i_cnt3=0;  //����CCS������ʾ
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

//----------20121103����ӱ���--------------
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
float   Te_feedback_lv;                    //ʵ��ת��ֵ����
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
