/*
 * ResponseBase.h
 *
 *  Created on: 2016年9月21日
 *      Author: seeing
 */

#ifndef _RESPONSEBASE_H_
#define _RESPONSEBASE_H_

namespace NS_ServiceType
{
  
  class ResponseBase
  {
  public:
    ResponseBase (){};
    virtual
    ~ResponseBase (){};

    bool result;
  };

} /* namespace NS_NaviCommon */

#endif /* _RESPONSEBASE_H_ */
