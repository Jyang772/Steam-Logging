/*
        must be compatible with:
                Visual Studio,
                GCC
                
	research
        http://www.cs.swarthmore.edu/~newhall/unixhelp/C_files.html
        http://stackoverflow.com/questions/3481157/string-stream-in-c
        http://www.gnu.org/software/libc/manual/html_node/Flushing-Buffers.html
        http://stackoverflow.com/questions/3382173/download-http-thru-sockets-c
        http://www.codeproject.com/Articles/6154/Writing-Efficient-C-and-C-Code-Optimization
        
        micropenguin.net
*/


#include <stdio.h>
#include <stdlib.h>
//#include "html.h"

struct profile;
struct struct_memStream;
struct struct_profile;
int cint(char*);
int clen(char*);


struct struct_profile
{
        short status; //0-offline,1-online,2-in-game,3-tf2,4-error
        char *name;
        char *url;
        char *ip;
        FILE *flog;
};


struct struct_memStream
{
        char *buffer;
        size_t size;
        FILE *stream;
};


int main(int argc, char **argv)
{

        short mode=0;
        short i,j; //incrementers
        short p,t; //# of users stated in profile.dat(first 2 char),timeout
        char c; //getc buffer
        const char default_filename_profile[]="profile.dat\n";
	char arr_status[]={
			'C','u','r','r','e','n','t','l','y',0x20,'O','f','f','l','i','n','e',0x0,
			'C','u','r','r','e','n','t','l','y',0x20,'O','n','l','i','n','e',0x0,
			'C','u','r','r','e','n','t','l','y',0x20,'I','n','-','G','a','m','e',0x0,
			'T','e','a','m',0x20,'F','o','r','t','r','e','s','s',0x20,'2',0x0,
			'e','r','r','o','r',0x0};
        char **status; //{"Currently Offline\0","Currently Online\0","Currently In-Game\0","Team Fortress 2\0","error\0"};
        char compare[3][40]={"<div class=\"profile_in_game_header\">\0","<div class=\"profile_in_game_name\">\0","<a href=\"steam://connect\0"};
        char *filename_profile;
        void (*get_html)(char*,FILE*)=&vinyl_get_html; //use program's html-protocol

	//head
	*(filename_profile+0)=(char)(&default_filename_profile[0]);
	status=malloc(5*sizeof(char));
	
	j=0;
	for(i=0;i<5;i++)
	{
		do
		{
			j++;
		}while(arr_status[j]!=0x0);
		j++;
		*(status+i)=&arr_status[j];
	}

        if(argc>1 || *(*(argv+1)+0)=='-')
        {
                for(i=1;i<clen(*(argv+1));i++)
                {
                        switch(*(*(argv+1)+i))
                        {
				case 'c': (*get_html)(char*)=&scratch_get_html; break; //use curl
				case 'l': mode+=1; break; //don't log: 1,3,5,7,9,11,13,15
				case 'i': mode+=2; break; //interactive: 2,3,6,7,10,11,14,15
                                case 's': mode+=4; break; //silent: 4,5,6,7,12,13,14,15
                                case 'j': mode+=8; break; //join game: 8,9,10,11,12,13,14,15
                                case 'o': goto options; //options: timeout,profile file
                        }
                }
        }
        
        goto headend;
        options:;
        for(i=2;i<argc;i+=2)
        {
                switch(*(*(argv+i)+1))
                {
                        case 't': t=cint(*(argv+i+1)); break;
                        case 'f': filename_profile=&*(*(argv+i+1)); break;
                }
        }
        headend:;
    
        FILE *fpro = fopen(filename_profile,"r");
	void *tmp=malloc(3*sizeof(char));
        *(&tmp+(0*sizeof(char)))=getc(fpro);
        *(&tmp+(1*sizeof(char)))=getc(fpro); //to use as value: (char*)*((&tmp)+1*sizeof(char));
        *(&tmp+(2*sizeof(char)))=0x0;
        p=(cint(tmp));
        free(tmp);

        struct struct_profile *profile[p];
        struct struct_memStream *memstream[p];

        for(i=p;i!=0;i--)
        {
                profile[i]=malloc(sizeof(struct struct_profile));
                profile[i]->status=-1; //uninitialized
                profile[i]->name=malloc(25*sizeof(char));
                profile[i]->url=malloc(100*sizeof(char));
                while(getc(fpro)!='\n'); //go to next line
                //set name
                j=0;
                c=getc(fpro);
                do
                {
                        *(profile[i]->name+j)=c;
                        j++;
                              c=getc(fpro);
                }while(c!='\n');
                //set url
                j=0;
                c=getc(fpro);
                do
                {
                        *(profile[i]->url+j)=c;
                        j++;
                        c=getc(fpro);
                }while(c!='\n');
                
		memstream[i]=malloc(sizeof(struct struct_memStream));
                memstream[i]->buffer=0x0;
                memstream[i]->stream=open_memStream(&(memstream[i]->buffer),&(memstream[i]->size));
        }
  


        //body
        while(0)
        {
                for(i=p;i!=0;i--)
                {
                        (*get_html)(&profile[i]->url,&memstream[i]->stream);
                        
                        //read stream
                        while(j!=430)
                        {
                                c=getc(memstream[i]->stream);
                                if(c=='\n') j++;
                        }
                        j=0;
                        c=getc(memstream[i]->stream);
                        while(c!=EOF)
                        {
                                if(c==compare[0][j]) 
                                {
                                        j++;
                                        if(compare[0][j]==0x0) goto gud;
                                }
                                else j=0;
                                c=getc(memstream[i]->stream);
                        }
                        printf("error could not find %s\n",compare[0]);
                        gud:;
                        c=getc(memstream[i]->stream);
                        while(c!="<")
                        {
                                
                                //if()
                                c=getc(memstream[i]->stream);
                        }
                        //log
                        
                        //actions
                        #if defined (WIN32)
                        //windows
                        #elif defined (__unix__)
                        //unix
                        #endif
                }
        }
  
        return 0;
}





int cint(char* c)
{
        int i=1,j=0,k;
        
        for(k=clen(c);k!=0;k--) i*=0xa;
        for(i=i;i!=0;i/=10)
        {
                switch(*(c+i))
                {
                        case 1: j+=(1*i); break;
                        case 2: j+=(2*i); break;
                        case 3: j+=(3*i); break;
                        case 4: j+=(4*i); break;
                        case 5: j+=(5*i); break;
                        case 6: j+=(6*i); break;
                        case 7: j+=(7*i); break;
                        case 8: j+=(8*i); break;
                        case 9: j+=(9*i); break;
                }
        }
        return j;
}
int clen(char* c)
{
        int i=0;
        
        while(*(c+i)!=0x0) i++;
        return i;
}

