/* Module Name : NVIC
 * File Name   : NVIC_program.c
 * Author      : Bishoy Nabil
 * Version     : 2.0
 * Date        : before 13/4/2020 */

#include "STDTYPES.h"

#include "NVIC_interface.h"

#define NVIC                     ((volatile NVICReg_t * const)0xE000E000)
#define NVIC_AIRCR               (*((volatile u32 * const)0xE000ED0C))    /* Application Interrupt and Control Register */

#define GROUPBITS_CLEAR_MASK     0xFFFFF8FF

typedef struct
{
	u32 DummyArray0[64];//000-0FC
	u32 SETENA0;        //100
	u32 SETENA1;        //104
	u32 SETENA2;        //108
	u32 SETENA3;        //10C
	u32 SETENA4;        //110
	u32 SETENA5;        //114
	u32 SETENA6;        //118
	u32 SETENA7;        //11C
	u32 DummyArray1[24];//120-17C
	u32 CLRENA0;        //180
	u32 CLRENA1;        //184
	u32 CLRENA2;        //188
	u32 CLRENA3;        //18C
	u32 CLRENA4;        //190
	u32 CLRENA5;        //194
	u32 CLRENA6;        //198
	u32 CLRENA7;        //19C
	u32 DummyArray2[24];//1A0-1FC
	u32 SETPEND0;       //200
	u32 SETPEND1;       //204
	u32 SETPEND2;       //208
	u32 SETPEND3;       //20C
	u32 SETPEND4;       //210
	u32 SETPEND5;       //214
	u32 SETPEND6;       //218
	u32 SETPEND7;       //21C
	u32 DummyArray3[24];//220-27C
	u32 CLRPEND0;       //280
	u32 CLRPEND1;       //284
	u32 CLRPEND2;       //288
	u32 CLRPEND3;       //28C
	u32 CLRPEND4;       //290
	u32 CLRPEND5;       //294
	u32 CLRPEND6;       //298
	u32 CLRPEND7;       //29C
	u32 DummyArray4[24];//2A0-2FC
	u32 ACTIVE0;        //300
	u32 ACTIVE1;        //304
	u32 ACTIVE2;        //308
	u32 ACTIVE3;        //30C
	u32 ACTIVE4;        //310
	u32 ACTIVE5;        //314
	u32 ACTIVE6;        //318
	u32 ACTIVE7;        //31C
	u32 DummyArray5[56];//320-3FC
	u8  PRI_0;          //400
	u8  PRI_1;          //401
	u8  PRI_2;          //402
	u8  PRI_3;          //403
	u8  PRI_4;          //404
	u8  PRI_5;          //405
	u8  PRI_6;          //406
	u8  PRI_7;          //407
	u8  PRI_8;          //408
	u8  PRI_9;          //409
	u8  PRI_10;         //40A
	u8  PRI_11;         //40B
	u8  PRI_12;         //40C
	u8  PRI_13;         //40D
	u8  PRI_14;         //40E
	u8  PRI_15;         //40F
	u8  PRI_16;         //410
	u8  PRI_17;         //411
	u8  PRI_18;         //412
	u8  PRI_19;         //413
	u8  PRI_20;         //414
	u8  PRI_21;         //415
	u8  PRI_22;         //416
	u8  PRI_23;         //417
	u8  PRI_24;         //418
	u8  PRI_25;         //419
	u8  PRI_26;         //41A
	u8  PRI_27;         //41B
	u8  PRI_28;         //41C
	u8  PRI_29;         //41D
	u8  PRI_30;         //41E
	u8  PRI_31;         //41F
	u8  PRI_32;         //420
	u8  PRI_33;         //421
	u8  PRI_34;         //422
	u8  PRI_35;         //423
	u8  PRI_36;         //424
	u8  PRI_37;         //425
	u8  PRI_38;         //426
	u8  PRI_39;         //427
	u8  PRI_40;         //428
	u8  PRI_41;         //429
	u8  PRI_42;         //42A
	u8  PRI_43;         //42B
	u8  PRI_44;         //42C
	u8  PRI_45;         //42D
	u8  PRI_46;         //42E
	u8  PRI_47;         //42F
	u8  PRI_48;         //430
	u8  PRI_49;         //431
	u8  PRI_50;         //432
	u8  PRI_51;         //433
	u8  PRI_52;         //434
	u8  PRI_53;         //435
	u8  PRI_54;         //436
	u8  PRI_55;         //437
	u8  PRI_56;         //438
	u8  PRI_57;         //439
	u8  PRI_58;         //43A
	u8  PRI_59;         //43B
	u8  PRI_60;         //43C
	u8  PRI_61;         //43D
	u8  PRI_62;         //43E
	u8  PRI_63;         //43F
	u8  PRI_64;         //440
	u8  PRI_65;         //441
	u8  PRI_66;         //442
	u8  PRI_67;         //443
	u8  PRI_68;         //444
	u8  PRI_69;         //445
	u8  PRI_70;         //446
	u8  PRI_71;         //447
	u8  PRI_72;         //448
	u8  PRI_73;         //449
	u8  PRI_74;         //44A
	u8  PRI_75;         //44B
	u8  PRI_76;         //44C
	u8  PRI_77;         //44D
	u8  PRI_78;         //44E
	u8  PRI_79;         //44F
	u8  PRI_80;         //450
	u8  PRI_81;         //451
	u8  PRI_82;         //452
	u8  PRI_83;         //453
	u8  PRI_84;         //454
	u8  PRI_85;         //455
	u8  PRI_86;         //456
	u8  PRI_87;         //457
	u8  PRI_88;         //458
	u8  PRI_89;         //459
	u8  PRI_90;         //45A
	u8  PRI_91;         //45B
	u8  PRI_92;         //45C
	u8  PRI_93;         //45D
	u8  PRI_94;         //45E
	u8  PRI_95;         //45F
	u8  PRI_96;         //460
	u8  PRI_97;         //461
	u8  PRI_98;         //462
	u8  PRI_99;         //463
	u8  PRI_100;        //464
	u8  PRI_101;        //465
	u8  PRI_102;        //466
	u8  PRI_103;        //467
	u8  PRI_104;        //468
	u8  PRI_105;        //469
	u8  PRI_106;        //46A
	u8  PRI_107;        //46B
	u8  PRI_108;        //46C
	u8  PRI_109;        //46D
	u8  PRI_110;        //46E
	u8  PRI_111;        //46F
	u8  PRI_112;        //470
	u8  PRI_113;        //471
	u8  PRI_114;        //472
	u8  PRI_115;        //473
	u8  PRI_116;        //474
	u8  PRI_117;        //475
	u8  PRI_118;        //476
	u8  PRI_119;        //477
	u8  PRI_120;        //478
	u8  PRI_121;        //479
	u8  PRI_122;        //47A
	u8  PRI_123;        //47B
	u8  PRI_124;        //47C
	u8  PRI_125;        //47D
	u8  PRI_126;        //47E
	u8  PRI_127;        //47F
	u8  PRI_128;        //480
	u8  PRI_129;        //481
	u8  PRI_130;        //482
	u8  PRI_131;        //483
	u8  PRI_132;        //484
	u8  PRI_133;        //485
	u8  PRI_134;        //486
	u8  PRI_135;        //487
	u8  PRI_136;        //488
	u8  PRI_137;        //489
	u8  PRI_138;        //48A
	u8  PRI_139;        //48B
	u8  PRI_140;        //48C
	u8  PRI_141;        //48D
	u8  PRI_142;        //48E
	u8  PRI_143;        //48F
	u8  PRI_144;        //490
	u8  PRI_145;        //491
	u8  PRI_146;        //492
	u8  PRI_147;        //493
	u8  PRI_148;        //494
	u8  PRI_149;        //495
	u8  PRI_150;        //496
	u8  PRI_151;        //497
	u8  PRI_152;        //498
	u8  PRI_153;        //499
	u8  PRI_154;        //49A
	u8  PRI_155;        //49B
	u8  PRI_156;        //49C
	u8  PRI_157;        //49D
	u8  PRI_158;        //49E
	u8  PRI_159;        //49F
	u8  PRI_160;        //4A0
	u8  PRI_161;        //4A1
	u8  PRI_162;        //4A2
	u8  PRI_163;        //4A3
	u8  PRI_164;        //4A4
	u8  PRI_165;        //4A5
	u8  PRI_166;        //4A6
	u8  PRI_167;        //4A7
	u8  PRI_168;        //4A8
	u8  PRI_169;        //4A9
	u8  PRI_170;        //4AA
	u8  PRI_171;        //4AB
	u8  PRI_172;        //4AC
	u8  PRI_173;        //4AD
	u8  PRI_174;        //4AE
	u8  PRI_175;        //4AF
	u8  PRI_176;        //4B0
	u8  PRI_177;        //4B1
	u8  PRI_178;        //4B2
	u8  PRI_179;        //4B3
	u8  PRI_180;        //4B4
	u8  PRI_181;        //4B5
	u8  PRI_182;        //4B6
	u8  PRI_183;        //4B7
	u8  PRI_184;        //4B8
	u8  PRI_185;        //4B9
	u8  PRI_186;        //4BA
	u8  PRI_187;        //4BB
	u8  PRI_188;        //4BC
	u8  PRI_189;        //4BD
	u8  PRI_190;        //4BE
	u8  PRI_191;        //4BF
	u8  PRI_192;        //4C0
	u8  PRI_193;        //4C1
	u8  PRI_194;        //4C2
	u8  PRI_195;        //4C3
	u8  PRI_196;        //4C4
	u8  PRI_197;        //4C5
	u8  PRI_198;        //4C6
	u8  PRI_199;        //4C7
	u8  PRI_200;        //4C8
	u8  PRI_201;        //4C9
	u8  PRI_202;        //4CA
	u8  PRI_203;        //4CB
	u8  PRI_204;        //4CC
	u8  PRI_205;        //4CD
	u8  PRI_206;        //4CE
	u8  PRI_207;        //4CF
	u8  PRI_208;        //4D0
	u8  PRI_209;        //4D1
	u8  PRI_210;        //4D2
	u8  PRI_211;        //4D3
	u8  PRI_212;        //4D4
	u8  PRI_213;        //4D5
	u8  PRI_214;        //4D6
	u8  PRI_215;        //4D7
	u8  PRI_216;        //4D8
	u8  PRI_217;        //4D9
	u8  PRI_218;        //4DA
	u8  PRI_219;        //4DB
	u8  PRI_220;        //4DC
	u8  PRI_221;        //4DD
	u8  PRI_222;        //4DE
	u8  PRI_223;        //4DF
	u8  PRI_224;        //4E0
	u8  PRI_225;        //4E1
	u8  PRI_226;        //4E2
	u8  PRI_227;        //4E3
	u8  PRI_228;        //4E4
	u8  PRI_229;        //4E5
	u8  PRI_230;        //4E6
	u8  PRI_231;        //4E7
	u8  PRI_232;        //4E8
	u8  PRI_233;        //4E9
	u8  PRI_234;        //4EA
	u8  PRI_235;        //4EB
	u8  PRI_236;        //4EC
	u8  PRI_237;        //4ED
	u8  PRI_238;        //4EE
	u8  PRI_239;        //4EF
}NVICReg_t;

