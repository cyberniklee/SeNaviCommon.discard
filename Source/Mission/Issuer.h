/*
 * Issuer.h
 *
 *  Created on: Jul 19, 2017
 *      Author: root
 */

#ifndef _MISSION_ISSUER_H_
#define _MISSION_ISSUER_H_

#include "GoalType/GoalBase.h"

namespace NS_NaviCommon
{
  class Issuer
  {
  public:
    Issuer ();
    virtual ~Issuer ();
  public:
    bool publish ();
  };




}


#endif /* MISSION_ISSUER_H_ */
