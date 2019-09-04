#ifndef USER_PROTOCOL_H__
#define USER_PROTOCOL_H__

extern volatile bit gbv_TxSDKWeightStatus;
extern volatile bit gbv_TxSDKImpedanceStatus;
extern volatile bit gbv_TxFinishStatus;


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 共用函數 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
extern u8 get_XOR_Checksum(volatile u8 * psurce, u8 length);
extern void fun_TxSDKImpedanceWeightStatus();
extern void fun_UserProtocol();



#endif //USER_PROTOCOL_H__
