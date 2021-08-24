#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <unistd.h>
#include "linux_parser.h"
#include <iostream>
#include <stdexcept>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  string line, key, value, kB;
  float MemTotal, MemFree;
  bool bMemTotal = false;
  bool bMemFree = false;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      //std::replace(line.begin(), line.end(), 'kB', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value >> kB) {
        if (key == "MemTotal") {MemTotal =  std::stof(value); bMemTotal = true;}
        if (key == "MemFree") {MemFree =  std::stof(value); bMemFree = true;}
        if(bMemTotal && bMemFree) {break;}
      }
    }
  }
  return (MemTotal - MemFree) / MemTotal;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  string uptime, idletime, line;
  long uptime_long = 0;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
  	std::istringstream linestream(line);
    linestream >> uptime;

    uptime_long = std::stol(uptime);
    }
  return uptime_long;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) { 
  vector<string> data;
  string line, value;
  long utime, stime, cutime, cstime, total_time;
  
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename); //Create a steam for reading Process data
  if (stream.is_open()) { //Open file
    std::getline(stream, line); //Read line
    std::istringstream linestream(line); //convert line to line stream
    while (linestream >> value) { //read word by word in the line till finished
			data.push_back(value); //Add each word to vector to use later to access each data seperatly 
        }
    }
  
  utime = std::stol(data[13]);
  stime = std::stol(data[14]);
  cutime = std::stol(data[15]);
  cstime = std::stol(data[16]);
 
  total_time = (utime + stime + cutime + cstime); //in CLK ticks
  
  return total_time;
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  string line, key, user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
  vector<string> Jiffies;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
  	std::istringstream linestream(line);
   	while (linestream >> key >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice){
    	if (key == "cpu"){
          Jiffies.push_back(user);
          Jiffies.push_back(nice);
          Jiffies.push_back(system);
          Jiffies.push_back(idle);
          Jiffies.push_back(iowait);
          Jiffies.push_back(irq);
          Jiffies.push_back(softirq);
          Jiffies.push_back(steal);
          Jiffies.push_back(guest);
          Jiffies.push_back(guest_nice);
          return Jiffies;
        }
      }
    }
  return Jiffies;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string value, line, key;
  int totalProcesses = -1;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)){
  		std::istringstream linestream(line);
    	while (linestream >> key >> value) {
          if (key == "processes"){
            totalProcesses = std::stoi(value);
          }
        }
    }
  }
  return totalProcesses;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string value, line, key;
  int runningProcesses = -1;
  std::ifstream stream(kProcDirectory + kStatFilename);
  
  if (stream.is_open()) {
    while (std::getline(stream, line)){
  		std::istringstream linestream(line);
    	while (linestream >> key >> value) {
          if (key == "procs_running"){
            runningProcesses = std::stoi(value);
          }
        }
    }
  }
  return runningProcesses;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  string line;
  string command = "NA"; 
  
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
        std::getline(stream, line); //Read line
  		std::istringstream linestream(line);
    	linestream >> command;
    }
  
  return command;   
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {
  string line, key, value, kB;
  int val;
  value = "NA"; //initilization value if not found
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)){
  		std::istringstream linestream(line);
    	while (linestream >> key >> value >> kB) {
        	if (key == "VmSize:") {
                val = std::stoi(value)/1024;
            	  return std::to_string(val); // Value returned is converted to Mb
              }
        	}
      	}
    }
  return value; 
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
  string key, value, uid, line;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)){
  		std::istringstream linestream(line);
    	while (linestream >> key >> value) {
        	if (key == "Uid:") { uid = value;}
        	}
      	}
    }
  return uid;
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  string uid, userid, x, username, line;
  username = "unassigned"; //initial value to username if not found
  uid = LinuxParser::Uid(pid);
  std::ifstream stream(kPasswordPath);
  if (stream.is_open()) {
    while (std::getline(stream, line)){
        std::replace(line.begin(), line.end(), ':', ' ');
  		std::istringstream linestream(line);
    	while (linestream >> username >> x >> userid) {
        	if (userid == uid) { return username;}
        	}
      	}
    }
  return username;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
  vector<string> data;
  string line, value;
  long upTime;
  
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename); //Create a steam for reading Process data
  if (stream.is_open()) { //Open file
    std::getline(stream, line); //Read line
    std::istringstream linestream(line); //convert line to line stream
    while (linestream >> value) { //read word by word in the line till finished
			data.push_back(value); //Add each word to vector to use later to access each data seperatly 
        }
    }
  
    try{
      upTime = LinuxParser::UpTime() - std::stol(data[21]) / sysconf(_SC_CLK_TCK); // Convert from CLK ticket to Seconds
    }
    catch (std::runtime_error& e) {
          std::cout << "Exception occurred" << std::endl << e.what();
    }
  
   return upTime;
}
