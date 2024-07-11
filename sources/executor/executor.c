/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/24 15:06:32 by rmaes         #+#    #+#                 */
/*   Updated: 2024/06/05 12:58:15 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>

// if/elseifs to check if the command is a builtin. A builtin cannot be piped
static int	builtin(t_commands *cmd, t_dllist *env)
{
	int	fd;

	fd = 2;
	if (!cmd->next && !cmd->prev && cmd->fd_output)
		fd = cmd->fd_output[0];
	if (!ft_strcmp("echo", cmd->args[0]))
		bi_echo(cmd, fd);
	else if (!ft_strcmp("cd", cmd->args[0]))
		bi_cd(env, cmd);
	else if (!ft_strcmp("pwd", cmd->args[0]))
		bi_pwd(fd);
	else if (!ft_strcmp("export", cmd->args[0]))
		bi_export(cmd, env, fd);
	else if (!ft_strcmp("unset", cmd->args[0]))
		bi_unset(cmd, env);
	else if (!ft_strcmp("env", cmd->args[0]))
		bi_env(env, fd);
	else if (!ft_strcmp("exit", cmd->args[0]))
		bi_exit(cmd);
	else
		return (0);
	return (1);
}

// the child. Minishell works using execve(),
// which *replaces* the calling process with
// an executable passed as argument.
// if you were to call it in the main process, it would close minishell.
static void	child(t_commands *cmd, int *pipenew, int *pipeold, t_dllist *env)
{
	char	*path;
	char	**envp;

	envp = NULL;
	startpipe(cmd, pipenew, pipeold);
	if (builtin(cmd, env))
		exit(0);
	else
	{
		path = pathfinder(cmd->args[0], env);
		if (path == NULL)
			exit(1);
		if (access(path, X_OK) != 0)
			exit(2);
		if (env)
			envp = arrayize(env);
		if (execve(path, cmd->args, envp) == -1)
			perror("minishell");
		exit(1);
	}
}

// setup pipes, and create a child
static int	execute(t_commands *cmd, t_dllist *env, int *pipenew, int *pipeold)
{
	int		pid;

	if (cmd->next)
		pipe(pipenew);
	pid = fork();
	if (pid == 0)
		child(cmd, pipenew, pipeold, env);
	else
	{
		wait(NULL);
		endpipe(cmd, pipenew, pipeold);
	}
	return (0);
}

// The executor runs with two arguments: a 'commands' struct list that contains
// all the information about the commands it is to run,
// and a linked list 'env' containing all the env variables.
int	executor(t_commands *cmd, t_dllist *env)
{
	int	pipenew[2];
	int	pipeold[2];

	if (!(cmd->next) && builtin(cmd, env))
		return (0);
	else
	{
		while (cmd)
		{
			execute(cmd, env, pipenew, pipeold);
			cmd = cmd->next;
		}
	}
	return (0);
}
