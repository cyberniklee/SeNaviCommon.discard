/*
 * Dispitcher.cpp
 *
 *  Created on: 2016年9月12日
 *      Author: seeing
 */

#include "Dispitcher.h"
#include "../Console/Console.h"

namespace _Navi_Common_
{
  
  Dispitcher::~Dispitcher ()
  {
    // TODO Auto-generated destructor stub

  }
  
  Dispitcher::Dispitcher ()
  {
    // TODO Auto-generated constructor stub
    
  }

  bool Dispitcher::initialize()
  {
    DataDictionaryIterator i, end;
    boost::mutex::scoped_lock lock(data_dict_lock);
    end = data_dictionary.end();
    for(i = data_dictionary.begin(); i != end; ++i)
    {
      NaviDataItemPtr data_item_ptr = (*i).second;
      data_item_ptr->stopProcess();
    }
    return true;
  }

  template <typename M>
  bool Dispitcher::publish(NaviDataTypes publish_type, M* publish_data)
  {
    boost::mutex::scoped_lock lock(data_dict_lock);
    std::pair<DataDictionaryIterator, DataDictionaryIterator> ranger;
    ranger = data_dictionary.equal_range(publish_type);
    for(DataDictionaryIterator it = ranger.first; it != ranger.second; ++it)
    {
      NaviDataItemPtr data_item_ptr = it->second;
      if(data_item_ptr == NULL)
      {
        throw NullPointException("Data item point is null!", data_item_ptr);
        return false;
      }
      data_item_ptr->append(publish_data);
    }
    return true;
  }

  template <class M, class C, typename R, typename P>
  bool Dispitcher::subscribe(NaviDataTypes subscribe_type, CallbackClass<C, R, P>* callback)
  {
    boost::mutex::scoped_lock lock(data_dict_lock);
    DataQueue<M>* queue = new DataQueue<M>;
    if(queue == NULL)
    {
      throw NullPointException("Create queue fail!", queue);
      return false;
    }
    NaviDataItemPtr data_item_ptr = new DataProcessQueue<M, C, R, P>(callback);
    if(data_item_ptr == NULL)
    {
      throw NullPointException("Create data item fail!", data_item_ptr);
      return false;
    }
    data_item_ptr->startProcess();
    data_dictionary.insert(std::pair<NaviDataTypes, NaviDataItemPtr>(subscribe_type, data_item_ptr));
    return true;
  }

} /* namespace _Navi_Common_ */
