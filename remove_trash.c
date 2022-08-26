/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_trash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ressalhi <ressalhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 16:28:52 by ressalhi          #+#    #+#             */
/*   Updated: 2022/08/20 16:04:13 by ressalhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_qoutes2(char *str, char *s, int *i, int *j)
{
	(*i)++;
	while (str[(*i)] != '"' && str[(*i)])
	{
		s[(*j)] = str[(*i)];
		(*i)++;
		(*j)++;
	}
}

void	remove_qoutes3(char *str, char *s, int *i, int *j)
{
	(*i)++;
	while (str[(*i)] != 39 && str[(*i)])
	{
		s[(*j)] = str[(*i)];
		(*i)++;
		(*j)++;
	}
}

char	*remove_qoutes(char *str)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	j = 0;
	s = malloc(ft_strlen(str) + 1);
	if (!s)
		return (0);
	while (str[i])
	{
		if (str[i] == '"')
			remove_qoutes2(str, s, &i, &j);
		else if (str[i] == 39)
			remove_qoutes3(str, s, &i, &j);
		else
			s[j++] = str[i];
		i++;
	}
	s[j] = '\0';
	free(str);
	return (s);
}

char	**remove_qoute(char **tab)
{
	int		i;
	char	**t;

	i = 0;
	while (tab[i])
		i++;
	t = malloc(sizeof(char *) * (i + 1));
	if (!t)
		return (0);
	i = 0;
	while (tab[i])
	{
		t[i] = remove_qoutes(tab[i]);
		i++;
	}
	t[i] = 0;
	free(tab);
	return (t);
}

int	remove_trash(t_parse *parse, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		if (parse->data[i].cmd != NULL)
		{
			parse->data[i].cmd = remove_qoutes(parse->data[i].cmd);
			if (!parse->data[i].cmd)
				continue ;
			parse->data[i].args = remove_qoute(parse->data[i].args);
			if (!parse->data[i].args)
				continue ;
		}
		i++;
	}
	return (1);
}
