#ifndef _CALLBACK_QUEUE_INTERFACE_H_
#define _CALLBACK_QUEUE_INTERFACE_H_

#include <boost/shared_ptr.hpp>

namespace NS_NaviCommon
{
  
  /**
   * \brief Abstract interface for items which can be added to a CallbackQueueInterface
   */
  class CallbackInterface
  {
  public:
    /**
     * \brief Possible results for the call() method
     */
    enum CallResult
    {
      Success,   ///< Call succeeded
      TryAgain,  ///< Call not ready, try again later
      Invalid,   ///< Call no longer valid
    };

    virtual
    ~CallbackInterface ()
    {
    }
    
    /**
     * \brief Call this callback
     * \return The result of the call
     */
    virtual CallResult
    call () = 0;
    /**
     * \brief Provides the opportunity for specifying that a callback is not ready to be called
     * before call() actually takes place.
     */
    virtual bool
    ready ()
    {
      return true;
    }
  };
  typedef boost::shared_ptr<CallbackInterface> CallbackInterfacePtr;
  
  /**
   * \brief Abstract interface for a queue used to handle all callbacks within roscpp.
   *
   * Allows you to inherit and provide your own implementation that can be used instead of our
   * default CallbackQueue
   */
  class CallbackQueueInterface
  {
  public:
    virtual
    ~CallbackQueueInterface ()
    {
    }
    
    /**
     * \brief Add a callback, with an optional owner id.  The owner id can be used to
     * remove a set of callbacks from this queue.
     */
    virtual void
    addCallback (const CallbackInterfacePtr& callback, unsigned long owner_id =
                     0) = 0;

    /**
     * \brief Remove all callbacks associated with an owner id
     */
    virtual void
    removeByID (unsigned long owner_id) = 0;
  };

}

#endif
