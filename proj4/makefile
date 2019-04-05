CC = g++ -g -std=c++11
RM = rm -f
DRIV = proj4_driver.cpp
DRIVO = proj4_driver.o

bet.x: bet.o $(DRIVO)
	$(CC) -o bet.x bet.o $(DRIVO)
bet.o: bet.cpp $(DRIV)
	$(CC) -c bet.cpp $(DRIV)
clean:
	@echo "Cleaning up..."
	$(RM) *.o bet.x
