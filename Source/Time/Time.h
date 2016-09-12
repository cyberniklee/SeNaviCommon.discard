/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2010, Willow Garage, Inc.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Willow Garage, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

#ifndef _TIME_H_
#define _TIME_H_

/*********************************************************************
 ** Headers
 *********************************************************************/

#include <iostream>
#include <cmath>
#include <boost/math/special_functions/round.hpp>
#include <sys/time.h>
#include <boost/date_time/posix_time/posix_time_types.hpp>

#include "../Common/Declare.h"
#include "../Exception/Exception.h"

namespace boost
{
  namespace posix_time
  {
    class ptime;
    class time_duration;
  }
}

namespace _Navi_Common_
{
  
  class Rate;
  
  /*********************************************************************
   ** Duration
   *********************************************************************/
  HANDLE_DECLARE void
  normalizeSecNSecSigned (int64_t& sec, int64_t& nsec);
  HANDLE_DECLARE void
  normalizeSecNSecSigned (int32_t& sec, int32_t& nsec);
  
  /**
   * \brief Base class for Duration implementations.  Provides storage, common functions and operator overloads.
   * This should not need to be used directly.
   */
  template<class T>
    class DurationBase
    {
    public:
      int32_t sec, nsec;
      DurationBase () :
          sec (0), nsec (0)
      {
      }
      DurationBase (int32_t _sec, int32_t _nsec);
      explicit
      DurationBase (double t)
      {
        fromSec (t);
      }
      ;
      ~DurationBase ()
      {
      }
      T
      operator+ (const T &rhs) const;
      T
      operator- (const T &rhs) const;
      T
      operator- () const;
      T
      operator* (double scale) const;
      T&
      operator+= (const T &rhs);
      T&
      operator-= (const T &rhs);
      T&
      operator*= (double scale);
      bool
      operator== (const T &rhs) const;
      inline bool
      operator!= (const T &rhs) const
      {
        return !(*static_cast<const T*> (this) == rhs);
      }
      bool
      operator> (const T &rhs) const;
      bool
      operator< (const T &rhs) const;
      bool
      operator>= (const T &rhs) const;
      bool
      operator<= (const T &rhs) const;
      double
      toSec () const
      {
        return (double) sec + 1e-9 * (double) nsec;
      }
      ;
      int64_t
      toNSec () const
      {
        return (int64_t) sec * 1000000000ll + (int64_t) nsec;
      }
      ;
      T&
      fromSec (double t);
      T&
      fromNSec (int64_t t);
      bool
      isZero () const;
      boost::posix_time::time_duration
      toBoost () const;
    };
  
  /**
   * \brief Duration representation for use with the Time class.
   *
   * ros::DurationBase provides most of its functionality.
   */
  class HANDLE_DECLARE Duration : public DurationBase<Duration>
  {
  public:
    Duration () :
        DurationBase<Duration> ()
    {
    }
    
    Duration (int32_t _sec, int32_t _nsec) :
        DurationBase<Duration> (_sec, _nsec)
    {
    }
    
    explicit
    Duration (double t)
    {
      fromSec (t);
    }
    explicit
    Duration (const Rate&);
    /**
     * \brief sleep for the amount of time specified by this Duration.  If a signal interrupts the sleep, resleeps for the time remaining.
     * @return True if the desired sleep duration was met, false otherwise.
     */
    bool
    sleep () const;
  };
  
  extern HANDLE_DECLARE const Duration DURATION_MAX;
  extern HANDLE_DECLARE const Duration DURATION_MIN;
  
  /**
   * \brief Duration representation for use with the WallTime class.
   *
   * ros::DurationBase provides most of its functionality.
   */
  class HANDLE_DECLARE WallDuration : public DurationBase<WallDuration>
  {
  public:
    WallDuration () :
        DurationBase<WallDuration> ()
    {
    }
    
    WallDuration (int32_t _sec, int32_t _nsec) :
        DurationBase<WallDuration> (_sec, _nsec)
    {
    }
    
    explicit
    WallDuration (double t)
    {
      fromSec (t);
    }
    explicit
    WallDuration (const Rate&);
    /**
     * \brief sleep for the amount of time specified by this Duration.  If a signal interrupts the sleep, resleeps for the time remaining.
     * @return True if the desired sleep duration was met, false otherwise.
     */
    bool
    sleep () const;
  };
  
