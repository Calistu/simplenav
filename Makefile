CC=gcc
RESULT=simplenav
TARGET=$(RESULT).c
INCLUDE=-I include/
CC_FLAGS=`pkg-config --libs --cflags webkit2gtk-4.0` $(INCLUDE)
OBJS=init.o http.o home.o

all: objects.o

init.o: src/init.c
	$(CC) -c src/init.c $(CC_FLAGS)

http.o: src/http.c
	$(CC) -c src/http.c $(CC_FLAGS)

home.o: src/home.c
	$(CC) -c src/home.c $(CC_FLAGS)

objects.o: $(OBJS)
	$(CC) $(OBJS) $(TARGET) -o $(RESULT)  $(CC_FLAGS)

clear:
	rm *.o $(RESULT)
