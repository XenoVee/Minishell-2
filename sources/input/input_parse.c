#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "libft.h"
#include "input.h"

int empty_input(char *input)
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

char* expand_variables_with_double_quotes(char *str)
{
	char *var;
	char *str1;
	str1 = 0;
	if (strlen(str) < 2)
		return NULL;
	if (str[0] == '$')
	{
		var = getenv(&str[1]);
		str1 = malloc(sizeof(char)*strlen(var));
		// handle error when malloc returns null
		strcpy(str1, var);
	}
	return str1;
}

void expand_variables_with_single_quotes(char *str)
{
	while (*str)
	{
		if (*str == '\'')
			*str = ' ';
		str++;
	}
}

void input_parse_env_variables(t_commands *cmds, int count)
{
	int i;
	int j;
	char *var;

	i = 0;
	j = 0;
    while (i<count) {
        while (cmds[i].args[j]) {
			var = expand_variables_with_double_quotes(cmds[i].args[j]);
			if (var)
			{
				free(cmds[i].args[j]);
				cmds[i].args[j] = var;
			}
			expand_variables_with_single_quotes(cmds[i].args[j]);
            j++;
        }
        i++;
    }
}

t_commands *input_parse(char *input) {
	int count;
	t_commands *cmds;

	if (empty_input(input))
		return NULL;
	
	count = ft_count_word(input, '|');
	cmds = (t_commands*)malloc(sizeof(t_commands)*(count));
	init_struct(cmds, count);
	input_parse_pipes(input, cmds, count);
	parse_redirection(cmds, count);
	input_parse_env_variables(cmds, count);

	return cmds;
}
