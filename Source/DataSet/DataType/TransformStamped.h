/*
 * TransformStamped.h
 *
 *  Created on: 2016年9月23日
 *      Author: seeing
 */

#ifndef _TRANSFORMSTAMPED_H_
#define _TRANSFORMSTAMPED_H_

#include "DataBase.h"
#include "DataHeader.h"
#include "Transform.h"

namespace NS_NaviCommon
{

  template <class ContainerAllocator>
  struct TransformStamped_ : public DataBase
  {
    typedef TransformStamped_<ContainerAllocator> Type;
  public:
    TransformStamped_ () : header(), child_frame_id(), transform()
    {
    };

    TransformStamped_ (const ContainerAllocator& allocator)
    : header(allocator), child_frame_id(allocator), transform(allocator)
    {
    };

    DataHeader_<ContainerAllocator> header;

    std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other> child_frame_id;

    Transform_<ContainerAllocator> transform;

    typedef boost::shared_ptr<TransformStamped_<ContainerAllocator> > Ptr;
    typedef boost::shared_ptr<TransformStamped_<ContainerAllocator> const> ConstPtr;
  };

  typedef TransformStamped_<std::allocator<void> > TransformStamped;

  typedef boost::shared_ptr<TransformStamped> TransformStampedPtr;
  typedef boost::shared_ptr<TransformStamped const> TransformStampedConstPtr;

}



#endif /* _TRANSFORMSTAMPED_H_ */
