#include "../execution.h"

void    raise_error(char *err_msg, char *err_src, int exit_code)
{
    if (err_msg)
        printf("%s: %s\n",err_src, err_msg);
    else
        perror(err_src);
    //g_exitm = exit_code;
}