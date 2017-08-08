/*
 * Console.cpp
 *
 *  Created on: 2016年8月16日
 *      Author: seeing
 */

#include "Console.h"

namespace NS_NaviCommon
{
  void
  disableStdoutStream ()
  {
    std::cout.setstate (std::ios::failbit);
    std::cerr.setstate (std::ios::failbit);
  };

} /* namespace NS_NaviCommon */
