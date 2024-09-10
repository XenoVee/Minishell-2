/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/02 18:50:31 by rmaes         #+#    #+#                 */
/*   Updated: 2024/09/10 15:49:54 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

// doesnt segfault when given NULL
size_t	safestrlen(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i++])
		;
	return (i);
}

// adds current directory to list of places to look for executable
static char	**find_paths(t_dllist *env)
{
	char	*path;
	char	**split;

	path = ft_tristrjoin(ft_getenv(env, "PATH"), ":", ft_getenv(env, "PWD"));
	split = ft_split(path, ':');
	free (path);
	return (split);
}

// checks if a given file exists
char	*pathfinder(char *f, t_dllist *env)
{
	char	**split;
	int		i;
	char	*check;
	char	*find;

	split = find_paths(env);
	find = ft_strjoin("/", f);
	i = 0;
	while (split[i])
	{
		check = ft_strjoin(split[i], find);
		if (access(check, F_OK) == 0)
		{
			free (find);
			return (check);
		}
		free(check);
		i++;
	}
	perror("minishell");
	return (NULL);
}

// I handle the env as a list because it is many many times easier to edit.
// some functions (such a execve()) need it as an array, so this turns it back.
char	**arrayize(t_dllist *env)
{
	char	**array;
	int		i;
	int		len[2];

	i = 0;
	array = malloc(sizeof(char *) * (env->listlen + 1));
	array[env->listlen] = NULL;
	env->current = env->head;
	if (!array)
		error(ERR_MALLOC);
	while (env->current != env->head || i == 0)
	{
		len[NAME] = ft_strlen(env->current->name);
		len[VALUE] = safestrlen(env->current->value);
		array[i] = malloc(sizeof(char) * (len[NAME] + len[VALUE] + 2));
		ft_strlcpy(array[i], env->current->name, len[NAME] + 1);
		if (len[VALUE])
			ft_strlcat(array[i], "=", len[NAME] + 2);
		if (len[VALUE])
			ft_strlcat(array[i],
				env->current->value, len[NAME] + len[VALUE] + 2);
		i++;
		env->current = env->current->next;
	}
	return (array);
}
