/*
 * CommDataBase.h
 *
 *  Created on: 2016年10月19日
 *      Author: seeing
 */

#ifndef _COMMUNICATION_DATATYPES_H_
#define _COMMUNICATION_DATATYPES_H_

#include <time.h>

namespace NS_CommDataType
{
  
  enum
  {
    COMMUNICATION_DATA_TYPE_NULL = 0,
    COMMUNICATION_DATA_TYPE_REQUEST,
    COMMUNICATION_DATA_TYPE_RESPONSE,
  };
  
  enum
  {
    COMMUNICATION_DATA_REASON_NULL = 0,
    COMMUNICATION_DATA_REASON_MAP,
    COMMUNICATION_DATA_REASON_MAP_SIZE,
    COMMUNICATION_DATA_REASON_POSE,
    COMMUNICATION_DATA_REASON_PATH,
    COMMUNICATION_DATA_REASON_MAP_META,
  };
  
  struct CommData
  {
    unsigned char type;
    unsigned char reason;
    unsigned long sequence;
    time_t time_stamp;
    unsigned char result;
    unsigned short payload_length;
    unsigned char payload[500];
  }__attribute__((packed));

}

#endif /* COMMUNICATION_DATATYPE_COMMDATABASE_H_ */
