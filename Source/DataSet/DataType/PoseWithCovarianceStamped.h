
#ifndef _DATATYPE_POSEWITHCOVARIANCESTAMPED_H_
#define _DATATYPE_POSEWITHCOVARIANCESTAMPED_H_

#include "DataBase.h"
#include "DataHeader.h"
#include "Pose.h"

namespace NS_DataType
{
  
  template<class ContainerAllocator>
    struct PoseWithCovarianceStamped_: public DataBase
    {
      typedef PoseWithCovarianceStamped_<ContainerAllocator> Type;
    public:
      PoseWithCovarianceStamped_ ()
          : header (), pose ()
      {
      }
      ;

      PoseWithCovarianceStamped_ (const ContainerAllocator& allocator)
          : header (allocator), pose (allocator)
      {
      }
      ;

      DataHeader_<ContainerAllocator> header;
      Pose_<ContainerAllocator> pose;

      double covariance[36];

      typedef boost::shared_ptr<PoseWithCovarianceStamped_<ContainerAllocator> > Ptr;
      typedef boost::shared_ptr<PoseWithCovarianceStamped_<ContainerAllocator> const> ConstPtr;
    };
  
  typedef PoseWithCovarianceStamped_<std::allocator<void> > PoseWithCovarianceStamped;
  
  typedef boost::shared_ptr<PoseWithCovarianceStamped> PoseWithCovarianceStampedPtr;
  typedef boost::shared_ptr<PoseWithCovarianceStamped const> PoseWithCovarianceStampedConstPtr;

}

#endif /* _DATATYPE_POSEWITHCOVARIANCESTAMPED_H_ */
