//*******************************************************************************************
//																							*
//                    ProductName:	BH66F2650-48LQFP_JPD-BFS200-LED��������֬����_NW1986   	    *
//                    MCU Body:		BH66F2650-48LQFP 			               	       		*
//                    HT-IDE3000: 	V8.01	                                           		*
//                    Date:         2019/08/20                                    	   		*
//                    Author:       ghg                                      				*
//                    Company:		New Wave Eelectronics (ShenZhen) LTD.					*
//																							*
//*******************************************************************************************
//																							*
//              	 	Files Required: Omitted												*
//																							*
//*******************************************************************************************
//   Configuration Option Setting:                                                     		*
//*******************************************************************************************
//																							*
//   		 		Notes: 	1.Fsys = 4MHz(Extern) @3.3V									    *
//						   	2.WDT ENABLE (1S)												*
//																							*
//																							*
//*******************************************************************************************
//
//	Revision History:
//			1.Initial on 2019.08.20

#include "common.h"


int main(void)
{
    /* 1.Power on reset or abnormal reset. */
    /* 2.WDT overflow reset. */
	if (_to == 0 || _pdf ==0)
	{
        /* 1.Power on reset or abnormal reset. */
		poweron_system_init();
		// ��늺��{��fun_BodyFatScalesSDK_PowerOn()����
		fun_BodyFatScalesSDK_PowerOn();
		user_initial();
	}
	else
	{
		/* 2.WDT overflow reset.*/
		GCC_CLRWDT();
		/* ˯�߻��Ѻ����TASK_SCALESģʽ����ϳ�״̬ */
		gu8_worktasks = TASK_SCALES;
	}
	//��ѭ�h
	while(1)
	{
		GCC_CLRWDT();
		// ��LOOPѭ�h�{�� fun_BodyFatScalesSDK()
		fun_BodyFatScalesSDK();

		switch(gu8_worktasks)
		{
			case TASK_STARTUP:
				task_scalesstartup();
				break;

			case TASK_LOWBATTERY:
				task_scaleslowbattry();
				break;

			case TASK_SCALES:
				task_bodyfatscales();
				fun_UserProtocol();
    			key_scan();
				break;

			case TASK_SLEEP:
				task_scales2sleep();
				break;

			case TASK_WEIGHT_AUTOON:
				task_scaleswakeup();
				break;

			default:
				gu8_worktasks = TASK_SCALES;
				break;
		}

		/* LED display mode and set display content */
		fun_diaplay_mode();

		/* Is it time to shut down ? */
		is_timedshutdown();


		/* For Debug */

	}

	return 0;
}
