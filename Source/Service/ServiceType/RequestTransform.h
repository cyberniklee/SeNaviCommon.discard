/*
 * RequestTransform.h
 *
 *  Created on: 2016年10月22日
 *      Author: seeing
 */

#ifndef _SERVICETYPE_REQUESTTRANSFORM_H_
#define _SERVICETYPE_REQUESTTRANSFORM_H_

#include "RequestBase.h"

namespace NS_ServiceType
{

  template <class ContainerAllocator>
  struct RequestTransform_ : public RequestBase
  {
    typedef RequestTransform_<ContainerAllocator> Type;
  public:
    RequestTransform_ ()
    {
    };

    RequestTransform_ (const ContainerAllocator& allocator)
    {
    };

    typedef boost::shared_ptr<RequestTransform_<ContainerAllocator> > Ptr;
    typedef boost::shared_ptr<RequestTransform_<ContainerAllocator> const> ConstPtr;
  };

  typedef RequestTransform_<std::allocator<void> > RequestTransform;

  typedef boost::shared_ptr<RequestTransform> RequestTransformPtr;
  typedef boost::shared_ptr<RequestTransform const> RequestTransformConstPtr;


}



#endif /* SERVICE_SERVICETYPE_REQUESTTRANSFORM_H_ */
