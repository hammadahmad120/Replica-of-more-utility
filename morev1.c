#include<stdio.h>
#include<stdlib.h>
#define linelength 512
void do_more(FILE*);
int main(int argc,char *argv[])
{
	if(argc==1){
	   printf("this is the help page displaying in front of you\n");
		exit(0);
	}
	
	FILE *fp;
int i=0;
char c;
	while(i<argc-1){
     fp=fopen(argv[i+1],"r");
	if(fp==NULL){
		printf("error opening file\n");
	exit(1);
		   } 
	do_more(fp);
	fclose(fp);
	i++;
	printf("----------------------\n\n");
     }
return 0;
}


	
 void do_more(FILE *myFp ){

	char buff[linelength];
	while(fgets(buff,linelength,myFp)){
	    fputs(buff,stdout);   
	
   }
}
