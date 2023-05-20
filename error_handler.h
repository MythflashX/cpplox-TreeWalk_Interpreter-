#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <iostream>
#include <string>

namespace Lox
{
  // - err[o]r han[d]ling -
  
  static bool hadError { false };    
  void report (int line, const std::string& where, const std::string& message); // Well apparently it is a good practice to separate error codes from codes that report those errors
  void error (int line, const std::string& message);
}

#endif
