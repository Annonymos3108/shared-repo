#Makefile
PROGRAMM_NAME = Polyhedron_Lightning
EXECUTABLE = $(BIN)\$(PROGRAMM_NAME)
CCXX = g++ -std=c++11
CXXFLAGS = -c -I"C:\Program Files\SFML-2.5.1\include" 
BXXFLAGS = -o $(EXECUTABLE) -L"C:\Program Files\SFML-2.5.1\lib" -lsfml-graphics -lsfml-window -lsfml-system
SRC = src
BIN = bin
POLYHEDRON_LIGHTNING = Polyhedron_Lightning
SOURCES =  	$(SRC)\main.cpp \
			$(SRC)\Menu.cpp \
			$(SRC)\$(POLYHEDRON_LIGHTNING)\PLmenu.cpp \
			$(SRC)\$(POLYHEDRON_LIGHTNING)\myMesh.cpp 
			
			
OBJECTS = 	$(BIN)\main.o \
			$(BIN)\Menu.o \
			$(BIN)\$(POLYHEDRON_LIGHTNING)\PLmenu.o \
			$(BIN)\$(POLYHEDRON_LIGHTNING)\myMesh.o 

$(EXECUTABLE) : $(OBJECTS)
	$(CCXX) $(OBJECTS) $(BXXFLAGS)

$(BIN)\main.o : $(SRC)\main.cpp $(BIN)\Menu.o \
				$(BIN)\$(POLYHEDRON_LIGHTNING)\PLmenu.o


	$(CCXX) $(CXXFLAGS) $< -o $(BIN)\$(basename $(<F)).o

$(BIN)\Menu.o : $(addprefix $(SRC)\,Menu.cpp Menu.h)
	$(CCXX) $(CXXFLAGS) $< -o $(BIN)\$(basename $(<F)).o
	

$(BIN)\$(POLYHEDRON_LIGHTNING)\PLmenu.o :	$(SRC)\$(POLYHEDRON_LIGHTNING)\PLmenu.cpp \
									$(SRC)\$(POLYHEDRON_LIGHTNING)\PLmenu.h \
									$(SRC)\OBJ_Loader.h \
									$(BIN)\$(POLYHEDRON_LIGHTNING)\myMesh.o
	$(CCXX) $(CXXFLAGS) $< -o $(BIN)\$(POLYHEDRON_LIGHTNING)\$(basename $(<F)).o	

$(BIN)\$(POLYHEDRON_LIGHTNING)\myMesh.o :	$(SRC)\$(POLYHEDRON_LIGHTNING)\myMesh.cpp \
									$(SRC)\$(POLYHEDRON_LIGHTNING)\myMesh.h
	$(CCXX) $(CXXFLAGS) $< -o $(BIN)\$(POLYHEDRON_LIGHTNING)\$(basename $(<F)).o	
	