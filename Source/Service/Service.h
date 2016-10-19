/*
 * Service.h
 *
 *  Created on: 2016年9月21日
 *      Author: seeing
 */

#ifndef SERVICE_SERVICE_H_
#define SERVICE_SERVICE_H_

#include <map>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include "ServiceType/RequestBase.h"
#include "ServiceType/ResponseBase.h"

namespace NS_NaviCommon
{
  
  typedef enum
  {
    SERVICE_TYPE_NONE = 0,
    SERVICE_TYPE_MAP,
    SERVICE_TYPE_RAW_ODOMETRY,
    SERVICE_TYPE_IMU_ODOMETRY,
    SERVICE_TYPE_START_SCAN,
    SERVICE_TYPE_STOP_SCAN,
  }NaviServiceTypes;

  typedef boost::function<void (NS_ServiceType::RequestBase*, NS_ServiceType::ResponseBase*)> ServiceEntryType;

  typedef std::multimap<NaviServiceTypes, ServiceEntryType> ServiceDictionary;
  typedef ServiceDictionary::iterator ServiceDictionaryIterator;

  class Service
  {
  public:
    Service (){};
    virtual
    ~Service (){};
  private:
    ServiceDictionary service_dictionary;
    boost::mutex service_dict_lock;
  public:
    bool initialize()
    {

      return true;
    }

    bool advertise(NaviServiceTypes service_type, ServiceEntryType service_entry)
    {
      boost::mutex::scoped_lock lock(service_dict_lock);
      service_dictionary.insert(std::pair<NaviServiceTypes, ServiceEntryType>(service_type, service_entry));
      return true;
    };

    bool call(NaviServiceTypes service_type, NS_ServiceType::RequestBase* request, NS_ServiceType::ResponseBase* response)
    {
      boost::mutex::scoped_lock lock(service_dict_lock);
      std::pair<ServiceDictionaryIterator, ServiceDictionaryIterator> ranger;
      ranger = service_dictionary.equal_range(service_type);
      for(ServiceDictionaryIterator it = ranger.first; it != ranger.second; ++it)
      {
        ServiceEntryType entry = it->second;
        if(entry == NULL)
        {
          //throw NullPointException("Entry point is null!", entry);
          return false;
        }
        boost::thread(boost::bind(entry, request, response));
      }
      return true;
    };
  };

} /* namespace NS_NaviCommon */

#endif /* SERVICE_SERVICE_H_ */
