/*
 * RequestOdometry.h
 *
 *  Created on: 2016年10月15日
 *      Author: seeing
 */

#ifndef _SERVICETYPE_REQUESTODOMETRY_H_
#define _SERVICETYPE_REQUESTODOMETRY_H_

#include "RequestBase.h"

namespace NS_ServiceType
{
  
  template<class ContainerAllocator>
    struct RequestOdometry_: public RequestBase
    {
      typedef RequestOdometry_<ContainerAllocator> Type;
    public:
      RequestOdometry_ ()
      {
      }
      ;

      RequestOdometry_ (const ContainerAllocator& allocator)
      {
      }
      ;

      typedef boost::shared_ptr<RequestOdometry_<ContainerAllocator> > Ptr;
      typedef boost::shared_ptr<RequestOdometry_<ContainerAllocator> const> ConstPtr;
    };
  
  typedef RequestOdometry_<std::allocator<void> > RequestOdometry;
  
  typedef boost::shared_ptr<RequestOdometry> RequestOdometryPtr;
  typedef boost::shared_ptr<RequestOdometry const> RequestOdometryConstPtr;

}

#endif /* SERVICE_SERVICETYPE_REQUESTODOMETRY_H_ */
