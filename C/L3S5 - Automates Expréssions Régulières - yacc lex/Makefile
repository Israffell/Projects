LDFLAGS="-L/usr/local/opt/flex/lib"

## L'organisation des fichiers est la suivant
# 
# regexp.l -- flex --> lex.yy.c
# regexp.y -- bison --> regexp.tab.c
# 
# lex.yy.c + regexp.tab.c -- gcc --> regexp
# 
# test.1 -- regexp --> main.c
# 
# automate.c -- gcc --> automate.o
# main.c -- gcc --> main.o
# 
# automate.o + main.o -- gcc --> main
# 
# Finalement c'est l'exécution du main qui fait ce qui est demandé
# 

run: main
	./main

main: automate.o main.o
	gcc -Wall -o main automate.o main.o

automate.o: automate.c automate.h
	gcc -c -Wall automate.c

main.o: main.c automate.h
	gcc -c -Wall main.c

main.c: regexp test.1
	./regexp < test.1

# Commenter deux des trois lignes en fonction de l'ordi
# La deuxième et la troisième est normalement pour les MAC
# La première pour les autres systèmes
# il faut éventuelleme,nt remplacer -ll par -lfl
regexp: lex.yy.c regexp.tab.c
#	gcc -o $@ $^ -ly -ll
#	gcc -o $@ $^ ${LDFLAGS} -ly -lfl
	gcc -mmacosx-version-min=13.1 -o $@ $^ ${LDFLAGS} -ly -lfl

regexp.tab.c: regexp.y
	bison -d --report=all $^
#	bison -d -v -g $^
# -d pour générer le fichier exo01.tab.h
# -v pour générer le fichier exo01.output
# -g pour générer le fichier exo01.vcg

lex.yy.c: regexp.l
	flex -o $@ $^



#

install:
	sudo apt-get install -y libbison-dev


clean:
	# Ce qui est généré par bison
	rm -f lex.yy.c	rm -f regexp.output regexp.tab.c regexp.tab.h
	# Ce qui est généré par flex
	rm -f lex.yy.c
	# L'exécutanle regexp
	rm -f regexp
	# Ce qui est généré à partir de regexp automate.c et de main.c
	rm -f automate.o main.o main.c
	# L'exécutable main
	ls -als

LADIR="IN520_Projet_Langage_C"
zip:
	rm -rf ${LADIR}
	mkdir ${LADIR}
	cp Makefile automate.h main.1.c ${LADIR}
	cp automate_etudiant.c ${LADIR}/automate.c
	cp test.1 ${LADIR}
	rm -f ${LADIR}.zip
	zip -r ${LADIR}.zip ${LADIR}
	rm -rf ${LADIR}

