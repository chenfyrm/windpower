//-------------����1.5MW˫�������鲢���������������������----201005atcpc-201007atbjtu--------------------------------
#ifndef DCDC_database_H
#define DCDC_database_H

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------------//�������Զ���
#define	WR0		1						//write only
#define	RDO		2						//read only
#define WR1		4						//write enable when stop
#define	WR2		8						//write enable with password
#define	WR3		16						//write on RAM without eerom
#define	MAX_PT	32						//���ֵΪָ��
#define	MIN_PT	64						//��СֵΪָ��
#define	SIG		128						//�з�����
#define	VA0		256						//��ʾ������ֵ0(�൱�ڽ�ֹ��Ӧ�Ĺ���)
#define	UNS		512						//��ֹ�洢
#define	KEY		1024						//�鿴���޸���Ҫ����������
#define	DOT1	2048					//��������1λС����
#define	DOT2	4096					//��������2λС����
#define	DOT3	8192					//��������3λС����

//--------------------------------------//��ʾ��Ϣ���Զ���
#define	NONE	0						//��
#define	SOFT	1						//��ֹͣ
#define	SHUT	2						//��ͣ
#define	N_RCVR	4						//���ָܻ�
#define	D_RCVR	8						//��ʱ�ָ�
#define	I_RCVR	16						//�����ָ�
#define	CNT		32						//������ϴ���
#define	OT_SER	64						//��ʱ1min�������ع���
#define	SAVE	128						//��Ϣ��Ҫ����
#define	OFFCB	256						//������
#define	WARNING	512						//����

//--------------------------�궨��-----------------------------------------------
				
//-----------------------������غ궨��------------------------------------------
//�����������������(�����������ֻ��Ҫ�������ݿ��ڵ����ݺʹ˴�����Ӧ�������弴��)
#define NUM_GROUP1			29				//���鹦����ĸ�����'��������'��
#define	NUM_GROUP2			42				//�ڶ��鹦����ĸ�����'PI����'��
#define NUM_GROUP3			43				//�����鹦����ĸ�����'������ֵ'��201005atcpc
#define NUM_GROUP4			14				//�����鹦����ĸ�����'����ģʽ')
#define NUM_TIME			6				//ʱ���趨������ĸ���
#define NUM_WATCHLCD		53				//���м�ع�����ĸ���
#define NUM_ERRINF			42				//������Ϣ������ĸ���
#define NUM_ERROR			35				//��ʷ���¹�����Ϣ

//����������������
#define PARA_NUM			NUM_GROUP1+NUM_GROUP2+NUM_GROUP3+NUM_GROUP4+NUM_TIME+NUM_WATCHLCD+NUM_ERRINF+NUM_ERROR

//���ϲ���������
#define ERRO_NUM			NUM_ERROR+NUM_ERRINF

//���ϲ������һ�����������		
#define TAB_ERR_FIRST		NUM_GROUP1+NUM_GROUP2+NUM_GROUP3+NUM_GROUP4+NUM_TIME+NUM_WATCHLCD

//���ϲ����������������		
#define TAB_ERR_END			NUM_GROUP1+NUM_GROUP2+NUM_GROUP3+NUM_GROUP4+NUM_TIME+NUM_WATCHLCD+NUM_ERRINF+NUM_ERROR-1

//��ز������һ�����������(����ʱ�����)
#define BANK_FIRST			NUM_GROUP1+NUM_GROUP2+NUM_GROUP3+NUM_GROUP4+NUM_TIME				

//��ز��������һ�����������
#define BANK_END			NUM_GROUP1+NUM_GROUP2+NUM_GROUP3+NUM_GROUP4+NUM_TIME+NUM_WATCHLCD-1				

//ʱ��������һ�����������
#define TIME_FIRST			NUM_GROUP1+NUM_GROUP2+NUM_GROUP3+NUM_GROUP4				

//ʱ����������һ�����������
#define TIME_END			NUM_GROUP1+NUM_GROUP2+NUM_GROUP3+NUM_GROUP4+NUM_TIME-1	

//����дָ��������һ�����������		
#define TAB_COMSTATE_FIRST		NUM_GROUP1+NUM_GROUP2+NUM_GROUP3

//����дָ������������������		
#define TAB_COMSTATE_END			NUM_GROUP1+NUM_GROUP2+NUM_GROUP3+NUM_GROUP4-1


