#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char* HexToBin(char hexdec) 
{ 
      switch (hexdec) { 
        case '0': 
            return("0000\0");  
        case '1': 
           return("0001\0");  
        case '2': 
           return("0010\0");  
        case '3': 
           return("0011\0");  
        case '4': 
           return("0100\0");  
        case '5': 
           return("0101\0");  
        case '6': 
           return("0110\0");  
        case '7': 
           return("0111\0");  
        case '8': 
           return("1000\0");  
        case '9': 
           return("1001\0");  
        case 'A': 
 			return("1010\0");  
        case 'B':  
           return("1011\0");  
        case 'C': 
			return("1100\0");  
        case 'D': 
 			return("1101\0");  
        case 'E': 
 			return("1110\0");  
        case 'F': 
           return("1111\0"); 
        }  

}
int main(){
	FILE *f_source = fopen("sic_xe.txt","r");
	char label[20],mnemonics[20],operand[20],temp_1[20],temp_2[20],object[20];
	int loc,buffer = 0036,base = 0033,disp=0,i,j=0;
	while(fscanf(f_source,"%X %s %s %s",&loc,label,mnemonics,operand) == 4){
		if(operand[strlen(operand)-1] == 'X'){
			for(i = 0; i < strlen(operand) -2;i++){
				temp_1[i] = operand[i];
			}
			temp_1[i] = '\0';
			disp = buffer - base;
			strcpy(object,"010101");
			i = 6;
			object[i] = '0';
			while(i < 12){
				if(i == 6 || i==7 || i == 8 || i==9){
					object[i]='1';
				}
				else
					object[i] = '0';
				i++;
			}
			object[i] = '\0';
			printf("%s%.3X\n",object,disp);

		}
		else
		{
			strcpy(object,"011101");
			i = 6;
			object[i] = '0';
			while(i < 12){
				if( i==7 || i == 11){
					object[i]='1';
				}
				else
					object[i] = '0';
				i++;
			}
			object[i] = '\0';
			printf("%s",object);
			i = 1;
			while(i < strlen(operand)){
				temp_1[j++] = operand[i++];
			}
			temp_1[j] = '\0';
			//printf("0000%s%s%s%s\n",HexToBin(temp_1[0]),HexToBin(temp_1[1]),HexToBin(temp_1[2]),HexToBin(temp_1[3]));
		printf("0%s\n",temp_1);
		}
	}
}
