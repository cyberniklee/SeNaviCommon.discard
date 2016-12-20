/*
 * Dispitcher.h
 *
 *  Created on: 2016年9月12日
 *      Author: seeing
 */

#ifndef _DISPITCHER_H_
#define _DISPITCHER_H_

#include <map>
#include <boost/thread/mutex.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include "DataProcessQueue.h"
#include "../Common/Declare.h"

namespace NS_NaviCommon
{

  typedef enum
  {
    DATA_TYPE_NONE = 0,
    DATA_TYPE_TWIST,
    DATA_TYPE_ODOMETRY,
    DATA_TYPE_PATH,
    DATA_TYPE_POSE_STAMPED,
    DATA_TYPE_TRANSFORM,
    DATA_TYPE_LASER_SCAN,
    DATA_TYPE_MAP,
    DATA_TYPE_TARGET_GOAL,
  }NaviDataTypes;

  typedef std::multimap<NaviDataTypes, DataProcessQueue*> DataDictionary;
  typedef DataDictionary::iterator DataDictionaryIterator;

  class Dispitcher
  {
  public:
    virtual
    ~Dispitcher ()
    {
      DataDictionaryIterator i, end;
      boost::mutex::scoped_lock lock(data_dict_lock);
      end = data_dictionary.end();
      for(i = data_dictionary.begin(); i != end; ++i)
      {
        DataProcessQueue* data_item_ptr = (*i).second;
        data_item_ptr->stopProcess();
      }
    };
    Dispitcher ()
    {};

  private:
    DataDictionary data_dictionary;
    boost::mutex data_dict_lock;

  public:
    bool initialize()
    {
      return true;
    };

    bool remap(NaviDataTypes publish_type, NaviDataTypes remap_type)
    {
      return true;
    };

    bool publish(NaviDataTypes publish_type, DataBase* publish_data)
    {
      boost::mutex::scoped_lock lock(data_dict_lock);
      std::pair<DataDictionaryIterator, DataDictionaryIterator> ranger;
      ranger = data_dictionary.equal_range(publish_type);
      for(DataDictionaryIterator it = ranger.first; it != ranger.second; ++it)
      {
        DataProcessQueue* data_item_ptr = it->second;
        if(data_item_ptr == NULL)
        {
          //throw NullPointException("Data item point is null!", data_item_ptr);
          return false;
        }
        data_item_ptr->append(publish_data);
      }
      return true;
    };

    bool subscribe(NaviDataTypes subscribe_type, boost::function<void (DataBase*)> callback)
    {
      boost::mutex::scoped_lock lock(data_dict_lock);
      DataQueue* queue = new DataQueue;
      if(queue == NULL)
      {
        //throw NullPointException("Create queue fail!", queue);
        return false;
      }
      DataProcessQueue* data_item_ptr = new DataProcessQueue();
      if(data_item_ptr == NULL)
      {
        //throw NullPointException("Create data item fail!", data_item_ptr);
        return false;
      }
      data_item_ptr->setCallback(callback);
      data_item_ptr->setFrequency(DEFAULT_DATA_PROCESS_RATE);
      data_item_ptr->startProcess();
      data_dictionary.insert(std::pair<NaviDataTypes, DataProcessQueue*>(subscribe_type, data_item_ptr));
      return true;
    };
  };

} /* namespace NS_NaviCommon */

#endif /* _DISPITCHER_H_ */
