#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif

extern const unsigned char auchCRCHi[];
extern const unsigned  char auchCRCLo[];


void EeStart(void);
void EeStop(void);
void EeWrite(unsigned char number);
void EeRead(unsigned char number);
void EeWpre(unsigned char index);
void EeRpre(unsigned char index);
void EeWrword(unsigned char index);
void InitEeprom(void);
Uint16 CheckCode(Uint16 index);
void EeCtrl(void);

void SetRtimer(void);
void RtRead(void);
void InitRtimer(void);

unsigned short GetCrc_16(unsigned int *puchMsg , unsigned int usDataLen);

void Sci485_TxInit(void);
void Sci485_RxInit(void);

void READSTATE(void);
void WRCOMMAND(void);

Uint16 ScibDatpro(void);
void Sci485Ctrl(void);

void Scicanopen_Init(void);
void Sci_canopenrx(void);
void Sci_canopentx_read(void);
void Sci_canopentx(void);

void DataFilter(float c,float *out,float in);
void BS_Loop_S(struct BS_DATA *var,struct BS_PARA BS_var);
void BS_Loop100(struct BS_DATA *var,struct BS_PARA BS_var);

void Ad8364Ctrl(void);
void Da5344Manage(void);

void Output(void);
void Input(void);

void Disepwmio_NPR(void);
void Disepwmio_MPR(void);
void DisPwm(void);
void Enepwmio_NPR(void);
void Enepwmio_MPR(void);
void ConfigPwm(void);
void EnPdpint(void);
void DisPdpint(void);
void ClrPdpint(void);

#ifdef __cplusplus
}
#endif /* extern "C" */


#endif

