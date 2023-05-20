#ifndef OBJECT_H
#define OBJECT_H

#include <variant>
#include <string>

class Object
{
  private:
    double doubV;
    char charV;
    std::string striV;
    
  public:
    Object ();
    Object (double doubV_);
    Object (char charV_);
    Object (std::string striV_);

    friend std::ostream& operator<< (std::ostream& oupt, const Object& obj);

    template <typename variant>
    variant return_obj ();
};

#endif
