CXX = g++
CXXFLAGS = -Wall `pkg-config --cflags sdl2`
LDFLAGS  = `pkg-config --libs sdl2`
SRCS = main.cpp entity.cpp fruit.cpp movable.cpp
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