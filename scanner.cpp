#include "scanner.h"

//// - con[s]tructors
Scanner::Scanner () {}
Scanner::Scanner (std::string source_) : source{source_} {}

//// - func[t]ions -
                                                // - condi]tion ch[e]ckers -
bool Scanner::isAtEnd() 
  { return current >= source.length(); }

                                                // - lo[o]k ah[e]ad -
char Scanner::advance ()
  { return source[current++]; }


                                                // - to[k]en han[d]lers -
std::vector<Token> Scanner::scanTokens ()
{
  while (!isAtEnd())
  {                   // at the beginning of next lexeme
    start = current;  // current will advance in the following functions and by the start of new loop current will be at the end of the previous lexeme thus...assigning start as current where current will advance again in this loop
    scanToken();      // scan a single token and add them inside tokens 
  }

  tokens.emplace_back(END_OF_FILE, "", Object{nullptr}, line);  // complete the tokens with fine END_OF_FILE                                               
  return tokens;
}

void Scanner::addToken (TokenType type, Object literal)
{
  std::string text {source.substr(start, current)};   // start will be start of lexeme and current will be the word count to take
  tokens.emplace_back(type, text, literal, line);     // add a token in tokens
}

void Scanner::scanToken ()
{
  char fetch = advance ();
  switch (fetch)
  {
  // - si[n]gle cha[r]acter to[k]ens -
    case '(':   addToken(LEFT_PAREN,    Object{"hello world"});     break;
    case ')':   addToken(RIGHT_PAREN);                      break;
    case '{':   addToken(LEFT_BRACE);                       break;
    case '}':   addToken(RIGHT_BRACE);                      break;
    case ',':   addToken(COMMA);                            break;
    case '.':   addToken(DOT);                              break;
    case '-':   addToken(MINUS);                            break;
    case '+':   addToken(PLUS);                             break;
    case ';':   addToken(COMMA);                            break;
    case '*':   addToken(STAR);                             break;
    
    default: break;
  }
}
