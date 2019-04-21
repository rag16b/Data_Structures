CC = g++ -g -std=c++11
RM = rm -f

proj5.x: testPS.o
	$(CC) -o proj5.x testPS.o
testPS.o: testPS.cpp
	$(CC) -c testPS.cpp
clean:
	@echo "Cleaning up..."
	$(RM) *.o proj5.x *.gch
