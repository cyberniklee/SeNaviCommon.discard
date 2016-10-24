/*
 * ResponseTransform.h
 *
 *  Created on: 2016年10月22日
 *      Author: seeing
 */

#ifndef _SERVICETYPE_RESPONSETRANSFORM_H_
#define _SERVICETYPE_RESPONSETRANSFORM_H_

#include "ResponseBase.h"
#include "../../DataSet/DataType/Transform.h"

namespace NS_ServiceType
{

  template <class ContainerAllocator>
  struct ResponseTransform_ : public ResponseBase
  {
    typedef ResponseTransform_<ContainerAllocator> Type;
  public:
    ResponseTransform_ () : transform()
    {
    };

    ResponseTransform_ (const ContainerAllocator& allocator) : transform(allocator)
    {
    };

    NS_DataType::Transform_<ContainerAllocator> transform;

    typedef boost::shared_ptr<ResponseTransform_<ContainerAllocator> > Ptr;
    typedef boost::shared_ptr<ResponseTransform_<ContainerAllocator> const> ConstPtr;
  };

  typedef ResponseTransform_<std::allocator<void> > ResponseTransform;

  typedef boost::shared_ptr<ResponseTransform> ResponseTransformPtr;
  typedef boost::shared_ptr<ResponseTransform const> ResponseTransformConstPtr;


}



#endif /* SERVICE_SERVICETYPE_RESPONSETRANSFORM_H_ */
