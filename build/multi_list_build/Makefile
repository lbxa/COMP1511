#Makefile: Lucas Barbosa | Open source software
C_FLAGS := -Wall -Werror -std=c99 -g -m64 -pedantic
CXX     := gcc

# -Wall 	 : Warning[all]
# -Werror    : Warning[error]
# -std=c99   : C99 ANSI & C99 ISO standard
# -pedantic  : ISO error thrower mode
# -O         : Compilation optimiser
# -m64       : 64 bit architecture
# -g         : GDB Debugging mode (Turn off -O optimiser)

# automatically link all .c source code files
MAIN_SRC := $(wildcard *.c)	
MAIN_O   := main.o
ALL_O    := $(wildcard *.o)

default_action: compile_all run_all
	
compile_all:
	@echo "Compiling Code..."
	$(CXX) $(MAIN_SRC) $(C_FLAGS) -o $(MAIN_O)
	 
run_all: $(MAIN_O)
	@echo "Executing code..."
	./$<

clean: $(ALL_O)
	@echo "Clearning object files..."
	rm -r $<

