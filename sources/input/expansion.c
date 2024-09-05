/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/27 16:53:09 by rmaes         #+#    #+#                 */
/*   Updated: 2024/09/05 16:48:35 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "input.h"

static void	count_quotes(char *str, int *i, int *len, t_dllist *env)
{
	char	mode;

	mode = str[*i];
	++*i;
	while (str[*i] != mode && str[*i])
	{
		if (mode == '"' && str[*i] == '$')
		{
			++*i;
			*len += ft_strlen(find_var(&str[*i], env));
			*i += ft_strlen(find_var(&str[*i], env));
		}
		else
		{
			++*len;
			++*i;
		}
	}
	++*i;
}

static int	find_expansion_len(t_dlnode *node, t_dllist *env)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (((char *)node->name)[i])
	{
		if (((char *)node->name)[i] == '\'' || ((char *)node->name)[i] == '"')
			count_quotes((char *)node->name, &i, &len, env);
		else if (((char *)node->name)[i] == '$')
		{
			len += ft_strlen(find_var(&((char *)node->name)[++i], env));
			while (!ms_isspace(((char *)node->name)[i])
				&& ((char *)node->name)[i])
				i++;
		}
		else
		{
			len++;
			i++;
		}
	}
	printf("__\nLen of expanded string: %i\n", len);
	return (len);
}

static int	expand(char	*s, t_dllist *env, int *i, char *str)
{
	char	*tmp;
	int		j;

	tmp = find_var(&s[1], env);
	j = 0;
	while (tmp[j])
	{
		str[*i] = tmp[j];
		++*i;
		j++;
	}
	return (j);
}

static void	expansion(t_dlnode *node, t_dllist *env, int i, int j)
{
	char	*str;
	char	mode;

	str = malloc(sizeof(char) * (find_expansion_len(node, env) + 1));
	mode = '\0';
	while (((char *)node->name)[j])
	{
		if (((char *)node->name)[j] == '\'' || ((char *)node->name)[j] == '"')
		{
			if (mode == '\0')
				mode = ((char *)node->name)[j];
			else if (((char *)node->name)[j] == mode)
				mode = '\0';
			if (mode == '\0' || mode == ((char *)node->name)[j])
				j++;
		}
		if (((char *)node->name)[j] == '$' && mode != '\'')
			j += expand(&((char *)node->name)[j], env, &i, str);
		else
			str[i] = ((char *)node->name)[j];
		i++;
		j++;
	}
	free (node->name);
	node->name = str;
}

void	check_expansion(t_comm_data *c_data, t_dlnode *node, t_dllist *env)
{
	int	i;

	i = 0;
	c_data = c_data;
	while (((char *)node->name)[i])
	{
		if (((char *)node->name)[i] == '"' || ((char *)node->name)[i] == '\''
			|| ((char *)node->name)[i] == '$')
		{
			expansion(node, env, 0, 0);
			break ;
		}
		i++;
	}
	return ;
}
