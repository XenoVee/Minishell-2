/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/05 16:02:19 by rmaes         #+#    #+#                 */
/*   Updated: 2024/08/22 14:58:08 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	bi_echo(t_comm_data *c_data, int fd)
{
	int	i;
	int	j;
	int	newline;

	newline = TRUE;
	i = 1;
	while (c_data->cmd[i] && c_data->cmd[i][0] == '-')
	{
		j = 1;
		while (c_data->cmd[i][j] == 'n')
			j++;
		if (!c_data->cmd[i][j])
			newline = FALSE;
		else
			break ;
		i++;
	}
	while (c_data->cmd[i] && c_data->cmd[i++])
	{
		ft_putstr_fd(c_data->cmd[i - 1], fd);
		if (c_data->cmd[i])
			write(1, " ", 1);
	}
	if (newline == TRUE)
		write(1, "\n", 1);
}
