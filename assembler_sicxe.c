#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"myfile.h"
int main(){
	FILE *f_prog = fopen("SICXEFILE.txt","r");
	FILE *f_opc = fopen("sicxe_opcode.txt","r");
	FILE *f_p1 = fopen("pass_1.txt","w");
	FILE *f_p2 = fopen("pass_2.txt","w+");
	FILE *f_sym = fopen("symbol_table_sicxe.txt","w");
	FILE *f_obj = fopen("object_code_xe.txt","w");
	char label_1[50],mnemonics[50],operand[50],name[50],temp[50],number[10],object_code[15],mne[20],opcd[20];
	int start_loc,opc,loc,i,j,bin;
	char x[4],y[4],buffer[6],buffer1[6],buffer2[6],opr[6];
	fscanf(f_prog,"%s %*s %.4X",name,&start_loc);
	//FOR PASS_1
	while(fscanf(f_prog,"%s %s %s",label_1,mnemonics,operand) == 3){
		fprintf(f_p1,"%s\t%s\n",label_1,operand);
	}
	rewind(f_prog);
	fscanf(f_prog,"%s %*s %X",name,&start_loc);
	loc = start_loc;
	//FOR INTERMEDIATE
	while(fscanf(f_prog,"%s %s %s",label_1,mnemonics,operand) == 3){
		if(strcmp(mnemonics,"RESW") == 0){
			fprintf(f_p2,"%.4X\t%s\t%s\t%s\n",loc,label_1,mnemonics,operand);
        	loc = loc + (atoi(operand) * 3);
   		}
   		else if(mnemonics[0] == '+'){
   			fprintf(f_p2,"%.4X\t%s\t%s\t%s\n",loc,label_1,mnemonics,operand);
   			loc+=4;
   		}
   		else if(strcmp(mnemonics,"BASE") == 0 || strcmp(mnemonics,"END") == 0){
   			fprintf(f_p2,"----\t%s\t%s\t%s\n",label_1,mnemonics,operand);
   		}
   		else{
   			fprintf(f_p2,"%.4X\t%s\t%s\t%s\n",loc,label_1,mnemonics,operand);
   			loc+=3;
   		}
	}
	rewind(f_prog);
	rewind(f_p2);
	rewind(f_p1);
	//FOR SYMBOL TABLE
	while(fscanf(f_p2,"%s %s %s %s",temp,label_1,mnemonics,operand) == 4){
		if(strcmp(label_1,"----") != 0){
			fprintf(f_sym,"%s\t%s\n",temp,label_1);
		}
	}
	rewind(f_prog);
	rewind(f_p2);
	rewind(f_p1);
	rewind(f_sym);
	rewind(f_opc);

	//FOR OBJECT CODE
	i=0;
	while(fscanf(f_p2,"%s %s %s %s",temp,label_1,mnemonics,operand) == 4){
		if(operand[0] == '#'){
				//printf("%s\n",opcd);
			while(fscanf(f_opc,"%s %s",mne,opcd)==2){
				if(strcmp(mne,mnemonics) == 0){
					strcpy(x,HexToBin(opcd[0]));
					strcpy(y,HexToBin(opcd[1]));
					while(i < 4){
						object_code[i] = x[i];
						i++;
					}
					j = 0;
					while(j < 2){
						object_code[i++] = y[j++];
					}
					while(i < 12){
						if(i == 7)
							object_code[i] = '1';
						else
							object_code[i] = '0';	
						i++;				
					}
					object_code[i] = '\0';
					i =0 ;j =0;
					printf("%s\n",object_code);
					while(i < 4){
						buffer[j++] = object_code[i++];
					}
					j = 0;
					while(i < 8){
						buffer1[j++] = object_code[i++];
					}
					j = 0;
					while(i<12){
						buffer2[j++] = object_code[i++];
					}
					j=0;
					for(i = 1;i<strlen(operand);i++){
						opr[j++] = operand[i];
					}
					fprintf(f_obj,"%s\t%s\t%s\t%s\t%c%c%c%.3X\n",temp,label_1,mnemonics,operand,BinToHex(buffer),BinToHex(buffer1),BinToHex(buffer2),atoi(opr));
					i=0;j=0;
				
				}
			}
			rewind(f_opc);
			
		}
		

	}


}