//���и�����λ��//
#define NO_URF				NUM_GROUP1-16	
#define NO_MIDRF			NUM_GROUP1-15
#define NO_NIQRF			NUM_GROUP1-14
#define NO_MIQRF			NUM_GROUP1-13
#define NO_TOQRF            NUM_GROUP1-12
#define NO_AGLRF			NUM_GROUP1-11



//---------------------------������Ϣ���-systest----------------------------------------------
#define MSG_NUM				45				//������Ϣ����

#define	MSG_NONE			0				//����Ϣ
#define	MSG_CODEOK			1				//EEPROM����
#define	MSG_EE_FAIL			2				//EEPROM����
#define	MSG_ESTOP			3				//��ͣ����
#define	MSG_CBTRIP			4				//�����ѿ۹���
#define	MSG_EXFAULT 		5				//�������ⲿӲ������
#define	MSG_CAN_FAIL		6				//CANͨѶ����
#define	MSG_ENCODFAULT		7				//����������
#define	MSG_CBERROR 		8				//���Ϻ�բ����
#define	MSG_PREERROR 		9				//Ԥ������
#define	MSG_MAINKERROR 		10				//���Ӵ����պϹ���
#define	MSG_MAINFERROR 		11				//���˲����պϹ���
#define	MSG_STACERROR 		12				//���ӽӴ����պϹ���
#define	MSG_HIA1			13				//����,A��Ӳ������
#define	MSG_HIB1			14				//����,B��Ӳ������
#define	MSG_HIC1			15				//����,C��Ӳ������
#define	MSG_HIA2			16				//�����,A��Ӳ������
#define	MSG_HIB2			17  			//�����,B��Ӳ������
#define	MSG_HIC2			18				//�����,C��Ӳ������
#define	MSG_UDCOV           19	            //Ӳ������м�ֱ����ѹ��ѹ
#define	MSG_HIAC1			20				//����Ӳ������
#define	MSG_HIAC2			21				//�����Ӳ������
#define MSG_PDPASERIES      22            	//�������ع���
#define MSG_PDPBSERIES      23            	//��������ع���
#define	MSG_MSPEEDOUT 		24				//ת�ٳ�����Χ����
#define	MSG_SIAC1			25				//�����������
#define	MSG_SIAC2			26				//������������
#define	MSG_FE1				27				//����Ƶ�ʴ���
#define	MSG_SUDCOV			28				//����м�ֱ����ѹ��ѹ
#define	MSG_SUACOV1			29				//�����ѹ������ѹ
#define	MSG_SIDCOV			30				//��Ϊdc-chopper��������BJTULVRT201204
//#define	MSG_SUDCLV			30				//����м�ֱ����ѹǷѹ
#define	MSG_SUACLV1			31				//�����ѹ����Ƿѹ��ʧ��
#define	MSG_UDCWAVE			32				//�м��ѹ��������
#define	MSG_SIOVST	    	33				//���ӵ�����������
#define	MSG_GFAULT1			34				//����ӵع���
#define	MSG_GFAULT2		   	35				//����ӵع���
#define	MSG_TOV1			36				//����SKIIP����
#define	MSG_TOV2			37  			//�����SKIIP����
#define	MSG_SKTOV			38  			//����ж�SKIIP����
#define	MSG_TLOV1			39				//�����г���
#define MSG_TLOV2           40            	//�����г���
#define	MSG_PGOV			41				//�����й�����
#define MSG_QGOV            42            	//�����޹�����
#define	MSG_STASYNFAIL 		43				//����ͬ������ʧ�ܹ���
#define	MSG_PHORDE			44				//�����������

//--------------------------------------//��������ͽṹ��
struct PARA
{
 Uint16 *para_add;						//������ַָ��
 Uint16 init;							//��ʼֵ
 Uint16	min;
 Uint16 max;						//��Сֵ ���ֵ
 Uint16	*min_add;
 Uint16 *max_add;				//��Сֵ ���ֵָ��
 Uint16 attr;							//����
};

struct MESSAGE
{
 Uint16	name[3];						//����
 Uint16 rank;							//��Ϣ����
 Uint16 attr;							//����
};


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


#endif  // end

//===========================================================================
// No more.
//===========================================================================
