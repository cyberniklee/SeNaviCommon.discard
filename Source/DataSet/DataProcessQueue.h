/*
 * DataProcessQueue.h
 *
 *  Created on: 2016年9月18日
 *      Author: seeing
 */

#ifndef _DATAPROCESSQUEUE_H_
#define _DATAPROCESSQUEUE_H_

#include <boost/thread/thread.hpp>
#include <boost/function.hpp>
#include "DataQueue.h"
#include "../Time/Time.h"
#include "../Time/Rate.h"
#include "../Common/Declare.h"

namespace NS_NaviCommon
{
  using namespace NS_DataType;

  #define DEFAULT_DATA_PROCESS_RATE 10.0

  class DataProcessQueue : public DataQueue
  {
  private:
    bool running;
    double process_frequency;

    boost::function<void (DataBase*)> callback_;

    boost::thread* process_thread_handle;

    void DataProcessThread()
    {
      Rate rate(this->process_frequency);
      while(running)
      {
        if(!this->isEmpty())
        {
          DataBase* m = this->front();
          this->callback_(m);
        }
        rate.sleep();
      }
    };
    /*
  public:
    DataProcessQueue ()
    {
      //this->process_frequency = 0.1;
    };

    virtual
    ~DataProcessQueue ();
    */

  public:
    void setCallback(boost::function<void (DataBase*)> callback)
    {
      this->callback_ = callback;
    };

    void setFrequency(double frequency)
    {
      this->process_frequency = frequency;
    };

    void startProcess()
    {
      running = true;
      process_thread_handle = new boost::thread(boost::bind(&DataProcessQueue::DataProcessThread, this));
    };

    void stopProcess()
    {
      running = false;
      process_thread_handle->join();
    };

  };

} /* namespace NS_NaviCommon */

#endif /* _DATAPROCESSQUEUE_H_ */
