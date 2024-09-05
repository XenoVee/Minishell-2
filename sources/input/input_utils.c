/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/21 16:08:18 by rmaes         #+#    #+#                 */
/*   Updated: 2024/09/05 16:48:51 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "minishell.h"

int	skipover_quotes(char const *s, int *i, int j)
{
	char	c;

	c = 0;
	if (s[j + *i] == '"' || s[j + *i] == '\'')
		c = s[j + *i];
	else
		return (0);
	while (s[j + ++*i] != c)
		if (s[j + *i] == '\0')
			return (1);
	return (0);
}

// whitespace is: space ' ', tab '\t', carriage return '\r',
// newline '\n', vertical tab ( '\v' ) and formfeed '\f'.
int	ms_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\r'
		|| c == '\n' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

void	*num(int i)
{
	int	*o;

	o = malloc(sizeof(int));
	*o = i;
	return (o);
}

char	*find_var(char	*str, t_dllist *env)
{
	int		i;
	char	c;
	char	*s;

	i = 0;
	while (str[i] && !ms_isspace(str[i]) && str[i] != '"' && str[i] != '\'')
	{
		i++;
	}
	c = str[i];
	str[i] = '\0';
	s = ft_getenv(env, str);
	str[i] = c;
	if (s == NULL)
	{
		s = malloc(sizeof(char));
		s[0] = '\0';
	}
	return (s);
}
