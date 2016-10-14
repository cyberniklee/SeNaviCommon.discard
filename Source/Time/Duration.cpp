#include "Duration.h"
#include "Implement/Duration.h"

namespace NS_NaviCommon {

  Duration::Duration(const Rate& rate)
    : DurationBase<Duration>(rate.expectedCycleTime().sec, rate.expectedCycleTime().nsec)
  { }

  WallDuration::WallDuration(const Rate& rate)
    : DurationBase<WallDuration>(rate.expectedCycleTime().sec, rate.expectedCycleTime().nsec)
  { }

  void normalizeSecNSecSigned(int64_t& sec, int64_t& nsec)
  {
    int64_t nsec_part = nsec % 1000000000L;
    int64_t sec_part = sec + nsec / 1000000000L;
    if (nsec_part < 0)
      {
        nsec_part += 1000000000L;
        --sec_part;
      }

    if (sec_part < INT_MIN || sec_part > INT_MAX)
      throw std::runtime_error("Duration is out of dual 32-bit range");

    sec = sec_part;
    nsec = nsec_part;
  }

  void normalizeSecNSecSigned(int32_t& sec, int32_t& nsec)
  {
    int64_t sec64 = sec;
    int64_t nsec64 = nsec;

    normalizeSecNSecSigned(sec64, nsec64);

    sec = (int32_t)sec64;
    nsec = (int32_t)nsec64;
  }

  template class DurationBase<Duration>;
  template class DurationBase<WallDuration>;
}

