run: dico
	./dico pg31469.txt

dico: recherche.o tableaux.o ABR.o dico.o
	gcc -o dico recherche.o tableaux.o ABR.o dico.o

recherche.o: recherche.c recherche.h
	gcc -Wall -c recherche.c

tableaux.o: tableaux.c tableaux.h
	gcc -Wall -c tableaux.c

ABR.o: ABR.c ABR.h
	gcc -Wall -c ABR.c

dico.o: dico.c dico.h
	gcc -Wall -c dico.c

valgrind: dico
	valgrind ./dico pg31469.txt

clean:
	rm -f *.o
	rm -f dico

NOM = HOUNGUEVOU_PIRES-GUERREIRO

.PHONY: zip
zip:
	mkdir $(NOM)
	cp *.c *.h data.txt Makefile pg31469.txt $(NOM)
	zip -r $(NOM).zip $(NOM)
	rm -rf $(NOM)
	ls -l