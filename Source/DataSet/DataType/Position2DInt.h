/*
 * Position2DInt.h
 *
 *  Created on: 2016年8月18日
 *      Author: seeing
 */

#ifndef _DATATYPE_POSITION2DINT_H_
#define _DATATYPE_POSITION2DINT_H_

#include <string>
#include <vector>
#include <ostream>
#include <boost/shared_ptr.hpp>
#include "DataBase.h"

namespace NS_DataType
{
  
  template<class ContainerAllocator>
    struct Position2DInt_: public DataBase
    {
      typedef Position2DInt_<ContainerAllocator> Type;

      Position2DInt_ ()
          : x (0), y (0)
      {
      }
      
      Position2DInt_ (const ContainerAllocator& _alloc)
          : x (0), y (0)
      {
      }
      
      typedef long long _x_type, _y_type;

      long long x, y;

      typedef boost::shared_ptr<Position2DInt_<ContainerAllocator> > Ptr;
      typedef boost::shared_ptr<Position2DInt_<ContainerAllocator> const> ConstPtr;
    };
  
  typedef Position2DInt_<std::allocator<void> > Position2DInt;
  
  typedef boost::shared_ptr<Point> Position2DIntPtr;
  typedef boost::shared_ptr<Point const> Position2DIntConstPtr;

}

#endif /* _Position2DInt_H_ */
