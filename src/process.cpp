#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

//Constructor
Process::Process(int pid) {
  _pid = pid;
  _cpu_util = Process::CpuUtilization();
}

// TODO: Return this process's ID
int Process::Pid() { return _pid; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
  _total_time = LinuxParser::ActiveJiffies(_pid)/sysconf(_SC_CLK_TCK); 
  _seconds = LinuxParser::UpTime(_pid);
  if(_seconds>0){
      return _total_time/_seconds;
  }
  else
  {
     return 0;
  }
  
}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(_pid); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(_pid); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(_pid); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(_pid); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
   return a._cpu_util < _cpu_util; 
}