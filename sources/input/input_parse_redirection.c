#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "libft.h"
#include "input.h"

static void free_split_result(char **split_result)
{
	int i;

	i=0;
	if (split_result)
	{
		while (split_result[i])
		{
			free(split_result[i]);
			split_result[i] = 0;
		}
		free(split_result);	
		split_result = 0;
	}
}

static void parse_output_redirection(t_commands *cmds, int i) {
	int j;
	char **split_result;
	
	split_result = 0;
	if (ft_count_word(cmds[i].str, '>')>1)
	{
		cmds[i].fd_output = (int*)malloc(sizeof(int)*(ft_count_word(cmds[i].str, '>')));
		split_result = ft_split(cmds[i].str, '>');
		j=1;
		while (split_result[j])
		{			
			remove_white_spaces_and_tabs(split_result[j],'\0', 1);
			cmds[i].fd_output[j-1] = open(split_result[j], O_RDWR|O_CREAT, 00666);
			j++;
		}
		cmds[i].fd_output[j-1] = -1;
		cmds[i].args = ft_split(split_result[0], ' ');
		cmds[i].cmd = cmds[i].args[0];
		free_split_result(split_result);
	}
}

static void parse_input_redirection(t_commands *cmds, int i) {
	char **split_result;
	char **split_result1;
	int count;
	
	split_result1 = 0;
	split_result = ft_split(cmds[i].str, '>');
	count = ft_count_word(split_result[0], '<');
	if (count > 1)
	{
		split_result1 = ft_split(split_result[0], '<');
		remove_white_spaces_and_tabs(split_result1[count-1],'\0', 1);
		cmds[i].fd_input = open(split_result1[count-1], O_RDWR);
		if (cmds[i].cmd)
			free_split_result(cmds[i].args);
		cmds[i].args = ft_split(split_result1[0], ' ');
		cmds[i].cmd = cmds[i].args[0];
	}
	free_split_result(split_result);
	free_split_result(split_result1);
}


void parse_redirection(t_commands *cmds, int count) {
	int i;

	i=0;
	while (i < count)
	{
		remove_white_spaces_and_tabs(cmds[i].str,'<', 1);
		remove_white_spaces_and_tabs(cmds[i].str,'<', 0);
		remove_white_spaces_and_tabs(cmds[i].str,'>', 1);
		remove_white_spaces_and_tabs(cmds[i].str,'>', 0);
		parse_output_redirection(cmds, i);
		parse_input_redirection(cmds, i);
		if(!cmds[i].cmd)
		{
			cmds[i].args = ft_split(cmds[i].str, ' ');
			cmds[i].cmd = cmds[i].args[0];
		}
		i++;
	}
}