  std::ostream &
  operator << (std::ostream &os, const Duration &rhs);
  std::ostream &
  operator << (std::ostream &os, const WallDuration &rhs);
  
  /*********************************************************************
   ** Time
   *********************************************************************/
  /**
   * @brief Thrown if the ros subsystem hasn't been initialised before use.
   */
  class HANDLE_DECLARE TimeNotInitializedException : public Exception
  {
  public:
    TimeNotInitializedException () :
            Exception (
                "Cannot use ros::Time::now() before the first NodeHandle has been created or ros::start() has been called.  "
                "If this is a standalone app or test that just uses ros::Time and does not communicate over ROS, you may also call ros::Time::init()")
    {
    }
  };
  
  /**
   * @brief Thrown if windoze high perf. timestamping is unavailable.
   *
   * @sa getWallTime
   */
  class HANDLE_DECLARE NoHighPerformanceTimersException : public Exception
  {
  public:
    NoHighPerformanceTimersException () :
        Exception ("This windows platform does not "
                   "support the high-performance timing api.")
    {
    }
  };
  
  /*********************************************************************
   ** Functions
   *********************************************************************/

  HANDLE_DECLARE void
  normalizeSecNSec (uint64_t& sec, uint64_t& nsec);
  HANDLE_DECLARE void
  normalizeSecNSec (uint32_t& sec, uint32_t& nsec);
  HANDLE_DECLARE void
  normalizeSecNSecUnsigned (int64_t& sec, int64_t& nsec);
  
  /*********************************************************************
   ** Time Classes
   *********************************************************************/

  /**
   * \brief Base class for Time implementations.  Provides storage, common functions and operator overloads.
   * This should not need to be used directly.
   */
  template<class T, class D>
    class TimeBase
    {
    public:
      uint32_t sec, nsec;

      TimeBase () :
          sec (0), nsec (0)
      {
      }
      TimeBase (uint32_t _sec, uint32_t _nsec) :
          sec (_sec), nsec (_nsec)
      {
        normalizeSecNSec (sec, nsec);
      }
      explicit
      TimeBase (double t)
      {
        fromSec (t);
      }
      ~TimeBase ()
      {
      }
      D
      operator- (const T &rhs) const;
      T
      operator+ (const D &rhs) const;
      T
      operator- (const D &rhs) const;
      T&
      operator+= (const D &rhs);
      T&
      operator-= (const D &rhs);
      bool
      operator== (const T &rhs) const;
      inline bool
      operator!= (const T &rhs) const
      {
        return !(*static_cast<const T*> (this) == rhs);
      }
      bool
      operator> (const T &rhs) const;
      bool
      operator< (const T &rhs) const;
      bool
      operator>= (const T &rhs) const;
      bool
      operator<= (const T &rhs) const;

      double
      toSec () const
      {
        return (double) sec + 1e-9 * (double) nsec;
      }
      ;
      T&
      fromSec (double t)
      {
        sec = (uint32_t) floor (t);
        nsec = (uint32_t) boost::math::round ((t - sec) * 1e9);
        // avoid rounding errors
        sec += (nsec / 1000000000ul);
        nsec %= 1000000000ul;
        return *static_cast<T*> (this);
      }
      
      uint64_t
      toNSec () const
      {
        return (uint64_t) sec * 1000000000ull + (uint64_t) nsec;
      }
      T&
      fromNSec (uint64_t t);

      inline bool
      isZero () const
      {
        return sec == 0 && nsec == 0;
      }
      inline bool
      is_zero () const
      {
        return isZero ();
      }
      boost::posix_time::ptime
      toBoost () const;
      
    };
  
  /**
   * \brief Time representation.  May either represent wall clock time or ROS clock time.
   *
   * ros::TimeBase provides most of its functionality.
   */
  class HANDLE_DECLARE Time : public TimeBase<Time, Duration>
  {
  public:
    Time () :
        TimeBase<Time, Duration> ()
    {
      
    }
    
    Time (uint32_t _sec, uint32_t _nsec) :
        TimeBase<Time, Duration> (_sec, _nsec)
    {
      
    }
    
    explicit
    Time (double t)
    {
      fromSec (t);
    }
    
    /**
     * \brief Retrieve the current time.  If ROS clock time is in use, this returns the time according to the
     * ROS clock.  Otherwise returns the current wall clock time.
     */
    static Time
    now ();
    /**
     * \brief Sleep until a specific time has been reached.
     * @return True if the desired sleep time was met, false otherwise.
     */
    static bool
    sleepUntil (const Time& end);

