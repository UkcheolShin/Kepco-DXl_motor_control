# -kepco-DXl_motor_control
KEPCO Motor Control Code
/***********************************************************
* @PROJECT : KEPCO Motor Monitor tool Makefile
* @TITLE   : 모터를 세팅하자.
* @AUTHOR  : Uk Cheol Shin, KAIST RCV LAB
* @DATE    : 2018-04-16
***********************************************************/

1. Dynamixel Library installation
$ cd SDK
$ cd build/linux64
$ make && make install

2. Compile KEPCO Motor program 
$ cd ../../../ 
$ make
$ ./KEPCO_motor -p 2048

3. 하세요.
