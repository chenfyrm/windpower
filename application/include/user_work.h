#ifndef USER_WORK_H
#define USER_WORK_H

#ifdef __cplusplus
extern "C" {
#endif

void InitWork(void);
void PwmDrive(void);
void SVPWM_NPR(float alfa, float beta);
void SVPWM_MPR(float alfa, float beta);
void Transform_3s_2s_2r(struct TRANS_DATA *var1);
void Anti_Transform_2r_2s(struct TRANS_DATA *var2);
void PI_Loop(struct PI_DATA *var,struct PI_PARA PI_var);
void PLLCtrl(void);
void PTransform_3s_2s_2r(struct TRANS_DATA *var2);
void NTransform_3s_2s_2r(struct TRANS_DATA *var3);
void De_ONE_P_2r(struct TRANS_DATA *var4);
void De_ONE_N_2r(struct TRANS_DATA *var5);
void PLL_PI_Loop(struct PI_DATA *var,struct PI_PARA PI_var,struct TRANS_DATA *var1);
void I_Loop(struct PI_DATA *var6);
void Magnet_Curve(struct MC_DATA *var);
float Give_Integral(float give,float step,float out);
void Give(void);
void RunCtrl(void);
void QepEncodPos(void);
void PhaseOrderChk(void);
void CapQepCtrl(void);
void MPR_CONTROL(void);
void NPR_CONTROL(void);

void SysCtrl(void);
void RUN_SYN(void);
void NOR_STOP(void);
void SER_STOP(void);
void ERR_STOP(void);
void CB_ON(void);

#ifdef __cplusplus
}
#endif /* extern "C" */


#endif
