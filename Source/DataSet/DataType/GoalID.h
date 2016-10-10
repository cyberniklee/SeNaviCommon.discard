/*
 * GoalID.h
 *
 *  Created on: 2016年10月8日
 *      Author: seeing
 */

#ifndef _GOALID_H_
#define _GOALID_H_

#include "DataBase.h"
#include "DataHeader.h"

namespace _Navi_Common_
{

  template <class ContainerAllocator>
  struct GoalID_ : public DataBase
  {
    typedef GoalID_<ContainerAllocator> Type;
  public:
    GoalID_ () : stamp(), id()
    {
    };

    GoalID_ (const ContainerAllocator& allocator) : stamp(), id(allocator)
    {
    };

    Time stamp;
    std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other> id;

    typedef boost::shared_ptr<GoalID_<ContainerAllocator> > Ptr;
    typedef boost::shared_ptr<GoalID_<ContainerAllocator> const> ConstPtr;
  };

  typedef GoalID_<std::allocator<void> > GoalID;

  typedef boost::shared_ptr<GoalID> GoalIDPtr;
  typedef boost::shared_ptr<GoalID const> GoalIDConstPtr;


}



#endif /* DATASET_DATATYPE_GOALID_H_ */
