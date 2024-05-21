// Use below command to compile tests
// cc test_input.c  ../sources/input/ft_split.c ../sources/input/input_parse.c -I../includes/ -I../libraries/libftprintf/ -g -Wall -Wextra -Werror

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"

void test_with_print(char *input)
{
    t_commands *cmds = input_parse(input);
    int i=0;

    printf("\n\nTest for command: %s\n", input);

    if (!cmds)
    {
        printf("input_parse function returned NULL cmds structure\n");
        return;
    }
    while (1)
    {
        printf("command %d str = %s\n", i, cmds[i].str);
        printf("command %d cmd = %s\n", i, cmds[i].cmd);

        int j=0;
        while (cmds[i].args[j])
        {
            printf("command %d argument %d, value = %s\n", i, j, cmds[i].args[j]);
            j++;
        }

        printf("command %d pipe= %d\n", i, cmds[i].pipe);
        printf("command %d next= %p\n", i, cmds[i].next);
        printf("command %d prev= %p\n", i, cmds[i].prev);
        printf("command %d fd_input= %d\n", i, cmds[i].fd_input);
        printf("command %d fd_output= %p\n", i, cmds[i].fd_output);
    
        if (cmds[i].fd_output)
        {
            j=0;
            while (cmds[i].fd_output[j] != -1)
            {
                printf("command %d fd %d, value = %d\n", i, j, cmds[i].fd_output[j]);
                j++;
            }
        }

        if (cmds[i].next == 0)
        {
            break;
        }

        i++;
        printf("\n\n");
    }
    free_cmds_memory(cmds);
}

int main(void)
{
    test_with_print("");
    test_with_print("ls");
    test_with_print("ls -ltr");
    test_with_print("ls -ltr | grep abc");
    test_with_print("ls -ltr | grep abc | grep cde");
    test_with_print("ls -ltr | grep abc | grep cde > file.txt");
    test_with_print("ls -ltr | grep abc > file2.txt | grep cde > file.txt");
    test_with_print("grep todo < todo");

    printf("-----test special situations-----\n");
    test_with_print("grep todo < Makefile < todo");
    
    if (setenv("VAR", "test", 1) == 0)
    {
        test_with_print("echo $VAR");
    }
    test_with_print("echo '$VAR'");

    return (0);
}