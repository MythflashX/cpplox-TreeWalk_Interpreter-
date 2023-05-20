#include "object.h"
          
                      //// - con[s]tructors -
Object::Object () {}
Object::Object (variant obj_) : obj{obj_} {}

std::ostream& operator<< (std::ostream& os, const Object& o)
{
  std::visit (        // std::visit takes "visitor function" and "variant" as argument { visitor function -> lamba function or function obj is a callable object } 
              [&os] (const auto& val)    // lambda function : "val" store value variant and "os" object was captured by labmda with reference make it possible to use it inside labmda
                        {
                          os << val;
                        }, o.obj);            // i think actual type deduction is done by std::visit and store inside val

    return os;
}
