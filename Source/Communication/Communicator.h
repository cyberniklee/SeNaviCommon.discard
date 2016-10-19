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
#include "../Thread/Condition.h"

namespace NS_NaviCommon
{
  using namespace NS_CommDataType;

  typedef unsigned long MsgSeqID;
  typedef std::multimap<MsgSeqID, CommData*> MsgHolder;
  typedef MsgHolder::iterator MsgIterator;


  class Communicator
  {
  public:
    Communicator ();
    ~Communicator ();
  private:
    NetTranceiver tranceiver;

    Condition timeout_cond;
    Condition sync_cond;

    boost::mutex msg_holder_lock;
  private:
    void timeoutProcess();
    void msgReceiveProcess();
  protected:
    virtual void onTimeout(CommData* timeout_message);
    virtual void onMessageReceive(CommData* message);
  public:
    bool initialize();
    CommData* createMessage();
    CommData* sendAndWait(CommData* request);
    void sendResponse(CommData* response);
    void finishMessage(CommData* message);
  };

} /* namespace NS_NaviCommon */

#endif /* COMMUNICATION_COMMUNICATOR_H_ */
