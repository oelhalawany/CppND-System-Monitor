#include "processor.h"
#include <string>
#include <vector>
#include <unistd.h>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 

  float Util = 0;
  vector<string> Jiffies =  LinuxParser::CpuUtilization();
  
  _user =        stoi(Jiffies[user]);
  _nice =        stoi(Jiffies[nice]);
  _system =      stoi(Jiffies[system]);
  _idle =        stoi(Jiffies[idle]);
  _iowait =      stoi(Jiffies[iowait]);
  _irq =         stoi(Jiffies[irq]);
  _softirq =     stoi(Jiffies[softirq]);
  _steal =       stoi(Jiffies[steal]);
  _guest =       stoi(Jiffies[guest]);
  _guest_nice =  stoi(Jiffies[guest_nice]);
  
  unsigned long long int usertime = _user - _guest;                             
  unsigned long long int nicetime = _nice - _guest_nice;  
  
  unsigned long long int idlealltime = _idle + _iowait;
  unsigned long long int systemalltime = _system + _irq + _softirq;
  unsigned long long int virtalltime = _guest + _guest;
  unsigned long long int totaltime = _user + _nice + systemalltime + idlealltime + steal + virtalltime;

  Util = (totaltime - idlealltime) / totaltime;
  
  
  
  return Util;
  
}