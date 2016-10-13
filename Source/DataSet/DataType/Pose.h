/*
 * Pose.h
 *
 *  Created on: 2016年9月23日
 *      Author: seeing
 */

#ifndef _DATATYPE_POSE_H_
#define _DATATYPE_POSE_H_

#include "DataBase.h"
#include "Point.h"
#include "Quaternion.h"

namespace NS_DataType
{

  template <class ContainerAllocator>
  struct Pose_ : public DataBase
  {
    typedef Pose_<ContainerAllocator> Type;
  public:
    Pose_ () : position(), orientation()
    {
    };

    Pose_ (const ContainerAllocator& allocator) : position(allocator), orientation(allocator)
    {
    };

    Point_<ContainerAllocator> position;
    Quaternion_<ContainerAllocator> orientation;

    typedef boost::shared_ptr<Pose_<ContainerAllocator> > Ptr;
    typedef boost::shared_ptr<Pose_<ContainerAllocator> const> ConstPtr;
  };

  typedef Pose_<std::allocator<void> > Pose;

  typedef boost::shared_ptr<Pose> PosePtr;
  typedef boost::shared_ptr<Pose const> PoseConstPtr;

}



#endif /* _POSE_H_ */
