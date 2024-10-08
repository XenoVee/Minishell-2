/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/25 13:21:34 by rmaes         #+#    #+#                 */
/*   Updated: 2024/08/22 14:59:42 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"

static int	setpwd(t_dllist *env, char *n)
{
	char	*cwd;
	int		i;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (1);
	i = envsearch(env, n);
	if (i == -1)
	{
		cdl_listdecr(env);
		cdl_listaddback(env, cdl_nodenew(n, cwd));
		cdl_listincr(env);
	}
	else
	{
		env->current = cdl_listgetnode(env, i);
		if (env->current->value)
			free (env->current->value);
		env->current->value = cwd;
	}
	return (0);
}

static int	ereturn(char *rel)
{
	perror("minishell: cd");
	if (rel)
		free (rel);
	return (1);
}

static char	*buildrel(t_comm_data *c_data)
{
	char	*rel;

	rel = getcwd(NULL, 0);
	rel = ft_realloc(rel, (ft_strlen(rel) + ft_strlen(c_data->cmd[1]) + 2));
	ft_strlcat(rel, "/", ft_strlen(rel) + 2);
	ft_strlcat(rel, c_data->cmd[1],
		(ft_strlen(rel) + ft_strlen(c_data->cmd[1]) + 2));
	return (rel);
}

int	bi_cd(t_dllist *env, t_comm_data *c_data)
{
	char	*rel;

	if (setpwd(env, "OLDPWD") == 0 && c_data->cmd[1] != NULL)
	{
		rel = buildrel(c_data);
		if (chdir(rel) != 0 && chdir(c_data->cmd[0]) != 0)
			return (ereturn(rel));
		free (rel);
	}
	else
	{
		if (chdir(ft_getenv(env, "HOME")) != 0)
			return (ereturn(NULL));
	}
	setpwd(env, "PWD");
	return (0);
}
