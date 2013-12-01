#if defined (WINNT)
        //path to libcurl for NT systems
#elif (__unix__)
        //path to libcurl for unix
#endif

void vinyl_get_html(*char,*FILE); //internal http-protocol
void scratch_get_html(*char,*FILE); //external curl-lib

void vinyl_get_html(char *url,FILE *stream)
{

}
void scratch_get_html(char *url,FILE *stream)
{

}
