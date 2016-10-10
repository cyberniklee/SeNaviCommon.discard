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
#include <stdio.h>
#include <string>

using namespace std;
namespace _Navi_Common_
{

  class Console
  {
    public:
      void message(const char* message_, ...)
      {
        char out[1024] = {0};
        va_list args;
        va_start(args, message_);
        vsnprintf(out, sizeof(out), message_, args);
        va_end(args);
        printf("Message: ");
        printf(out);
        printf("\r\n");
      };

      void warning(const char* warning_, ...)
      {
        char out[1024] = {0};
        va_list args;
        va_start(args, warning_);
        vsnprintf(out, sizeof(out), warning_, args);
        va_end(args);
        printf("Warning: ");
        printf(out);
        printf("\r\n");
      };

      void error(const char* error_, ...)
      {
        char out[1024] = {0};
        va_list args;
        va_start(args, error_);
        vsnprintf(out, sizeof(out), error_, args);
        va_end(args);
        printf("Error: ");
        printf(out);
        printf("\r\n");
      };
  };

  static Console console;

}

#endif /* _CONSOLE_H_ */
