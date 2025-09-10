CXX = g++
CXXFLAGS = -std=c++20 -Wall `pkg-config --cflags sdl2 SDL2_ttf` -I .
LDFLAGS  = `pkg-config --libs sdl2 SDL2_ttf`
SRCS = main.cpp game.cpp entity.cpp fruit.cpp movable.cpp snake.cpp
OBJS = $(patsubst %.cpp,build/%.o,$(SRCS))
TARGET = build/snake

all: build $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

build/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build:
	mkdir -p build

clean:
	rm -rf build/
