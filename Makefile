
NAME := a.out
PROJDIR := .

SRCS := main.cpp test.cpp
LIBS := 

CC := gcc
CXX := g++
LD := $(CXX)
INCLUDEPATH := -Iinclude
CFLAGS := -O3 $(INCLUDEPATH)
CXXFLAGS := -O3 -std=c++17 $(INCLUDEPATH)

OBJS := $(SRCS:%.c=%.o)
OBJS := $(OBJS:%.cpp=%.o)
OBJS := $(OBJS:%.cc=%.o)
DEPS := $(SRCS:%.c=%.d)
DEPS := $(DEPS:%.cpp=%.d)
DEPS := $(DEPS:%.cc=%.d)

all: $(NAME)

$(NAME): $(OBJS)
	$(LD) $(OBJS) -o $(NAME) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -MMD -MP -MF $(<:%.c=%.d) -c $< -o $(<:%.c=%.o)

.cc.o:
	$(CXX) $(CXXFLAGS) -MMD -MP -MF $(<:%.cc=%.d) -c $< -o $(<:%.cc=%.o)

.cpp.o:
	$(CXX) $(CXXFLAGS) -MMD -MP -MF $(<:%.cpp=%.d) -c $< -o $(<:%.cpp=%.o)

.PHONY: clean
clean:
	-rm $(NAME)
	find $(PROJDIR) -name "*.o" -exec rm {} \;
	find $(PROJDIR) -name "*.d" -exec rm {} \;
	rm -fr _bin
	rm -fr build

.PHONY: run
run:
	./$(NAME)

.PHONY: install
install:
	install -m 755 $(NAME) ~/.local/bin/

.PHONY: uninstall
uninstall:
	rm ~/.local/bin/$(NAME)

-include $(DEPS)

