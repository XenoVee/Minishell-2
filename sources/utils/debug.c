/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/10 13:58:14 by rmaes         #+#    #+#                 */
/*   Updated: 2024/09/10 15:08:05 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	logv(char *str, int m)
{
	static int	depth = 0;
	int			i;

	if (m == RESET)
	{
		depth = 0;
		return ;
	}
	depth += m;
	i = 0;
	if (m == START)
	{
		while (i++ < depth)
			printf("  ");
		printf("%s \n", str);
	}
}
