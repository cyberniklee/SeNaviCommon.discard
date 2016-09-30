/*
 * PoseStamped.h
 *
 *  Created on: 2016年9月23日
 *      Author: seeing
 */

#ifndef _POSESTAMPED_H_
#define _POSESTAMPED_H_


#include "DataBase.h"
#include "DataHeader.h"
#include "Pose.h"

namespace _Navi_Common_
{

  template <class ContainerAllocator>
  struct PoseStamped_ : public DataBase
  {
    typedef PoseStamped_<ContainerAllocator> Type;
  public:
    PoseStamped_ () : header(), pose()
    {
    };

    PoseStamped_ (const ContainerAllocator& allocator) : header(allocator), pose(allocator)
    {
    };

    DataHeader_<ContainerAllocator> header;
    Pose_<ContainerAllocator> pose;

    typedef boost::shared_ptr<PoseStamped_<ContainerAllocator> > Ptr;
    typedef boost::shared_ptr<PoseStamped_<ContainerAllocator> const> ConstPtr;
  };

  typedef PoseStamped_<std::allocator<void> > PoseStamped;

  typedef boost::shared_ptr<PoseStamped> PoseStampedPtr;
  typedef boost::shared_ptr<PoseStamped const> PoseStampedConstPtr;


}



#endif /* _POSESTAMPED_H_ */
