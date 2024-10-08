/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/17 16:42:25 by rmaes         #+#    #+#                 */
/*   Updated: 2024/05/27 16:29:59 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*ret;
	int		i;

	ret = 0;
	i = 0;
	while (s[i])
	{
		if ((unsigned char) s[i] == (unsigned char) c)
			ret = (char *)&s[i];
		i++;
	}
	if ((unsigned char) s[i] == (unsigned char) c)
		ret = (char *)&s[i];
	return (ret);
}
