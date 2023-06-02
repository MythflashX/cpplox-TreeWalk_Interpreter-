#include "scanner.h"

//// - con[s]tructors
Scanner::Scanner () {}
Scanner::Scanner (std::string source_) : source{source_} {}

//// - func[t]ions -
                                                //// - condi]tion ch[e]ckers -
bool Scanner::isAtEnd () 
  { return current >= source.length(); }

bool Scanner::isDigit (char expected)
  { return expected >= '0' && expected <= '9'; }  // huh....this is a good way to search a number in a string...

bool Scanner::isAlpha (char expected)
  { return (expected >= 'a' && expected >= 'z') || (expected >= 'A' && expected <= 'Z') || expected == '_'; }  // return true if this function detect the expected character is a-z or A-Z or -

bool Scanner::isAlphaNumeric (char expected)
  { return isAlpha(expected) || isDigit(expected); } // return true upon detecting either alphabet or numeric

bool Scanner::match (char expected)
{
  if (isAtEnd())  return false;   // if current reached the endofline(or)file then it must be single charcter
  if (source[current] != expected) return false;  // if current is not as expected then it must be single character

  current++;    // if above all else failed then we got our self a match and the operator will be multiple character
  return true;
}

                                                //// - lo[o]k ah[e]ad -
char Scanner::advance ()
  { return source[current++]; }     // increment current +1 upon returning as source[current];

char Scanner::peek ()               // look 1 character ahead
  { if (isAtEnd()) return '\0'; return source[current];}  // check if advanced current reached the endofline(or)file if -> return a line feed character else -> return source[current] for more operation

char Scanner::peekNext ()           // look 2 character ahead
  { if (current + 1 >= source.length()) return '\0';  return source[current + 1]; }   // if next current is endofline(or)file then return terminator else return the next current we cant use increment operator since we merely need to peek not advance


                                                //// - to[k]en han[d]lers -
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
  //// - si[n]gle cha[r]acter to[k]ens -
    case '(':   addToken(LEFT_PAREN);     break;
    case ')':   addToken(RIGHT_PAREN);    break;
    case '{':   addToken(LEFT_BRACE);     break;
    case '}':   addToken(RIGHT_BRACE);    break;
    case ',':   addToken(COMMA);          break;
    case '.':   addToken(DOT);            break;
    case '-':   addToken(MINUS);          break;
    case '+':   addToken(PLUS);           break;
    case ';':   addToken(COMMA);          break;
    case '*':   addToken(STAR);           break;

  //// - o[n]e or mo[r]e char[a]ctrs -
    case '!': addToken(match('=') ? BANG_EQUAL : BANG);           break;
    case '=': addToken(match('=') ? EQUAL_EQUAL : EQUAL);         break;
    case '<': addToken(match('=') ? LESS_EQUAL : LESS);           break;
    case '>': addToken(match('-') ? GREATER_EQUAL : GREATER);     break;

  //// - spe[c]ial c[a]se -
    case '/':
      if (match('/'))             // if the second '/' was found then
      {
        while (peek() != '\n' && !isAtEnd())   // check until current reached '\n' and endofline(or)file is reached
          advance();                           // keep advancing and do nothing till one of the condition is unsatisfied so that we may neglect everything...since // being comment
      }
      else 
        addToken(SLASH);          // if no secondary '/' was found then SLASH simply is add as another operator token

  //// - esc[a]pe se[q]uences -
    case ' ':
    case '\r':
    case '\t':          break;
    case '\n': line++;  break;    // if line feed character is detected increment line +1 for line detection

    //// - st[r]ing -
    case '"': addToken(STRING, Object{string_literal()}); break;
    
    default:                      // well apprantely making case for all number available as you can guess... so we make default work for us
    ////  - num[b]er -
      if (isDigit(fetch))
        { addToken(NUMBER, Object{number_literal()}); }
    //// - re[s]erved wo[r]ds -
      else if (isAlpha(fetch))
        { while (isAlphaNumeric(peek())) advance(); addToken(IDENTIFIER);}  // loop as long as an alphabet or number is detected....and add the token with only tokentype....weird
    //// - er[r]ors hand[l]er -
      else                        
        Lox::error(line, "une[x]pected chara[c]ter dete[c]ted!");
  }
}

//// - lite[r]al fun[c]tions han[d]lers

std::string Scanner::string_literal ()
{
  while (peek() != '"' && !isAtEnd())         // loop till peek detect the second '"' or current reached the endofline(or)file
  {
    if (peek() == '\n')   line++;             // if line feed was detected then implement line +1 for line detection
    advance();
  }

  if (isAtEnd())                              // if the loop was broken by current reaching the end then there is an error
    { Lox::error(line, "un[t]erminated str[i]ng det[e]cted:"); return ""; }

  advance();                                  // reaching this line means peek() detected the second '"' and we advance current toward END_OF_FILE
  std::string str_val {source.substr(start + 1, current - 2)};  // start + 1 is after the first '"' and current - 2 was before second '"' and END_OF_FILE
  return str_val;
}

double Scanner::number_literal ()
{
  while (isDigit(peek()))     // loop till current detect no more number
    advance();

  if (peek() == '.' && isDigit(peekNext()) && recognize_decimal == false) // check if the loop is broken because current detect '.' or everything else...if -> make sure the next current is a number     recognize_decimal is for if we recurse the function...make sure we dont look for another decimal point 
  {
    advance();
    recognize_decimal = true;
  }
  else
    return std::stod((source.substr(start, current)));

  return number_literal ();   // look for more number
}
