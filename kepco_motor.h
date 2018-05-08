/***********************************************************
* @PROJECT : KEPCO Motor Monitor tool Makefile
* @TITLE   : Motor class file
* @AUTHOR  : Uk Cheol Shin, KAIST RCV LAB
* @DATE    : 2018-04-16
* @BRIEF   : XL430-W250 모터 제어를 위한 클래스.
* @UPDATE  : 2018-05-08
* @BRIEF   : Motor 좌우 제어
***********************************************************/
#ifndef __KEPCO_MOTOR_H__
#define __KEPCO_MOTOR_H__

#include "Control_Table_XL430-W250.h"   // XL430-W250 컨트롤 테이블 
#include "dynamixel_sdk/dynamixel_sdk.h"                                // Uses Dynamixel SDK library
#include "motor_io.h"   // Motor 기본 input/output library

#include <assert.h>
#include <unistd.h>

// Protocol version
#define PROTOCOL_VERSION1               1.0                 // See which protocol version is used in the Dynamixel
#define PROTOCOL_VERSION2               2.0

// Default setting
#define DEVICENAME                      "/dev/ttyUSB0"      // Check which port is being used on your controller
                                                            // ex) Windows: "COM1"   Linux: "/dev/ttyUSB0" Mac: "/dev/tty.usbserial-*"
#define ENABLE  1
#define DISABLE 0
#define NUM_ID 6
#define INIT_POS 2200
#define MAX_POS 2900
#define MIN_POS 2048

class KEPCO_Motor
{
private:
  int init_pos_;
  char *dev_name;
  dynamixel::PacketHandler *packetHandler;
  dynamixel::PortHandler *portHandler;

public :
  //@brief 생성자
  KEPCO_Motor(int argc, char * argv[]);
  //@brief input argument 설명서
  void usage(char *progname);
  //@brief input argument parsing
  int parsing(int argc, char *argv[]);
  //@brief 모터 port open
  int MotorOpenPort(void);
  //@brief 모터 initialization
  int MotorInit(void);
  //@brief run에서의 argument 설명
  void help();
  //@brief run
  int run(void);
  //@brief showes motors operation
  int show(void);
  //@brief Group Write
  int Group_Write(int* values, int from_motor, int to_motor);
};
#endif //#define __KEPCO_MOTOR_H__
