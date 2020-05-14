CC = gcc
CFLAGS = -std=c99 -Wall -Werror

app: main.o sparse_matrix_input.o sparse_matrix_oper.o matrix_oper.o 
	$(CC) -o $@ $^

main.o: main.c main.h	
	$(CC) $(CFLAGS) -c $<

sparse_matrix_input.o: sparse_matrix_input.c sparse_matrix_input.h
	$(CC) $(CFLAGS) -c $<

sparse_matrix_oper.o: sparse_matrix_oper.c sparse_matrix_oper.h sparse_matrix_t.h
	$(CC) $(CFLAGS) -c $<

matrix_oper.o: matrix_oper.c matrix_oper.h matrix_t.h
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) *.o *.exe
