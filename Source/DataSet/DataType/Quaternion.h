/*
 * Quaternion.h
 *
 *  Created on: 2016年8月23日
 *      Author: seeing
 */

#ifndef _DATATYPE_QUATERNION_H_
#define _DATATYPE_QUATERNION_H_

#include <string>
#include <vector>
#include <ostream>
#include <boost/shared_ptr.hpp>
#include "DataBase.h"

namespace NS_DataType
{
  
  template<class ContainerAllocator>
    struct Quaternion_: public DataBase
    {
      typedef Quaternion_<ContainerAllocator> Type;

      Quaternion_ ()
          : x (0.0), y (0.0), z (0.0), w (0.0)
      {
      }
      
      Quaternion_ (const ContainerAllocator& _alloc)
          : x (0.0), y (0.0), z (0.0), w (0.0)
      {
      }
      
      typedef double _x_type, _y_type, _z_type, _w_type;

      double x, y, z, w;

      typedef boost::shared_ptr<Quaternion_<ContainerAllocator> > Ptr;
      typedef boost::shared_ptr<Quaternion_<ContainerAllocator> const> ConstPtr;
    };
  
  typedef Quaternion_<std::allocator<void> > Quaternion;
  
  typedef boost::shared_ptr<Quaternion> QuaternionPtr;
  typedef boost::shared_ptr<Quaternion const> QuaternionConstPtr;

} /* namespace NS_NaviCommon */

#endif /* GEOMETRY_QUATERNION_H_ */
