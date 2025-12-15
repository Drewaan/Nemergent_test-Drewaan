CC = gcc
CFLAGS = -Wall -Wextra -pthread -g
TARGET = entropy

SRCS = src/main.c \
       src/bucket/bucket_init.c \
       src/bucket/bucket_ops.c \
       src/bucket/bucket_utils.c \
       src/world/world_init.c \
       src/world/world_ops.c \
       src/workers/thread_worker.c \
       src/workers/random_gen.c \
       src/display/results_display.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean