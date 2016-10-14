/*
 * RequestMap.h
 *
 *  Created on: 2016年10月14日
 *      Author: seeing
 */

#ifndef _SERVICETYPE_REQUESTMAP_H_
#define _SERVICETYPE_REQUESTMAP_H_

#include "RequestBase.h"

namespace NS_ServiceType
{

  template <class ContainerAllocator>
  struct RequestMap_ : public RequestBase
  {
    typedef RequestMap_<ContainerAllocator> Type;
  public:
    RequestMap_ ()
    {
    };

    RequestMap_ (const ContainerAllocator& allocator)
    {
    };

    typedef boost::shared_ptr<RequestMap_<ContainerAllocator> > Ptr;
    typedef boost::shared_ptr<RequestMap_<ContainerAllocator> const> ConstPtr;
  };

  typedef RequestMap_<std::allocator<void> > RequestMap;

  typedef boost::shared_ptr<RequestMap> RequestMapPtr;
  typedef boost::shared_ptr<RequestMap const> RequestMapConstPtr;


}

#endif /* SERVICE_SERVICETYPE_REQUESTMAP_H_ */
