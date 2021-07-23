#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "linux_parser.h"

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
  enum Jiff{user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice};
  int _user, _nice, _system, _idle, _iowait, _irq, _softirq, _steal, _guest, _guest_nice;
};

#endif