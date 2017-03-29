#ifndef _DURATION_IMPL_H_
#define _DURATION_IMPL_H_

#include "../Implement/Duration.h"

#include "../Rate.h"
#include <boost/date_time/posix_time/posix_time_types.hpp>

namespace NS_NaviCommon
{
  //
  // DurationBase template member function implementation
  //
  template<class T>
    DurationBase<T>::DurationBase (int32_t _sec, int32_t _nsec)
        : sec (_sec), nsec (_nsec)
    {
      normalizeSecNSecSigned (sec, nsec);
    }
  
  template<class T>
    T&
    DurationBase<T>::fromSec (double d)
    {
      sec = (int32_t) floor (d);
      nsec = (int32_t) ((d - (double) sec) * 1000000000);
      return *static_cast<T*> (this);
    }
  
  template<class T>
    T&
    DurationBase<T>::fromNSec (int64_t t)
    {
      sec = (int32_t) (t / 1000000000);
      nsec = (int32_t) (t % 1000000000);
      
      normalizeSecNSecSigned (sec, nsec);
      
      return *static_cast<T*> (this);
    }
  
  template<class T>
    T
    DurationBase<T>::operator+ (const T &rhs) const
    {
      return T (sec + rhs.sec, nsec + rhs.nsec);
    }
  
  template<class T>
    T
    DurationBase<T>::operator* (double scale) const
    {
      return T (toSec () * scale);
    }
  
  template<class T>
    T
    DurationBase<T>::operator- (const T &rhs) const
    {
      return T (sec - rhs.sec, nsec - rhs.nsec);
    }
  
  template<class T>
    T
    DurationBase<T>::operator- () const
    {
      return T (-sec, -nsec);
    }
  
  template<class T>
    T&
    DurationBase<T>::operator+= (const T &rhs)
    {
      *this = *this + rhs;
      return *static_cast<T*> (this);
    }
  
  template<class T>
    T&
    DurationBase<T>::operator-= (const T &rhs)
    {
      *this += (-rhs);
      return *static_cast<T*> (this);
    }
  
  template<class T>
    T&
    DurationBase<T>::operator*= (double scale)
    {
      fromSec (toSec () * scale);
      return *static_cast<T*> (this);
    }
  
  template<class T>
    bool
    DurationBase<T>::operator< (const T &rhs) const
    {
      if (sec < rhs.sec)
        return true;
      else if (sec == rhs.sec && nsec < rhs.nsec)
        return true;
      return false;
    }
  
  template<class T>
    bool
    DurationBase<T>::operator> (const T &rhs) const
    {
      if (sec > rhs.sec)
        return true;
      else if (sec == rhs.sec && nsec > rhs.nsec)
        return true;
      return false;
    }
  
  template<class T>
    bool
    DurationBase<T>::operator<= (const T &rhs) const
    {
      if (sec < rhs.sec)
        return true;
      else if (sec == rhs.sec && nsec <= rhs.nsec)
        return true;
      return false;
    }
  
  template<class T>
    bool
    DurationBase<T>::operator>= (const T &rhs) const
    {
      if (sec > rhs.sec)
        return true;
      else if (sec == rhs.sec && nsec >= rhs.nsec)
        return true;
      return false;
    }
  
  template<class T>
    bool
    DurationBase<T>::operator== (const T &rhs) const
    {
      return sec == rhs.sec && nsec == rhs.nsec;
    }
  
  template<class T>
    bool
    DurationBase<T>::isZero () const
    {
      return sec == 0 && nsec == 0;
    }
  
  template<class T>
    boost::posix_time::time_duration
    DurationBase<T>::toBoost () const
    {
      namespace bt = boost::posix_time;
#if defined(BOOST_DATE_TIME_HAS_NANOSECONDS)
      return bt::seconds(sec) + bt::nanoseconds(nsec);
#else
      return bt::seconds (sec) + bt::microseconds (nsec / 1000.0);
#endif
    }
}
#endif
