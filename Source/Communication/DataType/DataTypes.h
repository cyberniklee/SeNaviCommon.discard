/*
 * CommDataBase.h
 *
 *  Created on: 2016年10月19日
 *      Author: seeing
 */

#ifndef _COMMUNICATION_DATATYPES_H_
#define _COMMUNICATION_DATATYPES_H_

#include <time.h>

namespace NS_CommDataType{

  enum {
    COMMUNICATION_DATA_TYPE_NULL = 0,
    COMMUNICATION_DATA_TYPE_REQUEST_MAP = 1,
    COMMUNICATION_DATA_TYPE_RESPONSE_MAP,
    COMMUNICATION_DATA_TYPE_REQUEST_POSE,
    COMMUNICATION_DATA_TYPE_RESPONSE_POSE,
    COMMUNICATION_DATA_TYPE_REQUEST_PATH,
    COMMUNICATION_DATA_TYPE_RESPONSE_PATH,
  };

  struct CommData{
    unsigned short type;
    unsigned long sequence;
    time_t time_stamp;
    unsigned char result;
    unsigned short payload_length;
    unsigned char payload[500];
  };

}



#endif /* COMMUNICATION_DATATYPE_COMMDATABASE_H_ */
