CC = g++ -g -std=c++11
RM = rm -f

proj5.x: test.o
	$(CC) -o proj5.x test.o
test.o: test.cpp
	$(CC) -c test.cpp
clean:
	@echo "Cleaning up..."
	$(RM) *.o proj5.x *.gch
