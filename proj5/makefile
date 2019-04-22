CC = g++ -g -lcrypt -std=c++11
RM = rm -f

proj5.x: proj5.o passserver.o
	$(CC) -o proj5.x proj5.o passserver.o
proj5.o: proj5.cpp
	$(CC) -c proj5.cpp
passserver.o: passserver.cpp
	$(CC) -c passserver.cpp
clean:
	@echo "Cleaning up..."
	$(RM) *.o proj5.x *.gch
