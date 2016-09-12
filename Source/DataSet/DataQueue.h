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

namespace _Navi_Common_
{
  template <class M>
  class DataQueue
  {
  public:
    DataQueue();
    ~DataQueue();

  private:
    boost::mutex data_queue_lock;
    std::queue<M> data_queue;

  public:
    void append(M);
    M back();
    M front();
    int size();
    bool isEmpty();
    void clear();
  };

  typedef DataQueue<std::allocator<void> > DataQueueType;

  typedef boost::shared_ptr<DataQueueType> DataQueuePtr;
  typedef boost::shared_ptr<DataQueueType const> DataQueueConstPtr;

} /* namespace _Navi_Common_ */

#endif /* _DATAQUEUE_H_ */
