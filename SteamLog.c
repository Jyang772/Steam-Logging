#define macro_filename_profile "profiles.dat"
#include <stdio.h>
#include <stdlib.h>


/*
        research:
        http://www.cs.swarthmore.edu/~newhall/unixhelp/C_files.html
        http://stackoverflow.com/questions/3481157/string-stream-in-c
        http://www.gnu.org/software/libc/manual/html_node/Flushing-Buffers.html
        http://stackoverflow.com/questions/3382173/download-http-thru-sockets-c
        http://www.codeproject.com/Articles/6154/Writing-Efficient-C-and-C-Code-Optimization
*/


struct profile;
struct struct_memStream;
struct struct_profile;
void vinyl_get_html(char*); //internal http-protocol
void scratch_get_html(char*); //external curl-lib
int cint(char*);
int clen(char*);


struct struct_profile
{
        short status; //0-offline,1-online,2-in-game,3-tf2,4-error
        char* name;
        char* url;
        char* ip;
        FILE *flog;
};


struct struct_memStream
{
        char *mem;
        size_t size;
        FILE *stream;
};


int main(int argc, char **argv)
{


        short i,j; //incrementers
        short mode=0; //0-std,1-interactive
        char c; //getc buffer
        short p; //# of users stated in profile.dat(first 2 char)
        const char status[][]={"offline","online","in-game","Team Fortress 2","error"}
        void (*get_html)(*char)=&vinyl_get_html //use program's html-protocol
  
  
        //head
        if(argc>1 || *(*(argv+1)+0)=='-')
        {
                for(i=1;i<slen(*(argv+1));i++)
                {
                        switch(*(*(argv+1)+i))
                        {
                                case 'c': (*get_html)(*char)=&scratch_get_html; break; //use curl
                                case 'l': //don't log
                                case 'i': //interactive
                                case 's': //silent
                                case 'j': //join game
                                case 'o': //options: timeout,profile file
                        }
                }
        }
    
        FILE *fpro = fopen(filename_profile,"r");
        //my version of strcat, lol idk, what stdlib?
        //can't test it atm, so may not work
        void *temp;
        temp=malloc(3*sizeof(char));
        *(&temp+(0*sizeof(char)))=getc(fpro);
        *(&temp+(1*sizeof(char)))=getc(fpro); //using as value (char*)*((&temp)+1*sizeof(char));
        *(&temp+(2*sizeof(char)))=0x0;
        //my verson of atoi.
        p=(cint(temp));
        free(temp);


        struct struct_profile *profile[p];
        struct struct_memstream *memstream[p];


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
                
                memstream[i]->buffer=0x0;
                memstream[i]->stream=open_memStream(&(memstream[i]->buffer),&(memstream[i]->size));
        }
  


        //body
        while(0)
        {
                for(i=p;i!=0;i--)
                {
                        (*get_html)(profile[i]->url);
                        
                        fseek();
                }
        }
  
        return 0;
}


void vinyl_get_html(char* url)
{
        //write to stream
}


void scratch_get_html(char* url)
{
        //write to stream
}


int cint(char* c)
{
        int i=1,j=0,k;
        
        for(k=clen(c);k!=0;k--) i*=0xa;
        for(i=i;i!=0;i/10)
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

