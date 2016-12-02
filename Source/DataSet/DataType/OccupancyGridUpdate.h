/*
 * OccupancyGridUpdate.h
 *
 *  Created on: 2016年11月4日
 *      Author: seeing
 */

#ifndef _DATATYPE_OCCUPANCYGRIDUPDATE_H_
#define _DATATYPE_OCCUPANCYGRIDUPDATE_H_

#include "DataBase.h"
#include "DataHeader.h"

namespace NS_DataType
{

  template <class ContainerAllocator>
  struct OccupancyGridUpdate_ : public DataBase
  {
    typedef OccupancyGridUpdate_<ContainerAllocator> Type;
  public:
    OccupancyGridUpdate_ () : header(), x(0), y(0), width(0), height(0), data()
    {
    };

    OccupancyGridUpdate_ (const ContainerAllocator& allocator) : header(allocator),
        x(0), y(0), width(0), height(0), data(allocator)
    {
    };

    DataHeader_<ContainerAllocator> header;

    int x;
    int y;

    unsigned int width;
    unsigned int height;

    std::vector<char, typename ContainerAllocator::template rebind<char>::other> data;

    typedef boost::shared_ptr<OccupancyGridUpdate_<ContainerAllocator> > Ptr;
    typedef boost::shared_ptr<OccupancyGridUpdate_<ContainerAllocator> const> ConstPtr;
  };

  typedef OccupancyGridUpdate_<std::allocator<void> > OccupancyGridUpdate;

  typedef boost::shared_ptr<OccupancyGridUpdate> OccupancyGridUpdatePtr;
  typedef boost::shared_ptr<OccupancyGridUpdate const> OccupancyGridUpdateConstPtr;


}




#endif /* DATASET_DATATYPE_OCCUPANCYGRIDUPDATE_H_ */
