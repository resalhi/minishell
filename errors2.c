/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ressalhi <ressalhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 18:34:35 by ressalhi          #+#    #+#             */
/*   Updated: 2022/08/25 14:02:58 by ressalhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_to_split(char *str, char c)
{
	int		i;
	char	*s;

	s = ft_strdup(str);
	i = 0;
	while (s[i])
	{
		if (s[i] == c || s[i] == '\t')
			s[i] = SPLIT_TOKEN;
		else if (s[i] == '"')
		{
			i++;
			while (s[i] != '"' && s[i])
				i++;
		}
		else if (s[i] == 39)
		{
			i++;
			while (s[i] != 39 && s[i])
				i++;
		}
		i++;
	}
	return (s);
}

int	check_str_split(char *s, int *i)
{
	if (s[(*i)] == '"')
	{
		(*i)++;
		if (s[(*i)] == '\0')
			return (0);
		while (s[(*i)] != '"' && s[(*i)])
			(*i)++;
		if (s[(*i)] == '\0')
			return (0);
	}
	else if (s[(*i)] == 39)
	{
		(*i)++;
		if (s[(*i)] == '\0')
			return (0);
		while (s[(*i)] != 39 && s[(*i)])
			(*i)++;
		if (s[(*i)] == '\0')
			return (0);
	}
	return (1);
}

char	*str_to_split2(char *str, char c)
{
	int		i;
	char	*s;

	s = ft_strdup(str);
	free(str);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			s[i] = SPLIT_TOKEN;
		if (!check_str_split(s, &i))
			break ;
		i++;
	}
	return (s);
}

int	check_pipes2(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '|')
	{
		g_status.g_status = 258;
		printf("Syntax error\n");
		return (0);
	}
	if (str[0] == ' ' || str[0] == '\t')
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] == '|')
		{
			g_status.g_status = 258;
			printf("Syntax error\n");
			return (0);
		}
	}
	return (1);
}

int	check_pipes(char *str)
{
	int	i;

	if (!check_pipes2(str))
		return (0);
	i = 0;
	while (str[i])
	{
		if (!skipping_qoutes(str, &i))
			break ;
		if (str[i] == '|')
		{
			i++;
			while (str[i] == ' ' || str[i] == '\t')
				i++;
			if (str[i] == '|' || str[i] == '\0')
			{
				g_status.g_status = 258;
				printf("Syntax error\n");
				return (0);
			}
		}
		i++;
	}
	return (1);
}
