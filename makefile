playlist: LLstruct.c
	gcc -o out LLstruct.c
run: out
	./out
clean: out
	rm out
