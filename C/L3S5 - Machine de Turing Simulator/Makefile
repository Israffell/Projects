q5LE: QLE
	./QLE left.txt 00000 11111 0101010101
	./QLE erase.txt 00000 11111 000001000

q5search: Qsearch
	./Qsearch 000001 00010 11111 0101011

q5copy: Qcopy
	./Qcopy left.txt 000000 111111 010101

QLE: QLE.o q5-copy.o
	gcc -o QLE QLE.o q5-copy.o

QLE.o: QLE.c
	gcc -c QLE.c

Qsearch: Qsearch.o q5-search.o
	gcc -o Qsearch Qsearch.o q5-search.o

Qsearch.o: Qsearch.c
	gcc -c Qsearch.c

Qcopy: Qcopy.o q5-copy.o
	gcc -o Qcopy Qcopy.o q5-copy.o

Qcopy.o: Qcopy.c
	gcc -c Qcopy.c

q5-search.o: q5-search.c q5-search.h
	gcc -Wall -c q5-search.c -g

q5-copy.o: q5-copy.c q5-copy.h
	gcc -Wall -c q5-copy.c -g

valgrind: testq5
	valgrind --leak-check=full --show-leak-kinds=all ./q5copy left.txt 000000 111111

clean:
	rm -f *.o
	rm -f q5LE
	rm -f q5search
	rm -f q5copy
	rm -f QLE

NOM = PC_PIRES_GUERREIRO_Alexandre-MARTIN_Brice

.PHONY: zip
zip:
	mkdir $(NOM)
	cp *.c *.h *.txt Makefile $(NOM)
	zip -r $(NOM).zip $(NOM)
	rm -rf $(NOM)
	ls -l