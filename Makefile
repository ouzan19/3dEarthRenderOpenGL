LIB=-Llib
INC=-Iinc
SRC=hw3.cpp glinit.cpp glentry.cpp utils.cpp	
DIRS=lib/ inc/ res/

all:
	g++ $(SRC) $(LIB) $(INC) -o hw3 -lGL -lGLU -lglut -lSOIL -lpthread
	
dist:
	@tar -czvf hw3.tar.gz $(DIRS) $(SRC) Makefile --exclude "*~"
