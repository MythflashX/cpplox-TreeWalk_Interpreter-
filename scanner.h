#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <string>
#include <vector>

#include "error_handler.h"
#include "token.h"
#include "object.h"

class Scanner
{
  private:
                                              // fl[a]gs
    int start {0};
    int current {0};
    int line{1};
                                              // d[a]ta st[o]rage
    const std::string source;
    std::vector<Token> tokens;                

  public:
    //// - con[s]tructors -
    Scanner ();
    Scanner (std::string source_);

    //// - func[t]ions -
                                              // - cond[i]tion ch[e]ckers
    bool isAtEnd ();
                                              // - lo[o]k ah[e]ad
    char advance ();
                                              // - to[k]en han[d]lers
    std::vector<Token> scanTokens ();
    void scanToken ();
    void addToken (TokenType type, Object literal = Object{nullptr});
};

#endif
