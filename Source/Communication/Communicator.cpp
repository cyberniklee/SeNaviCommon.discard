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


namespace NS_NaviCommon
{
  using namespace NS_CommDataType;
  
  Communicator::Communicator ()
  {
    // TODO Auto-generated constructor stub
    tranceiver = NULL;
    id_ = 0;
    running = false;
    work_thread_count = 0;
    instance = this;
  }
  
  Communicator::~Communicator ()
  {
    // TODO Auto-generated destructor stub


  }

  void Communicator::timeoutProcess()
  {
    NS_NaviCommon::Rate rate(1);

    while(running)
    {
      time_t cur_time;
      time(&cur_time);
      msg_holder_lock.lock();
      for(MsgIterator it = msg_holder.begin(); it != msg_holder.end();)
      {
        CommData* data = (CommData*)(it->second);
        if(data->time_stamp - cur_time > MESSAGE_TIMEOUT)
        {
          msg_holder.erase(it++);

          boost::thread excute_thread(boost::bind(&Communicator::onTimeout, instance, data));

          holder_cond_lock.lock();
          holder_cond.notify_all();
          holder_cond_lock.unlock();
        }
      }
      msg_holder_lock.unlock();

      rate.sleep();
    }
  }

  void Communicator::receiveProcess()
  {
    unsigned char buf[2000] = {0};
    int bytes_received = 0;
    while(running)
    {
      if(tranceiver->receive(buf, bytes_received) == false)
      {
        continue;
      }
      if(bytes_received != sizeof(CommData))
      {
        continue;
      }

      CommData* data = reinterpret_cast<CommData*>(buf);

      if(data->type == COMMUNICATION_DATA_TYPE_NULL ||
          data->reason == COMMUNICATION_DATA_REASON_NULL)
      {
        continue;
      }

      CommData* new_data = new CommData;

      *new_data = *data;

      new_data->time_stamp = NS_NaviCommon::getTimeStamp();

      msg_holder_lock.lock();
      msg_holder.insert(MsgPair(new_data->sequence, data));
      msg_holder_lock.unlock();

      if(new_data->reason == COMMUNICATION_DATA_TYPE_REQUEST)
      {
        //request
        if(work_thread_count <= MAX_WORK_THREADS)
        {
          boost::thread excute_thread(boost::bind(&Communicator::onReceive, instance, new_data));
          work_thread_count++;
        }
      }else{
        //response
        holder_cond_lock.lock();
        holder_cond.notify_all();
        holder_cond_lock.unlock();
      }

    }
  }



  CommData* Communicator::findMessage(MsgSeqID seq, unsigned char reason, unsigned char type)
  {
    boost::mutex::scoped_lock lock(msg_holder_lock);
    std::pair<MsgIterator, MsgIterator> ranger;
    ranger = msg_holder.equal_range(seq);
    for(MsgIterator it = ranger.first; it != ranger.second; ++it)
    {
      CommData* data = it->second;
      if(data == NULL)
      {
        continue;
      }
      if(data->type != type || data->reason != reason)
      {
        continue;
      }
      return data;
    }
    return NULL;
  }

  CommData* Communicator::findRequest(MsgSeqID seq, unsigned char reason)
  {
    return findMessage(seq, reason, COMMUNICATION_DATA_TYPE_REQUEST);
  }

  CommData* Communicator::findResponse(MsgSeqID seq, unsigned char reason)
  {
    return findMessage(seq, reason, COMMUNICATION_DATA_TYPE_RESPONSE);
  }

  void Communicator::onTimeout(CommData* timeout_message)
  {
    if(timeout_message != NULL)
      delete timeout_message;
  }

  void Communicator::onReceive(CommData* message)
  {

    work_thread_count--;
  }

  bool Communicator::initialize(int local_port)
  {
    tranceiver = new NetTranceiver(local_port);
    if(tranceiver->open() == false)
    {
      return false;
    }

    receive_thread = boost::thread(boost::bind(&Communicator::receiveProcess, this));

    timeout_thread = boost::thread(boost::bind(&Communicator::timeoutProcess, this));

    return true;
  }

  CommData* Communicator::createMessage()
  {
    id_++;

    CommData* new_data = new CommData;
    new_data->sequence = id_;

    return new_data;
  }

  CommData* Communicator::createResponseByRequest(CommData* request)
  {
    CommData* response = createMessage();

    response->type = request->type;
    response->reason = request->reason;
    response->sequence = request->sequence;

    return response;
  }

  CommData* Communicator::sendAndWait(CommData** request)
  {
    if(sendMessage(*request) == false)
    {
      return NULL;
    }

    msg_holder_lock.lock();
    msg_holder.insert(MsgPair((*request)->sequence, *request));
    msg_holder_lock.unlock();

    CommData* response = NULL;
    holder_cond_lock.lock();
    while(findRequest((*request)->sequence, (*request)->reason) == *request &&
        (response = findResponse((*request)->sequence, (*request)->reason)) == NULL)
    {
      holder_cond.timed_wait(holder_cond_lock,
                             boost::get_system_time() + boost::posix_time::seconds(HOLDER_COND_TIMEOUT));
    }

    holder_cond_lock.unlock();

    return response;
  }

  bool Communicator::sendMessage(CommData* message)
  {
    if(message == NULL && message->type == COMMUNICATION_DATA_TYPE_NULL)
    {
      return false;
    }
    if(tranceiver->transmit((unsigned char*)message, sizeof(CommData)) == false)
    {
      return false;
    }
    return true;
  }

  bool Communicator::sendResponse(CommData* response)
  {
    return sendMessage(response);
  }

  void Communicator::finishMessage(CommData* message)
  {
    if(message == NULL)
      return;
    msg_holder_lock.lock();
    for(MsgIterator it = msg_holder.begin(); it != msg_holder.end();)
    {
      CommData* data = (CommData*)(it->second);

      if(data->reason == message->reason && data->sequence == message->sequence)
      {
        msg_holder.erase(it++);
        delete data;
      }
    }
    msg_holder_lock.unlock();
  }

  void Communicator::quit()
  {
    running = false;
    receive_thread.join();
    timeout_thread.join();
    tranceiver->close();
    delete tranceiver;
  }

} /* namespace NS_NaviCommon */
