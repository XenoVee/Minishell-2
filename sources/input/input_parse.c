#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "libft.h"
#include "input.h"

static void fill_struct_input_redirect(t_commands *cmds, int count) {
	int i;
	int j;
	int count_out;
	char **split_result;
	int *fd;
	
	i=0;
	while (i < count)
	{
		count_out = ft_count_word(cmds[i].str, '>');
		if (count_out>1)
		{
			split_result = ft_split(cmds[i].str, '>');
			cmds[i].fd_output = (int*)malloc(sizeof(int)*(count_out));
			j=1;
			while (split_result[j])
			{
				remove_white_spaces_and_tabs(split_result[j],'\0', 1);
				cmds[i].fd_output[j-1] = open(split_result[j], O_RDWR|O_CREAT, 00666);
				if (cmds[i].fd_output[j-1] < 0)
					printf("file open failed for %s \n", split_result[j]);
				j++;
			}

			if (ft_count_word(split_result[0], '<') > 1)
			{
				split_result = ft_split(split_result[0], '<');

				remove_white_spaces_and_tabs(split_result[1],'\0', 1);
				cmds[i].fd_input = open(split_result[1], O_RDWR);
			}
		}
		else
		{
			if (ft_count_word(cmds[i].str, '<') > 1)
			{
				split_result = ft_split(cmds[i].str, '<');

				remove_white_spaces_and_tabs(split_result[1],'\0', 1);
				cmds[i].fd_input = open(split_result[1], O_RDWR);
			}			
		}

		cmds[i].args = ft_split(split_result[0], ' ');
		cmds[i].cmd = cmds[i].args[0];
		i++;
	}
}

static void fill_struct(char *input, t_commands *cmds, int count) {
	int i;
	char **split_result;
    split_result = ft_split(input, '|');
	
	i=0;
	while (i<count)
	{
		remove_white_spaces_and_tabs(split_result[i],'<', 1);
		remove_white_spaces_and_tabs(split_result[i],'<', 0);
		remove_white_spaces_and_tabs(split_result[i],'>', 1);
		remove_white_spaces_and_tabs(split_result[i],'>', 0);
		cmds[i].str = split_result[i];
		cmds[i].pipe = 1;
		cmds[i].next = &cmds[i+1];
		cmds[i].prev = &cmds[i-1];
		if(i == count-1)
		{
			cmds[i].pipe = 0;
			cmds[i].next = 0;
		}
		if(i == 0)
			cmds[i].prev = 0;	
		//free(split_result[i]);		
		i++;
	}
    //free(split_result);
}

void remove_char(char *str, int position)
{
	int i;
	
	i=position;
	while (1)
	{
		*(str + i) = *(str + i + 1);
		if (*(str+i) == '\0')
			break;
		i++;
	}
}

void remove_white_spaces_and_tabs(char *input, char chr, int before)
{
	int i;
	i = 0;
	while(1)
	{
		if (before)
		{
			if (*(input+i) == ' ' && *(input+i+1) == chr)
			{
				remove_char(input, i--);
			}
			else if (*(input+i) == '\t' && *(input+i+1) == chr)
				remove_char(input, i--);
			else
				i++;
		}
		else if (!before)
		{		
			if (*(input+i) == ' ' && *(input+i-1) == chr)
				remove_char(input, i--);
			else if (*(input+i) == '\t' && *(input+i-1) == chr)
				remove_char(input, i--);
			else
				i++;
		}
		else
			i++;
		if (*(input+i) == '\0')
			break;
	}
}

int invalid_input(char *input)
{
	if (input[0] == '\0')
		return (1);
	return (0);
}

void init_struct(t_commands *cmds, int count) {
	int i;

	i=0;
	while (i<count)
	{
		cmds[i].args = 0;
		cmds[i].cmd = 0;
		cmds[i].pipe = 0;
		cmds[i].next = 0;
		cmds[i].prev = 0;
		cmds[i].fd_input = -1;
		cmds[i].fd_output = 0;		
		i++;
	}
}

t_commands *input_parse(char *input) {
	int count;
	t_commands *cmds;

	if (invalid_input(input))
		return NULL;
	
	count = ft_count_word(input, '|');
	cmds = (t_commands*)malloc(sizeof(t_commands)*(count));
	init_struct(cmds, count);
	fill_struct(input, cmds, count);
	fill_struct_input_redirect(cmds, count);

	return cmds;
}

void free_cmds_memory(t_commands *cmds)
{
  int i;
  int j;

  if (!cmds)
	return;
  
  i=0;
  while(1)
  {
	j = 0;
	while (cmds[i].args[j])
	{
		free(cmds[i].args[j]);
		j++;
	}
	free(cmds[i].args);

	if (!cmds[i].next)
		break;
    i++;
  }

  free(cmds);
}