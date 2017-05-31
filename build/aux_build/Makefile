#Makefile: Lucas Barbosa
C_FLAGS=-std=c99 -g -Wall -Werror -m64 
C_COMP=gcc

# -Wall 	   : Warning[all]
# -Werror    : Warning[error]
# -std=c99   : C99 ANSI & C99 ISO standard
# -O         : Compilation optimiser
# -m64       : 64 bit architecture
# -g         : Debugging option for GDB

# automatically link all .c source code files
MAIN_SRC=$(wildcard *.c)	
MAIN_O=main.o
ALL_O=$(wildcard *.o)

default_action: compile_all run_all
	
compile_all: 
	$(C_COMP) $(MAIN_SRC) $(C_FLAGS) -o $(MAIN_O)
   
run_all: $(MAIN_O)
	./$(MAIN_O)

clean:
	rm -r $(ALL_O)

