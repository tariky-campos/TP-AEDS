CC = gcc
CFLAGS = -Wall -g
SOURCES = DadosSonda.c ListaSondasEspaciais.c compartimento.c listamineral.c mainFINALTAR.c mineral.c rochamineral.c menu.c
OBJFILES = $(SOURCES:.c=.o)
EXEC = app

all: $(EXEC)

$(EXEC): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJFILES) -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
ifeq ($(OS),Windows_NT)
	del /Q $(OBJFILES) $(EXEC).exe
else
	rm -f $(OBJFILES) $(EXEC)
endif
