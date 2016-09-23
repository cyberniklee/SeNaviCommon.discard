/*
 * Console.h
 *
 *  Created on: 2016年8月16日
 *      Author: seeing
 */

#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include <iostream>
#include <stdarg.h>

using namespace std;

namespace _Navi_Common_
{
  
  void
  printMessage (const char* message, ...);
  
  void
  printError (const char* error, ...);

} /* namespace _Navi_Common_ */

#endif /* _CONSOLE_H_ */
