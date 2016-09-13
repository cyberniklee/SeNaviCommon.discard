/*
 * Parameter.h
 *
 *  Created on: 2016年9月13日
 *      Author: seeing
 */

#ifndef _PARAMETER_H_
#define _PARAMETER_H_

#include "XMLParser.h"

namespace _Navi_Common_
{
  
  class Parameter
  {
  public:
    Parameter ();
    virtual
    ~Parameter ();

  private:
    XMLNode main_node;
  public:
    bool loadConfigurationFile(const std::string file_name);

    std::string getParameter(const std::string node_name, const std::string default_value);

    int getParameter(const std::string node_name, const int default_value);

    float getParameter(const std::string node_name, const float default_value);
  };

} /* namespace _Navi_Common_ */

#endif /* _PARAMETER_H_ */
