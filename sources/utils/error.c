/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/05 16:50:47 by rmaes         #+#    #+#                 */
/*   Updated: 2024/08/27 14:36:35 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

void	error(char *errmsg)
{
	ft_putstr_fd("Error\n", 2);
	if (errno == 0)
		ft_putendl_fd(errmsg, 2);
	else
		perror(errmsg);
	exit(EXIT_FAILURE);
}

void	*parse_error(char *errmsg)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd("Syntax error: ", 2);
	ft_putendl_fd(errmsg, 2);
	return (NULL);
}
