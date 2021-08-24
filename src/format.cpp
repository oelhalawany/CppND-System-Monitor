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
  string time, hrs_str, mins_str, sec_str;

  hrs = total_time/3600;
  total_time = total_time%3600;
  mins = total_time/60;
  total_time = total_time%60;
  sec = total_time;

  if(hrs<10)
  	hrs_str = '0'+std::to_string(hrs);
  else
    hrs_str = '0'+std::to_string(hrs);
  
  if(mins<10)
   mins_str = '0'+std::to_string(mins);
  else
    mins_str = std::to_string(mins);
  
  if(sec<10)
  	sec_str = '0'+std::to_string(sec);
  else
    sec_str = std::to_string(sec);
  
  time = hrs_str+':'+mins_str+':'+sec_str;
  
  return time;




}