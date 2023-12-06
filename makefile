# List your *.h files (if you do not have them in your project then leave the variable "headers" empty):
headers = Matrix.h

# List your *.cpp files:
sources = Matrix.cpp TestMatrix.cpp

# Specify name of your program:
executable = matrix

$(executable): $(headers) $(sources)
	g++ -fsanitize=undefined -g -Wall -pedantic $(sources) -o $(executable)

.PHONY: clean
clean:
	rm $(executable)

.PHONY: check
check: $(executable)
	valgrind --leak-check=full --track-origins=yes -s ./$(executable)
#--leak-check=full --show-leak-kinds=all