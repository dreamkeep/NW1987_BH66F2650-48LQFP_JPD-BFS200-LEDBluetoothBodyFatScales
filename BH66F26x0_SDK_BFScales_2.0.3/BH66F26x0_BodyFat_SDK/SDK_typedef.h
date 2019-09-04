//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ====================================================================================@
//                              ���ļ������޸�!!!                                       @
// ====================================================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#ifndef _SDK_TYPEDEF_H_
#define _SDK_TYPEDEF_H_
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
typedef enum
{
    // �P�]SDK
    ENTER_SDK_NONE, // 0 SDK ��ѭ�h,ADC���迹�·����ԭ���B
    STATE_SDK_NONE, // 1 SDK ̎춿�ѭ�h,ADC���迹�·����ԭ���B
    // ��ͨ�Q��
    ENTER_WEIGHT_NORMAL,   // 2 �M�������Q��ģʽ
    STATE_WEIGHT_PREPARE,  // 3 �Q�؜ʂ���
    STATE_WEIGHT_NOLOAD,   // 4 ���d/��ǰ����С���С�Q������
    STATE_WEIGHT_LOADUP,   // 5 ���ϷQ����/�i����B�¼��d���i����,������0�c׃��>��С�Q������
    STATE_WEIGHT_LOADOK,   // 6���һ�ηQ�؜y��
    STATE_WEIGHT_LOADFIX,  // 7 ���һ�ηQ�؜y�������������]�н��i
    STATE_WEIGHT_LOADDOWN, // 8 �³ӄ���
    STATE_WEIGHT_OVERLOAD, // 9 ����,��ǰ����������Q������
    // �Ԅ��ϷQ
    ENTER_WEIGHT_AUTOON,   // 10 �M���Ԅ��ϷQģʽ
    STATE_AUTOON_FASTMODE, // 11 ����ADC�Ԅ��ϷQ�Д�
    STATE_AUTOON_SLOWMODE, // 12 ����ADC�Ԅ��ϷQ�Д�
    STATE_AUTOON_PASS,     // 13 �Ԅ��ϷQOK, �˕r�����c���@ʾ,���ГQ����ͨ�Q��ģʽ�M��MCU����������
    STATE_AUTOON_FAIL,     // 14 �Ԅ��ϳ�ʧ��,�˕rՈ�^�m׌ MCU �M��HALT��B
    // ����У�ʘ˶�
    ENTER_WEIGHT_CAL,      // 15 �M������У��ģʽ
    STATE_WEIGHT_CAL0,     // 16 ���ژ˶����c
    STATE_WEIGHT_CAL1,     // 17 ���ژ˶���1�c
    STATE_WEIGHT_CAL2,     // 18 ���ژ˶���2�c
    STATE_WEIGHT_CAL3,     // 19 ���ژ˶���3�c
    STATE_WEIGHT_CALCHECK, // 20 �˶��Д�
    STATE_WEIGHT_CALPASS,  // 21 �˶��ɹ�
    STATE_WEIGHT_CALFAIL,  // 22 �˶�ʧ��
    // �迹���y
    ENTER_IMPEDANCE,            // 23 �M���迹�y��ģʽ
    STATE_IMPEDANCE_REFERENCE1, // 24 �������y�������1
    STATE_IMPEDANCE_REFERENCE2, // 25 �������y�������2
    STATE_IMPEDANCE_CHECKBODY,  // 26 �Д��Ƿ������w
    STATE_IMPEDANCE_RX,         // 27 �������y���y�迹
    STATE_IMPEDANCE_FINISH,     // 28 �迹���y�Y��,�˕r�����xȡgu16v_CurrentImpedance_ohm
    // �ض����y,��lib���ְ��� Temp��Ч
    ENTER_TEMP,     // 29 �¶Ȝy��
    STATE_TEMP_CAL, // 30 �¶�У��
    // ���ʜy��,��lib���ְ��� Heat��Ч
    ENTER_HEATRATE,         // 31 �M�����ʜy��
    STATE_HEATRATE_PREPARE, // 32 ���ʜy���ʂ���
    STATE_HEATRATE_UPDATE   // 33 ���ʜy��OK,�˕r�����xȡ����
} BHSDKState_t;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ======================================================@
//              SDK�ӿ�  ADC��ӽӿ�                      @
// ======================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
typedef struct
{
	unsigned char ByteHigh;		// R ADC ԭʼ������λ
	unsigned char ByteMid;		// R ADC ԭʼ������λ
	unsigned char ByteLow;		// R ADC ԭʼ������λ
	unsigned char SamplingCnt;	// R ADC �񼯴Δ�Ӌ��
	union {
		struct
		{
			unsigned char IsReady : 1;  // R ��һ�PԭʼADC����
		} b;
		unsigned char byte;
	} flag;
} ADCSource_t;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ======================================================@
//              SDK�ӿ�  ADC�V���ӿ�                      @
// ======================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
typedef struct
{
	unsigned long Current;			// R ��ǰ�V��ADC����
	unsigned long BufMax;			// R �V�� buf ������ADCֵ,�����0x00000000,�f������ֵ���^�O�ÞV������
	unsigned long BufMin;			// R �V�� buf ����С��ADCֵ,�����0xFFFFFFFF,�f������ֵ���^�O�ÞV������
	unsigned int StableThreshold;   // RW Ŀ�˷����yֵ,�Ñ���SDK_UserSetting.h�O��ֵ
	unsigned char StableCntTag;		// RW Ŀ�˷��ȴΔ�,�Ñ���SDK_UserSetting.h�O��ֵ
	unsigned char StableCntCurrent; // R ��ǰ���ȴΔ�
	union {
		struct
		{
			unsigned char IsReady : 1;  // R ��һ�P�V��ADC����
			unsigned char IsStable : 1; // R �V��ADC����̎춷�����B
		} b;
		unsigned char byte;
	} flag;
} ADCFilter_t;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ======================================================@
//              SDK�ӿ�  Weight�ӿ�                       @
// ======================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
typedef struct
{
    struct
    {
        unsigned long Cal0;	    // R    ADCֵ - ���c����
        unsigned long Cal1;	    // R    ADCֵ - ��1���˶�����
        unsigned long Cal2;	    // R    ADCֵ - ��2���˶�����
        unsigned long Cal3;	    // R    ADCֵ - ��3���˶�����
    }CalADCData;// У�ʔ���
    struct
    {
        unsigned long Cal0;	    // R    ADCֵ - ���c����
        unsigned long Cal1;	    // R    ADCֵ - ��1���˶�����
        unsigned long Cal2;	    // R    ADCֵ - ��2���˶�����
        unsigned long Cal3;	    // R    ADCֵ - ��3���˶�����
    }CalADCDataTemp; // У���Д���,for debug
    unsigned char Span;	        // R    ADCֵ - 1���ֱ���
	union {
		struct
		{
			unsigned char IsNeedTare : 1;  // RW ȥƤ,��ǰ�����鷀�������r��ǰ������0
		} b;
		unsigned char byte;
	} flag;
    unsigned int  DataCurrent;  // R    ��ǰ����ֵ,��λ��jin,�Ŵ�10��, ��500,��ʾ������50.0��
    unsigned int  DataStable;   // R    ��������ֵ,��λ��jin,�Ŵ�10��, ��500,��ʾ������50.0��
}Weight_t;

