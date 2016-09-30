/*
 * Point32.h
 *
 *  Created on: 2016年9月28日
 *      Author: seeing
 */

#ifndef _POINT32_H_
#define _POINT32_H_

#include <string>
#include <vector>
#include "../../Time/Time.h"
#include "DataBase.h"

namespace _Navi_Common_
{
  template <class ContainerAllocator>
  struct Point32_ : public DataBase
  {
    typedef Point32_<ContainerAllocator> Type;
  public:
    Point32_ () : x(0.0), y(0.0), z(0.0)
    {
    };

    Point32_ (const ContainerAllocator& allocator) : x(0.0), y(0.0), z(0.0)
    {
    };

    float x, y, z;

    typedef boost::shared_ptr<Point32_<ContainerAllocator> > Ptr;
    typedef boost::shared_ptr<Point32_<ContainerAllocator> const> ConstPtr;
  };

  typedef Point32_<std::allocator<void> > Point32;

  typedef boost::shared_ptr<Point32> Point32Ptr;
  typedef boost::shared_ptr<Point32 const> Point32ConstPtr;

} /* namespace _Navi_Common_ */



#endif /* _POINT32_H_ */
