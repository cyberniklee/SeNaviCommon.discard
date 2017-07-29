/*
 * Mission.h
 *
 *  Created on: Jul 28, 2017
 *      Author: root
 */

#ifndef _MISSION_MISSION_H_
#define _MISSION_MISSION_H_

#include <map>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include "GoalType/GoalBase.h"

namespace NS_NaviCommon
{

  class Mission
  {
  public:
    Mission ();
    virtual ~Mission ();
  private:

  };
}

#endif /* MISSION_MISSION_H_ */
