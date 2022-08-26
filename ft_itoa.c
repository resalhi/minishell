/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ressalhi <ressalhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 17:31:29 by ressalhi          #+#    #+#             */
/*   Updated: 2022/08/12 17:31:39 by ressalhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_intlen(int n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		i++;
	while (n != 0)
	{
		n /= 10 ;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*res;
	size_t		len;
	long int	nb;

	nb = n;
	len = ft_intlen(n);
	if (n < 0)
	{
		nb *= -1;
		len++;
	}
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	res[len] = '\0' ;
	while (len--)
	{
		res[len] = nb % 10 + '0';
		nb /= 10 ;
	}
	if (n < 0)
		res[0] = '-' ;
	return (res);
}
