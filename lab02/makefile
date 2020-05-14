CC = gcc
CFLAGS = -std=c99 -Wall -Werror -pedantic
app.exe: main.o file_oper.o contacts_array_oper.o 
	$(CC) -o $@ $^
main.o: main.c file_oper.o contacts_array_oper.o struct_contact.h
	$(CC) $(CFLAGS) -c $<
file_oper.o: file_oper.c file_oper.h struct_contact.h
	$(CC) $(CFLAGS) -c $<
contacts_array_oper.o: contacts_array_oper.c contacts_array_oper.h struct_contact.h
	$(CC) $(CFLAGS) -c $<
clean:
	$(RM) *.o *.exe

