appName := app

sources = $(wildcard src/*.cpp src/*/*.cpp)
objects = $(sources:.cpp=.o)
includePath = include

flagsWarnings := -Werror -Wall -Wextra
flagsCppVersion := -std=c++26

all: $(objects)
	$(CXX) $^ -o $(appName)

$(objects): %.o: %.cpp
	$(CXX) $(flagsWarnings) $(flagsCppVersion) -I$(includePath) -c $^ -o $@

clean:
	rm -f $(appName) $(objects)