/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cdl_listclear.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 18:03:54 by rmaes         #+#    #+#                 */
/*   Updated: 2024/07/25 17:35:43 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cdl_list.h"
#include <stdlib.h>
#include <stdio.h>

// deletes and frees all nodes, and the list itself
void	cdl_listclear(t_dllist *list)
{
	while (list->head)
		cdl_listdelnode(list, 0);
	free(list);
}
