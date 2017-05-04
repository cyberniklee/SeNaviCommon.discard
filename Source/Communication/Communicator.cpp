/*
 * Communicator.cpp
 *
 *  Created on: 2016年10月19日
 *      Author: seeing
 */

#include "Communicator.h"
#include "../Time/Utils.h"
#include "../Time/Rate.h"
#include <boost/bind.hpp>
#include <stdio.h>

namespace NS_NaviCommon
{
  using namespace NS_CommDataType;
  
  Communicator::Communicator ()
  {
    tranceiver = NULL;
    id_ = 0;
    running = false;
    work_thread_count = 0;
    //instance = this;
  }
  
  Communicator::~Communicator ()
  {
    if (tranceiver)
    {
      tranceiver->close();
      delete tranceiver;
    }
  }
  
  void
  Communicator::timeoutProcess ()
  {
    NS_NaviCommon::Rate rate (5);

    while (running)
    {
      time_t cur_time;
      time (&cur_time);
      bool timeout_ = false;
      
      msg_holder_lock.lock ();
      for (MsgIterator it = msg_holder.begin (); it != msg_holder.end ();)
      {
        CommData* data = *it;
        if (cur_time - data->time_stamp > MESSAGE_TIMEOUT)
        {
          msg_holder.erase (it);
          if (data != NULL)
            delete data;
          timeout_ = true;
        }
        else
        {
          it++;
        }
      }
      msg_holder_lock.unlock ();
      
      if (timeout_)
      {
        holder_cond_lock.lock ();
        holder_cond.notify_all ();
        holder_cond_lock.unlock ();
      }
      
      rate.sleep ();
    }
  }
  
  void
  Communicator::receiveProcess ()
  {
    unsigned char buf[2000] = { 0 };
    int bytes_received = 0;
    while (running)
    {
      bytes_received = tranceiver->receive (buf, sizeof(buf));
      if (bytes_received <= 0)
      {
        continue;
      }
      if (bytes_received != sizeof(CommData))
      {
        continue;
      }
      CommData* data = reinterpret_cast<CommData*> (buf);
      if (data->type == COMMUNICATION_DATA_TYPE_NULL
          || data->reason == COMMUNICATION_DATA_REASON_NULL)
      {
        continue;
      }
      CommData* new_data = new CommData;
      
      *new_data = *data;
      
      new_data->time_stamp = NS_NaviCommon::getTimeStamp ();
      
      msg_holder_lock.lock ();
      msg_holder.push_back (new_data);
      msg_holder_lock.unlock ();
      
      if (new_data->type == COMMUNICATION_DATA_TYPE_REQUEST)
      {
        //request
        if (work_thread_count <= MAX_WORK_THREADS)
        {
          boost::thread excute_thread (
              boost::bind (&Communicator::receiveMessageProcess, this,
                           new_data));
          work_thread_count++;
        }
      }
      else
      {
        //response
        holder_cond_lock.lock ();
        holder_cond.notify_all ();
        holder_cond_lock.unlock ();
      }
      
    }
  }
  
  CommData*
  Communicator::findMessage (unsigned long seq, unsigned char reason,
                             unsigned char type)
  {
    boost::mutex::scoped_lock lock (msg_holder_lock);
    
    for (MsgIterator it = msg_holder.begin (); it != msg_holder.end (); it++)
    {
      CommData* data = *it;
      
      if (data != NULL && data->sequence == seq && data->type == type
          && data->reason == reason)
      {
        return data;
      }
    }
    return NULL;
  }
  
  CommData*
  Communicator::findRequest (unsigned long seq, unsigned char reason)
  {
    return findMessage (seq, reason, COMMUNICATION_DATA_TYPE_REQUEST);
  }
  
  CommData*
  Communicator::findResponse (unsigned long seq, unsigned char reason)
  {
    return findMessage (seq, reason, COMMUNICATION_DATA_TYPE_RESPONSE);
  }
  
  void
  Communicator::receiveMessageProcess (CommData* message)
  {
    instance->onReceive (message);
    finishMessage (message);
    work_thread_count--;
  }

  void
  Communicator::onReceive (CommData* message)
  {
    
  }

  bool
  Communicator::initialize (int local_port, int remote_port)
  {
    tranceiver = new NetTranceiver (local_port, remote_port);
    if (tranceiver->open () == false)
    {
      return false;
    }
    
    running = true;
    
    receive_thread = boost::thread (
        boost::bind (&Communicator::receiveProcess, this));
    
    timeout_thread = boost::thread (
        boost::bind (&Communicator::timeoutProcess, this));
    
    return true;
  }
  
  CommData*
  Communicator::createMessage ()
  {
    id_++;
    
    CommData* new_data = new CommData;
    new_data->sequence = id_;
    
    return new_data;
  }
  
  CommData*
  Communicator::createRequestMessage (unsigned char reason)
  {
    CommData* new_data = createMessage ();
    new_data->type = COMMUNICATION_DATA_TYPE_REQUEST;
    new_data->reason = reason;
    
    return new_data;
  }
  
  CommData*
  Communicator::createResponseByRequest (CommData* request)
  {
    CommData* response = createMessage ();
    
    response->type = COMMUNICATION_DATA_TYPE_RESPONSE;
    response->reason = request->reason;
    response->sequence = request->sequence;
    
    return response;
  }
  
  CommData*
  Communicator::sendAndWait (CommData** request)
  {
    if (sendMessage (*request) == false)
    {
      return NULL;
    }
    
    msg_holder_lock.lock ();
    msg_holder.push_back (*request);
    msg_holder_lock.unlock ();
    
    CommData* response = NULL;
    holder_cond_lock.lock ();
    while ((findRequest ((*request)->sequence, (*request)->reason) == *request)
        && ((response = findResponse ((*request)->sequence, (*request)->reason))
            == NULL))
    {
      holder_cond.timed_wait (
          holder_cond_lock,
          boost::get_system_time ()
              + boost::posix_time::seconds (HOLDER_COND_TIMEOUT));
    }
    
    holder_cond_lock.unlock ();
    return response;
  }
  
  bool
  Communicator::sendMessage (CommData* message)
  {
    if (message == NULL && message->type == COMMUNICATION_DATA_TYPE_NULL)
    {
      return false;
    }
    
    message->time_stamp = NS_NaviCommon::getTimeStamp ();
    
    if (tranceiver->transmit ((unsigned char*) message, sizeof(CommData))
        == false)
    {
      return false;
    }
    return true;
  }
  
  bool
  Communicator::sendResponse (CommData* response)
  {
    return sendMessage (response);
  }
  
  void
  Communicator::finishMessage (CommData* message)
  {
    if (message == NULL)
      return;
    msg_holder_lock.lock ();
    
    for (MsgIterator it = msg_holder.begin (); it != msg_holder.end ();)
    {
      CommData* data = *it;
      
      if (data->sequence == message->sequence)
      {
        msg_holder.erase (it);
        if (data != NULL)
          delete data;
      }
      else
      {
        it++;
      }
    }
    msg_holder_lock.unlock ();
  }
  
  void
  Communicator::quit ()
  {
    running = false;
    receive_thread.join ();
    timeout_thread.join ();
    tranceiver->close ();
    delete tranceiver;
  }

} /* namespace NS_NaviCommon */
