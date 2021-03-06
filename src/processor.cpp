#include "processor.h"
#include <string>
#include <vector>
#include <unistd.h>
#include <iostream>

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
  
  float idlealltime = _idle + _iowait;
  float systemalltime = _system + _irq + _softirq;
  float virtalltime = _guest + _guest;
  float totaltime = _user + _nice + systemalltime + idlealltime + steal + virtalltime;

  Util = (totaltime - idlealltime) / totaltime;
  
  return Util;
  
}