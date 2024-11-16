CC = gcc
CFLAGS = -Wall -g
OBJFILES = DadosSonda.o ListaSondasEspaciais.o compartimento.o listamineral.o mainFINALTAR.o mineral.o rochamineral.o
EXEC = app

all: $(EXEC)

$(EXEC): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJFILES) -lm

DadosSonda.o: DadosSonda.c DadosSonda.h
	$(CC) $(CFLAGS) -c DadosSonda.c

ListaSondasEspaciais.o: ListaSondasEspaciais.c ListaSondasEspaciais.h
	$(CC) $(CFLAGS) -c ListaSondasEspaciais.c

compartimento.o: compartimento.c compartimento.h
	$(CC) $(CFLAGS) -c compartimento.c

listamineral.o: listamineral.c listamineral.h
	$(CC) $(CFLAGS) -c listamineral.c

mainFINALTAR.o: mainFINALTAR.c
	$(CC) $(CFLAGS) -c mainFINALTAR.c

mineral.o: mineral.c mineral.h
	$(CC) $(CFLAGS) -c mineral.c

rochamineral.o: rochamineral.c rochamineral.h
	$(CC) $(CFLAGS) -c rochamineral.c

clean:
ifeq ($(OS),Windows_NT)
	del /Q $(OBJFILES) $(EXEC).exe
else
	rm -f $(OBJFILES) $(EXEC)
endif
