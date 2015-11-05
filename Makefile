CF = -std=c++11 -lglfw3 -lGL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread
C = g++
FILES = main.cpp
OUTPUT = out

main: main.cpp
	$(C) $(FILES) $(CF) -o $(OUTPUT) 
