#include <stdexcept>
#include "object.h"

                            //// - cons[t]ructors -
Object::Object () {}
Object::Object (double doubV_) : doubV{doubV_} {}
Object::Object (char charV_) : charV{charV_} {}
Object::Object (std::string striV_) : striV{striV_} {}
    
                            //// - fun[c]tions -
template <typename variant>
variant Object::return_obj ()
{
  if (std::is_same_v<variant, double>)
    return doubV;
  else if (std::is_same_v<variant, char>)
    return charV;
  else if (std::is_same_v<variant, std::string>)
    return striV;

  throw std::runtime_error("un[s]upported t[y]pe detec[t]ed");
}
