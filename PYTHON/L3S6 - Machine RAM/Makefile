run: main main.py
	python3 main.py

main: regexp textEntrance.txt
	./regexp < textEntrance.txt

regexp: regexp.yy.c regexp.tab.c
	gcc -o $@ $^ -ly -ll

regexp.tab.c: regexp.y
	bison -d --report=all $^

regexp.yy.c: regexp.l
	flex -o $@ $^

install:
	sudo apt-get install -y libbison-dev

clean:
	rm -f regexp.yy.c regexp.output regexp.tab.c regexp.tab.h regexp
	rm -rf __pycache__
	ls -als
	truncate -c -s 0 main.py