/***********************************************************
* @PROJECT : KEPCO Motor Monitor tool Makefile
* @TITLE   : Motor class file
* @AUTHOR  : Uk Cheol Shin, KAIST RCV LAB
* @DATE    : 2018-04-16
* @BRIEF   : XL430-W250 모터 제어를 위한 클래스.
* @UPDATE  : 2018-05-08
* @BRIEF   : Motor 좌우 제어
***********************************************************/
#include "kepco_motor.h"


KEPCO_Motor::KEPCO_Motor(int argc, char * argv[]) : init_pos_((int)INIT_POS), dev_name((char*)DEVICENAME)
{
  packetHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION2);
  portHandler = dynamixel::PortHandler::getPortHandler(dev_name);

  // Data Pasing
  if(!parsing(argc,argv)){
    printf("[WARNING] : parsing error\n");
    assert(0);
  }

  // Open motor port
  if(MotorOpenPort())
    printf("[1]Motor port Open Success !!\n");
  else{
    printf("[1]Motor port Open Failed !!\n");
    assert(0);
  }

  // Set motor torque & init position
  if(MotorInit())
    printf("[2]MotorInit : Success !!\n");
  else{
    printf("[1]Motor port Open Failed !!\n");
    assert(0);
  }
}


void KEPCO_Motor::usage(char *progname)
{
  printf("-----------------------------------------------------------------------\n");
  printf("Usage: %s\n", progname);
  printf(" [-h | --help]........: display this help\n");
  printf(" [-d | --device]......: port to open\n");
  printf(" [-p | --position]......: initial position to set\n");
  printf("-----------------------------------------------------------------------\n");
}


int KEPCO_Motor::parsing(int argc, char *argv[])
{
  // parameter parsing
  while(1)
  {
    int option_index = 0, c = 0;
    static struct option long_options[] = {
        {"h", no_argument, 0, 0},
        {"help", no_argument, 0, 0},
        {"d", required_argument, 0, 0},
        {"device", required_argument, 0, 0},
        {"p", required_argument, 0, 0},
        {"position", required_argument, 0, 0},
        {0, 0, 0, 0}
    };

    // parsing all parameters according to the list above is sufficent
    c = getopt_long_only(argc, argv, "", long_options, &option_index);

    // no more options to parse
    if (c == -1) break;

    // unrecognized option
    if (c == '?') {
      usage(argv[0]);
      return 0;
    }

    // dispatch the given options
    switch(option_index) {
    // h, help
    case 0:
    case 1:
      usage(argv[0]);
      return 0;
      break;

    // d, device
    case 2:
    case 3:
      if (strlen(optarg) == 1)
      {
        char tmp[20];
        sprintf(tmp, "/dev/ttyUSB%s", optarg);
        dev_name = strdup(tmp);
      }
      else
        dev_name = strdup(optarg);
      break;

    // p, position
    case 4:
    case 5:
      if ( ((MIN_POS <= atoi(optarg)) & (atoi(optarg)<=MAX_POS)) & (strlen(optarg) == 3 || strlen(optarg) == 4) )
      {
        init_pos_ = atoi(optarg);
        printf("Set Init position : %d \n", init_pos_);
      }
      else{
        fprintf(stderr,"[WARNING] : You shoud insert the value between 2048 ~ 2500.\n");
        assert(0);
      }
      break;

    default:
      usage(argv[0]);
      return 0;
    }
  }
}


int KEPCO_Motor::MotorOpenPort(void)
{
  // Open port
  portHandler->closePort();
  if (portHandler->openPort())
  {
    printf("[0]Succeeded to open the port!\n\n");
    printf(" - Device Name : %s\n", dev_name);
    printf(" - Baudrate    : %d\n\n", portHandler->getBaudRate());
  }
  else
  {
    printf("[0]Failed to open the port! [%s]\n", dev_name);
    printf("[0]Press any key to terminate...\n");
    getch();
    return 0;
  }

  return 1;
}


