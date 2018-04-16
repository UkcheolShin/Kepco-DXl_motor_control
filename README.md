## -kepco-DXl_motor_control

/***********************************************************
* @PROJECT : KEPCO Motor Monitor tool
* @AUTHOR  : Uk Cheol Shin, KAIST RCV LAB
* @DATE    : 2018-04-16
***********************************************************/

# 1. Dynamixel Library installation
```bash
cd SDK
cd build/linux64
make && make install
```

# 2. Compile KEPCO Motor program 
```bash
cd ../../../ 
make
./KEPCO_motor -p 2048
```
