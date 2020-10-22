CC=gcc
RESULT=simplenav
TARGET=$(RESULT).c
INCLUDE=-I include/
CC_FLAGS=`pkg-config --libs --cflags webkit2gtk-4.0` $(INCLUDE)
OBJS=$(RESULT).o

all: $(RESULT).o

$(RESULT).o: $(TARGET)
	$(CC) -o $(RESULT) $(TARGET) $(CC_FLAGS)

clear:
	rm  $(RESULT)
