/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 11:15:03 by rmaes         #+#    #+#                 */
/*   Updated: 2024/07/11 14:35:25 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

static char	**sort_array(t_dllist *env)
{
	char			**cpy;
	char			*tmp;
	unsigned long	i;
	int				sorted;

	sorted = 0;
	i = 0;
	cpy = arrayize(env);
	while (!sorted)
	{
		sorted = 1;
		i = 0;
		while (i < env->listlen - 1)
		{
			if (ft_strcmp(cpy[i], cpy[i + 1]) < 0)
			{
				tmp = cpy[i];
				cpy[i] = cpy[i + 1];
				cpy[i + 1] = tmp;
				sorted = 0;
			}
			i++;
		}
	}
	return (cpy);
}

static void	export_list(t_dllist *env, int fd)
{
	char	**cpy;
	int		i;

	cpy = sort_array(env);
	i = 0;
	while (cpy[i])
	{
		write(fd, "declare -x ", 11);
		ft_putstr_fd(cpy[i], fd);
		write(fd, "\n", 1);
		i++;
	}
}

static void	export(t_dllist *env, char **s, int i)
{
	if (i == -1)
	{
		cdl_listdecr(env);
		cdl_listaddback(env, cdl_nodenew(s[0], s[1]));
		cdl_listincr(env);
	}
	else if (s[1])
	{
		env->current = cdl_listgetnode(env, i);
		if (env->current->value)
			free (env->current->value);
		env->current->value = s[1];
		free (s[0]);
	}
}

static void	fix_quotes(char **s)
{
	char	*tmp;

	if (s[1][0] == '"' && s[1][ft_strlen(s[1]) - 1] == s[1][0])
	{
		tmp = ft_strtrim(s[1], "\"");
		free (s[1]);
		s[1] = tmp;
	}
	else if (s[1][0] == '\'' && s[1][ft_strlen(s[1]) - 1] == s[1][0])
	{
		tmp = ft_strtrim(s[1], "\'");
		free (s[1]);
		s[1] = tmp;
	}
}

void	bi_export(t_commands *cmd, t_dllist *env, int fd)
{
	char	**s;
	int		n;
	int		i;

	i = 1;
	ft_printf("%s\n", cmd->str);
	if (cmd->args[i] == NULL)
	{
		export_list(env, fd);
		return ;
	}
	while (cmd->args[i])
	{
		s = ft_split(cmd->args[i], '=');
		ft_printf("%s\n", s[1]);
		if (s[1][0] == '"' || s[1][0] == '\'')
			fix_quotes(s);
		n = envsearch(env, s[0]);
		if (n == -1)
			export(env, s, n);
		else if (s[1])
			export(env, s, n);
		free (s);
		i++;
	}
}
