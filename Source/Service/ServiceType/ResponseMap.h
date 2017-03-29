/*
 * ResponseMap.h
 *
 *  Created on: 2016年10月14日
 *      Author: seeing
 */

#ifndef _SERVICETYPE_RESPONSEMAP_H_
#define _SERVICETYPE_RESPONSEMAP_H_

#include "ResponseBase.h"
#include "../../DataSet/DataType/OccupancyGrid.h"

namespace NS_ServiceType
{
  
  template<class ContainerAllocator>
    struct ResponseMap_: public ResponseBase
    {
      typedef ResponseMap_<ContainerAllocator> Type;
    public:
      ResponseMap_ ()
          : map ()
      {
      }
      ;

      ResponseMap_ (const ContainerAllocator& allocator)
          : map (allocator)
      {
      }
      ;

      NS_DataType::OccupancyGrid_<ContainerAllocator> map;

      typedef boost::shared_ptr<ResponseMap_<ContainerAllocator> > Ptr;
      typedef boost::shared_ptr<ResponseMap_<ContainerAllocator> const> ConstPtr;
    };
  
  typedef ResponseMap_<std::allocator<void> > ResponseMap;
  
  typedef boost::shared_ptr<ResponseMap> ResponseMapPtr;
  typedef boost::shared_ptr<ResponseMap const> ResponseMapConstPtr;

}

#endif /* SERVICE_SERVICETYPE_RESPONSEMAP_H_ */
