#Makefile: Lucas Barbosa
C_FLAGS= -Wall -Werror -std=c99 -O -m64 
C_COMP=gcc

# -Wall 	   : Warning[all]
# -Werror    : Warning[error]
# -std=c99   : C99 ANSI & C99 ISO standard
# -O         : Compilation optimiser
# -m64       : 64 bit architecture

MAIN_SRC=mandelbrot.c
MAIN_O=main.o
ALL_O=$(wildcard *.o)

default_comp: mandelbrot.c
	$(C_COMP) $(MAIN_SRC) $(C_FLAGS) -o $(MAIN_O)
   
run: $(MAIN_O) 
	./$(MAIN_O)

clean:
	rm -r $(ALL_O)

