/*
 * Polygon.h
 *
 *  Created on: 2016年11月3日
 *      Author: seeing
 */

#ifndef _DATATYPE_POLYGON_H_
#define _DATATYPE_POLYGON_H_

#include "DataBase.h"
#include "DataHeader.h"
#include "Point32.h"

namespace NS_DataType
{

  template <class ContainerAllocator>
  struct Polygon_ : public DataBase
  {
    typedef Polygon_<ContainerAllocator> Type;
  public:
    Polygon_ () : points()
    {
    };

    Polygon_ (const ContainerAllocator& allocator) : points(allocator)
    {
    };

    std::vector<Point32_<ContainerAllocator>, typename ContainerAllocator::template rebind<Point32_<ContainerAllocator> >::other> points;

    typedef boost::shared_ptr<Polygon_<ContainerAllocator> > Ptr;
    typedef boost::shared_ptr<Polygon_<ContainerAllocator> const> ConstPtr;
  };

  typedef Polygon_<std::allocator<void> > Polygon;

  typedef boost::shared_ptr<Polygon> PolygonPtr;
  typedef boost::shared_ptr<Polygon const> PolygonConstPtr;


}





#endif /* DATASET_DATATYPE_POLYGON_H_ */
