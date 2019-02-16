CC = g++ -g -std=c++11
RM = rm -f
OBJS = test_list.o

proj2.x: test_list.o
	$(CC) -o proj2.x test_list.o
test_list.o: test_list.cpp
	$(CC) -c test_list.cpp
clean:
	@echo "Cleaning up..."
	$(RM) $(OBJS)
