CC=gcc
CFLAGS=-I.
DEPS = BoardLib.h WordsLib.h
OBJ = main.o BoardLib.o WordsLib.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

run: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	.\$@

.PHONY: clean
clean:
	powershell " Remove-Item -ErrorAction Ignore main.o; $$null"
	powershell " Remove-Item -ErrorAction Ignore BoardLib.o; $$null"
	powershell " Remove-Item -ErrorAction Ignore WordsLib.o; $$null"