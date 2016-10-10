/*
 * GoalStatusArray.h
 *
 *  Created on: 2016年10月8日
 *      Author: seeing
 */

#ifndef _GOALSTATUSARRAY_H_
#define _GOALSTATUSARRAY_H_

#include "DataBase.h"
#include "DataHeader.h"
#include <vector>

namespace _Navi_Common_
{

  template <class ContainerAllocator>
  struct GoalStatusArray_ : public DataBase
  {
    typedef GoalStatusArray_<ContainerAllocator> Type;
  public:
    GoalStatusArray_ () : header(), status_list()
    {
    };

    GoalStatusArray_ (const ContainerAllocator& allocator)
    : header(allocator), status_list(allocator)
    {
    };

    DataHeader_<ContainerAllocator> header;

    std::vector<GoalStatus_<ContainerAllocator>, typename ContainerAllocator::template rebind<GoalStatus_<ContainerAllocator> >::other> status_list;

    typedef boost::shared_ptr<GoalStatusArray_<ContainerAllocator> > Ptr;
    typedef boost::shared_ptr<GoalStatusArray_<ContainerAllocator> const> ConstPtr;
  };

  typedef GoalStatusArray_<std::allocator<void> > GoalStatusArray;

  typedef boost::shared_ptr<GoalStatusArray> GoalStatusArrayPtr;
  typedef boost::shared_ptr<GoalStatusArray const> GoalStatusArrayConstPtr;

}



#endif /* DATASET_DATATYPE_GOALSTATUSARRAY_H_ */
