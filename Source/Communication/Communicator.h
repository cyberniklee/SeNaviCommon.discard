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
#include <vector>
#include <boost/thread/condition.hpp>
#include <boost/thread/thread.hpp>

namespace NS_NaviCommon
{
  using namespace NS_CommDataType;
  
  typedef std::vector<CommData*> MsgHolder;
  typedef MsgHolder::iterator MsgIterator;
  
#define HOLDER_COND_TIMEOUT 1
#define MESSAGE_TIMEOUT 3
#define MAX_WORK_THREADS 10
  
#define LOCAL_PORT 6688
#define REMOTE_PORT 6699
  
  class Communicator
  {
  public:
    Communicator ();
    virtual
    ~Communicator ();
  private:
    NetTranceiver* tranceiver;

    MsgHolder msg_holder;

    boost::condition holder_cond;
    boost::mutex holder_cond_lock;

    boost::mutex msg_holder_lock;

    unsigned long id_;

    bool running;

    int work_thread_count;

    boost::thread receive_thread;
    boost::thread timeout_thread;

  private:
    void
    timeoutProcess ();
    void
    receiveProcess ();

    void
    receiveMessageProcess (CommData* message);

    CommData*
    findMessage (unsigned long seq, unsigned char reason, unsigned char type);
    CommData*
    findRequest (unsigned long seq, unsigned char reason);
    CommData*
    findResponse (unsigned long seq, unsigned char reason);
  protected:
    Communicator* instance;

    virtual void
    onReceive (CommData* message);

  public:
    bool
    initialize (int local_port, int remote_port);
    void
    quit ();
    CommData*
    createMessage ();
    CommData*
    sendAndWait (CommData** request);
    bool
    sendMessage (CommData* message);
    bool
    sendResponse (CommData* response);
    void
    finishMessage (CommData* message);
    CommData*
    createRequestMessage (unsigned char reason);
    CommData*
    createResponseByRequest (CommData* request);
  };

} /* namespace NS_NaviCommon */

#endif /* COMMUNICATION_COMMUNICATOR_H_ */
