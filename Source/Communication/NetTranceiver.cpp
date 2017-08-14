/*
 * NetTranceiver.cpp
 *
 *  Created on: 2016年10月19日
 *      Author: seeing
 */

#include "NetTranceiver.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <resolv.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

namespace NS_NaviCommon
{
  
  NetTranceiver::NetTranceiver (int local_port, int remote_port)
  {
    bind_to_port = local_port;
    remote_port_ = remote_port;
  }
  
  NetTranceiver::~NetTranceiver ()
  {
  }
  
  bool
  NetTranceiver::open ()
  {
    bzero (&local_addr, sizeof(local_addr));
    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = inet_addr ("127.0.0.1");
    local_addr.sin_port = htons (bind_to_port);
    
    bzero (&remote_addr, sizeof(remote_addr));
    remote_addr.sin_family = AF_INET;
    remote_addr.sin_addr.s_addr = inet_addr ("127.0.0.1");
    remote_addr.sin_port = htons (remote_port_);
    
    handle = ::socket (AF_INET, SOCK_DGRAM, 0);
    if (handle < 0)
    {
      return false;
    }
    
    if (::bind (handle, (sockaddr*) &local_addr, sizeof(local_addr)) < 0)
    {
      ::close (handle);
      return false;
    }
    
    ::fcntl (handle, F_SETFL, O_NONBLOCK);
    
    return true;
  }
  
  bool
  NetTranceiver::close ()
  {
    ::close (handle);
    return true;
  }
  
  int
  NetTranceiver::receive (unsigned char* buffer, int length, int wait_seconds)
  {
    struct timeval tv;
    int count = 0;
    fd_set rcv_fd;
    int addr_len;
    FD_ZERO(&rcv_fd);
    FD_SET(handle, &rcv_fd);
    tv.tv_sec = wait_seconds;
    tv.tv_usec = 0;

    addr_len = sizeof (struct sockaddr);

    int ret = select (handle + 1, &rcv_fd, NULL, NULL, &tv);
    if (ret > 0)
    {
      if (FD_ISSET(handle, &rcv_fd))
      {
        if ((count = ::recvfrom (handle, buffer, length, 0,
                                 (struct sockaddr*) &remote_addr,
                                 (socklen_t*) &addr_len)) >= 0)
        {
          return count;
        }
        else
        {
          return NET_RX_FAILURE;
        }
      }
    }
    else if (ret == 0)
    {
      return NET_RX_TIMEOUT;
    }
    else
    {
      return NET_RX_FAILURE;
    }
  }
  
  int
  NetTranceiver::transmit (unsigned char* buffer, int length)
  {
    return ::sendto (handle, buffer, length, 0, (struct sockaddr*) &remote_addr,
                     sizeof(sockaddr_in));
  }

} /* namespace NS_NaviCommon */
