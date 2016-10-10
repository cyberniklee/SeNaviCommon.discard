/*
 * GoalStatus.h
 *
 *  Created on: 2016年10月8日
 *      Author: seeing
 */

#ifndef _GOALSTATUS_H_
#define _GOALSTATUS_H_

#include "DataBase.h"
#include "GoalID.h"

namespace _Navi_Common_
{

  template <class ContainerAllocator>
  struct GoalStatus_ : public DataBase
  {
    typedef GoalStatus_<ContainerAllocator> Type;
  public:
    GoalStatus_ () : goal_id(), status(0), text()
    {
    };

    GoalStatus_ (const ContainerAllocator& allocator)
    : goal_id(allocator), status(0), text(allocator)
    {
    };

    GoalID_<ContainerAllocator> goal_id;

    unsigned char status;

    std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other> text;

    enum {  PENDING         = 0 };   // The goal has yet to be processed by the action server
    enum {  ACTIVE          = 1 };   // The goal is currently being processed by the action server
    enum {  PREEMPTED       = 2 };   // The goal received a cancel request after it started executing
    enum {  SUCCEEDED       = 3 };   // The goal was achieved successfully by the action server (Terminal State)
    enum {  ABORTED         = 4 };   // The goal was aborted during execution by the action server due
    enum {  REJECTED        = 5 };   // The goal was rejected by the action server without being processed,
    enum {  PREEMPTING      = 6 };   // The goal received a cancel request after it started executing
    enum {  RECALLING       = 7 };   // The goal received a cancel request before it started executing,
    enum {  RECALLED        = 8 };   // The goal received a cancel request before it started executing
    enum {  LOST            = 9 };

    typedef boost::shared_ptr<GoalStatus_<ContainerAllocator> > Ptr;
    typedef boost::shared_ptr<GoalStatus_<ContainerAllocator> const> ConstPtr;
  };

  typedef GoalStatus_<std::allocator<void> > GoalStatus;

  typedef boost::shared_ptr<GoalStatus> GoalStatusPtr;
  typedef boost::shared_ptr<GoalStatus const> GoalStatusConstPtr;

}




#endif /* DATASET_DATATYPE_GOALSTATUS_H_ */
