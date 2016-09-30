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
#include <string>
#include <stdio.h>

using namespace std;
namespace _Navi_Common_
{

#define printMessage(message_, ...) \
  do{   \
    printf("Message: ");    \
    printf(message_, ##__VA_ARGS__);   \
  }while(0)
  
#define printError(error_, ...) \
  do{   \
    printf("Error: ");    \
    printf(error_, ##__VA_ARGS__);   \
  }while(0)


}

#endif /* _CONSOLE_H_ */
