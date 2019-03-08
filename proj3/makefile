CC = g++ -g -std=c++11
RM = rm -f
OBJS = test_stack1.o
SRC = test_stack1.cpp

proj3.x: $(OBJS)
	$(CC) -o proj3.x $(OBJS)
test_stack1.o: $(SRC)
	$(CC) -c $(SRC)
clean:
	@echo "Cleaning up..."
	$(RM) $(OBJS)
