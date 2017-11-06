TARGET = test
CC = 
SRC_FILE = main.c
CFLAGS = -fPIE -pie

$(TARGET): $(SRC_FILE)
	$(CC)gcc -g -o $(TARGET) $(SRC_FILE) $(CFLAGS)

clean:
	rm -rf $(TARGET)