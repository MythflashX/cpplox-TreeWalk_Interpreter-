# Compiler and flags
CC := g++
CFLAGS := -std=c++20 -Wall -Wextra

# Source Object Header
SRCS := lox.cpp error_handler.cpp token.cpp scanner.cpp object.cpp
OBJS := $(SRCS:.cpp=.o)
HEADERS := error_handler.h tokentype.h token.h scanner.h object.h

# Target executable
TARGET := obnox

# Build rule
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Compile rule
%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
		rm -f $(OBJS)
