#ifndef _CALLBACK_QUEUE_H_
#define _CALLBACK_QUEUE_H_

#include "CallbackQueueInterface.h"
#include "../Time/Time.h"

#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/tss.hpp>

#include <list>
#include <deque>

namespace NS_NaviCommon
{
  
  /**
   * \brief This is the default implementation of the CallbackQueueInterface
   */
  class CallbackQueue: public CallbackQueueInterface
  {
  public:
    CallbackQueue (bool enabled = true);
    virtual
    ~CallbackQueue ();

    virtual void
    addCallback (const CallbackInterfacePtr& callback,
                 unsigned long removal_id = 0);
    virtual void
    removeByID (unsigned long removal_id);

    enum CallOneResult
    {
      Called, TryAgain, Disabled, Empty,
    };

    /**
     * \brief Pop a single callback off the front of the queue and invoke it.  If the callback was not ready to be called,
     * pushes it back onto the queue.
     */
    CallOneResult
    callOne ()
    {
      return callOne (Duration ());
    }
    
    /**
     * \brief Pop a single callback off the front of the queue and invoke it.  If the callback was not ready to be called,
     * pushes it back onto the queue.  This version includes a timeout which lets you specify the amount of time to wait for
     * a callback to be available before returning.
     *
     * \param timeout The amount of time to wait for a callback to be available.  If there is already a callback available,
     * this parameter does nothing.
     */
    CallOneResult
    callOne (Duration timeout);

    /**
     * \brief Invoke all callbacks currently in the queue.  If a callback was not ready to be called, pushes it back onto the queue.
     */
    void
    callAvailable ()
    {
      callAvailable (Duration ());
    }
    /**
     * \brief Invoke all callbacks currently in the queue.  If a callback was not ready to be called, pushes it back onto the queue.  This version
     * includes a timeout which lets you specify the amount of time to wait for a callback to be available before returning.
     *
     * \param timeout The amount of time to wait for at least one callback to be available.  If there is already at least one callback available,
     * this parameter does nothing.
     */
    void
    callAvailable (Duration timeout);

    /**
     * \brief returns whether or not the queue is empty
     */
    bool
    empty ()
    {
      return isEmpty ();
    }
    /**
     * \brief returns whether or not the queue is empty
     */
    bool
    isEmpty ();
    /**
     * \brief Removes all callbacks from the queue.  Does \b not wait for calls currently in progress to finish.
     */
    void
    clear ();

    /**
     * \brief Enable the queue (queue is enabled by default)
     */
    void
    enable ();
    /**
     * \brief Disable the queue, meaning any calls to addCallback() will have no effect
     */
    void
    disable ();
    /**
     * \brief Returns whether or not this queue is enabled
     */
    bool
    isEnabled ();

  protected:
    void
    setupTLS ();

    struct TLS;
    CallOneResult
    callOneCB (TLS* tls);

    struct IDInfo
    {
      unsigned long id;
      boost::shared_mutex calling_rw_mutex;
    };
    typedef boost::shared_ptr<IDInfo> IDInfoPtr;
    typedef std::map<unsigned long, IDInfoPtr> M_IDInfo;

    IDInfoPtr
    getIDInfo (unsigned long id);

    struct CallbackInfo
    {
      CallbackInfo ()
          : removal_id (0), marked_for_removal (false)
      {
      }
      CallbackInterfacePtr callback;
      unsigned long removal_id;
      bool marked_for_removal;
    };
    typedef std::list<CallbackInfo> L_CallbackInfo;
    typedef std::deque<CallbackInfo> D_CallbackInfo;
    D_CallbackInfo callbacks_;
    size_t calling_;
    boost::mutex mutex_;
    boost::condition_variable condition_;

    boost::mutex id_info_mutex_;
    M_IDInfo id_info_;

    struct TLS
    {
      TLS ()
          : calling_in_this_thread (0xffffffffffffffffULL),
              cb_it (callbacks.end ())
      {
      }
      unsigned long calling_in_this_thread;
      D_CallbackInfo callbacks;
      D_CallbackInfo::iterator cb_it;
    };
    boost::thread_specific_ptr<TLS> tls_;

    bool enabled_;
  };
  typedef boost::shared_ptr<CallbackQueue> CallbackQueuePtr;

}

#endif
