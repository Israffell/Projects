#include "mt-abcd.h"

int main(int argc, char* argv[]) {
	printf("Input: %s\n",argv[2]);
	MT mt;
	lecture_mt_abcd(argc,&argv[1],mt);
	printf("Appuyez sur entrée pour terminer\n");
	getchar();
	return 0;
}