/*
 * OccupancyGrid.h
 *
 *  Created on: 2016年10月14日
 *      Author: seeing
 */

#ifndef _DATATYPE_OCCUPANCYGRID_H_
#define _DATATYPE_OCCUPANCYGRID_H_

#include "DataBase.h"
#include "DataHeader.h"
#include "MapMetaData.h"

namespace NS_DataType
{
  
  template<class ContainerAllocator>
    struct OccupancyGrid_: public DataBase
    {
      typedef OccupancyGrid_<ContainerAllocator> Type;
    public:
      OccupancyGrid_ ()
          : header (), info (), data ()
      {
      }
      ;

      OccupancyGrid_ (const ContainerAllocator& allocator)
          : header (allocator), info (allocator), data (allocator)
      {
      }
      ;

      DataHeader_<ContainerAllocator> header;
      MapMetaData_<ContainerAllocator> info;

      std::vector<char,
          typename ContainerAllocator::template rebind<char>::other> data;

      typedef boost::shared_ptr<OccupancyGrid_<ContainerAllocator> > Ptr;
      typedef boost::shared_ptr<OccupancyGrid_<ContainerAllocator> const> ConstPtr;
    };
  
  typedef OccupancyGrid_<std::allocator<void> > OccupancyGrid;
  
  typedef boost::shared_ptr<OccupancyGrid> OccupancyGridPtr;
  typedef boost::shared_ptr<OccupancyGrid const> OccupancyGridConstPtr;

}

#endif /* DATASET_DATATYPE_OCCUPANCYGRID_H_ */
