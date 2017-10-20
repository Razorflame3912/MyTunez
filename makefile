mytunez: LLstruct.c LLstruct.h mytunez.c mytunez.h
	gcc -c LLstruct.c mytunez.c
	gcc -o out LLstruct.o mytunez.o
run: out
	./out
clean: out
	rm *.o
	rm out
