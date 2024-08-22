/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/21 16:05:51 by rmaes         #+#    #+#                 */
/*   Updated: 2024/08/22 16:57:37 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "input.h"
#include "error.h"

static int	setmode(char *c, int i, int *mode)
{
	if (c[i] == '<')
		*mode = INFILE;
	else if (c[i] == '>' && c[i + 1] == '>')
	{
		*mode = OUTFILE_APPEND;
		return (2);
	}
	else if (c[i] == '>')
		*mode = OUTFILE;
	else
		return (0);
	return (1);
}

static int	make_fill_node(t_dllist *lex, char *command, int mode)
{
	int	l;

	l = 0;
	while (command[l] && !ms_isspace(command[l]))
	{
		if (command[l] == '"')
			while (command[++l] != '"')
				if (command[l] == '\0')
					error("tmp");
		if (command[l] == '\'')
			while (command[++l] != '\'')
				if (command[l] == '\0')
					error("tmp");
		l++;
	}
	cdl_listaddback(lex, cdl_nodenew(ft_substr(command, 0, l), num(mode)));
	if (mode == COMMAND)
		lex->arg_l++;
	lex->current = cdl_listgetnode(lex, lex->listlen - 1);
	printf("%s\nMode:%i\n", (char *)lex->current->name,
		*(int *)lex->current->value);
	return (l);
}

t_dllist	*lexer(char *command)
{
	size_t		i;
	int			e;
	t_dllist	*lex;
	int			mode;

	mode = COMMAND;
	i = 0;
	lex = cdl_listinit();
	while (command[i])
	{
		while (ms_isspace(command[i]))
		{
			i++;
			i += setmode(command, i, &mode);
		}
		if (!(command[i] == '\0' && ms_isspace(command[i - 1])))
		{
			e = make_fill_node(lex, &command[i], mode);
			if (e < 0)
			{
				cdl_listclear(lex);
				return (NULL);
			}
			i += e;
		}
	}
	return (lex);
}
