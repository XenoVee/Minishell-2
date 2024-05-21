#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "libft.h"
#include "input.h"

void input_parse_pipes(char *input, t_commands *cmds, int count) {
	int i;
	char **split_result;

    split_result = ft_split(input, '|');
	i=0;
	while (i<count)
	{
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
		i++;
	}
    free(split_result);
}