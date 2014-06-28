SOURCES := GarageServer.cc 

HEADERDIR := PiServer 
LIBNAME := PiServer

OBJS = $(SOURCES:%.cc=%.o)
DEPEND = $(SOURCES:%.cc=%.d)

CFLAGS :=  -std=c++11 -pthread -Wall -Winit-self 
LINKFLAGS := -lpthread -lprotobuf

EXE = GarageServer
LINKFLAGS = -l$(LIBNAME) -lprotobuf -lpthread 

# link
PiServer: $(OBJS)
	g++ $(OBJS) -o $(EXE) $(LINKFLAGS)


# pull in dependency info for *existing* .o files
-include $(OBJS:.o=.d)

# compile and generate dependency info
%.o: %.cc
	g++ -c $(CFLAGS) $*.cc -o $*.o 
	g++ -MM $(CFLAGS) $*.cc > $*.d

.c.o:
	$(CC) -c $*.c -o $*.o


# remove compilation products
clean:
	rm -f *.o *.d $(EXE)
