/*
 * GoalPose.h
 *
 *  Created on: Jul 19, 2017
 *      Author: root
 */

#ifndef _GOALTYPE_GOALPOSE_H_
#define _GOALTYPE_GOALPOSE_H_

#include "GoalBase.h"
#include "../../DataSet/DataType/PoseStamped.h"

namespace NS_GoalType
{

  template<class ContainerAllocator>
    struct GoalPose_: public GoalBase
    {
      typedef GoalPose_<ContainerAllocator> Type;
    public:
      GoalPose_ ()
          : target ()
      {
      }
      ;

      GoalPose_ (const ContainerAllocator& allocator)
          : target (allocator)
      {
      }
      ;

      NS_DataType::PoseStamped_<ContainerAllocator> target;

      typedef boost::shared_ptr<GoalPose_<ContainerAllocator> > Ptr;
      typedef boost::shared_ptr<GoalPose_<ContainerAllocator> const> ConstPtr;
    };

  typedef GoalPose_<std::allocator<void> > GoalPose;

  typedef boost::shared_ptr<GoalPose> RequestMapPtr;
  typedef boost::shared_ptr<GoalPose const> RequestMapConstPtr;

}


#endif /* MISSION_GOALTYPE_GOALPOSE_H_ */
