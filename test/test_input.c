// Use below command to compile tests
// cc test_input.c  ../sources/input/ft_split.c ../sources/input/input_parse.c -I../includes/ -I../libraries/libftprintf/ -g -Wall -Wextra -Werror

#include <stdio.h>
#include <string.h>
#include "input.h"
void test_empty_cmd(void)
{
    t_commands *cmds = input_parse("");
    if (cmds)
        printf("test_empty_cmd failed\n");    

    free_cmds_memory(cmds);
}

void test_single_cmd(void)
{
    t_commands *cmds = input_parse("ls -a -l");

    if (!cmds)
        printf("test_single_cmd failed\n");
    
    if (strcmp(cmds[0].cmd, "ls") != 0)
        printf("test_single_cmd failed due to command mismatch\n");
    
    if (strcmp(cmds[0].args[0], "ls") != 0)
        printf("test_single_cmd failed due to arg[0] mismatch\n");
    
    if (strcmp(cmds[0].args[1], "-a") != 0)
        printf("test_single_cmd failed due to arg[1] mismatch\n");
    
    if (strcmp(cmds[0].args[2], "-l") != 0)
        printf("test_single_cmd failed due to arg[2] mismatch\n");
    
    if (cmds[0].args[3] != 0)
    {
        printf("test_single_cmd failed due to arg[3] mismatch\n");
    }
	if (cmds[0].pipe != 0)
        printf("test_single_cmd failed due to pipe mismatch\n");

    if (cmds[0].next != 0)
        printf("test_single_cmd failed due to next mismatch\n");

    if (cmds[0].prev != 0)
        printf("test_single_cmd failed due to prev mismatch\n");   

    free_cmds_memory(cmds);
}

void test_two_cmd(void)
{
    t_commands *cmds = input_parse("ls -a -l | grep 123");

    if (!cmds)
        printf("test_two_cmd failed\n");
    printf("-->Test cmds[0]\n");
    if (strcmp(cmds[0].cmd, "ls") != 0)
        printf("test_two_cmd failed due to command mismatch\n");
    
    if (strcmp(cmds[0].args[0], "ls") != 0)
        printf("test_two_cmd failed due to arg[0] mismatch\n");
    
    if (strcmp(cmds[0].args[1], "-a") != 0)
        printf("test_two_cmd failed due to arg[1] mismatch\n");
    
    if (strcmp(cmds[0].args[2], "-l") != 0)
        printf("test_two_cmd failed due to arg[2] mismatch\n");
    
    if (cmds[0].args[3] != 0)
    {
        printf("test_two_cmd failed due to arg[3] mismatch\n");
    }
	if (cmds[0].pipe != 1)
        printf("test_two_cmd failed due to pipe mismatch\n");

    if (cmds[0].next == 0)
        printf("test_two_cmd failed due to next mismatch\n");

    if (cmds[0].prev != 0)
        printf("test_two_cmd failed due to prev mismatch\n");
    printf("-->Test cmds[1]\n");
    if (strcmp(cmds[1].cmd, "grep") != 0)
        printf("test_two_cmd failed due to command mismatch\n");
    
    if (strcmp(cmds[1].args[0], "grep") != 0)
        printf("test_two_cmd failed due to arg[0] mismatch\n");
    
    if (strcmp(cmds[1].args[1], "123") != 0)
        printf("test_two_cmd failed due to arg[1] mismatch\n");
    
    if (cmds[1].args[2] != 0)
    {
        printf("test_two_cmd failed due to arg[2] mismatch\n");
    }
	if (cmds[1].pipe != 0)
        printf("test_two_cmd failed due to pipe mismatch\n");

    if (cmds[1].next != 0)
        printf("test_two_cmd failed due to next mismatch\n");

    if (cmds[1].prev != &cmds[0])
        printf("test_two_cmd failed due to prev mismatch\n");
    
    free_cmds_memory(cmds);
}

void test_with_print(char *input)
{
    t_commands *cmds = input_parse(input);
    int i=0;

    printf("Test for command: %s\n", input);
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
        printf("command %d next= 0x%x\n", i, cmds[i].next);
        printf("command %d prev= 0x%x\n", i, cmds[i].prev);
        printf("command %d fd_input= %d\n", i, cmds[i].fd_input);
    
        j=0;
        if (cmds[i].fd_output)
        {
            while (cmds[i].fd_output[j])
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
}

int main(int argc, char **argv)
{
    test_with_print("grep    abc   123  <            /home/marghoob/rmaes_taj_minishell/test/abc  > xyz >   xyz1 |   grep taj 1>        ghijj  >   aw  >   qt    ");
    //test_with_print(argv[1]);
    return (0);
}