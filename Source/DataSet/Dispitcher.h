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
#include "DataProcessQueue.h"
#include "../Common/Declare.h"

namespace _Navi_Common_
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
  }NaviDataTypes;

  typedef DataProcessQueue<std::allocator<void>, std::allocator<void>, std::allocator<void>, std::allocator<void> > NaviDataItemType;
  typedef NaviDataItemType* NaviDataItemPtr;

  typedef std::multimap<NaviDataTypes, NaviDataItemPtr> DataDictionary;
  typedef DataDictionary::iterator DataDictionaryIterator;

  class Dispitcher
  {
  public:
    virtual
    ~Dispitcher ();
    Dispitcher ();

  private:
    DataDictionary data_dictionary;
    boost::mutex data_dict_lock;

  public:
    bool initialize();

    bool remap(NaviDataTypes publish_type, NaviDataTypes remap_type);

    template <typename M>
    bool publish(NaviDataTypes publish_type, M* publish_data);

    template <class M, class C, typename R, typename P>
    bool subscribe(NaviDataTypes subscribe_type, CallbackClass<C, R, P>* callback);

  };

} /* namespace _Navi_Common_ */

#endif /* _DISPITCHER_H_ */
