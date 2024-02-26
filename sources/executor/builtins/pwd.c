/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/25 13:11:01 by rmaes         #+#    #+#                 */
/*   Updated: 2024/02/22 13:20:33 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	bi_pwd(int fd)
{
	char	*path;

	path = getcwd(NULL, 0);
	ft_putstr_fd(path, fd);
	write(fd, "\n", 1);
	free (path);
}
