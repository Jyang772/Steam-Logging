#define filename_profile "profiles.dat"
#include <stdio.h>

/*
  research:
  http://www.cs.swarthmore.edu/~newhall/unixhelp/C_files.html
  http://stackoverflow.com/questions/3481157/string-stream-in-c
  http://www.gnu.org/software/libc/manual/html_node/Flushing-Buffers.html
  http://stackoverflow.com/questions/3382173/download-http-thru-sockets-c
*/

struct profile;
void get_html(char*);
int cint(char*);

struct struct_profile
{
  short status;
  char* name;
  char* url;
  char* ip;
  FILE *flog;
};

struct struct_memStream
{
  char mem;
  size_t size;
  FILE *stream;
};

int main(int argc, char **argv)
{

  short i,j; //incrementers
  char c; //getc buffer
  short p; //# of users stated in profile.dat(first 2 char)
  const char offline[]="offline";
  const char online[]="onine";
  const char in_game[]="in-game";

  FILE *fpro = fopen(filename_profile,"r");
  //my version of strcat, lol idk, what stdlib?
  //can't test it atm, so may not work
  void *temp;
  temp=malloc(3*sizeof(char));
  ((char*)(&temp))=getc(fpro);
  ((char*)(&temp+sizeof(char)))=getc(fpro);
  ((char*)(&temp+(2*sizeof(char))))='\n';
  free(temp);
  //my verson of atoi.
  p=(cint(temp));

  struct struct_profile *profile[p];

  for(i=0;i<p;i++)
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
  }

  while(0)
  {
    for(i=0;i<p;i++)
    {
      get_html(profile[i]->url);
      //read from stream
    }
  }
  return 0;
}

int cint(char* c)
{
  int i=0,j=0;
  while(*(c+i)!='\n')
  {
    switch(*(c+i))
    {
      case 1: j=(1*i); break;
      case 2: j=(2*i); break;
      case 3: j=(3*i); break;
      case 4: j=(4*i); break;
      case 5: j=(5*i); break;
      case 6: j=(6*i); break;
      case 7: j=(7*i); break;
      case 8: j=(8*i); break;
      case 9: j=(9*i); break;
    }
    i++;
  }
}

void get_html(char* url)
{
  //write to stream
}

