#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>
#include "tokentype.h"
#include "object.h"

class Token
{
  private:
    const TokenType type;
    const std::string lexeme;
    const Object literal;
    const int line;

  public:
    //// - cons[t]ructors -
    Token ();
    Token (TokenType type_, std::string lexeme_, Object literal_, int line_);

    //// - fu[n]ctios -
    void print () const;
    const std::string tokentype_to_string (const TokenType& type) const;
};

#endif
