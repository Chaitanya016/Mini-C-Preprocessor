	CC = gcc
CFLAGS = -Wall -Wextra -g

TARGET = my_preprocessor

OBJS = main.o headerFile_Inclusion.o removeComments.o replaceMacro.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

main.o: main.c header.h
	$(CC) $(CFLAGS) -c main.c

headerFile_Inclusion.o: headerFile_Inclusion.c header.h
	$(CC) $(CFLAGS) -c headerFile_Inclusion.c

removeComments.o: removeComments.c header.h
	$(CC) $(CFLAGS) -c removeComments.c

replaceMacro.o: replaceMacro.c header.h
	$(CC) $(CFLAGS) -c replaceMacro.c

clean:
	rm -f $(OBJS) $(TARGET)