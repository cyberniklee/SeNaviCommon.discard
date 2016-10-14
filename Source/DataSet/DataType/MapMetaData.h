/*
 * MapMetaData.h
 *
 *  Created on: 2016年10月13日
 *      Author: seeing
 */

#ifndef _DATATYPE_MAPMETADATA_H_
#define _DATATYPE_MAPMETADATA_H_


#include "DataBase.h"
#include "DataHeader.h"
#include "Pose.h"

namespace NS_DataType
{

  template <class ContainerAllocator>
  struct MapMetaData_ : public DataBase
  {
    typedef MapMetaData_<ContainerAllocator> Type;
  public:
    MapMetaData_ () : map_load_time(), resolution(0.0),
      width(0), height(0), origin()
    {
    };

    MapMetaData_ (const ContainerAllocator& allocator) : map_load_time(), resolution(0.0),
        width(0), height(0), origin(allocator)
    {
    };

    NS_NaviCommon::Time map_load_time;
    float resolution;
    unsigned int width;
    unsigned int height;

    Pose_<ContainerAllocator> origin;

    typedef boost::shared_ptr<MapMetaData_<ContainerAllocator> > Ptr;
    typedef boost::shared_ptr<MapMetaData_<ContainerAllocator> const> ConstPtr;
  };

  typedef MapMetaData_<std::allocator<void> > MapMetaData;

  typedef boost::shared_ptr<MapMetaData> MapMetaDataPtr;
  typedef boost::shared_ptr<MapMetaData const> MapMetaDataConstPtr;


}


#endif /* DATASET_DATATYPE_MAPMETADATA_H_ */
