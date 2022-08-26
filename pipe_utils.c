/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanouze <mmanouze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:23:03 by mmanouze          #+#    #+#             */
/*   Updated: 2022/08/25 17:00:57 by mmanouze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*str;
	unsigned char	*ssr;

	str = (unsigned char *)s1;
	ssr = (unsigned char *)s2;
	i = 0;
	while ((str[i] && ssr[i]) && str[i] == ssr[i] && i < n - 1)
		i++;
	return (str[i] - ssr[i]);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = (char *)s;
	while (str[j])
		j++;
	while (i <= j)
	{
		if (str[i] == (char)c)
			return (str + i);
		i++;
	}
	return (NULL);
}

char	*ft_strjoin_p(char *s1, char *s2)
{
	int		i;
	int		c;
	char	*store;

	i = 0;
	c = 0;
	if (!s1 || !s2)
		return (0);
	store = malloc((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	if (!store)
		return (NULL);
	while (s1[i])
	{
		store[i] = s1[i];
		i++;
	}
	store[i++] = '/';
	while (s2[c])
		store[i++] = s2[c++];
	store[i] = '\0';
	return (store);
}

char	*join_data(char *s1, char *s2)
{
	int		i;
	int		c;
	char	*store;

	i = 0;
	c = 0;
	if (!s1 || !s2)
		return (0);
	store = malloc((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	if (!store)
		return (NULL);
	while (s1[i])
	{
		store[i] = s1[i];
		i++;
	}
	store[i++] = ' ';
	while (s2[c])
		store[i++] = s2[c++];
	free(s1);
	store[i] = '\0';
	return (store);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t len)
{
	size_t	i;
	size_t	j;

	j = 0;
	if (!*dst && !*src)
		return (0);
	while (src[j])
		j++;
	if (!len)
		return (j);
	i = 0;
	while (i < len - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (j);
}
