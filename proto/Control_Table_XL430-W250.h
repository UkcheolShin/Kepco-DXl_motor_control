#ifndef __XL430_W250_H__
#define __XL430_W250_H__
/*************************************************************************
*  @TITLE   XL430-W250 CONTROL TABLE
*  @AUTHOR  UK CHEOL SHIN
*  @DATE    2018-04-16
*  @REF 	HTP://EMANUAL.ROBOTIS.COM/DOCS/KR/DXL/X/XL430-W250/
*************************************************************************/

/* 1. EPROM 영역*/
			//	명칭				//주소	//크기(BYTE) //의미	 	 //접근 //기본값
#define 	ADDR_MODEL_NUMBER			0	//	2	모델 번호			R	1060
#define 	ADDR_MODEL_INFORMATION		2	//	4	모델 정보			R	-
#define 	ADDR_FIRMWARE_VERSION		6	//	1	펌웨어 버전 정보		R	-
#define 	ADDR_ID						7	//	1	다이나믹셀 ID		RW	1
#define 	ADDR_BAUD_RATE				8	//	1	다이나믹셀 통신 속도	RW	1
#define 	ADDR_RETURN_DELAY_TIME		9	//	1	응답 지연 시간		RW	250
#define 	ADDR_DRIVE_MODE				10	//	1	드라이브 모드			RW	0
#define 	ADDR_OPERATING_MODE			11	//	1	동작 모드			RW	3
#define 	ADDR_SECONDARY_ID			12	//	1	보조 ID				RW	255
#define 	ADDR_PROTOCOL_VERSION		13	//	1	프로토콜 버전			RW	2
#define 	ADDR_HOMING_OFSET			20	//	4	‘0’점 위치 조정값T	RW	0
#define 	ADDR_MOVING_THRESHOLD		24	//	4	움직임 유무를 결정하는 속도 기준값	RW	10
#define 	ADDR_TEMPERATURE_LIMIT		31	//	1	내부 한계 온도		RW	72
#define 	ADDR_MAX_VOLTAGE_LIMIT		32	//	2	최고 한계 전압		RW	140
#define 	ADDR_MIN_VOLTAGE_LIMIT		34	//	2	최저 한계 전압		RW	60
#define 	ADDR_PWM_LIMIT				36	//	2	PWM 한계값			RW	885
#define 	ADDR_ACELERATION_LIMIT		40	//	4	가속도 한계값			RW	32767
#define 	ADDR_VELOCITY_LIMIT			44	//	4	속도 한계값			RW	415
#define 	ADDR_MAX_POSITION_LIMIT		48	//	4	최대 위치 제한값		RW	4095
#define 	ADDR_MIN_POSITION_LIMIT		52	//	4	최소 위치 제한값		RW	0
#define 	ADDR_SHUTDOWN				63	//	1	셧다운				RW	52

#define 	LEN_MODEL_NUMBER			2	
#define 	LEN_MODEL_INFORMATION		4	
#define 	LEN_FIRMWARE_VERSION		1	
#define 	LEN_ID						1	
#define 	LEN_BAUD_RATE				1	
#define 	LEN_RETURN_DELAY_TIME		1	
#define 	LEN_DRIVE_MODE				1	
#define 	LEN_OPERATING_MODE			1	
#define 	LEN_SECONDARY_ID			1	
#define 	LEN_PROTOCOL_VERSION		1	
#define 	LEN_HOMING_OFSET			4	
#define 	LEN_MOVING_THRESHOLD		4	
#define 	LEN_TEMPERATURE_LIMIT		1	
#define 	LEN_MAX_VOLTAGE_LIMIT		2	
#define 	LEN_MIN_VOLTAGE_LIMIT		2	
#define 	LEN_PWM_LIMIT				2	
#define 	LEN_ACELERATION_LIMIT		4	
#define 	LEN_VELOCITY_LIMIT			4	
#define 	LEN_MAX_POSITION_LIMIT		4	
#define 	LEN_MIN_POSITION_LIMIT		4	
#define 	LEN_SHUTDOWN				1

