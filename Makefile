CF = -std=c++11 
DEPS = -lglfw3 -lGL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread -ldl
C = g++
FILES = main.cpp
OUTPUT = out

main: main.cpp
	$(C) $(CF) $(FILES) $(DEPS) -o $(OUTPUT) 
