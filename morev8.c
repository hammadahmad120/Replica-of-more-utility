#include<stdio.h>
#include <sys/ioctl.h>
#include<stdlib.h> 
#include <unistd.h>
#include <string.h>
#define LINELEN 512
//#define PAGELEN 20
void do_more(FILE*);
int get_input(FILE*);
void mygrep(FILE*, char*);
void get_lines_count(FILE*);
 int cur_lines=1;
 int file_lines=1;
 int page_len=0;
int flag=1;
int main(int argc,char *argv[])
{
	
	if(argc==1){
	page_len=24;
	flag=0;	
	get_lines_count(stdin);	
	   do_more(stdin);
	}
	else
	{
	struct winsize ws;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
	page_len=ws.ws_row;
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
	char str[20];
	FILE *fp_tty=fopen("/dev/tty","r");
	while(fgets(buff,LINELEN,myFp)){
	    fputs(buff,stdout);
		ttl_lines++;
		cur_lines++;
		if(ttl_lines==page_len){
			int inp=get_input(fp_tty);
				
			if(inp==0){
			printf(" \033[1K \033[1G"); // q pressed ,quit
			break;
				}
			else if(inp==1){ //space pressed ,print one more page
			ttl_lines=ttl_lines-page_len;
			printf(" \033[1K \033[1G");
			}
			else if(inp==2){
			printf("\033[1A \033[2K \033[1G");	 //enter pressed ,print one line more
			ttl_lines--;
				}
			
			else if(inp==4){
			fgets(str,20,stdin);
			int len=strlen(str);
			str[len-1]='\0';
			printf("\033[1A \033[2K \033[1G");
			int loc_ptr=ftell(myFp);
			mygrep(myFp,str);
			fseek(myFp, loc_ptr, SEEK_SET);
			
			getchar();
			}
			else if(inp==3){
			printf(" \033[1K \033[1G"); //invalid character
			break;
			}		
		}
   
	
   }
}


int get_input(FILE* cmdstm){
	char c;
	
	printf("\033[7m --more-- (%d %)  \033[m",(cur_lines*100/file_lines)-1);
	//if(flag==1)
	//system( "stty -icanon" );
	c=getc(cmdstm);

	if(c=='q')
	return 0;
	if(c==' ')
	return 1;
	if(c=='\n')
	return 2;
	if(c=='/')
	return 4;

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

void mygrep(FILE *fp,char *find)
{
	char c1[100];
	char c2[100]; 
	int line=0; 
rewind(fp);
	
	while(fgets(c1,100,fp)!=NULL)
	{
		line++;
        char* ptr;
        int i=0;
	//fputs(c1,stdout);
	strncpy(c2,c1,100);
        ptr = strtok(c1, " ");
        while(ptr !=NULL){
	
		if((strcmp(ptr,find))==0)
		{
                	printf("\033[7m%s\033[m",c2);
			//printf("\n");
			
			//break;
		}
                ptr = strtok(NULL, " ");
        }

	}

}



