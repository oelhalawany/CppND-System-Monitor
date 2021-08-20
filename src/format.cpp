#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 

  long total_time = seconds;
  int hrs, mins, sec;
  string time;

  hrs = total_time/3600;
  total_time = total_time%3600;
  mins = total_time/60;
  total_time = total_time%60;
  sec = total_time;

  time = std::to_string(hrs)+':'+std::to_string(mins)+':'+std::to_string(sec);
  return time;




}