/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 14:14:33 by rmaes         #+#    #+#                 */
/*   Updated: 2024/08/22 15:02:42 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	bi_unset(t_comm_data *c_data, t_dllist *env)
{
	int	n;
	int	i;

	i = 1;
	while (c_data->cmd[i])
	{
		n = envsearch(env, c_data->cmd[i]);
		if (n == -1)
			return ;
		cdl_listdelnode(env, n);
		i++;
	}
}
