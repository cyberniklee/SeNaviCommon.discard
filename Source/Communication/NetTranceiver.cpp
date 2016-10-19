/*
 * NetTranceiver.cpp
 *
 *  Created on: 2016年10月19日
 *      Author: seeing
 */

#include "NetTranceiver.h"

namespace NS_NaviCommon
{
  
  NetTranceiver::NetTranceiver (int local_port)
  {
    // TODO Auto-generated constructor stub
    bind_to_port = local_port;
  }
  
  NetTranceiver::~NetTranceiver ()
  {
    // TODO Auto-generated destructor stub
  }

  bool NetTranceiver::open()
  {

  }

  bool NetTranceiver::close()
  {

  }

  bool NetTranceiver::receive(unsigned char* buffer, int& length)
  {

  }

  bool NetTranceiver::transmit(unsigned char* buffer, int length)
  {

  }

} /* namespace NS_NaviCommon */
