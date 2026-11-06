#include "ml/time_util.h"

#include <math.h>

#include "ml/dev_clock.h"
#include "mm_mtl/fixstr.h"
#include "nn/result.h"
#include "nn/time.h"

namespace ml {

bool TimeUtil::getTime(TimeInfo &info) {
  nn::time::PosixTime posixTime;
  nn::Result result = nn::time::StandardUserSystemClock::GetCurrentTime(&posixTime);
  if (result.IsSuccess()) {
    nn::time::CalendarTime calendarTime;
    nn::time::CalendarAdditionalInfo additionalInfo;
    nn::time::ToCalendarTime(&calendarTime, &additionalInfo, posixTime);
    info.unknown06_2 = calendarTime.year;
    info.unknown05_6 = calendarTime.month;
    info.unknown04_0 = calendarTime.day;
    info.unknown04_5 = additionalInfo.dayOfYear;
    info.unknown03_2 = calendarTime.hour;
    info.unknown02_4 = calendarTime.minute;
    info.unknown01_6 = calendarTime.second;
    long clock;
    DevClock::getClockNow(clock);
    f32 sec = DevClock::getClock2Sec(clock);
    info.unknown00_0 = static_cast<u32>(fmodf(sec, 1.0f) * 1000.0f);
    return true;
  }
  return false;
}

bool TimeUtil::getDateStr(mm::mtl::FixStr<64> &str) {
  str.clear();
  TimeInfo info;
  if (getTime(info)) {
    str.format("%04d/%02d/%02d", info.unknown06_2, info.unknown05_6, info.unknown04_0);
    return true;
  }
  return false;
}

bool TimeUtil::getTimeStr(mm::mtl::FixStr<64> &str) {
  str.clear();
  TimeInfo info;
  if (getTime(info)) {
    str.format("%02d:%02d:%02d", info.unknown03_2, info.unknown02_4, info.unknown01_6);
    return true;
  }
  return false;
}

bool TimeUtil::getSteadyClock(SteadyClockInfo &info) {
  nn::time::SteadyClockTimePoint timePoint;
  nn::Result result = nn::time::StandardSteadyClock::GetCurrentTimePoint(&timePoint);
  if (result.IsSuccess()) {
    info.unknown00 = timePoint.unknown00;
    info.unknown10 = timePoint.unknown10;
    info.unknown08 = timePoint.unknown08;
    return true;
  }
  return false;
}

bool TimeUtil::getElapseSec(long &elapsed, const SteadyClockInfo &from, const SteadyClockInfo &to) {
  nn::time::SteadyClockTimePoint fromPoint;
  fromPoint.unknown00 = from.unknown00;
  fromPoint.unknown10 = from.unknown10;
  fromPoint.unknown08 = from.unknown08;
  nn::time::SteadyClockTimePoint toPoint;
  toPoint.unknown00 = to.unknown00;
  toPoint.unknown10 = to.unknown10;
  toPoint.unknown08 = to.unknown08;
  long span;
  nn::Result result = nn::time::GetSpanBetween(&span, fromPoint, toPoint);
  elapsed = result.IsSuccess() ? span : 0;
  return result.IsSuccess();
}

int TimeUtil::aggregateNumberOfDays(int year, int month, int day) {
  if (month < 3) {
    year -= 1;
    month += 12;
  }
  return day + year * 365 - 366 - year / 100 + (year >> 2) + (year / 100 >> 2) + (month * 979 - 1033 >> 5);
}

} // namespace ml
