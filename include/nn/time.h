#pragma once
#include "nn/result.h"
#include "types.h"

// PosixTime, CalendarTime, TimeZone and CalendarAdditionalInfo follow include/nn/time of open-ead/nnheaders; the imported symbols are
// _ZN2nn4time14ToCalendarTimeEPNS0_12CalendarTimeEPNS0_22CalendarAdditionalInfoERKNS0_9PosixTimeE and others.
namespace nn {
namespace time {

struct PosixTime {
  s64 time;
};

struct CalendarTime {
  s16 year;
  s8 month;
  s8 day;
  s8 hour;
  s8 minute;
  s8 second;
};

struct TimeZone {
  char standardTimeName[8];
  bool isDaylightSavingTime;
  s32 utcOffset;
};

struct CalendarAdditionalInfo {
  s32 dayOfWeek;
  s32 dayOfYear;
  TimeZone timeZone;
};

// The type name comes from the imported symbols (GetSpanBetween, GetCurrentTimePoint); the 0x18 layout comes from the use in ml::TimeUtil. The members are not from nnheaders.
struct SteadyClockTimePoint {
  s64 unknown00; // Inferred role: clock value; original member name unknown.
  u64 unknown08; // Inferred role: clock source id, low word; original member name unknown.
  u64 unknown10; // Inferred role: clock source id, high word; original member name unknown.
};

Result ToCalendarTime(CalendarTime *calendarTime, CalendarAdditionalInfo *additionalInfo, const PosixTime &posixTime);
Result GetSpanBetween(s64 *span, const SteadyClockTimePoint &from, const SteadyClockTimePoint &to);

class StandardUserSystemClock {
public:
  static Result GetCurrentTime(PosixTime *posixTime);
};

class StandardSteadyClock {
public:
  static Result GetCurrentTimePoint(SteadyClockTimePoint *timePoint);
};

} // namespace time
} // namespace nn
