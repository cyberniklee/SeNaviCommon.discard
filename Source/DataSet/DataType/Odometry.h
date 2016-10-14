/*
 * Odometry.h
 *
 *  Created on: 2016年10月14日
 *      Author: seeing
 */

#ifndef _DATATYPE_ODOMETRY_H_
#define _DATATYPE_ODOMETRY_H_


#include "DataBase.h"
#include "DataHeader.h"
#include "Pose.h"
#include "Twist.h"

namespace NS_DataType
{

  template <class ContainerAllocator>
  struct Odometry_ : public DataBase
  {
    typedef Odometry_<ContainerAllocator> Type;
  public:
    Odometry_ () : header(), pose(), twist()
    {
    };

    Odometry_ (const ContainerAllocator& allocator) : header(allocator), pose(allocator), twist(allocator)
    {
    };

    DataHeader_<ContainerAllocator> header;
    Pose_<ContainerAllocator> pose;
    Twist_<ContainerAllocator> twist;

    typedef boost::shared_ptr<Odometry_<ContainerAllocator> > Ptr;
    typedef boost::shared_ptr<Odometry_<ContainerAllocator> const> ConstPtr;
  };

  typedef Odometry_<std::allocator<void> > Odometry;

  typedef boost::shared_ptr<Odometry> OdometryPtr;
  typedef boost::shared_ptr<Odometry const> OdometryConstPtr;


}


#endif /* DATASET_DATATYPE_ODOMETRY_H_ */
