/*
 * Point.h
 *
 *  Created on: 2016年8月18日
 *      Author: seeing
 */

#ifndef _POINT_H_
#define _POINT_H_

#include <string>
#include <vector>
#include <ostream>
#include <boost/shared_ptr.hpp>

namespace _Navi_Common_ {

template <class ContainerAllocator>
struct Point_
{
	typedef Point_<ContainerAllocator> Type;

	Point_(): x(0.0), y(0.0), z(0.0)
	{
	}

	Point_(const ContainerAllocator& _alloc): x(0.0), y(0.0), z(0.0)
	{
	}

	typedef double _x_type, _y_type, _z_type;

	double x, y, z;

	typedef boost::shared_ptr<Point_<ContainerAllocator> > Ptr;
	typedef boost::shared_ptr<Point_<ContainerAllocator> const> ConstPtr;
};

typedef Point_<std::allocator<void> > Point;

typedef boost::shared_ptr<Point> PointPtr;
typedef boost::shared_ptr<Point const> PointConstPtr;

}

#endif /* _POINT_H_ */
