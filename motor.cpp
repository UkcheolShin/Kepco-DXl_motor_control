/***********************************************************
* @PROJECT : KEPCO Motor Monitor tool Makefile
* @TITLE   : Motor Main File
* @AUTHOR  : Uk Cheol Shin, KAIST RCV LAB
* @DATE    : 2018-04-16
* @BRIEF   : 모터 제어 파일.
***********************************************************/
#include "kepco_motor.h"

int main(int argc, char *argv[])
{
  KEPCO_Motor * Motor = new KEPCO_Motor(argc,argv);

  Motor->run();

  delete Motor;
}
