# Variáveis
CC = gcc                   # Compilador
CFLAGS = -Wall -Wextra     # Flags do compilador
SRCS = $(wildcard *.c)     # Todos os arquivos .c no diretório atual
OBJS = $(SRCS:.c=.o)       # Converte .c para .o
EXEC = main                # Nome do executável final

# Regra principal (executar tudo)
all: $(EXEC)

# Regra para compilar o executável
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Regra para compilar arquivos .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza dos arquivos gerados
clean_win:
	del /Q $(OBJS) $(EXEC).exe

clean_all_win:
	del /Q *~

clean:
	rm -f $(OBJS) $(EXEC)

clean_all:
	rm -f *~

