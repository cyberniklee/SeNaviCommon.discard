/*
 * Twist.h
 *
 *  Created on: 2016年9月24日
 *      Author: seeing
 */

#ifndef _DATATYPE_TWIST_H_
#define _DATATYPE_TWIST_H_

#include "DataBase.h"
#include "Vector3.h"

namespace NS_DataType
{

  template <class ContainerAllocator>
  struct Twist_ : public DataBase
  {
    typedef Twist_<ContainerAllocator> Type;
  public:
    Twist_ () : linear(), angular()
    {
    };

    Twist_ (const ContainerAllocator& allocator) : linear(allocator), angular(allocator)
    {
    };

    Vector3_<ContainerAllocator> linear;
    Vector3_<ContainerAllocator> angular;

    typedef boost::shared_ptr<Twist_<ContainerAllocator> > Ptr;
    typedef boost::shared_ptr<Twist_<ContainerAllocator> const> ConstPtr;
  };

  typedef Twist_<std::allocator<void> > Twist;

  typedef boost::shared_ptr<Twist> TwistPtr;
  typedef boost::shared_ptr<Twist const> TwistConstPtr;

}

#endif /* _TWIST_H_ */
