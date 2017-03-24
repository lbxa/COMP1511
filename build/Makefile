#Makefile: Lucas Barbosa
C_FLAGS= -Wall -Werror -O
C_COMP=gcc

MAIN_SRC=$(wildcard *.c)
MAIN_O=main.o
ALL_O=$(wildcard *.o)

default_comp:  
	$(C_COMP) $(MAIN_SRC) $(C_FLAGS) -o $(MAIN_O)
   
run: $(MAIN_O) 
	./$(MAIN_O)

clean:
	rm -r $(ALL_O)
