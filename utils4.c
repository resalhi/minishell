/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ressalhi <ressalhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 18:39:59 by ressalhi          #+#    #+#             */
/*   Updated: 2022/08/21 18:43:56 by ressalhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	errors_manag(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (!check_errors(tab[i]))
		{
			ft_free_tab(tab);
			return (0);
		}
		i++;
	}
	return (1);
}

char	**error_management(char *str, t_parse *parse)
{
	char	*s;
	char	**tab;

	if (!check_pipes(str))
	{
		free(str);
		return (0);
	}
	s = str_to_split2(str, '|');
	tab = ft_split(s, SPLIT_TOKEN);
	free(s);
	if (!tab)
		return (0);
	if (!check_qoutes(tab, parse))
	{
		ft_free_tab(tab);
		return (0);
	}
	if (!errors_manag(tab))
		return (0);
	return (tab);
}

int	ft_strcmp(char *s1, char *s2)
{
	if (!s1)
		return (1);
	while (*s1 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

char	*ft_strdup(char *s1)
{
	int		i;
	char	*str;

	str = malloc(ft_strlen(s1) + 1);
	if (!str)
		return (0);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab[i]);
	free(tab);
}