typedef struct
{
    unsigned long WeightMax;          // RW ���y������
    unsigned int WeightMin;           // RW ��С�y������
    unsigned int WeightAutoOn;        // RW �Զ���������
    unsigned int WeightUnLockTemp;    // RW �Ԅӽ��i����-�R�r
    unsigned char WeightUnLockStable; // RW �Ԅӽ��i����-����
    union {
        struct
        {
            unsigned char IsAutoCalOn : 1;    // �Ԅ�У�ʿ���
            unsigned char IsAutoUnlockOn : 1; // �Ԅӽ��i����
        } b;
        unsigned char byte;
    } flag;
} BodyScalesSetting_t;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ======================================================@
//              SDK�ӿ�  �w�迹�ӿ�                       @
// ======================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
typedef enum {
    IMPEDANCE_CHANNEL_TWOLEGS,  	// ���y�p�_�迹
    IMPEDANCE_CHANNEL_TWOARMS,      // ���y�p���迹
    IMPEDANCE_CHANNEL_LEFTARM,      // ���y�����迹
    IMPEDANCE_CHANNEL_RIGHTARM,     // ���y�����迹
    IMPEDANCE_CHANNEL_LEFTLEG,      // ���y���_�迹
    IMPEDANCE_CHANNEL_RIGHTLEG,     // ���y���_�迹
    IMPEDANCE_CHANNEL_LEFTBODY,     // ���y��ȫ���迹
    IMPEDANCE_CHANNEL_RIGHTBODY,    // ���y��ȫ���迹
    IMPEDANCE_CHANNEL_RIGHTRAMANDLEFTLEG, // ���y�������_
    IMPEDANCE_CHANNEL_LEFTRAMANDRIGHTLEG, // ���y�������_
    IMPEDANCE_CHANNEL_TRUNK,        // ���y�|��
}impedance_channel_t;

typedef struct
{
    struct
    {
        unsigned long Cal0;	    // R    ADCֵ - �������1
        unsigned long Cal1;	    // R    ADCֵ - �������2
        unsigned long CalRx0;	// R    ADCֵ - �������1�KRx
        unsigned long CalRx;	// R    ADCֵ - ���y���Rx
    }CalADC;
    union {
        struct
        {
            unsigned char IsUseTwoArms : 1; // RW 0���㲿�迹�Ƿ���ڙz�y���w  1 ���p���迹�z�y�Ƿ�����
        } b;
        unsigned char byte;
    } flag;
    impedance_channel_t Channel; // RW   �迹 - ���yͨ�� �O��,����impedance_channelö�e
    unsigned int Data;           // R    �迹 - �迹ֵ,��λohm. ����(0xffff-�o���y�迹�e�`)/(0xFFF1-���|�����e�`)/(0xFFF2-�迹��������)
} Impedance_t;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ======================================================@
//              SDK�ӿ�    ���ʽӿ�                       @
// ======================================================@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
typedef struct
{
    unsigned char Flag[6]; // R ���ʱ����־λ �����������Ϊ10  buff0 ����ʱ�����Ϊ10 �Ľ�� ��buff1 ����ʱ�����Ϊ9 �Ľ������
    unsigned char Data[6]; // R ����ֵ
    union {
        struct
        {
            unsigned char IsUseTwoArms : 1; // RW 0ʹ���p�_�y������,1ʹ���p�֜y������
        } b;
        unsigned char byte;
    } flag;
} HeartRate_t;

#endif
