#ifndef _TIMER_H_
#define _TIMER_H_

#include "TimerOptions.h"

namespace NS_NaviCommon
{
  
  /**
   * \brief Manages a timer callback
   *
   * A Timer should always be created through a call to NodeHandle::createTimer(), or copied from one
   * that was. Once all copies of a specific
   * Timer go out of scope, the callback associated with that handle will stop
   * being called.
   */
  class Timer
  {
  public:
    Timer ()
    {
    }
    Timer (const Timer& rhs);
    ~Timer ();

    /**
     * \brief Start the timer.  Does nothing if the timer is already started.
     */
    void
    start ();
    /**
     * \brief Stop the timer.  Once this call returns, no more callbacks will be called.  Does
     * nothing if the timer is already stopped.
     */
    void
    stop ();

    /**
     * \brief Returns whether or not the timer has any pending events to call.
     */
    bool
    hasPending ();

    /**
     * \brief Set the period of this timer
     * \param reset Whether to reset the timer. If true, timer ignores elapsed time and next cb occurs at now()+period
     */
    void
    setPeriod (const Duration& period, bool reset = true);

    bool
    isValid ()
    {
      return impl_ && impl_->isValid ();
    }
    operator void* ()
    {
      return isValid () ? (void*) 1 : (void*) 0;
    }
    
    bool
    operator< (const Timer& rhs)
    {
      return impl_ < rhs.impl_;
    }
    
    bool
    operator== (const Timer& rhs)
    {
      return impl_ == rhs.impl_;
    }
    
    bool
    operator!= (const Timer& rhs)
    {
      return impl_ != rhs.impl_;
    }
    
  private:
    Timer (const TimerOptions& ops);

    class Impl
    {
    public:
      Impl ();
      ~Impl ();

      bool
      isValid ();
      bool
      hasPending ();
      void
      setPeriod (const Duration& period, bool reset = true);

      void
      start ();
      void
      stop ();

      bool started_;
      int32_t timer_handle_;

      Duration period_;
      TimerCallback callback_;
      CallbackQueueInterface* callback_queue_;
      VoidConstWPtr tracked_object_;
      bool has_tracked_object_;
      bool oneshot_;
    };
    typedef boost::shared_ptr<Impl> ImplPtr;
    typedef boost::weak_ptr<Impl> ImplWPtr;

    ImplPtr impl_;

    friend class NodeHandle;
  };

}

#endif
