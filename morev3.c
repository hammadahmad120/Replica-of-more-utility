#include<stdio.h>
#include<stdlib.h>
#define LINELEN 512
#define PAGELEN 20
void do_more(FILE*);
int get_input();
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


	int ttl_lines=0;
	char buff[LINELEN];
	while(fgets(buff,LINELEN,myFp)){
	    fputs(buff,stdout);
		ttl_lines++;
		if(ttl_lines==PAGELEN){
			int inp=get_input();
			printf("\033[1A \033[2K \033[1G");	
			if(inp==0) // q pressed ,quit
			break;
			else if(inp==1) //space pressed ,print one more page
			ttl_lines=ttl_lines-PAGELEN;
			else if(inp==2) //enter pressed ,print one line more
			ttl_lines--;
			else if(inp==3) //invalid character
			break;		
		}
   
	
   }
}


int get_input(){
	char c;
	printf("\033[7m --more-- (%%) \033[m");
	c=getchar();
	
	if(c=='q')
	return 0;
	if(c==' ')
	return 1;
	if(c=='\n')
	return 2;

   return 3;
}
