#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "error_handler.h"
#include "scanner.h"
#include "token.h"

namespace Lox {
void run(const std::string &source);
void runFile(const std::string &path);
void runPrompt();
} // namespace Lox

// -r[u]n

void Lox::runFile(const std::string &path) {
  if (hadError)
    throw std::runtime_error(
        "une[x]pected pr[o]blem occu[r]ed wh[i]le exec[u]ting spec[f]ied "
        "f[i]le"); // check to see if there were any error

  std::fstream infi(path);   // open file for read and writing
  std::ostringstream buffer; // store data from file as buffer
  buffer << infi.rdbuf();

  infi.close();
  run(buffer.str()); // buffer from ostring stream is used as
                     // buffer.str()...read data as string that way
}

void Lox::runPrompt() {
  std::cout << "\t\t\t Started ob[n]ox as Interactive prompt: \n\n";
  std::string line;

  while (true) {
    std::cout << "ob[n]ox -> ";
    if (!std::getline(std::cin, line))
      break;   // read user input as line
    run(line); // run as source
  }
}

void Lox::run(const std::string &source) {
  Scanner scanner{source}; // Create a new object scanner
  std::vector<Token> tokens{
      scanner.scanTokens()}; // scan tokens and initialized them inside tokens

  for (const Token &token : tokens) // loop and print to display scanned tokens
    token.print();
}

int main(int argc, char *argv[]) {
  try {
    if (argc > 2) {
      std::cerr << "Us[a]ge: cppl[o]x [script]";
    std:
      exit(64);
    } else if (argc == 2)
      Lox::runFile(argv[1]);
    else
      Lox::runPrompt();
  }

  catch (const std::exception &err) {
    std::cerr << "err[o]r: " << err.what() << std::endl;
    return 1;
  }

  return 0;
}
