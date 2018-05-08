#ifndef __MOTOR_IO_H_
#define __MOTOR_IO_H__
/*******************************************************************************
* Copyright 2017 ROBOTIS CO., LTD.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/
// *********     DXL Monitor Example      *********

#include <fcntl.h>
#include <getopt.h>
#include <termios.h>
#define STDIN_FILENO 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#include "dynamixel_sdk/dynamixel_sdk.h"                                // Uses Dynamixel SDK library

// @brief tty commnication에서 charcter 취득
int getch(void);

// @brief 커넥션 확인
int kbhit(void);

// @brief 커넥션 확인
void scan(dynamixel::PortHandler *portHandler, dynamixel::PacketHandler *packetHandler2);

// @brief 데이터 쓰기
void write(dynamixel::PortHandler *portHandler, dynamixel::PacketHandler *packetHandler, uint8_t id, uint16_t addr, uint16_t length, uint32_t value);

// @brief 데이터 읽기
void read(dynamixel::PortHandler *portHandler, dynamixel::PacketHandler *packetHandler, uint8_t id, uint16_t addr, uint16_t length);

void dump(dynamixel::PortHandler *portHandler, dynamixel::PacketHandler *packetHandler, uint8_t id, uint16_t addr, uint16_t len);

#endif // __MOTOR_FILEIO__
