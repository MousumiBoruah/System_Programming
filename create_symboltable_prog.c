#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(){
    FILE *f_source = fopen("sicfile.txt","r");
    FILE *f_inter = fopen("intermediate.txt","a+");
    FILE *f_opcode = fopen("opcode.txt","r");
    FILE *f_sym = fopen("symbol_table.txt","a+");
    FILE *fp1 = fopen("opcode.txt","r");
    FILE *fp3 = fopen("first.txt","a+");
    FILE *fp4 = fopen("second.txt","a+");
    FILE *fp5 = fopen("mnemonicsopcode.txt" , "a+");
    FILE *f_final = fopen("object_code.txt","w");
	int loc,start_loc,object_code,opc,target_address,loc_1,buffer,x,disp,displacement;
	char mnemonics[30],label_1[30],label_2[100],lbl[20];
	char lbl1[25], mne[25], lbl2[25], opcode[25],mne1[25],str[25],num[25],xyz[30],buffer_2[30],buffer_3[30];
	//FOR PASS 1 FILE GENERATION.
	while(fscanf(f_source , "%s %s %s" ,lbl1, mne ,lbl2) == 3){
            fprintf(fp3,"%s\t%s\n",lbl1,lbl2);
            fputs(mne,fp4);
            fputc('\n',fp4);
        }
        rewind(fp4);
    //FOR PASS 2 FILE GENERATION    
    while(fscanf(fp4 , "%s" , mne) == 1 ){
        while(fscanf(fp1 , "%s %X", mne1,&opc)==2){
            if(strcmp(mne , mne1) == 0){
				fputs(mne1 , fp5);
				fputc('\t' ,fp5);
				fprintf(fp5, "%X",opc);
				fputc('\n' ,fp5);
                }
            }
            rewind(fp1);
     }
    
    rewind(f_source);
	fscanf(f_source , "%*s %*s %X" ,&start_loc);
	loc = start_loc;
	//FOR INTERMEDIATE FILE GENERATION.
	while(fscanf(f_source,"%s %s %s",label_1,mnemonics,label_2) == 3){
		    fprintf(f_inter,"%X",loc);
			fputc('\t',f_inter);
			fputs(label_1,f_inter);
			fputc('\t',f_inter);
			fputs(mnemonics,f_inter);
			fputc('\t',f_inter);
			fputs(label_2,f_inter);
			fputc('\n',f_inter);
		if(strcmp(mnemonics,"RESW") == 0){
			loc = loc + (atoi(label_2) * 3);
		}
		else if(strcmp(mnemonics,"RESB") == 0){
			loc =loc + atoi(label_2);
		}
		else if(strcmp(mnemonics,"BYTE")==0){
        	if(label_2[0] == 'C'){
                 loc = loc + (strlen(label_2) - 3);
            }
            else{
                 int d = strlen(label_2) - 3;
                 if((d % 2)==0){
                         d = d/2;
                    }
                 else{
                         d=(d+1)/2;
                     }
            loc = loc + d;
            }
        }
 
        else{
			loc+=3;
		 }
	}
    //FOR SYMBOL TABLE FILE GENERATION
    rewind(f_inter);
    while(fscanf(f_inter,"%x %s %s %s" , &loc, label_1 ,mnemonics, label_2)==4){
    	if(strcmp(label_1,"-----") != 0){
   		 fprintf(f_sym, "%X",loc );
    	 fputc('\t',f_sym);
    	 fputs(label_1,f_sym);
	     fputc('\n',f_sym);
	    }
   }
   rewind(f_sym);
   rewind(f_source);
   rewind(f_inter);
   rewind(fp1);
   rewind(fp3);
   rewind(fp4);
   rewind(fp5);
   int i=0,j=0;
   //FOR OBJECT CODE GENERATION
   fprintf(f_final,"LOCAION LABEL1 MNEM LABEL2 OBJECTCODE\n");
   while(fscanf(f_inter,"%X %s %s %s",&loc ,label_1,mnemonics,label_2) == 4){
   		if((strcmp(mnemonics,"RESB") != 0) && (strcmp(mnemonics,"RESW") != 0)  && (strcmp(mnemonics,"WORD") != 0)  && strcmp(mnemonics,"BYTE") != 0){
   	 		fscanf(fp5,"%*s %X" , &opc);
   	 		object_code = opc;
   	 		while(fscanf(f_sym,"%X %s",&loc_1,lbl) == 2){
   	 			int length = strlen(label_2);
   	 			int i=0,j=0;
   	 			if(label_2[length-1] == 'X'){
   	 				while(fscanf(f_source,"%*s %s %s",mne,lbl2) == 2){
   	 					if(strcmp(mne,"LDX") == 0){
   	 						strcpy(buffer_3,lbl2);
   	 						printf("%s\n",buffer_3);
   	 				}}
   	 				while(fscanf(fp3,"%s %s",lbl1,lbl2) == 2){
   	 					if(strcmp(buffer_3,lbl1) == 0){
   	 						x = atoi(lbl2);
   	 						printf("%X\n",x);
   	 				    }	
   	 			    }
   	 				while(label_2[i] != ','){
						buffer_2[j++] = label_2[i++];
   	 				}
   	 				if(strcmp(buffer_2,lbl) == 0){
   	                       printf("%X\n",x);
   	                        disp = loc_1 - x;
   	                        displacement = disp;
   	                       printf("%X\n",disp);
   	 					while(disp >= 16)
   	 						disp=disp/16;
   	 					printf("%X\n",disp);
   	 					if(disp < 8)
   	 						target_address = displacement + 32768;
   	 				    else
   	 				    	target_address = displacement;
   	 			    }
   	 		    }
   	 		    else{
   	 		    	if(strcmp(label_2,lbl) == 0){
   	 		    		  disp = loc_1;
   	 		    		  displacement = disp;
   	 					while(disp >= 16)
   	 						disp=disp/16;
   	 					if(disp > 8)
   	 						target_address = displacement - 32768;
   	 				    else
   	 				    	target_address = displacement;
   	 		    		
   	 		    	}
   	 		    }

   	 		}
   	 		 fprintf(f_final,"%X\t%s\t%s\t%s\t%.2X%X\n",loc,label_1,mnemonics,label_2,object_code,target_address );
   	 		  rewind(f_sym);
   	 	}
  	 	else if(strcmp(mnemonics,"BYTE") == 0){
  	 		i = 0;
  	 		j = 0;
   	 		fprintf(f_final,"%X\t%s\t%s\t%s\t",loc,label_1,mnemonics,label_2);
   	 		while(label_2[i] != '\''){
                i++;
            }
            i++;
            while(label_2[i] != '\''){
            	xyz[j++] = label_2[i++];
            }
            j=0;
            for(j = 0 ;j < (strlen(label_2) - 3) ;j++)
            fprintf(f_final,"%X",xyz[j]);
            fprintf(f_final,"\n");
   	 	
   	 	}
   	 	else if((strcmp(mnemonics,"WORD") == 0)){
   	 		fprintf(f_final,"%X\t%s\t%s\t%s\t%.6X\n",loc,label_1,mnemonics,label_2,atoi(label_2));
  		}
   	 	else {
   	 		 fprintf(f_final,"%X\t%s\t%s\t%s\t NO OBJECT CODE GENERATED \n",loc,label_1,mnemonics,label_2);
   	 	}
   }
   fclose(f_source);
   fclose(fp1);
   fclose(fp3);
   fclose(fp4);
   fclose(fp5);
   fclose(f_opcode);
   fclose(f_inter);
   fclose(f_sym);
   fclose(f_final);

}
