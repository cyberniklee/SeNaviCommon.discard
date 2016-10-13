/*
 * TransformData.h
 *
 *  Created on: 2016年9月28日
 *      Author: seeing
 */

#ifndef _DATATYPE_TRANSFORMDATA_H_
#define _DATATYPE_TRANSFORMDATA_H_

#include "DataBase.h"
#include "TransformStamped.h"


namespace NS_DataType
{

  template <class ContainerAllocator>
  struct TransformData_ : public DataBase
  {
    typedef TransformData_<ContainerAllocator> Type;
  public:
    TransformData_ () : transforms()
    {
    };

    TransformData_ (const ContainerAllocator& allocator) : transforms(allocator)
    {
    };

    std::vector<TransformStamped_<ContainerAllocator>, typename ContainerAllocator::template rebind<TransformStamped_<ContainerAllocator> >::other> transforms;

    typedef boost::shared_ptr<TransformData_<ContainerAllocator> > Ptr;
    typedef boost::shared_ptr<TransformData_<ContainerAllocator> const> ConstPtr;
  };

  typedef TransformData_<std::allocator<void> > TransformData;

  typedef boost::shared_ptr<TransformData> TransformDataPtr;
  typedef boost::shared_ptr<TransformData const> TransformDataConstPtr;


}



#endif /* DATASET_DATATYPE_TRANSFORMDATA_H_ */
