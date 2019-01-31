#include<stdio.h>
#include<stdlib.h>
#include <sys/ioctl.h> 
#include <unistd.h>
#define LINELEN 512
#define PAGELEN 20
void do_more(FILE*);
int get_input(FILE*);
void get_lines_count(FILE*);
 int cur_lines=1;
 int file_lines=1;
int flag=1;
int main(int argc,char *argv[])
{

	if(argc==1){
	get_lines_count(stdin);	
	flag=0;
	   do_more(stdin);
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
	get_lines_count(fp);
	
	fclose(fp);
     fp=fopen(argv[i+1],"r");
	if(fp==NULL){
		printf("error opening file\n");
	exit(1);
		   } 
	do_more(fp);
	fclose(fp);
	i++;
	cur_lines=0;
	file_lines=0;
	printf("----------------------\n\n");
     }
return 0;
}


	
 void do_more(FILE *myFp ){


	int ttl_lines=0;
	char buff[LINELEN];
	FILE *fp_tty=fopen("/dev/tty","r");
	while(fgets(buff,LINELEN,myFp)){
	    fputs(buff,stdout);
		ttl_lines++;
		cur_lines++;
		if(ttl_lines==PAGELEN){
			int inp=get_input(fp_tty);
				

			if(inp==0){
			printf(" \033[2K \033[1G"); // q pressed ,quit
			break;
				}
			else if(inp==1){ //space pressed ,print one more page
			ttl_lines=ttl_lines-PAGELEN;
			printf(" \033[2K \033[1G");
			}
			else if(inp==2){
			printf("\033[1A \033[2K \033[1G");	 //enter pressed ,print one line more
			ttl_lines--;
				}
			else if(inp==3){
			printf(" \033[2K \033[1G"); //invalid character
			break;
			}		
		}
   
	
   }
}


int get_input(FILE* cmdstm){
	char c;
	
	printf("\033[7m --more-- (%d %)  \033[m",(cur_lines*100/file_lines)-1);
	if(flag==1)
	system( "stty -icanon" );
	c=getc(cmdstm);
	system( "stty icanon" );
	if(c=='q')
	return 0;
	if(c==' ')
	return 1;
	if(c=='\n')
	return 2;

   return 3;
}

void get_lines_count(FILE *fp){
	
	char buff1[LINELEN];
	int count=0;
	while(fgets(buff1,LINELEN,fp)){
	file_lines++;
	}
	rewind(fp);
  }

