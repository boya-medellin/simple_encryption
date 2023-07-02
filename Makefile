CC = gcc
CFLAGS =
TARGET = crypto

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) -o $(TARGET) $(TARGET).c $(TARGET).h $(CFLAGS)

clean: 
	$(RM) $(TARGET)
