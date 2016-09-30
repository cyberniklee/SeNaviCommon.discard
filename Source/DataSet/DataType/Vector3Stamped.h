/*
 * Vector3Stamped.h
 *
 *  Created on: 2016年9月23日
 *      Author: seeing
 */

#ifndef _VECTOR3STAMPED_H_
#define _VECTOR3STAMPED_H_

#include "DataBase.h"
#include "DataHeader.h"
#include "../../Geometry/Vector3.h"

namespace _Navi_Common_
{

  template <class ContainerAllocator>
  struct Vector3Stamped_ : public DataBase
  {
    typedef Vector3Stamped_<ContainerAllocator> Type;
  public:
    Vector3Stamped_ () : header(), vector()
    {
    };

    Vector3Stamped_ (const ContainerAllocator& allocator) : header(allocator), vector(allocator)
    {
    };

    DataHeader_<ContainerAllocator> header;
    Vector3_<ContainerAllocator> vector;

    typedef boost::shared_ptr<Vector3Stamped_<ContainerAllocator> > Ptr;
    typedef boost::shared_ptr<Vector3Stamped_<ContainerAllocator> const> ConstPtr;
  };

  typedef Vector3Stamped_<std::allocator<void> > Vector3Stamped;

  typedef boost::shared_ptr<Vector3Stamped> Vector3StampedPtr;
  typedef boost::shared_ptr<Vector3Stamped const> Vector3StampedConstPtr;

}



#endif /* DATASET_DATATYPE_VECTOR3STAMPED_H_ */
