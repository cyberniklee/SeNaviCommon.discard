/*
 * Transform.h
 *
 *  Created on: 2016年9月23日
 *      Author: seeing
 */

#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "DataBase.h"
#include "../../Geometry/Vector3.h"
#include "../../Geometry/Quaternion.h"

namespace _Navi_Common_
{

  template <class ContainerAllocator>
  struct Transform_ : public DataBase
  {
    typedef Transform_<ContainerAllocator> Type;
  public:
    Transform_ () : translation(), rotation()
    {
    };

    Transform_ (const ContainerAllocator& allocator) : translation(allocator), rotation(allocator)
    {
    };

    Vector3_<ContainerAllocator> translation;
    Quaternion_<ContainerAllocator> rotation;

    typedef boost::shared_ptr<Transform_<ContainerAllocator> > Ptr;
    typedef boost::shared_ptr<Transform_<ContainerAllocator> const> ConstPtr;
  };

  typedef Transform_<std::allocator<void> > Transform;

  typedef boost::shared_ptr<Transform> TransformPtr;
  typedef boost::shared_ptr<Transform const> TransformConstPtr;

}



#endif /* GEOMETRY_TRANSFORM_H_ */
