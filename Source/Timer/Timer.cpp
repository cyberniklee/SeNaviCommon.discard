#include "Timer.h"
#include "TimerManager.h"
#include "../Console/Console.h"

namespace NS_NaviCommon
{
  
  Timer::Impl::Impl ()
      : started_ (false), timer_handle_ (-1)
  {
  }
  
  Timer::Impl::~Impl ()
  {
    console.warning ("Timer deregistering callbacks.");
    stop ();
  }
  
  bool
  Timer::Impl::isValid ()
  {
    return !period_.isZero ();
  }
  
  void
  Timer::Impl::start ()
  {
    if (!started_)
    {
      VoidConstPtr tracked_object;
      if (has_tracked_object_)
      {
        tracked_object = tracked_object_.lock ();
      }
      
      timer_handle_ = TimerManager<Time, Duration, TimerEvent>::global ().add (
          period_, callback_, callback_queue_, tracked_object, oneshot_);
      started_ = true;
    }
  }
  
  void
  Timer::Impl::stop ()
  {
    if (started_)
    {
      started_ = false;
      TimerManager<Time, Duration, TimerEvent>::global ().remove (
          timer_handle_);
      timer_handle_ = -1;
    }
  }
  
  bool
  Timer::Impl::hasPending ()
  {
    if (!isValid () || timer_handle_ == -1)
    {
      return false;
    }
    
    return TimerManager<Time, Duration, TimerEvent>::global ().hasPending (
        timer_handle_);
  }
  
  void
  Timer::Impl::setPeriod (const Duration& period, bool reset)
  {
    period_ = period;
    TimerManager<Time, Duration, TimerEvent>::global ().setPeriod (
        timer_handle_, period, reset);
  }
  
  Timer::Timer (const TimerOptions& ops)
      : impl_ (new Impl)
  {
    impl_->period_ = ops.period;
    impl_->callback_ = ops.callback;
    impl_->callback_queue_ = ops.callback_queue;
    impl_->tracked_object_ = ops.tracked_object;
    impl_->has_tracked_object_ = (ops.tracked_object != NULL);
    impl_->oneshot_ = ops.oneshot;
  }
  
  Timer::Timer (const Timer& rhs)
  {
    impl_ = rhs.impl_;
  }
  
  Timer::~Timer ()
  {
  }
  
  void
  Timer::start ()
  {
    if (impl_)
    {
      impl_->start ();
    }
  }
  
  void
  Timer::stop ()
  {
    if (impl_)
    {
      impl_->stop ();
    }
  }
  
  bool
  Timer::hasPending ()
  {
    if (impl_)
    {
      return impl_->hasPending ();
    }
    
    return false;
  }
  
  void
  Timer::setPeriod (const Duration& period, bool reset)
  {
    if (impl_)
    {
      impl_->setPeriod (period, reset);
    }
  }

}