/* 2. RAM 영역*/
			//	명칭				//주소	//크기(BYTE) //의미	 	 //접근 //기본값
#define 	ADDR_TORQUE_ENABLE			64	//	1	토크 ON/OF	RW	0
#define 	ADDR_LED					65	//	1	LED ON/OF	RW	0
#define 	ADDR_STATUS_RETURN_LEVEL	68	//	1	응답레벨	RW	2
#define 	ADDR_REGISTERED_INSTRUCTION	69	//	1	INSTRUCTION의 등록 여부	R	0
#define 	ADDR_HARDWARE_EROR_STATUS	70	//	1	하드웨어 에러 상태	R	0
#define 	ADDR_VELOCITY_I_GAIN		76	//	2	속도 I GAIN	RW	1000
#define 	ADDR_VELOCITY_P_GAIN		78	//	2	속도 P GAIN	RW	100
#define 	ADDR_POSITION_D_GAIN		80	//	2	위치 D GAIN	RW	4000
#define 	ADDR_POSITION_I_GAIN		82	//	2	위치 I GAIN	RW	0
#define 	ADDR_POSITION_P_GAIN		84	//	2	위치 P GAIN	RW	640
#define 	ADDR_FEEDFORWARD_2ND_GAIN	88	//	2	피드포워드 2ND GAIN	RW	0
#define 	ADDR_FEEDFORWARD_1ST_GAIN	90	//	2	피드포워드 1ST GAIN	RW	0
#define 	ADDR_BUS_WATCHDOG			98	//	1	다이나믹셀 버스 워치독	RW	0
#define 	ADDR_GOAL_PWM				100	//	2	목표 PWM 값	RW	-
#define 	ADDR_GOAL_VELOCITY			104	//	4	목표 속도 값	RW	-
#define 	ADDR_PROFILE_ACCELERATION	108	//	4	프로파일 가속도 값	RW	0
#define 	ADDR_PROFILE_VELOCITY		112	//	4	프로파일 속도 값	RW	0
#define 	ADDR_GOAL_POSITION			116	//	4	목표 위치 값	RW	-
#define 	ADDR_REALTIME_TICK			120	//	2	실시간 TICK	R	-
#define 	ADDR_MOVING					122	//	1	움직임 유무	R	0
#define 	ADDR_MOVING_STATUS			123	//	1	움직임의 상태	R	0
#define 	ADDR_PRESENT_PWM			124	//	2	현재 PWM 값	R	-
#define 	ADDR_PRESENT_LOAD			126	//	2	현재 부하 값	R	-
#define 	ADDR_PRESENT_VELOCITY		128	//	4	현재 속도 값	R	-
#define 	ADDR_PRESENT_POSITION		132	//	4	현재 위치 값	R	-
#define 	ADDR_VELOCITY_TRAJECTORY	136	//	4	속도 궤적 값	R	-
#define 	ADDR_POSITION_TRAJECTORY	140	//	4	위치 궤적 값	R	-
#define 	ADDR_PRESENT_INPUT_VOLTAGE	144	//	2	현재 전압	R	-
#define 	ADDR_PRESENT_TEMPERATURE	146	//	1	현재 온도	R	-

