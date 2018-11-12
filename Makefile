target = tcp_server

SRCS = main.cpp

OBJS = $(SRCS:%.cpp=%.o)

CPP = g++

all: $(target)

$(target):$(OBJS)
	$(CPP)  $(OBJS) -o $@

%.o:%.cpp
	$(CPP) -c $<

.PHONY:clean
clean:
	rm -f $(target)
	rm -f $(OBJS)