ErrorStatus NVIC_ControlEnableInterrupt   (NVIC_t *Copy_NVICStruct)
{
	u8 Local_u8ErrorStatus = OK;
	volatile u32 Local_u32Register;
	u8 Local_u8ID;
	if(Copy_NVICStruct->ID < 32)
	{
		if(Copy_NVICStruct->EnableBit)//enable
		{
			Local_u32Register = NVIC->CLRPEND0;
			Local_u32Register |= (1<<Copy_NVICStruct->ID);
			NVIC->CLRPEND0 = Local_u32Register;
			Local_u32Register = NVIC->SETENA0;
			Local_u32Register |= (1<<Copy_NVICStruct->ID);
			NVIC->SETENA0 = Local_u32Register;
		}
		else if(!Copy_NVICStruct->EnableBit)//disable
		{
			Local_u32Register = NVIC->CLRENA0;
			Local_u32Register |= (1<<Copy_NVICStruct->ID);
			NVIC->CLRENA0 = Local_u32Register;
		}
		else
		{
			Local_u8ErrorStatus = NOK;
		}
	}
	else if(Copy_NVICStruct->ID < 64)
	{
		Local_u8ID = Copy_NVICStruct->ID - 32;
		if(Copy_NVICStruct->EnableBit)//enable
		{
			Local_u32Register = NVIC->CLRPEND1;
			Local_u32Register |= (1<<Local_u8ID);
			NVIC->CLRPEND1 = Local_u32Register;
			Local_u32Register = NVIC->CLRPEND1;
			Local_u32Register = NVIC->SETENA1;
			Local_u32Register |= (1<<Local_u8ID);
			NVIC->SETENA1 = Local_u32Register;
		}
		else if(!Copy_NVICStruct->EnableBit)//disable
		{
			Local_u32Register = NVIC->CLRENA1;
			Local_u32Register |= (1<<Local_u8ID);
			NVIC->CLRENA1 = Local_u32Register;
		}
		else
		{
			Local_u8ErrorStatus = NOK;
		}
	}
	else if(Copy_NVICStruct->ID < 96)
	{
		Local_u8ID = Copy_NVICStruct->ID - 64;
		if(Copy_NVICStruct->EnableBit)//enable
		{
			Local_u32Register = NVIC->CLRPEND2;
			Local_u32Register |= (1<<Local_u8ID);
			NVIC->CLRPEND2 = Local_u32Register;
			Local_u32Register = NVIC->SETENA2;
			Local_u32Register |= (1<<Local_u8ID);
			NVIC->SETENA2 = Local_u32Register;
		}
		else if(!Copy_NVICStruct->EnableBit)//disable
		{
			Local_u32Register = NVIC->CLRENA2;
			Local_u32Register |= (1<<Local_u8ID);
			NVIC->CLRENA2 = Local_u32Register;
		}
		else
		{
			Local_u8ErrorStatus = NOK;
		}
	}
	else if(Copy_NVICStruct->ID < 128)
	{
		Local_u8ID = Copy_NVICStruct->ID - 96;
		if(Copy_NVICStruct->EnableBit)//enable
		{
			Local_u32Register = NVIC->CLRPEND3;
			Local_u32Register |= (1<<Local_u8ID);
			NVIC->CLRPEND3 = Local_u32Register;
			Local_u32Register = NVIC->SETENA3;
			Local_u32Register |= (1<<Local_u8ID);
			NVIC->SETENA3 = Local_u32Register;
		}
		else if(!Copy_NVICStruct->EnableBit)//disable
		{
			Local_u32Register = NVIC->CLRENA3;
			Local_u32Register |= (1<<Local_u8ID);
			NVIC->CLRENA3 = Local_u32Register;
		}
		else
		{
			Local_u8ErrorStatus = NOK;
		}
	}
	else if(Copy_NVICStruct->ID < 160)
	{
		Local_u8ID = Copy_NVICStruct->ID - 128;
		if(Copy_NVICStruct->EnableBit)//enable
		{
			Local_u32Register = NVIC->CLRPEND4;
			Local_u32Register |= (1<<Local_u8ID);
			NVIC->CLRPEND4 = Local_u32Register;
			Local_u32Register = NVIC->SETENA4;
			Local_u32Register |= (1<<Local_u8ID);
			NVIC->SETENA4 = Local_u32Register;
		}
		else if(!Copy_NVICStruct->EnableBit)//disable
		{
			Local_u32Register = NVIC->CLRENA4;
			Local_u32Register |= (1<<Local_u8ID);
			NVIC->CLRENA4 = Local_u32Register;
		}
		else
		{
			Local_u8ErrorStatus = NOK;
		}
	}
	else if(Copy_NVICStruct->ID < 192)
	{
		Local_u8ID = Copy_NVICStruct->ID - 160;
		if(Copy_NVICStruct->EnableBit)//enable
		{
			Local_u32Register = NVIC->CLRPEND5;
			Local_u32Register |= (1<<Local_u8ID);
			NVIC->CLRPEND5 = Local_u32Register;
			Local_u32Register = NVIC->SETENA5;
			Local_u32Register |= (1<<Local_u8ID);
			NVIC->SETENA5 = Local_u32Register;
		}
		else if(!Copy_NVICStruct->EnableBit)//disable
		{
			Local_u32Register = NVIC->CLRENA5;
			Local_u32Register |= (1<<Local_u8ID);
			NVIC->CLRENA5 = Local_u32Register;
		}
		else
		{
			Local_u8ErrorStatus = NOK;
		}
	}
	else if(Copy_NVICStruct->ID < 224)
	{
		Local_u8ID = Copy_NVICStruct->ID - 192;
		if(Copy_NVICStruct->EnableBit)//enable
		{
			Local_u32Register = NVIC->CLRPEND6;
			Local_u32Register |= (1<<Local_u8ID);
			NVIC->CLRPEND6 = Local_u32Register;
			Local_u32Register = NVIC->SETENA6;
			Local_u32Register |= (1<<Local_u8ID);
			NVIC->SETENA6 = Local_u32Register;
		}
		else if(!Copy_NVICStruct->EnableBit)//disable
		{
			Local_u32Register = NVIC->CLRENA6;
			Local_u32Register |= (1<<Local_u8ID);
			NVIC->CLRENA6 = Local_u32Register;
		}
		else
		{
			Local_u8ErrorStatus = NOK;
		}
	}
	else if(Copy_NVICStruct->ID < 239)
	{
		Local_u8ID = Copy_NVICStruct->ID - 224;
		if(Copy_NVICStruct->EnableBit)//enable
		{
			Local_u32Register = NVIC->CLRPEND7;
			Local_u32Register |= (1<<Local_u8ID);
			NVIC->CLRPEND7 = Local_u32Register;
			Local_u32Register = NVIC->SETENA7;
			Local_u32Register |= (1<<Local_u8ID);
			NVIC->SETENA7 = Local_u32Register;
		}
		else if(!Copy_NVICStruct->EnableBit)//disable
		{
			Local_u32Register = NVIC->CLRENA7;
			Local_u32Register |= (1<<Local_u8ID);
			NVIC->CLRENA7 = Local_u32Register;
		}
		else
		{
			Local_u8ErrorStatus = NOK;
		}
	}
	else
	{
		Local_u8ErrorStatus = NOK;
	}
	return Local_u8ErrorStatus;
}
ErrorStatus NVIC_ControlPendingFlag       (NVIC_t *Copy_NVICStruct)
{
	u8 Local_u8ErrorStatus = OK;
	u32 Local_u32Register;
	u8 Local_u8ID;
	if(Copy_NVICStruct->ID < 32)
	{
		if(Copy_NVICStruct->PendingFlag)//enable
		{
			Local_u32Register = NVIC->SETPEND0;
			Local_u32Register |= (1<<Copy_NVICStruct->ID);
			NVIC->SETPEND0 = Local_u32Register;
		}
		else if(!Copy_NVICStruct->PendingFlag)//disable
		{
			Local_u32Register = NVIC->CLRPEND0;
			Local_u32Register |= (1<<Copy_NVICStruct->ID);
			NVIC->CLRPEND0 = Local_u32Register;
		}
		else
		{
			Local_u8ErrorStatus = NOK;
		}
	}
	else if(Copy_NVICStruct->ID < 64)
	{
		Local_u8ID = Copy_NVICStruct->ID - 32;
		if(Copy_NVICStruct->PendingFlag)//enable
		{
			Local_u32Register = NVIC->SETPEND1;
			Local_u32Register |= (1<<Local_u8ID);
			NVIC->SETPEND1 = Local_u32Register;
		}
		else if(!Copy_NVICStruct->PendingFlag)//disable
		{
			Local_u32Register = NVIC->CLRPEND1;
			Local_u32Register |= (1<<Local_u8ID);
			NVIC->CLRPEND1 = Local_u32Register;
		}
		else
		{
			Local_u8ErrorStatus = NOK;
		}
	}
	else if(Copy_NVICStruct->ID < 96)
	{
		Local_u8ID = Copy_NVICStruct->ID - 64;
		if(Copy_NVICStruct->PendingFlag)//enable
		{
			Local_u32Register = NVIC->SETPEND2;
			Local_u32Register |= (1<<Local_u8ID);
			NVIC->SETPEND2 = Local_u32Register;
		}
		else if(!Copy_NVICStruct->PendingFlag)//disable
		{
			Local_u32Register = NVIC->CLRPEND2;
			Local_u32Register |= (1<<Local_u8ID);
			NVIC->CLRPEND2 = Local_u32Register;
		}
		else
		{
			Local_u8ErrorStatus = NOK;
		}
	}
	else if(Copy_NVICStruct->ID < 128)
	{
		Local_u8ID = Copy_NVICStruct->ID - 96;
		if(Copy_NVICStruct->PendingFlag)//enable
		{
			Local_u32Register = NVIC->SETPEND3;
			Local_u32Register |= (1<<Local_u8ID);
			NVIC->SETPEND3 = Local_u32Register;
		}
		else if(!Copy_NVICStruct->PendingFlag)//disable
		{
			Local_u32Register = NVIC->CLRPEND3;
			Local_u32Register |= (1<<Local_u8ID);
			NVIC->CLRPEND3 = Local_u32Register;
		}
		else
		{
			Local_u8ErrorStatus = NOK;
		}
	}
	else if(Copy_NVICStruct->ID < 160)
	{
		Local_u8ID = Copy_NVICStruct->ID - 128;
		if(Copy_NVICStruct->PendingFlag)//enable
		{
			Local_u32Register = NVIC->SETPEND4;
			Local_u32Register |= (1<<Local_u8ID);
			NVIC->SETPEND4 = Local_u32Register;
		}
		else if(!Copy_NVICStruct->PendingFlag)//disable
		{
			Local_u32Register = NVIC->CLRPEND4;
			Local_u32Register |= (1<<Local_u8ID);
			NVIC->CLRPEND4 = Local_u32Register;
		}
		else
		{
			Local_u8ErrorStatus = NOK;
		}
	}
	else if(Copy_NVICStruct->ID < 192)
	{
		Local_u8ID = Copy_NVICStruct->ID - 160;
		if(Copy_NVICStruct->PendingFlag)//enable
		{
			Local_u32Register = NVIC->SETPEND5;
			Local_u32Register |= (1<<Local_u8ID);
			NVIC->SETPEND5 = Local_u32Register;
		}
		else if(!Copy_NVICStruct->PendingFlag)//disable
		{
			Local_u32Register = NVIC->CLRPEND5;
			Local_u32Register |= (1<<Local_u8ID);
			NVIC->CLRPEND5 = Local_u32Register;
		}
		else
		{
			Local_u8ErrorStatus = NOK;
		}
	}
	else if(Copy_NVICStruct->ID < 224)
	{
		Local_u8ID = Copy_NVICStruct->ID - 192;
		if(Copy_NVICStruct->PendingFlag)//enable
		{
			Local_u32Register = NVIC->SETPEND6;
			Local_u32Register |= (1<<Local_u8ID);
			NVIC->SETPEND6 = Local_u32Register;
		}
		else if(!Copy_NVICStruct->PendingFlag)//disable
		{
			Local_u32Register = NVIC->CLRPEND6;
			Local_u32Register |= (1<<Local_u8ID);
			NVIC->CLRPEND6 = Local_u32Register;
		}
		else
		{
			Local_u8ErrorStatus = NOK;
		}
	}
	else if(Copy_NVICStruct->ID < 239)
	{
		Local_u8ID = Copy_NVICStruct->ID - 224;
		if(Copy_NVICStruct->PendingFlag)//enable
		{
			Local_u32Register = NVIC->SETPEND7;
			Local_u32Register |= (1<<Local_u8ID);
			NVIC->SETPEND7 = Local_u32Register;
		}
		else if(!Copy_NVICStruct->PendingFlag)//disable
		{
			Local_u32Register = NVIC->CLRPEND7;
			Local_u32Register |= (1<<Local_u8ID);
			NVIC->CLRPEND7 = Local_u32Register;
		}
		else
		{
			Local_u8ErrorStatus = NOK;
		}
	}
	else
	{
		Local_u8ErrorStatus = NOK;
	}
	return Local_u8ErrorStatus;
}
ErrorStatus NVIC_InterruptActiveStatus    (NVIC_t *Copy_NVICStruct)
{
	u8 Local_u8ErrorStatus = OK;
	u8 Local_u8ID;
	if(Copy_NVICStruct->ID < 32)
	{
		Copy_NVICStruct->ActiveStatus = (NVIC->ACTIVE0 >> Copy_NVICStruct->ID) & 0x00000001;
	}
	else if(Copy_NVICStruct->ID < 64)
	{
		Local_u8ID = Copy_NVICStruct->ID - 32;
		Copy_NVICStruct->ActiveStatus = (NVIC->ACTIVE1 >> Local_u8ID) & 0x00000001;
	}
	else if(Copy_NVICStruct->ID < 96)
	{
		Local_u8ID = Copy_NVICStruct->ID - 64;
		Copy_NVICStruct->ActiveStatus = (NVIC->ACTIVE2 >> Local_u8ID) & 0x00000001;
	}
	else if(Copy_NVICStruct->ID < 128)
	{
		Local_u8ID = Copy_NVICStruct->ID - 96;
		Copy_NVICStruct->ActiveStatus = (NVIC->ACTIVE3 >> Local_u8ID) & 0x00000001;
	}
	else if(Copy_NVICStruct->ID < 160)
	{
		Local_u8ID = Copy_NVICStruct->ID - 128;
		Copy_NVICStruct->ActiveStatus = (NVIC->ACTIVE4 >> Local_u8ID) & 0x00000001;
	}
	else if(Copy_NVICStruct->ID < 192)
	{
		Local_u8ID = Copy_NVICStruct->ID - 160;
		Copy_NVICStruct->ActiveStatus = (NVIC->ACTIVE5 >> Local_u8ID) & 0x00000001;
	}
	else if(Copy_NVICStruct->ID < 224)
	{
		Local_u8ID = Copy_NVICStruct->ID - 192;
		Copy_NVICStruct->ActiveStatus = (NVIC->ACTIVE6 >> Local_u8ID) & 0x00000001;
	}
	else if(Copy_NVICStruct->ID < 239)
	{
		Local_u8ID = Copy_NVICStruct->ID - 224;
		Copy_NVICStruct->ActiveStatus = (NVIC->ACTIVE7 >> Local_u8ID) & 0x00000001;
	}
	else
	{
		Local_u8ErrorStatus = NOK;
	}
	return Local_u8ErrorStatus;
}
ErrorStatus NVIC_SetInterruptPriority     (NVIC_t *Copy_NVICStruct)
{
	u8 Local_u8ErrorStatus = OK;
	*((&(NVIC->PRI_0))+(Copy_NVICStruct->ID)) = Copy_NVICStruct->Priority;
	return Local_u8ErrorStatus;
}
ErrorStatus NVIC_GetInterruptPriority     (NVIC_t *Copy_NVICStruct)
{
	u8 Local_u8ErrorStatus = OK;
	Copy_NVICStruct->Priority = *((&(NVIC->PRI_0))+(Copy_NVICStruct->ID));
	return Local_u8ErrorStatus;
}
ErrorStatus NVIC_SetPriorityGroupBits     (NVIC_t *Copy_NVICStruct)
{
	u8 Local_u8ErrorStatus = OK;
	u32 Local_u32AIRCR = NVIC_AIRCR;
	Local_u32AIRCR &= GROUPBITS_CLEAR_MASK;
	Local_u32AIRCR |= Copy_NVICStruct->PriorityGroupBits;
	NVIC_AIRCR = Local_u32AIRCR;
	return Local_u8ErrorStatus;
}
ErrorStatus NVIC_ControlAllInterrupts     (NVIC_t *Copy_NVICStruct)
{
	u8 Local_u8ErrorStatus = OK;
	return Local_u8ErrorStatus;
}
ErrorStatus NVIC_ControlAllFaults         (NVIC_t *Copy_NVICStruct)
{
	u8 Local_u8ErrorStatus = OK;
	return Local_u8ErrorStatus;
}
ErrorStatus NVIC_SetPriorityFilter        (NVIC_t *Copy_NVICStruct)
{
	u8 Local_u8ErrorStatus = OK;
	return Local_u8ErrorStatus;
}
ErrorStatus NVIC_GenerateSoftwareInterrupt(NVIC_t *Copy_NVICStruct)
{
	u8 Local_u8ErrorStatus = OK;
	return Local_u8ErrorStatus;
}