int KEPCO_Motor::MotorInit(void)
{
  // 1.Torque Enable
  // 1-1. groupSyncWriter instance 생성 
  dynamixel::GroupSyncWrite groupTorqueWrite(portHandler, packetHandler, ADDR_TORQUE_ENABLE, LEN_TORQUE_ENABLE);

  bool dxl_result = false;

  // 1-2. Syncwrite storage에 torque enable 값 저장
  for(int id = 1 ; id <= NUM_ID ; id++)
  {
    uint8_t enable_ = ENABLE;
    dxl_result = groupTorqueWrite.addParam(id,&enable_);
    if (dxl_result != true)
    {
      fprintf(stderr, "[1-1]MotorInit : [ID:%03d] groupTorqueWrite addparam failed", id);
      return 0;
    }
  }

  // 1-3. Syncwrite 수행
  dxl_result = groupTorqueWrite.txPacket();
  if(dxl_result != COMM_SUCCESS) 
    printf("%s\n", packetHandler->getTxRxResult((int)dxl_result));
  else
    printf("[1-1]MotorInit : All Motors Torque is Enabled !!\n");

  // 1-4. Clear syncwrite parameter storage
  groupTorqueWrite.clearParam();

  // 2.INIT POSITION 설정
  // 2-1. groupSyncWriter instance 생성 
  dynamixel::GroupSyncWrite groupPosWrite(portHandler, packetHandler, ADDR_GOAL_POSITION, LEN_GOAL_POSITION);

  // 2-2. Syncwrite storage에 Position 값 저장
  for(int id = 1 ; id <= NUM_ID ; id++)
  {
    dxl_result = groupPosWrite.addParam(id, (uint8_t*)&init_pos_);
    if (dxl_result != true)
    {
      fprintf(stderr, "[1-2]MotorInit : [ID:%03d] groupPosWrite addparam failed", id);
      return 0;
    }
  }

  // 2-3. Syncwrite 수행
  dxl_result = groupPosWrite.txPacket();
  if(dxl_result != COMM_SUCCESS) 
    printf("%s\n", packetHandler->getTxRxResult((int)dxl_result));
  else
    printf("[1-2]MotorInit : All Motors Init Position [%d] is Seted !!\n", init_pos_);

  // 2-4. Clear syncwrite parameter storage
  groupPosWrite.clearParam();

  return 1;
}


void KEPCO_Motor::help()
{
  printf("\n");
  printf("                 .------------------------------------.\n");
  printf("                 |  KEPCO Motor Monitor Command List  |\n");
  printf("                 '------------------------------------'\n");
  printf(" =========================== Common Commands ===========================\n");
  printf(" \n");
  printf(" help|h|?                    :Displays help information\n");
  printf(" exit                        :Exit this program\n");
  printf(" scan                        :Outputs the current status of all Dynamixels\n");
  printf(" ping [ID] [ID] ...          :Outputs the current status of [ID]s \n");
  printf(" bp                          :Broadcast ping (Dynamixel Protocol 2.0 only)\n");
  printf(" \n");
  printf(" ==================== Commands for Dynamixel Protocol 2.0 ====================\n");
  printf(" \n");
  printf(" wrb2|w2 [ID] [ADDR] [VALUE] :Write byte [VALUE] to [ADDR] of [ID]\n");
  printf(" wrw2 [ID] [ADDR] [VALUE]    :Write word [VALUE] to [ADDR] of [ID]\n");
  printf(" wrd2 [ID] [ADDR] [VALUE]    :Write dword [VALUE] to [ADDR] of [ID]\n");
  printf(" rdb2 [ID] [ADDR]            :Read byte value from [ADDR] of [ID]\n");
  printf(" rdw2 [ID] [ADDR]            :Read word value from [ADDR] of [ID]\n");
  printf(" rdd2 [ID] [ADDR]            :Read dword value from [ADDR] of [ID]\n");
  printf(" r2 [ID] [ADDR] [LENGTH]     :Dumps the control table of [ID]\n");
  printf("                               ([LENGTH] bytes from [ADDR])\n");
  printf(" reboot2|rbt2 [ID]           :reboot the Dynamixel of [ID]\n");
  printf(" reset2|rst2 [ID] [OPTION]   :Factory reset the Dynamixel of [ID]\n");
  printf("                               OPTION: 255(All), 1(Except ID), 2(Except ID&Baud)\n");
  printf(" \n");
  printf(" =========================== User define function =============================\n");
  printf(" \n");
  printf(" wlr [VALUE1] [VALUE2]        : Write byte [VALUE1] to [Left Motor Set], [VALUE2] to [Right Motor Set]\n");
  printf(" wlr [VALUE1]                 : Write byte [VALUE1] to [Left Motor Set], [Right Motor Set] \n");
  printf(" wl [VALUE1] [VALUE2] [VALUE3]: Write byte [VALUE1],[VALUE2],[VALUE3] to [Left Motor Set]\n");
  printf(" wl [VALUE1]                  : Write byte [VALUE1] to [Left Motor Set]\n");
  printf(" wr [VALUE1] [VALUE2] [VALUE3]: Write byte [VALUE1],[VALUE2],[VALUE3] to [Right Motor Set]\n");
  printf(" wr [VALUE1]                  : Write byte [VALUE1] to [Right Motor Set]\n");
  printf(" \n");
  printf(" ==================== ADDR & LEN for XL430-W250 =============================\n");
  printf(" Goal Position ADDR : %d, LENGTH : %d \n", ADDR_GOAL_POSITION, LEN_GOAL_POSITION);
  printf(" Torque Enable ADDR : %d, LENGTH : %d \n", ADDR_TORQUE_ENABLE, LEN_TORQUE_ENABLE);
  printf(" LED ADDR           : %d, LENGTH : %d \n", ADDR_LED, LEN_LED);
  printf(" \n");

  printf("\n");
}
  

