/*
 * Goal.h
 *
 *  Created on: Jul 19, 2017
 *      Author: root
 */

#ifndef _MISSION_GOAL_H_
#define _MISSION_GOAL_H_

namespace NS_NaviCommon
{

  typedef enum
  {
    GOAL_READY,
    GOAL_EXECUTING,
    GOAL_ABORTED,
    GOAL_FINISHED
  } MissionGoalStatus;

  class MissionGoal
  {
  public:
    MissionGoal (int id, NS_GoalType::GoalBase* goal_)
    {
      goal = goal_;
      status = GOAL_READY;
      goal_id = id;
    }

    virtual ~MissionGoal ()
    {
    }
  private:
    int goal_id;
    MissionGoalStatus status;
    NS_GoalType::GoalBase* goal;
  public:
    void
    start ()
    {
      status = GOAL_EXECUTING;
    }

    void
    abort ()
    {
      status = GOAL_ABORTED;
    }

    void
    end ()
    {
      status = GOAL_FINISHED;
    }

    MissionGoalStatus
    getStatus ()
    {
      return status;
    }

    NS_GoalType::GoalBase*
    getGoal ()
    {
      return goal;
    }

  };

}

#endif /* MISSION_GOAL_H_ */