    static void
    init ();
    static void
    shutdown ();
    static void
    setNow (const Time& new_now);
    static bool
    useSystemTime ();
    static bool
    isSimTime ();
    static bool
    isSystemTime ();

    /**
     * \brief Returns whether or not the current time is valid.  Time is valid if it is non-zero.
     */
    static bool
    isValid ();
    /**
     * \brief Wait for time to become valid
     */
    static bool
    waitForValid ();
    /**
     * \brief Wait for time to become valid, with timeout
     */
    static bool
    waitForValid (const WallDuration& timeout);

    static Time
    fromBoost (const boost::posix_time::ptime& t);
    static Time
    fromBoost (const boost::posix_time::time_duration& d);
  };
  
  extern HANDLE_DECLARE const Time TIME_MAX;
  extern HANDLE_DECLARE const Time TIME_MIN;
  
  /**
   * \brief Time representation.  Always wall-clock time.
   *
   * ros::TimeBase provides most of its functionality.
   */
  class HANDLE_DECLARE WallTime : public TimeBase<WallTime, WallDuration>
  {
  public:
    WallTime () :
        TimeBase<WallTime, WallDuration> ()
    {
    }
    
    WallTime (uint32_t _sec, uint32_t _nsec) :
        TimeBase<WallTime, WallDuration> (_sec, _nsec)
    {
    }
    
    explicit
    WallTime (double t)
    {
      fromSec (t);
    }
    
    /**
     * \brief Returns the current wall clock time.
     */
    static WallTime
    now ();

    /**
     * \brief Sleep until a specific time has been reached.
     * @return True if the desired sleep time was met, false otherwise.
     */
    static bool
    sleepUntil (const WallTime& end);

    static bool
    isSystemTime ()
    {
      return true;
    }
  };
  
  HANDLE_DECLARE std::ostream &
  operator << (std::ostream &os, const Time &rhs);
  HANDLE_DECLARE std::ostream &
  operator << (std::ostream &os, const WallTime &rhs);
  
  /*********************************************************************
   ** Rate
   *********************************************************************/

  /**
   * @class Rate
   * @brief Class to help run loops at a desired frequency
   */
  class HANDLE_DECLARE Rate
  {
  private:
    Time start_;
    Duration expected_cycle_time_, actual_cycle_time_;

  public:
    /**
     * @brief  Constructor, creates a Rate
     * @param  frequency The desired rate to run at in Hz
     */
    Rate (double frequency);
    explicit
    Rate (const Duration&);

    /**
     * @brief  Sleeps for any leftover time in a cycle. Calculated from the last time sleep, reset, or the constructor was called.
     * @return True if the desired rate was met for the cycle, false otherwise.
     */
    bool
    sleep ();

    /**
     * @brief  Sets the start time for the rate to now
     */
    void
    reset ();

    /**
     * @brief  Get the actual run time of a cycle from start to sleep
     * @return The runtime of the cycle
     */
    Duration
    cycleTime () const;

    /**
     * @brief Get the expected cycle time -- one over the frequency passed in to the constructor
     */
    Duration
    expectedCycleTime () const
    {
      return expected_cycle_time_;
    }
    
  };
  
  /**
   * @class WallRate
   * @brief Class to help run loops at a desired frequency.  This version always uses wall-clock time.
   */
  class HANDLE_DECLARE WallRate
  {
  public:
    /**
     * @brief  Constructor, creates a Rate
     * @param  frequency The desired rate to run at in Hz
     */
    WallRate (double frequency);
    explicit
    WallRate (const Duration&);

    /**
     * @brief  Sleeps for any leftover time in a cycle. Calculated from the last time sleep, reset, or the constructor was called.
     * @return Passes through the return value from WallDuration::sleep() if it slept, false otherwise.
     */
    bool
    sleep ();

    /**
     * @brief  Sets the start time for the rate to now
     */
    void
    reset ();

    /**
     * @brief  Get the actual run time of a cycle from start to sleep
     * @return The runtime of the cycle
     */
    WallDuration
    cycleTime () const;

    /**
     * @brief Get the expected cycle time -- one over the frequency passed in to the constructor
     */
    WallDuration
    expectedCycleTime () const
    {
      return expected_cycle_time_;
    }
    
  private:
    WallTime start_;
    WallDuration expected_cycle_time_, actual_cycle_time_;
  };

}

#endif // _TIME_H

