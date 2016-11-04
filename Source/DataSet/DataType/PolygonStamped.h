/*
 * PolygonStamped.h
 *
 *  Created on: 2016年11月3日
 *      Author: seeing
 */

#ifndef _DATATYPE_POLYGONSTAMPED_H_
#define _DATATYPE_POLYGONSTAMPED_H_

#include "DataBase.h"
#include "DataHeader.h"
#include "Polygon.h"

namespace NS_DataType
{

  template <class ContainerAllocator>
  struct PolygonStamped_ : public DataBase
  {
    typedef PolygonStamped_<ContainerAllocator> Type;
  public:
    PolygonStamped_ () : header(), polygon()
    {
    };

    PolygonStamped_ (const ContainerAllocator& allocator) : header(allocator), polygon(allocator)
    {
    };

    DataHeader_<ContainerAllocator> header;
    Polygon_<ContainerAllocator> polygon;

    typedef boost::shared_ptr<PolygonStamped_<ContainerAllocator> > Ptr;
    typedef boost::shared_ptr<PolygonStamped_<ContainerAllocator> const> ConstPtr;
  };

  typedef PolygonStamped_<std::allocator<void> > PolygonStamped;

  typedef boost::shared_ptr<PolygonStamped> PolygonStampedPtr;
  typedef boost::shared_ptr<PolygonStamped const> PolygonStampedConstPtr;


}



#endif /* DATASET_DATATYPE_POLYGONSTAMPED_H_ */
