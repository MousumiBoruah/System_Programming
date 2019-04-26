#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(){
	FILE *f_obj_prog = fopen("object_program.txt","r");
	FILE *f_load = fopen("Absolute_loader_sic.txt","w");
	char start_add[5],line1[20];
	int i,j = 0,add;
	fgets(line1,1000,f_obj_prog);
	for(i = 9;i < 13;i++){
		start_add[j++] = line1[i];
	}
	printf("%s\n",start_add);
	add = atoi(start_add);
	printf("A:%X\n",add);
}