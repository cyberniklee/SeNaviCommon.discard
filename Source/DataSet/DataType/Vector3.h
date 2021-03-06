/*
 * Vector3.h
 *
 *  Created on: 2016年9月23日
 *      Author: seeing
 */

#ifndef _DATATYPE_VECTOR3_H_
#define _DATATYPE_VECTOR3_H_

#include <string>
#include <vector>
#include <ostream>
#include <boost/shared_ptr.hpp>
#include "DataBase.h"

namespace NS_DataType
{
  
  template<class ContainerAllocator>
    struct Vector3_: public DataBase
    {
      typedef Vector3_<ContainerAllocator> Type;

      Vector3_ ()
          : x (0.0), y (0.0), z (0.0)
      {
      }
      
      Vector3_ (const ContainerAllocator& _alloc)
          : x (0.0), y (0.0), z (0.0)
      {
      }
      
      typedef double _x_type, _y_type, _z_type;

      double x, y, z;

      typedef boost::shared_ptr<Vector3_<ContainerAllocator> > Ptr;
      typedef boost::shared_ptr<Vector3_<ContainerAllocator> const> ConstPtr;
    };
  
  typedef Vector3_<std::allocator<void> > Vector3;
  
  typedef boost::shared_ptr<Vector3> Vector3Ptr;
  typedef boost::shared_ptr<Vector3 const> Vector3ConstPtr;

} /* namespace NS_NaviCommon */

#endif /* _VECTOR3_H_ */
