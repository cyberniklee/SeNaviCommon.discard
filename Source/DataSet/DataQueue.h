/*
 * DataSet.h
 *
 *  Created on: 2016年9月9日
 *      Author: seeing
 */

#ifndef _DATAQUEUE_H_
#define _DATAQUEUE_H_

#include <queue>
#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>
#include "../Exception/Exception.h"
#include "DataType/DataBase.h"

namespace NS_NaviCommon
{
  using namespace NS_DataType;
  class DataQueue
  {
  public:
    DataQueue ()
    {
      capacity_ = 10;
    }
    ;
    DataQueue (int capacity)
    {
      this->capacity_ = capacity;
    }
    ;
    virtual
    ~DataQueue ()
    {
    }
    ;

  private:
    boost::mutex data_queue_lock;
    std::queue<DataBase*> data_queue;
    int capacity_;

  public:
    void
    append (DataBase* item)
    {
      boost::mutex::scoped_lock lock (data_queue_lock);
      if (data_queue.size () >= capacity_)
      {
        //throw DataQueueException("Data queue is full!");
        return;
      }
      data_queue.push (item);
    }
    ;

    DataBase*
    front ()
    {
      DataBase* item;
      boost::mutex::scoped_lock lock (data_queue_lock);
      item = data_queue.front ();
      data_queue.pop ();
      return item;
    }
    ;

    int
    size ()
    {
      boost::mutex::scoped_lock lock (data_queue_lock);
      return data_queue.size ();
    }
    ;

    bool
    isEmpty ()
    {
      bool is_empty;
      boost::mutex::scoped_lock lock (data_queue_lock);
      is_empty = data_queue.empty ();
      return is_empty;
    }
    ;

    void
    setCapacity (int capacity)
    {
      this->capacity_ = capacity;
    }
    ;
  };

} /* namespace NS_NaviCommon */

#endif /* _DATAQUEUE_H_ */
