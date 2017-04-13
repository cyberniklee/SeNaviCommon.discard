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

  void
  redirectStdoutStream (std::string out_file)
  {
    std::streambuf* sbuf;
    std::ofstream ofs;
    ofs.open (out_file.c_str());
    if (!ofs.is_open ())
      return;
    sbuf = ofs.rdbuf ();
    std::cout.rdbuf (sbuf);
    std::cerr.rdbuf (sbuf);
  };

} /* namespace NS_NaviCommon */
