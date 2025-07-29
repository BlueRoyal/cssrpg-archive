CXX ?= g++
CXXFLAGS ?= -std=c++11 -fPIC -I. -Ithird_party/sqlite
LDFLAGS ?= -shared
TARGET ?= cssrpg.so

SRCS := $(wildcard *.cpp) \
$(wildcard items/*.cpp) \
$(wildcard third_party/sqlite/*.c)
OBJS := $(SRCS:.cpp=.o)
OBJS := $(OBJS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $(OBJS)

clean:
	 rm -f $(OBJS) $(TARGET)

.PHONY: all clean
