#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

//Constructor
Process::Process(int pid) {
  _pid = pid;
  _cpu_util = Process::CpuUtilization();
  _cmd = LinuxParser::Command(_pid);
  _ram = LinuxParser::Ram(_pid);
  _usr = LinuxParser::User(_pid);
  _uptime = LinuxParser::UpTime(_pid);
}

// TODO: Return this process's ID
int Process::Pid() { return _pid; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return _cpu_util; }

// TODO: Return the command that generated this process
string Process::Command() { return _cmd; }

// TODO: Return this process's memory utilization
string Process::Ram() { return _ram; }

// TODO: Return the user (name) that generated this process
string Process::User() { return _usr; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return _uptime; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
   return a._cpu_util < _cpu_util; 
}