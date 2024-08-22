/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 15:25:50 by rmaes         #+#    #+#                 */
/*   Updated: 2024/08/22 14:24:27 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "executor.h"
// I feel like I close pipes too often, might need changes, have to test
// especially with the in/outfile handlers

// runs in parent process
void	endpipe(t_comm_data *cmd, int *pipenew, int *pipeold)
{
	if (cmd->prev)
	{
		close(pipeold[0]);
		close(pipeold[1]);
	}
	if (cmd->next)
	{
		pipeold[0] = pipenew[0];
		pipeold[1] = pipenew[1];
	}
}

// runs in child process
// opens the pipes using dup(2);
// pipe: array of two file descriptors. pipe[0] is read, pipe[1] is write
void	startpipe(t_comm_data *cmd, int *pipenew, int *pipeold)
{
	if (cmd->fd_input != -1)
	{
		dup2(cmd->fd_input, STDIN);
		close(pipeold[1]);
	}
	else if (cmd->prev)
	{
		dup2(pipeold[0], STDIN);
		close(pipeold[0]);
		close(pipeold[1]);
	}
	if (cmd->fd_output)
	{
		close(pipenew[0]);
		dup2(cmd->fd_output[0], STDOUT);
	}
	else if (cmd->next)
	{
		close(pipenew[0]);
		dup2(pipenew[1], STDOUT);
		close(pipenew[1]);
	}
}
// handling multiple oufiles... Execve can only write into one FD.
// Write into pipe, then copy from pipe to file?
// send file to execve, copy from that file into the other files if theres more?
