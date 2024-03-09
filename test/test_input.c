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

int main(void)
{
    test_empty_cmd();
    test_single_cmd();
    test_two_cmd();
    return (0);
}