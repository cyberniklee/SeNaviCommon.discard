
#ifndef _TWISTSTAMPED_H_
#define _TWISTSTAMPED_H_


#include "DataBase.h"
#include "DataHeader.h"
#include "Twist.h"

namespace NS_NaviCommon
{

  template <class ContainerAllocator>
  struct TwistStamped_ : public DataBase
  {
    typedef TwistStamped_<ContainerAllocator> Type;
  public:
    TwistStamped_ () : header(), twist()
    {
    };

    TwistStamped_ (const ContainerAllocator& allocator)
    : header(allocator), twist(allocator)
    {
    };

    DataHeader_<ContainerAllocator> header;

    Twist_<ContainerAllocator> twist;

    typedef boost::shared_ptr<TwistStamped_<ContainerAllocator> > Ptr;
    typedef boost::shared_ptr<TwistStamped_<ContainerAllocator> const> ConstPtr;
  };

  typedef TwistStamped_<std::allocator<void> > TwistStamped;

  typedef boost::shared_ptr<TwistStamped> TwistStampedPtr;
  typedef boost::shared_ptr<TwistStamped const> TwistStampedConstPtr;

}

#endif /* _TWISTSTAMPED_H_ */
