#include <string.h>
#include <stdio.h>

int main(void)
{

	char test[50] = "12.345.678.9";
	char *p;

	p = strtok(test,".");

	//1つ目のトークン表示
	puts(p);

	//トークンがNULLになるまでループ
	while(p!=NULL){

		//2回目以降は第一引数はNULL
		p = strtok(NULL,".");

		if(p!=NULL){
			puts(p);
		}

	}


	return 0;
}
