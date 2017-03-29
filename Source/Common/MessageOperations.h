#ifndef _MESSAGE_OPERATIONS_H_
#define _MESSAGE_OPERATIONS_H_

#include <ostream>

namespace NS_NaviCommon
{
  
  template<typename M>
    struct Printer
    {
      template<typename Stream>
        static void
        stream (Stream& s, const std::string& indent, const M& value)
        {
          s << value << "\n";
        }
    };
  
// Explicitly specialize for uint8_t/int8_t because otherwise it thinks it's a char, and treats
// the value as a character code
  template<>
    struct Printer<int8_t>
    {
      template<typename Stream>
        static void
        stream (Stream& s, const std::string& indent, int8_t value)
        {
          s << static_cast<int32_t> (value) << "\n";
        }
    };
  
  template<>
    struct Printer<uint8_t>
    {
      template<typename Stream>
        static void
        stream (Stream& s, const std::string& indent, uint8_t value)
        {
          s << static_cast<uint32_t> (value) << "\n";
        }
    };

} // namespace

#endif // _MESSAGE_OPERATIONS_H_

