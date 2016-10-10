/*
 * PointCloud.h
 *
 *  Created on: 2016年9月28日
 *      Author: seeing
 */

#ifndef _POINTCLOUD_H_
#define _POINTCLOUD_H_

#include "DataBase.h"
#include "DataHeader.h"
#include "Point32.h"
#include "ChannelFloat32.h"

namespace NS_NaviCommon
{

  template <class ContainerAllocator>
  struct PointCloud_ : public DataBase
  {
    typedef PointCloud_<ContainerAllocator> Type;
  public:
    PointCloud_ () : header(), points(), channels()
    {
    };

    PointCloud_ (const ContainerAllocator& allocator) : header(allocator), points(allocator), channels(allocator)
    {
    };

    DataHeader_<ContainerAllocator> header;
    std::vector<Point32_<ContainerAllocator>, typename ContainerAllocator::template rebind<Point32_<ContainerAllocator> >::other> points;
    std::vector<ChannelFloat32_<ContainerAllocator>, typename ContainerAllocator::template rebind<ChannelFloat32_<ContainerAllocator> >::other> channels;

    typedef boost::shared_ptr<PointCloud_<ContainerAllocator> > Ptr;
    typedef boost::shared_ptr<PointCloud_<ContainerAllocator> const> ConstPtr;
  };

  typedef PointCloud_<std::allocator<void> > PointCloud;

  typedef boost::shared_ptr<PointCloud> PointCloudPtr;
  typedef boost::shared_ptr<PointCloud const> PointCloudConstPtr;


}



#endif /* _POINTCLOUD_H_ */
