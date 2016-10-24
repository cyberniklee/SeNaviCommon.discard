/*
 * Communicator.h
 *
 *  Created on: 2016年10月19日
 *      Author: seeing
 */

#ifndef _COMMUNICATOR_H_
#define _COMMUNICATOR_H_

#include "NetTranceiver.h"
#include "DataType/DataTypes.h"
#include <map>
#include <boost/thread/condition.hpp>
#include <boost/thread/thread.hpp>

namespace NS_NaviCommon
{
  using namespace NS_CommDataType;

  typedef unsigned long MsgSeqID;
  typedef std::multimap<MsgSeqID, CommData*> MsgHolder;
  typedef MsgHolder::iterator MsgIterator;
  typedef std::pair<MsgSeqID, CommData*> MsgPair;

  #define HOLDER_COND_TIMEOUT 1
  #define MESSAGE_TIMEOUT 3
  #define MAX_WORK_THREADS 10

  #define LOCAL_PORT 6688
  #define REMOTE_PORT 6699


  class Communicator
  {
  public:
    Communicator ();
    virtual ~Communicator ();
  private:
    NetTranceiver* tranceiver;

    MsgHolder msg_holder;

    boost::condition holder_cond;
    boost::mutex holder_cond_lock;

    boost::mutex msg_holder_lock;

    MsgSeqID id_;

    bool running;

    int work_thread_count;

    boost::thread receive_thread;
    boost::thread timeout_thread;

  private:
    void timeoutProcess();
    void receiveProcess();

    CommData* findMessage(MsgSeqID seq, unsigned char reason, unsigned char type);
    CommData* findRequest(MsgSeqID seq, unsigned char reason);
    CommData* findResponse(MsgSeqID seq, unsigned char reason);
  protected:
    Communicator* instance;
    virtual void onTimeout(CommData* timeout_message);
    virtual void onReceive(CommData* message);
  public:
    bool initialize(int local_port);
    void quit();
    CommData* createMessage();
    CommData* sendAndWait(CommData** request);
    bool sendMessage(CommData* message);
    bool sendResponse(CommData* response);
    void finishMessage(CommData* message);
    CommData* createResponseByRequest(CommData* request);
  };

} /* namespace NS_NaviCommon */

#endif /* COMMUNICATION_COMMUNICATOR_H_ */
