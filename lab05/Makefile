CC = gcc
CFLAGS = -std=c99 -Wall -Werror

app.exe: main.o operations.o queue_list.o queue_array.o results.o
	$(CC) -o $@ $^

main.o: main.c main.h	
	$(CC) $(CFLAGS) -c $<

results.o: results.c results.h
	$(CC) $(CFLAGS) -c $<

operations.o: operations.c operations.h 
	$(CC) $(CFLAGS) -c $<

queue_list.o: queue_list.c queue_list.h 
	$(CC) $(CFLAGS) -c $<

queue_array.o: queue_array.c queue_array.h 
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) *.o *.exe
