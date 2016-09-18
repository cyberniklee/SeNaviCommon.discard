/*
 * DataProcessQueue.h
 *
 *  Created on: 2016年9月18日
 *      Author: seeing
 */

#ifndef _DATAPROCESSQUEUE_H_
#define _DATAPROCESSQUEUE_H_

#include <boost/thread/thread.hpp>
#include "DataQueue.h"
#include "../Time/Time.h"
#include "../Common/Declare.h"

namespace _Navi_Common_
{

  template <class M, class C, typename R, typename P>
  class DataProcessQueue : public DataQueue<M>
  {
  public:
    DataProcessQueue ()
    {
      process_frequency = 0.1;
    };
    DataProcessQueue (CallbackClass<C, R, P>* callback)
    {
      process_frequency = 0.1;
      this->callback_ = callback;
    };
    virtual
    ~DataProcessQueue ();
  private:
    bool running;
    double process_frequency;
    CallbackClass<C, R, P>* callback_;

    boost::thread* process_thread_handle;

    void DataProcessThread()
    {
      Rate rate(this->process_frequency);
      if(running)
      {
        if(!this->isEmpty())
        {
          M* m = this->front();
          this->callback_->execute(m);
        }
        rate.sleep();
      }
    };
  public:
    void startProcess()
    {
      running = true;
      process_thread_handle = new boost::thread(boost::bind(DataProcessThread, this));
    };

    void stopProcess()
    {
      running = false;
      process_thread_handle->join();
    };

  };

} /* namespace _Navi_Common_ */

#endif /* _DATAPROCESSQUEUE_H_ */
