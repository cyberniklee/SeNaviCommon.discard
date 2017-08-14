/*
 * Parameter.cpp
 *
 *  Created on: 2016年9月13日
 *      Author: seeing
 */

#include "Parameter.h"
#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "../Exception/Exception.h"
#include "../Console/Console.h"

namespace NS_NaviCommon
{
  
  Parameter::Parameter ()
  {
    main_node = XMLNode::emptyXMLNode;
    
  }
  
  Parameter::~Parameter ()
  {
  }
  
  bool
  Parameter::loadConfigurationFile (const std::string file_name)
  {
    std::string full_name = std::string (CONFIGURATION_PATH) + file_name;
    if (access (full_name.c_str (), R_OK) < 0)
    {
      //throw FileException("Configuration file not found!", file_name);
      return false;
    }
    main_node = XMLNode::openFileHelper (full_name.c_str (),
                                         CONFIGURATION_COMMON_NODE_NAME);
    if (main_node.isEmpty ())
    {
      //throw XMLException("Configuration file is not correct!", main_node);
      return false;
    }
    
    return true;
  }
  
  std::string
  Parameter::getParameter (const std::string node_name,
                           const std::string default_value)
  {
    XMLNode node = XMLNode::emptyXMLNode;
    std::string value;
    if (main_node.isEmpty ())
    {
      //throw XMLException("Main node is not correct!", main_node);
      return default_value;
    }
    node = main_node.getChildNode (node_name.c_str ());
    if (node.isEmpty ())
    {
      //throw XMLException("Node is not correct!", node);
      return default_value;
    }
    
    value = node.getAttribute (CONFIGURATION_COMMON_ATTRIBUTE_NAME);
    
    return value;
  }
  
  int
  Parameter::getParameter (const std::string node_name, const int default_value)
  {
    char buf[16] = { 0 };
    sprintf (buf, "%d", default_value);
    std::string value = this->getParameter (node_name, std::string (buf));
    return atoi (value.c_str ());
  }
  
  float
  Parameter::getParameter (const std::string node_name,
                           const float default_value)
  {
    char buf[16] = { 0 };
    sprintf (buf, "%f", default_value);
    std::string value = this->getParameter (node_name, std::string (buf));
    return atof (value.c_str ());
  }

} /* namespace NS_NaviCommon */
