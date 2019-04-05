#include<stdio.h>
#include<Stdlib.h>
#include<string.h>
int main(){
	FILE *f_source = fopen("sicfile.txt","r");
	FILE *f_obj = fopen("object_code.txt","r");
	FILE *f_prog = fopen("object_program.txt","w");
	char name[32],buffer[20],obj_cod[50],buffer1[10][50];
	int start_add,len,size,loc,i=0,j=0,x,m,temp,last,add;
	//FOR HEADER RECORD
	fscanf(f_source,"%s %*s %X",name,&start_add);
	fprintf(f_prog,"H^%s",name);
	len = strlen(name);
	if(len){
		fputc(' ',f_prog);
		len--;
	}
	fprintf(f_prog,"^");
	while(fscanf(f_obj,"%X\t%*s\t%*s\t%*s\t%*s",&last) == 1);
	size = last - start_add;
	fprintf(f_prog,"%.6X^%.6X\n",start_add,size);
	rewind(f_obj);
	//FOR TEXT RECORD
	while(fscanf(f_obj,"%X\t%*s\t%*s\t%*s\t%s",&loc,obj_cod) == 2){
		if(strcmp(obj_cod,"NO") != 0 && i == 0){
			add = loc;
			fprintf(f_prog,"T^%.6X^",add);
			i = 1;
		}
		if(strcmp(obj_cod,"NO") != 0 && i > 0 && i <= 10){
			strcpy(buffer1[j],obj_cod); 
			j++;
			i++;
		}
		temp = i;
		if(strcmp(obj_cod,"NO") == 0 && i > 0 && i <= 10){
		 	x = 3 * (temp-1);
		  	fprintf(f_prog,"%.2X^",x);
		  	for(m = 0; m < (temp-1);m++){
	    		fprintf(f_prog,"%s^",buffer1[m]);
	    	}
	    	fprintf(f_prog,"\n");
	    	j=0;
	    	i=0;
		}
		 else if(temp > 10){
		 	 x = 3 * (temp-1);
		  	fprintf(f_prog,"%.2X^",x);
		  	for(m = 0; m < (temp-1);m++){
	    		fprintf(f_prog,"%s^",buffer1[m]);
	    	}
	    	fprintf(f_prog,"\n");
	    	j=0;
	    	i=0;
		  }
		  else if(loc == last){
		  	  x = 3 * (temp-1);
		 	  fprintf(f_prog,"%.2X^",x);
		  	  for(m = 0; m < (temp-1);m++){
	    		 fprintf(f_prog,"%s^",buffer1[m]);
	    	 	}
	    	  fprintf(f_prog,"\n");
		  }
	    
	}
	//FOR END RECORD
	fprintf(f_prog,"E^%.6X",start_add);
}