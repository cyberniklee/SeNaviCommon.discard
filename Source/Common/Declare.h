/*
 * Declare.h
 *
 *  Created on: 2016年8月22日
 *      Author: seeing
 */

#ifndef _DECLARE_H_
#define _DECLARE_H_

#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>

#include <boost/shared_ptr.hpp>

namespace NS_NaviCommon
{
  typedef std::vector<std::pair<std::string, std::string> > StringVectorPair;
  typedef std::vector<std::string> StringVector;
  typedef std::set<std::string> StringSet;
  typedef std::map<std::string, std::string> StringMap;
  typedef std::pair<std::string, std::string> StringPair;
  
  typedef boost::shared_ptr<StringMap> StringMapPtr;
}

#endif /* COMMON_DECLARE_H_ */