int KEPCO_Motor::run(void  )
{
  fprintf(stderr, "\n***********************************************************************\n");
  fprintf(stderr,   "*                    KEPCO Motor Monitor                              *\n");
  fprintf(stderr,   "***********************************************************************\n\n");

  char    input[128];
  char    cmd[80];
  char    param[20][30];
  int     num_param;
  int     values[6];
  char    *token;
  uint8_t dxl_error;

  while(1)
  {
    printf("[CMD] ");
    fgets(input, sizeof(input), stdin);
    char *p;
    if ((p = strchr(input, '\n'))!= NULL) *p = '\0';
    fflush(stdin);

    if (strlen(input) == 0) continue;

    token = strtok(input, " ");

    if (token == 0) continue;

    strcpy(cmd, token);
    token = strtok(0, " ");
    num_param = 0;

    while(token != 0)
    {
      strcpy(param[num_param++], token);
      token = strtok(0, " ");
    }

    if (strcmp(cmd, "help") == 0 || strcmp(cmd, "h") == 0 || strcmp(cmd, "?") == 0)
    {
      help();
    }
    else if (strcmp(cmd, "exit") == 0)
    {
      portHandler->closePort();
      return 0;
    }
    else if (strcmp(cmd, "scan") == 0)
    {
      scan(portHandler,packetHandler);
    }
    else if (strcmp(cmd, "ping") == 0)
    {
      uint16_t dxl_model_num;

      if (num_param == 0)
      {
        fprintf(stderr, " Invalid parameters! \n");
        continue;
      }

      fprintf(stderr, "\n");
      fprintf(stderr, "ping Using Protocol 2.0\n");
      for (int i = 0; i < num_param; i++)
      {
        if (packetHandler->ping(portHandler, atoi(param[i]), &dxl_model_num, &dxl_error) == COMM_SUCCESS)
        {
          fprintf(stderr, "\n                                          ... SUCCESS \r");
          fprintf(stderr, " [ID:%.3d] Model No : %.5d \n", atoi(param[i]), dxl_model_num);
        }
        else
        {
          fprintf(stderr, "\n                                          ... FAIL \r");
          fprintf(stderr, " [ID:%.3d] \n", atoi(param[i]));
        }
      }
      fprintf(stderr, "\n");
    }
    else if (strcmp(cmd, "bp") == 0)
    {
      if (num_param == 0)
      {
        std::vector<unsigned char> vec;

        int dxl_result = packetHandler->broadcastPing(portHandler, vec);
        if (dxl_result != COMM_SUCCESS) packetHandler->printTxRxResult(dxl_result);

        for (unsigned int i = 0; i < vec.size(); i++)
        {
          fprintf(stderr, "\n                                          ... SUCCESS \r");
          fprintf(stderr, " [ID:%.3d] \n", vec.at(i));
        }
        printf("\n");
      }
      else
      {
        fprintf(stderr, " Invalid parameters! \n");
      }
    }
    else if (strcmp(cmd, "wrb2") == 0 || strcmp(cmd, "w2") == 0)
    {
      if (num_param == 3)
      {
        write(portHandler, packetHandler, atoi(param[0]), atoi(param[1]), 1, atoi(param[2]));
      }
      else
      {
        fprintf(stderr, " Invalid parameters! \n");
      }
    }
    else if (strcmp(cmd, "wrw2") == 0)
    {
      if (num_param == 3)
      {
        write(portHandler, packetHandler, atoi(param[0]), atoi(param[1]), 2, atoi(param[2]));
      }
      else
      {
        fprintf(stderr, " Invalid parameters! \n");
      }
    }
    else if (strcmp(cmd, "wrd2") == 0)
    {
      if (num_param == 3)
      {
        write(portHandler, packetHandler, atoi(param[0]), atoi(param[1]), 4, atoi(param[2]));
      }
      else
      {
        fprintf(stderr, " Invalid parameters! \n");
      }
    }
    else if (strcmp(cmd, "rdb2") == 0)
    {
      if (num_param == 2)
      {
        read(portHandler, packetHandler, atoi(param[0]), atoi(param[1]), 1);
      }
      else
      {
        fprintf(stderr, " Invalid parameters! \n");
      }
    }
    else if (strcmp(cmd, "rdw2") == 0)
    {
      if (num_param == 2)
      {
        read(portHandler, packetHandler, atoi(param[0]), atoi(param[1]), 2);
      }
      else
      {
        fprintf(stderr, " Invalid parameters! \n");
      }
    }
    else if (strcmp(cmd, "rdd2") == 0)
    {
      if (num_param == 2)
      {
        read(portHandler, packetHandler, atoi(param[0]), atoi(param[1]), 4);
      }
      else
      {
        fprintf(stderr, " Invalid parameters! \n");
      }
    }
    else if (strcmp(cmd, "r2") == 0)
    {
      if (num_param == 3)
      {
        dump(portHandler, packetHandler, atoi(param[0]), atoi(param[1]), atoi(param[2]));
      }
      else
      {
        fprintf(stderr, " Invalid parameters! \n");
      }
    }
    else if (strcmp(cmd, "reboot2") == 0 || strcmp(cmd, "rbt2") == 0)
    {
      if (num_param == 1)
      {
        int dxl_result = packetHandler->reboot(portHandler, atoi(param[0]), &dxl_error);
        if (dxl_result == COMM_SUCCESS)
        {
          if (dxl_error != 0) packetHandler->printRxPacketError(dxl_error);
          fprintf(stderr, "\n Success to reboot! \n\n");
        }
        else
        {
          packetHandler->printTxRxResult(dxl_result);
          fprintf(stderr, "\n Fail to reboot! \n\n");
        }
      }
      else
      {
          fprintf(stderr, " Invalid parameters! \n");
      }
    }
    else if (strcmp(cmd, "reset2") == 0 || strcmp(cmd, "rst2") == 0)
    {
      if (num_param == 2)
      {
        int dxl_result = packetHandler->factoryReset(portHandler, atoi(param[0]), atoi(param[1]), &dxl_error);
        if (dxl_result == COMM_SUCCESS)
        {
          if (dxl_error != 0) packetHandler->printRxPacketError(dxl_error);
          fprintf(stderr, "\n Success to reset! \n\n");
        }
        else
        {
          packetHandler->printTxRxResult(dxl_result);
          fprintf(stderr, "\n Fail to reset! \n\n");
        }
      }
      else
      {
        fprintf(stderr, " Invalid parameters! \n");
      }
    }
    else if (strcmp(cmd, "wrl") == 0 || strcmp(cmd, "wlr") == 0 )
    {
      //parsing parameter
      if (num_param == 1) // Value 1
      {
        int values[6] = {atoi(param[0]),atoi(param[0]),atoi(param[0]),atoi(param[0]),atoi(param[0]),atoi(param[0])};
        // write
        if (Group_Write(values,1,6) == 0) // success 0 / fail -1
          printf("\n Success to send to right and left motors ! \n\n");
        else
          printf("\n Fail to send to right and left motors ! \n\n");
      }
      else if (num_param == 2)  // Value1, Value 2
      {
        int values[6] = {atoi(param[0]),atoi(param[0]),atoi(param[0]),atoi(param[1]),atoi(param[1]),atoi(param[1])};
        // write
        if (Group_Write(values,1,6) == 0) // success 0 / fail -1
          printf("\n Success to send to right and left motors ! \n\n");
        else
          printf("\n Fail to send to right and left motors ! \n\n");
      }
      else
        fprintf(stderr, " Invalid parameters! \n");
    }
    else if (strcmp(cmd, "wr") == 0)
    {
      //parsing parameter
      if (num_param == 1) // Value 1
      {
        int values[3] = {atoi(param[0]),atoi(param[0]),atoi(param[0])};
        // write     
        if (Group_Write(values,1,3) == 0) // success 0 / fail -1
          printf("\n Success to send to right motors ! \n\n");
        else
          printf("\n Fail to send to right motors ! \n\n");
      }
      else if (num_param == 3)  // Value1, Value 2
      {
        int values[3] = {atoi(param[0]),atoi(param[1]),atoi(param[2])};
        // write     
        if (Group_Write(values,1,3) == 0) // success 0 / fail -1
          printf("\n Success to send to right motors ! \n\n");
        else
          printf("\n Fail to send to right motors ! \n\n");
      }
      else
        fprintf(stderr, " Invalid parameters! \n");

    }   
    else if (strcmp(cmd, "wl") == 0)
    {
      //parsing parameter
      if (num_param == 1) // Value 1
      {
        int values[3] = {atoi(param[0]),atoi(param[0]),atoi(param[0])};
        // write
        if (Group_Write(values,4,6) == 0) // success 0 / fail -1
          printf("\n Success to send to left motors ! \n\n");
        else
          printf("\n Fail to send to left motors ! \n\n");
      }
      else if (num_param == 3)  // Value1, Value 2
      {
        int values[3] = {atoi(param[0]),atoi(param[1]),atoi(param[2])};
        // write
        if (Group_Write(values,4,6) == 0) // success 0 / fail -1
          printf("\n Success to send to left motors ! \n\n");
        else
          printf("\n Fail to send to left motors ! \n\n");
      }
      else
        fprintf(stderr, " Invalid parameters! \n");

    }         
    else
    {
      printf(" Bad command! Please input 'help'.\n");
    }
  }
}

