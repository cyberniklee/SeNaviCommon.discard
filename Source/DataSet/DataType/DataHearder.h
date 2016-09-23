/*
 * DataHearder.h
 *
 *  Created on: 2016年9月23日
 *      Author: seeing
 */

#ifndef _DATAHEARDER_H_
#define _DATAHEARDER_H_

#include <string>
#include <vector>
#include "../../Time/Time.h"
#include "DataBase.h"

namespace _Navi_Common_
{
  template <class ContainerAllocator>
  struct DataHeader : public DataBase
  {
    typedef DataHeader<ContainerAllocator> Type;
  public:
    DataHeader () : seq(0), stamp(), frame_id()
    {
    };

    DataHeader (const ContainerAllocator& allocator) : seq(0), stamp(), frame_id(allocator)
    {
    };

    unsigned long seq;
    Time stamp;

    std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other> frame_id;

  };

} /* namespace _Navi_Common_ */

#endif /* DATASET_DATATYPE_DATAHEARDER_H_ */
