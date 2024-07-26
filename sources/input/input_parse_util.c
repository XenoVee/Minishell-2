/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse_util.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/23 14:49:50 by rmaes         #+#    #+#                 */
/*   Updated: 2024/07/23 15:08:00 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "libft.h"
#include "input.h"

void	remove_char(char *str, int position)
{
	int	i;

	i = position;
	while (1)
	{
		*(str + i) = *(str + i + 1);
		if (*(str + i) == '\0')
			break ;
		i++;
	}
}

void	remove_white_spaces_and_tabs(char *input, char chr, int before)
{
	int	i;

	i = 0;
	while (1)
	{
		if (before)
		{
			if (*(input + i) == ' ' && *(input + i + 1) == chr)
			{
				remove_char(input, i--);
			}
			else if (*(input + i) == '\t' && *(input + i + 1) == chr)
				remove_char(input, i--);
			else
				i++;
		}
		else if (!before)
		{
			if (*(input + i) == ' ' && *(input + i - 1) == chr)
				remove_char(input, i--);
			else if (*(input + i) == '\t' && *(input + i - 1) == chr)
				remove_char(input, i--);
			else
				i++;
		}
		else
			i++;
		if (*(input + i) == '\0')
			break ;
	}
}

void	free_cmds_memory(t_commands *cmds)
{
	int	i;
	int	j;

	if (!cmds)
		return ;
	i = 0;
	while (1)
	{
		j = 0;
		while (cmds[i].args[j])
		{
			free(cmds[i].args[j]);
			j++;
		}
		free(cmds[i].args);
		free(cmds[i].str);
		free(cmds[i].fd_output);
		if (!cmds[i].next)
			break ;
		i++;
	}
	free(cmds);
}

int	ft_count_word(char const *s, char c)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			cnt++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (cnt);
}
