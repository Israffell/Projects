testq5: partie1
	./partie1 mt1.txt 10101
	./partie1 mt2.txt 0100
	./partie1 mt3.txt 01110
	
testq8: partie2
#	./partie2 mtq6.txt 101011
	./partie2 mtq7.txt abcda

partie1: partie1.o mt-01.o
	gcc -o partie1 partie1.o mt-01.o

partie1.o: partie1.c
	gcc -c partie1.c

partie2: partie2.o mt-abcd.o
	gcc -o partie2 partie2.o mt-abcd.o

partie2.o: partie2.c
	gcc -c partie2.c

mt-01.o: mt-01.c mt-01.h
	gcc -Wall -c mt-01.c -g 

mt-abcd.o: mt-abcd.c mt-abcd.h
	gcc -Wall -c mt-abcd.c -g 

valgrind: testq5
	valgrind --leak-check=full --show-leak-kinds=all ./partie1 mt1.txt 10101


clean:
	rm -f *.o
	rm -f partie1
	rm -f patrie2

NOM = YS_HOUNGUEVOU_Thomas-PIRES_GUERREIRO_Alexandre

.PHONY: zip
zip:
	mkdir $(NOM)
	cp *.c *.h *.txt Makefile $(NOM)
	zip -r $(NOM).zip $(NOM)
	rm -rf $(NOM)
	ls -l