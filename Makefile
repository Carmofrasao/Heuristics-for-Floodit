# Anderson Aparecido do Carmo Frasão (GRR20204069)

CC = gcc 

#-----------------------------------------------------------------------------#
all : main

main: main.o leitura.o busca.o

#-----------------------------------------------------------------------------#

clean :
	$(RM) *.o

#-----------------------------------------------------------------------------#

purge:
	$(RM) main *.o