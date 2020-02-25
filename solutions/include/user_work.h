#ifndef USER_WORK_H
#define USER_WORK_H

#ifdef __cplusplus
extern "C" {
#endif

extern void InitWork(void);
extern void PwmDrive(void);
extern void SVPWM_NPR(float alfa, float beta);
extern void SVPWM_MPR(float alfa, float beta);
extern void Transform_3s_2s_2r(struct TRANS_DATA *var1);
extern void Anti_Transform_2r_2s(struct TRANS_DATA *var2);
extern void PI_Loop(struct PI_DATA *var,struct PI_PARA PI_var);
extern void PLLCtrl(void);
extern void PTransform_3s_2s_2r(struct TRANS_DATA *var2);
extern void NTransform_3s_2s_2r(struct TRANS_DATA *var3);
extern void De_ONE_P_2r(struct TRANS_DATA *var4);
extern void De_ONE_N_2r(struct TRANS_DATA *var5);
extern void PLL_PI_Loop(struct PI_DATA *var,struct PI_PARA PI_var,struct TRANS_DATA *var1);
extern void I_Loop(struct PI_DATA *var6);
extern void Magnet_Curve(struct MC_DATA *var);
extern float Give_Integral(float give,float step,float out);
extern void Give(void);
extern void RunCtrl(void);
extern void QepEncodPos(void);
extern void PhaseOrderChk(void);
extern void CapQepCtrl(void);
extern void MPR_CONTROL(void);
extern void NPR_CONTROL(void);

extern void SysCtrl(void);
extern void RUN_SYN(void);
extern void NOR_STOP(void);
extern void SER_STOP(void);
extern void ERR_STOP(void);
extern void CB_ON(void);

#ifdef __cplusplus
}
#endif /* extern "C" */


#endif
