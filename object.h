#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <variant>
#include <string>
#include <stdexcept>

typedef std::variant<double, std::string, std::nullptr_t> variant;

class Object
{
  private:
                                        //// - mem[b]er v[a]riables -
    variant obj;              // store one of the specified type in template argument

  public:
                                        //// - con[s]tructors
    Object ();
    Object (variant obj_);    // std::variant made it possible to build a constructor that can handle multiple data types
    
                                        //// - fun[c]tions
    friend std::ostream& operator<< (std::ostream& os, const Object& o);
};

#endif
