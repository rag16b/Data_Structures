CC = g++ -g -std=c++11
RM = rm -f
OBJS = test_stack1.o
SRC = test_stack1.cpp

all: in2post.x stack.x

in2post.x: in2post.o
	$(CC) -o in2post.x in2post.o
in2post.o: in2post.cpp stack.h
	$(CC) -c in2post.cpp

stack.x: $(OBJS)
	$(CC) -o stack.x $(OBJS)
test_stack1.o: $(SRC)
	$(CC) -c $(SRC)
clean:
	@echo "Cleaning up..."
	$(RM) in2post.x stack.x *.o
