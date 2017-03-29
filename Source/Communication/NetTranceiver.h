/*
 * NetTranceiver.h
 *
 *  Created on: 2016年10月19日
 *      Author: seeing
 */

#ifndef _NETTRANCEIVER_H_
#define _NETTRANCEIVER_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <boost/thread/mutex.hpp>

namespace NS_NaviCommon
{
  enum
  {
    NET_RX_TIMEOUT = -1, NET_RX_FAILURE = -2,
  };
  
#define NET_RX_WAIT 1
  
  class NetTranceiver
  {
  public:
    NetTranceiver (int local_port = 6688, int remote_port = 6689);
    ~NetTranceiver ();
  private:
    int handle;

    struct sockaddr_in local_addr;
    struct sockaddr_in remote_addr;

    int bind_to_port;
    int remote_port_;

    boost::mutex lock;

  public:
    bool
    open ();
    bool
    close ();
    int
    receive (unsigned char* buffer, int length, int wait_seconds = NET_RX_WAIT);
    int
    transmit (unsigned char* buffer, int length);
  };

} /* namespace NS_NaviCommon */

#endif /* COMMUNICATION_NETTRANCEIVER_H_ */
