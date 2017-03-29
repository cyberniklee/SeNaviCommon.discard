/*
 * Path.h
 *
 *  Created on: 2016年12月12日
 *      Author: seeing
 */

#ifndef _DATATYPE_PATH_H_
#define _DATATYPE_PATH_H_

#include "DataBase.h"
#include "DataHeader.h"
#include "PoseStamped.h"

namespace NS_DataType
{
  
  template<class ContainerAllocator>
    struct Path_: public DataBase
    {
      typedef Path_<ContainerAllocator> Type;
    public:
      Path_ ()
          : header (), poses ()
      {
      }
      ;

      Path_ (const ContainerAllocator& allocator)
          : header (allocator), poses (allocator)
      {
      }
      ;

      DataHeader_<ContainerAllocator> header;
      std::vector<PoseStamped_<ContainerAllocator>,
          typename ContainerAllocator::template rebind<
              PoseStamped_<ContainerAllocator> >::other> poses;

      typedef boost::shared_ptr<Path_<ContainerAllocator> > Ptr;
      typedef boost::shared_ptr<Path_<ContainerAllocator> const> ConstPtr;
    };
  
  typedef Path_<std::allocator<void> > Path;
  
  typedef boost::shared_ptr<Path> PathPtr;
  typedef boost::shared_ptr<Path const> PathConstPtr;

}

#endif /* DATASET_DATATYPE_PATH_H_ */
