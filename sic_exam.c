#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(){
	FILE *f_source = fopen("sic_exam.txt","r");
	FILE *f_opc =  fopen("sic_opcode.txt","r");
	FILE *f_des = fopen("destination.txt","w");
	FILE *f_sym = fopen("symbol_tab.txt","r");
	int loc,opc,add,temp_3,loc_1,i=0;
	char label[20],mnemonics[20],mne[20],operand[20],temp[5],temp_1[5],temp2[5],lbl[15],buffer[9];
	while(fscanf(f_source,"%X %s %s %s",&loc,label,mnemonics,operand) == 4){
		if(strcmp(mnemonics,"LDX") == 0){
			strcpy(temp,operand);
			printf("temp=%s\n",temp);
		}
	}
	rewind(f_source);
	while(fscanf(f_source,"%X %s %s %s",&loc,label,mnemonics,operand) == 4){
		if(strcmp(label,temp) == 0){
			strcpy(temp_1,operand);
			printf("temp1=%s\n",temp_1);
		}
	}
	rewind(f_source);
	while(fscanf(f_source,"%X %s %s %s",&loc,label,mnemonics,operand) == 4){
			if(operand[strlen(operand)-1] == 'X'){
				while(fscanf(f_opc,"%s %X",mne,&opc) == 2){
					printf("mmm");
					if(strcmp(mne,mnemonics) == 0){
						printf("nnnn");
						while(fscanf(f_sym,"%X %s",&loc_1,lbl) == 2){
							while(i < strlen(operand)-2){
								buffer[i] = operand[i];
								i++; 
							}
							if(strcmp(buffer,lbl) == 0){
								temp_3 = loc_1;
								printf("loc=%X",temp_3);
							}
						}
						rewind(f_sym);
						add = 32768 + temp_3;
						fprintf(f_des,"%X %s %s %s %X%X\n",loc,label,mnemonics,operand,opc,add);
					}
				}
				rewind(f_opc);
			}
			else{
				while(fscanf(f_opc,"%s %X",mne,&opc) == 2){
					//printf("mmm");
					if(strcmp(mne,mnemonics) == 0){
						//printf("nnnn");
						while(fscanf(f_sym,"%X %s",&loc_1,lbl) == 2){
							if(strcmp(operand,lbl) == 0){
								temp_3 = loc_1;
								printf("loc=%X",temp_3);
							}
						}
						rewind(f_sym);
						add =  temp_3;
						fprintf(f_des,"%X %s %s %s %.2X%X\n",loc,label,mnemonics,operand,opc,add);
					}
				}
				rewind(f_opc);
			}
	}
}