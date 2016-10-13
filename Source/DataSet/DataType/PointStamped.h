/*
 * PointStamped.h
 *
 *  Created on: 2016年9月23日
 *      Author: seeing
 */

#ifndef _DATATYPE_POINTSTAMPED_H_
#define _DATATYPE_POINTSTAMPED_H_

#include "DataBase.h"
#include "DataHeader.h"
#include "Point.h"

namespace NS_DataType
{

  template <class ContainerAllocator>
  struct PointStamped_ : public DataBase
  {
    typedef PointStamped_<ContainerAllocator> Type;
  public:
    PointStamped_ () : header(), point()
    {
    };

    PointStamped_ (const ContainerAllocator& allocator) : header(allocator), point(allocator)
    {
    };

    DataHeader_<ContainerAllocator> header;
    Point_<ContainerAllocator> point;

    typedef boost::shared_ptr<PointStamped_<ContainerAllocator> > Ptr;
    typedef boost::shared_ptr<PointStamped_<ContainerAllocator> const> ConstPtr;
  };

  typedef PointStamped_<std::allocator<void> > PointStamped;

  typedef boost::shared_ptr<PointStamped> PointStampedPtr;
  typedef boost::shared_ptr<PointStamped const> PointStampedConstPtr;


}



#endif /* _POINTSTAMPED_H_ */
