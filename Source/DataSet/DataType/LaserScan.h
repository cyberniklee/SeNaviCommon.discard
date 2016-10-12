/*
 * LaserScan.h
 *
 *  Created on: 2016年9月28日
 *      Author: seeing
 */

#ifndef _LASERSCAN_H_
#define _LASERSCAN_H_

#include "DataBase.h"
#include "DataHeader.h"

namespace NS_NaviCommon
{

  template <class ContainerAllocator>
  struct LaserScan_ : public DataBase
  {
    typedef LaserScan_<ContainerAllocator> Type;
  public:
    LaserScan_ () : header(), angle_min(0.0), angle_max(0.0),
      angle_increment(0.0), time_increment(0.0), scan_time(0.0),
      range_min(0.0), range_max(0.0), ranges(), intensities()
    {
    };

    LaserScan_ (const ContainerAllocator& allocator) : header(allocator), angle_min(0.0), angle_max(0.0),
      angle_increment(0.0), time_increment(0.0), scan_time(0.0),
      range_min(0.0), range_max(0.0), ranges(allocator), intensities(allocator)
    {
    };

    DataHeader_<ContainerAllocator> header;
    float angle_min;
    float angle_max;
    float angle_increment;
    float time_increment;
    float scan_time;
    float range_min;
    float range_max;

    std::vector<float, typename ContainerAllocator::template rebind<float>::other> ranges;
    std::vector<float, typename ContainerAllocator::template rebind<float>::other> intensities;

    typedef boost::shared_ptr<LaserScan_<ContainerAllocator> > Ptr;
    typedef boost::shared_ptr<LaserScan_<ContainerAllocator> const> ConstPtr;
  };

  typedef LaserScan_<std::allocator<void> > LaserScan;

  typedef boost::shared_ptr<LaserScan> LaserScanPtr;
  typedef boost::shared_ptr<LaserScan const> LaserScanConstPtr;


}



#endif /* _LASERSCAN_H_ */
