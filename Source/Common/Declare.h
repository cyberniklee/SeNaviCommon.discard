/*
 * Declare.h
 *
 *  Created on: 2016年8月22日
 *      Author: seeing
 */

#ifndef _DECLARE_H_
#define _DECLARE_H_

#define HANDLE_DECLARE __attribute__ ((visibility("default")))

namespace _Navi_Common_
{
  template <class C, typename R, typename P>
  class CallbackClass
  {
  public:
    typedef R (C::*Method)(P);

    CallbackClass(C* instance, Method method)
    {
      instance_ = instance;
      method_ = method;
    };

    R operator()(P parameter)
    {
      return (instance_->*method_)(parameter);
    };

    R execute(P parameter)
    {
      return operator()(parameter);
    };

  private:
    C* instance_;
    Method method_;
  };
}

#endif /* COMMON_DECLARE_H_ */