#define 	LEN_TORQUE_ENABLE			1
#define 	LEN_LED						1
#define 	LEN_STATUS_RETURN_LEVEL		1
#define 	LEN_REGISTERED_INSTRUCTION	1
#define 	LEN_HARDWARE_EROR_STATUS	1
#define 	LEN_VELOCITY_I_GAIN			2
#define 	LEN_VELOCITY_P_GAIN			2
#define 	LEN_POSITION_D_GAIN			2
#define 	LEN_POSITION_I_GAIN			2
#define 	LEN_POSITION_P_GAIN			2
#define 	LEN_FEEDFORWARD_2ND_GAIN	2
#define 	LEN_FEEDFORWARD_1ST_GAIN	2
#define 	LEN_BUS_WATCHDOG			1
#define 	LEN_GOAL_PWM				2
#define 	LEN_GOAL_VELOCITY			4
#define 	LEN_PROFILE_ACCELERATION	4
#define 	LEN_PROFILE_VELOCITY		4
#define 	LEN_GOAL_POSITION			4
#define 	LEN_REALTIME_TICK			2	
#define 	LEN_MOVING					1
#define 	LEN_MOVING_STATUS			1
#define 	LEN_PRESENT_PWM				2
#define 	LEN_PRESENT_LOAD			2
#define 	LEN_PRESENT_VELOCITY		4
#define 	LEN_PRESENT_POSITION		4
#define 	LEN_VELOCITY_TRAJECTORY		4
#define 	LEN_POSITION_TRAJECTORY		4
#define 	LEN_PRESENT_INPUT_VOLTAGE	2
#define 	LEN_PRESENT_TEMPERATURE		1

#define 	ADDR_INDIRECT_ADRESS_1		168	//	2	간접 주소 값 1	RW	224
#define 	ADDR_INDIRECT_ADRESS_2		170	//	2	간접 주소 값 2	RW	225
#define 	ADDR_INDIRECT_ADRESS_3		172	//	2	간접 주소 값 3	RW	226
#define 	ADDR_INDIRECT_ADRESS_26		218	//	2	간접 주소 값 26	RW	249
#define 	ADDR_INDIRECT_ADRESS_27		220	//	2	간접 주소 값 27	RW	250
#define 	ADDR_INDIRECT_ADRESS_28		222	//	2	간접 주소 값 28	RW	251
#define 	ADDR_INDIRECT_DATA_1		224	//	1	간접 주소 데이터 1	RW	0
#define 	ADDR_INDIRECT_DATA_2		225	//	1	간접 주소 데이터 2	RW	0
#define 	ADDR_INDIRECT_DATA_3		226	//	1	간접 주소 데이터 3	RW	0
#define 	ADDR_INDIRECT_DATA_26		249	//	1	간접 주소 데이터 26	RW	0
#define 	ADDR_INDIRECT_DATA_27		250	//	1	간접 주소 데이터 27	RW	0
#define 	ADDR_INDIRECT_DATA_28		251	//	1	간접 주소 데이터 28	RW	0
#define 	ADDR_INDIRECT_ADRESS_29		578	//	2	간접 주소 값 29	RW	634
#define 	ADDR_INDIRECT_ADRESS_30		580	//	2	간접 주소 값 30	RW	635
#define 	ADDR_INDIRECT_ADRESS_31		582	//	2	간접 주소 값 31	RW	636
#define 	ADDR_INDIRECT_ADRESS_54		628	//	2	간접 주소 값 54	RW	659
#define 	ADDR_INDIRECT_ADRESS_55		630	//	2	간접 주소 값 55	RW	660
#define 	ADDR_INDIRECT_ADRESS_56		632	//	2	간접 주소 값 56	RW	661
#define 	ADDR_INDIRECT_DATA_29		634	//	1	간접 주소 데이터 29	RW	0
#define 	ADDR_INDIRECT_DATA_30		635	//	1	간접 주소 데이터 30	RW	0
#define 	ADDR_INDIRECT_DATA_31		636	//	1	간접 주소 데이터 31	RW	0
#define 	ADDR_INDIRECT_DATA_54		659	//	1	간접 주소 데이터 54	RW	0
#define 	ADDR_INDIRECT_DATA_55		660	//	1	간접 주소 데이터 55	RW	0
#define 	ADDR_INDIRECT_DATA_56		661	//	1	간접 주소 데이터 56	RW	0

#endif // __XL430_W250_H__