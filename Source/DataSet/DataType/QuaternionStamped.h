/*
 * QuaternionStamped.h
 *
 *  Created on: 2016年9月23日
 *      Author: seeing
 */

#ifndef _QUATERNIONSTAMPED_H_
#define _QUATERNIONSTAMPED_H_



#include "DataBase.h"
#include "../../Geometry/Quaternion.h"

namespace _Navi_Common_
{

  template <class ContainerAllocator>
  struct QuaternionStamped_ : public DataBase
  {
    typedef QuaternionStamped_<ContainerAllocator> Type;
  public:
    QuaternionStamped_ () : header(), quaternion()
    {
    };

    QuaternionStamped_ (const ContainerAllocator& allocator) : header(allocator), quaternion(allocator)
    {
    };

    DataHeader_<ContainerAllocator> header;
    Quaternion_<ContainerAllocator> quaternion;

    typedef boost::shared_ptr<QuaternionStamped_<ContainerAllocator> > Ptr;
    typedef boost::shared_ptr<QuaternionStamped_<ContainerAllocator> const> ConstPtr;
  };

  typedef QuaternionStamped_<std::allocator<void> > QuaternionStamped;

  typedef boost::shared_ptr<QuaternionStamped> QuaternionStampedPtr;
  typedef boost::shared_ptr<QuaternionStamped const> QuaternionStampedConstPtr;

}




#endif /* DATASET_DATATYPE_QUATERNIONSTAMPED_H_ */
