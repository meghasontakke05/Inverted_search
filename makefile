CC = gcc

OBJ = main.o hash.o create_database.o display.o file_present.o save_database.o search_database.o update_database.o validation.o

invSearch.exe: $(OBJ)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -c $<

clean:
	rm -f *.o invSearch.exe