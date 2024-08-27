/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/27 16:53:09 by rmaes         #+#    #+#                 */
/*   Updated: 2024/08/27 17:35:34 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "input.h"

static char	*find_var(char	*str, t_dllist *env)
{
	int		i;
	char	c;
	char	*s;

	i = 0;
	while (str[i] && !ms_isspace(str[i]))
	{
		i++;
	}
	c = str[i];
	str[i] = '\0';
	s = ft_getenv(env, str);
	str[i] = c;
	return (s);
}

//segfaults, why, dont know. More importantly, single quotes shouldn't count var length
//also, please make this nicer this is ugly af btich
static void	expansion(t_comm_data *c_data, t_dlnode *node, t_dllist *env)
{
	int	len;
	int	i;

	len = ft_strlen((char *)node->name);
	i = 0;
	while (((char *)node->name)[i])
	{
		if (((char *)node->name)[i] == '"' || ((char *)node->name)[i] == '\'')
			len--;
		if (((char *)node->name)[i] == '$')
		{
			len += ft_strlen( find_var(&(((char *)node->name)[i]), env));
			while ((((char *)node->name)[i] != '"' || ((char *)node->name)[i] != '\'')
				&& !ms_isspace(((char *)node->name)[i]))
			{
				i++;
				len--;
			}
		}
		i++;
	}
	c_data->fd_input = 0;
	printf("__\nLen of expanded string: %i\n", len);
}

void	check_expansion(t_comm_data *c_data, t_dlnode *node, t_dllist *env)
{
	int	i;

	i = 0;
	while (((char *)node->name)[i])
	{
		if (((char *)node->name)[i] == '"' || ((char *)node->name)[i] == '\''
			|| ((char *)node->name)[i] == '$')
		{
			expansion(c_data, node, env);
			break ;
		}
		i++;
	}
	return ;
}
