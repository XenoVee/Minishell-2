#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"
#include "input.h"

static void fill_struct(char *input, t_commands *cmds, int count) {
	int i;
	char **split_result;
    split_result = ft_split(input, '|');
	
	i=0;
	while (i<count)
	{
		cmds[i].args = ft_split(split_result[i], ' ');
		cmds[i].cmd = cmds[i].args[0];
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
		free(split_result[i]);		
		i++;
	}
    free(split_result);
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
		cmds[i].fd_data = 0;		
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