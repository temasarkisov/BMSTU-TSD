CC = gcc
CFLAGS = -std=c99 -Wall -Werror

app: main.o stack_array_oper.o stack_list_oper.o word_oper.o stats.o
	$(CC) -o $@ $^

main.o: main.c main.h	
	$(CC) $(CFLAGS) -c $<

stats.o: stats.c stats.h 
	$(CC) $(CFLAGS) -c $<

word_oper.o: word_oper.c word_oper.h 
	$(CC) $(CFLAGS) -c $<

stack_list_oper.o: stack_list_oper.c stack_list_oper.h 
	$(CC) $(CFLAGS) -c $<

stack_array_oper.o: stack_array_oper.c stack_array_oper.h 
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) *.o *.exe
