#ifndef _MESSAGE_FORWARD_H_
#define _MESSAGE_FORWARD_H_

// Make sure that either __GLIBCXX__ or _LIBCPP_VERSION is defined.
#include <cstddef>
#include <iostream>

// C++ standard section 17.4.3.1/1 states that forward declarations of STL types
// that aren't specializations involving user defined types results in undefined
// behavior. Apparently only libc++ has a problem with this and won't compile it.
#ifndef _LIBCPP_VERSION
namespace std
{
  template<typename T>
    class allocator;
}
#else
#include <memory>
#endif

namespace boost
{
  template<typename T>
    class shared_ptr;
}

/**
 * \brief Forward-declare a message, including Ptr and ConstPtr types, with an allocator
 *
 * \param ns The namespace the message should be declared inside
 * \param m The "base" message type, i.e. the name of the .msg file
 * \param new_name The name you'd like the message to have
 * \param alloc The allocator to use, e.g. std::allocator
 */
#define DECLARE_MESSAGE_WITH_ALLOCATOR(msg, new_name, alloc) \
  template<class Allocator> struct msg##_; \
  typedef msg##_<alloc<void> > new_name; \
  typedef boost::shared_ptr<new_name> new_name##Ptr; \
  typedef boost::shared_ptr<new_name const> new_name##ConstPtr;

/**
 * \brief Forward-declare a message, including Ptr and ConstPtr types, using std::allocator
 * \param msg The "base" message type, i.e. the name of the .msg file
 */
#define DECLARE_MESSAGE(msg) DECLARE_MESSAGE_WITH_ALLOCATOR(msg, msg, std::allocator)

#endif // _MESSAGE_FORWARD_H_