int KEPCO_Motor::show(void)
{
  int init_value[10] = {2048,2100,2150,2200,2250,2300,2350,2400,2450,2500};
  bool dxl_result;

  // 2.INIT POSITION 설정
  // 2-1. groupSyncWriter instance 생성 
  dynamixel::GroupSyncWrite groupPosWrite(portHandler, packetHandler, ADDR_GOAL_POSITION, LEN_GOAL_POSITION);
  int j = 0;
  for(int i = 0 ; i < 30; i++)
  {
    // 2-2. Syncwrite storage에 Position 값 저장
    for(int id = 1 ; id <= NUM_ID ; id++)
    {
      j++;
      dxl_result = groupPosWrite.addParam(id, (uint8_t*)&init_value[j%9]);
      printf("num : %d : value : %d \t", id, init_value[j%9]);
      if (dxl_result != true)
      {
        fprintf(stderr, "[1-2]MotorInit : [ID:%03d] groupPosWrite addparam failed", id);
        return 0;
      }
    }
    printf("\n");

    // Syncwrite 수행
    dxl_result = groupPosWrite.txPacket();
    if(dxl_result != COMM_SUCCESS) 
      printf("%s\n", packetHandler->getTxRxResult((int)dxl_result));
    else
      printf("[1-2]MotorInit : All Motors Init Position [%d] is Seted !!\n", init_value[0]);

    sleep(1); 

    // Clear syncwrite parameter storage
    groupPosWrite.clearParam();
  } 
  return 1;
}

