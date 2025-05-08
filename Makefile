# Compiler and flags
CC = gcc
DEBUG_FLAGS = -g -Wall -Wextra
RELEASE_FLAGS = -Wall -Wextra
LFLAGS = -lpthread

# Source files
SRCS = webserver.c client_handler.c request_handler.c http_stuff.c response_builder.c

# Object files definition
OBJS = $(SRCS:.c=.o)

TARGET = webserver.out


# BUILD STUFF

# Default to debug
all: debug

debug: CFLAGS = $(DEBUG_FLAGS)
debug: $(TARGET)

release: CFLAGS = $(RELEASE_FLAGS)
release: $(TARGET)

# Link object files
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LFLAGS)

# Compile object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Object dependencies
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -f $(TARGET)

.PHONY: all debug release clean