/*
 * emu_tc_programming.cpp
 *
 *  Created on: Jan 13, 2017
 *
 *  Created on: Oct 26, 2024
 *      Author: Oscar Rodriguez Polo
 */

/****************************************************************************
 *
 *   This program is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU General Public License
 *   as published by the Free Software Foundation; either version 2
 *   of the License, or (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307,USA.
 *
 *
 ****************************************************************************/



#include <public/emu_hw_timecode_drv_v1.h>
#include <public/emu_sc_channel_drv_v1.h>
#include <public/emu_gss_v1.h>


//#define FT_UAH_PHOTSAT_SERV_129_0010
#define FT_UAH_PHOTSAT_SERV_129_FDIR_0020

//TODO DONE 10 Complete FT_UAH_PHOTSAT_SERV_129_0010

#ifdef FT_UAH_PHOTSAT_SERV_129_0010

EmuGSS_TCProgram129_1 prog_FT_0010_step0(OBT_AFTER_POWER_ON+10,"FT_ASW_SERV_129_0010_Step0, Set theta_pitch theta_yaw and "
		"number of images",600,600,8);

EmuGSS_TCProgram128_1 prog_FT_0010_step1(OBT_AFTER_POWER_ON+1000,"FT_ASW_SERV_128_0010_Step1, FInish the execution of "
		"the programme");

#endif

//TODO DONE 11 Complete FT_UAH_PHOTSAT_SERV_129_FDIR_0020

#ifdef FT_UAH_PHOTSAT_SERV_129_FDIR_0020

EmuGSS_TCProgram12_5_Value_UINT8 prog_FT_0020_step0a(OBT_AFTER_POWER_ON+2,"FT_ASW_SERV_12_0020_Step0a, "
		"Define PMONID 0 for monitoring parameter 13 (Pitch W Control)",0,13,1,1,0xFF,0x00,0x4003);

EmuGSS_TCProgram12_5_Value_UINT8 prog_FT_0020_step0b(OBT_AFTER_POWER_ON+2,"FT_ASW_SERV_12_0020_Step0b, "
		"Define PMONID 1 for monitoring parameter 14 (Yaw W Control)",1,14,1,1,0xFF,0x00,0x4003);

EmuGSS_TCProgram12_1 prog_FT_0020_step1a(OBT_AFTER_POWER_ON+3,"FT_ASW_SERV_12_0020_Step1a, Enable PMONID 0",0);

EmuGSS_TCProgram12_1 prog_FT_0020_step1b(OBT_AFTER_POWER_ON+3,"FT_ASW_SERV_12_0020_Step1b, Enable PMONID 1",1);

EmuGSS_TCProgram19_1_Action_129_3 prog_FT_0020_step2(OBT_AFTER_POWER_ON+4,"FT_ASW_SERV_19_0020_Step2, "
		"Link action of TM(129,3) to event 0x4003",0x4003);

EmuGSS_TCProgram19_4 prog_FT_0020_step3(OBT_AFTER_POWER_ON+5,"FT_ASW_SERV_19_0020_Step3, Activate event 0x4003",0x4003);

EmuGSS_TCProgram129_2 prog_FT_0020_step4(OBT_AFTER_POWER_ON+6,"FT_ASW_SERV_129_0020_Step4, "
		"Change values of Kp, Kd and Ki",0.5,0.5,0.5);

EmuGSS_TCProgram129_1 prog_FT_0020_step5(OBT_AFTER_POWER_ON+8,"FT_ASW_SERV_129_0020_Step5, Set theta_pitch theta_yaw and "
		"number of images",1200,1200,8);

EmuGSS_TCProgram128_1 prog_FT_0020_step6(OBT_AFTER_POWER_ON+15,"FT_ASW_SERV_128_0020_Step6, FInish the execution of "
		"the programme");

#endif