int KEPCO_Motor::Group_Write(int* values, int from_motor, int to_motor)
{
  int dxl_result;
  int i=0; 
  if(values == NULL) return -1;

  // groupSyncWriter instance 생성 
  static dynamixel::GroupSyncWrite groupPosWrite(portHandler, packetHandler, ADDR_GOAL_POSITION, LEN_GOAL_POSITION);

  for(int id = from_motor ; id <= to_motor ; id++,i++)
  {
    dxl_result = groupPosWrite.addParam(id, (uint8_t*)&values[i]);

    #ifdef DEBUG
    printf("num : %d : value : %d \t", id, values[id-1]);
    #endif

    if (dxl_result != true)
    {
      fprintf(stderr, "[ID:%03d] groupPosWrite addparam failed", id);
      return 0;
    }
  }

  #ifdef DEBUG
  printf("\n");
  #endif

  // Syncwrite 수행
  dxl_result = groupPosWrite.txPacket();
  if(dxl_result != COMM_SUCCESS)
  { 
    printf("Write Error : %s\n", packetHandler->getTxRxResult(dxl_result));
    groupPosWrite.clearParam();
    return -1;
  }
  else
    printf("All Motors Values are Seted !!\n");
  
  // Clear syncwrite parameter storage
  groupPosWrite.clearParam();
  return 0;
}
