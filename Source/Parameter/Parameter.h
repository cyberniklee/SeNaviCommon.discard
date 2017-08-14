/*
 * Parameter.h
 *
 *  Created on: 2016年9月13日
 *      Author: seeing
 */

#ifndef _PARAMETER_H_
#define _PARAMETER_H_

#include <string>
#include "XMLParser.h"

namespace NS_NaviCommon
{
  /*
   * configuration file sample
   * <configuration>
   *   <map_type value="cost_map"/>
   *   <interval value="10.0"/>
   *   <x_size value="100"/>
   *
   * </configuration>
   */
#define CONFIGURATION_PATH "/etc/SeNavigation/"
#define CONFIGURATION_COMMON_NODE_NAME "configuration"
#define CONFIGURATION_COMMON_ATTRIBUTE_NAME "value"
  
  class Parameter
  {
  public:
    Parameter ();
    virtual
    ~Parameter ();

  private:
    XMLNode main_node;
  public:
    bool
    loadConfigurationFile (const std::string file_name);

    std::string
    getParameter (const std::string node_name, const std::string default_value);

    int
    getParameter (const std::string node_name, const int default_value);

    float
    getParameter (const std::string node_name, const float default_value);

  };

} /* namespace NS_NaviCommon */

#endif /* _PARAMETER_H_ */
