/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cdl_listinit.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 16:17:09 by rmaes         #+#    #+#                 */
/*   Updated: 2024/09/13 15:30:18 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cdl_list.h"
#include <stdlib.h>

// creates and allocates a new list. Returns NULL if allocation fails
t_dllist	*cdl_listinit(void)
{
	t_dllist	*list;

	list = malloc(sizeof(t_dllist));
	if (list == NULL)
		return (NULL);
	list->head = NULL;
	list->current = NULL;
	list->listlen = 0;
	list->arg_l = 0;
	return (list);
}
