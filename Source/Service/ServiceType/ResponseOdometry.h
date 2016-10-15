/*
 * ResponseOdometry.h
 *
 *  Created on: 2016年10月15日
 *      Author: seeing
 */

#ifndef _SERVICETYPE_RESPONSEODOMETRY_H_
#define _SERVICETYPE_RESPONSEODOMETRY_H_



#include "ResponseBase.h"
#include "../../DataSet/DataType/Odometry.h"

namespace NS_ServiceType
{

  template <class ContainerAllocator>
  struct ResponseOdometry_ : public ResponseBase
  {
    typedef ResponseOdometry_<ContainerAllocator> Type;
  public:
    ResponseOdometry_ () : odom()
    {
    };

    ResponseOdometry_ (const ContainerAllocator& allocator) : odom(allocator)
    {
    };

    NS_DataType::Odometry_<ContainerAllocator> odom;

    typedef boost::shared_ptr<ResponseOdometry_<ContainerAllocator> > Ptr;
    typedef boost::shared_ptr<ResponseOdometry_<ContainerAllocator> const> ConstPtr;
  };

  typedef ResponseOdometry_<std::allocator<void> > ResponseOdometry;

  typedef boost::shared_ptr<ResponseOdometry> ResponseOdometryPtr;
  typedef boost::shared_ptr<ResponseOdometry const> ResponseOdometryConstPtr;


}


#endif /* SERVICE_SERVICETYPE_RESPONSEODOMETRY_H_ */
