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
#include <fstream>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

using namespace std;
namespace NS_NaviCommon
{
#define COLOR_NONE "\033[m"
#define COLOR_RED "\033[1;31m"
#define COLOR_GREEN "\033[1;32m"
#define COLOR_YELLOW "\033[1;33m"
#define COLOR_CYAN "\033[1;36m"

#define DEBUG_FLAG_FILE "/tmp/seeing-debug-flag"

  class Console
  {
  public:
    Console () {};
    ~Console () {};
  public:
    void
    message (const char* message_, ...)
    {
      char out[1024] = { 0 };
      va_list args;
      va_start(args, message_);
      vsnprintf (out, sizeof(out), message_, args);
      va_end(args);
      printf (COLOR_GREEN);
      printf ("Message: ");
      printf (out);
      printf (COLOR_NONE);
      printf ("\r\n");
    }
    ;

    void
    warning (const char* warning_, ...)
    {
      char out[1024] = { 0 };
      va_list args;
      va_start(args, warning_);
      vsnprintf (out, sizeof(out), warning_, args);
      va_end(args);
      printf (COLOR_YELLOW);
      printf ("Warning: ");
      printf (out);
      printf (COLOR_NONE);
      printf ("\r\n");
    }
    ;

    void
    error (const char* error_, ...)
    {
      char out[1024] = { 0 };
      va_list args;
      va_start(args, error_);
      vsnprintf (out, sizeof(out), error_, args);
      va_end(args);
      printf (COLOR_RED);
      printf ("Error: ");
      printf (out);
      printf (COLOR_NONE);
      printf ("\r\n");
    }
    ;

    void
    debug (const char* message_, ...)
    {
      char out[1024] = { 0 };
      va_list args;
      if (access (DEBUG_FLAG_FILE, F_OK) == 0)
      {
        va_start(args, message_);
        vsnprintf (out, sizeof(out), message_, args);
        va_end(args);
        printf (COLOR_CYAN);
        printf (">>>   ");
        printf (out);
        printf (COLOR_NONE);
        printf ("\r\n");
      }
    }
    ;

    void debugOn ()
    {
      char cmd[1024] = { 0 };
      strcat (cmd, "touch ");
      strcat (cmd, DEBUG_FLAG_FILE);
      system (cmd);
    }
    ;

    void debugOff ()
    {
      char cmd[1024] = { 0 };
      strcat (cmd, "rm -f ");
      strcat (cmd, DEBUG_FLAG_FILE);
      system (cmd);
    }
    ;

    void
    dump (unsigned char* ptr_, size_t len_)
    {
      printf (COLOR_YELLOW);
      printf ("[ ");
      for (size_t i = 0; i < len_; i++)
      {
        printf ("%02X ", *(ptr_ + i));
      }
      printf (" ]");
      printf (COLOR_NONE);
      printf ("\r\n");
    }
  };

  static Console console;

  void
  disableStdoutStream ();

  void
  redirectStdoutStream (std::string out_file);

}

#endif /* _CONSOLE_H_ */
