# Out
OUT = -o ./out/bin

# Flags
# -Wall = Warn ALl
FLAGS = -Wall

# C++ Standard Version
CPPSTDV = -std=c++2a

# File(s)
FILES = ./examples/main.cpp

# Default / Main
buildAndRunMain: clear buildMain runMain

# Builds executable
buildMain:
	g++ $(FILES) $(OUT) $(CPPSTDV) $(FLAGS)

# Runs the outputed file
runMain: clear
	./out/bin

# Clears The Terminal
clear:
	clear

# Cleans Outs
clean:
	rm ./out/*
