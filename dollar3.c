/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ressalhi <ressalhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 18:31:21 by ressalhi          #+#    #+#             */
/*   Updated: 2022/08/21 18:32:06 by ressalhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_status(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == 39)
		{
			i++;
			while (str[i] != 39 && str[i])
				i++;
		}
		else if (str[i] == '"')
			count_status2(str, &i, &count);
		else if (str[i] == '$' && str[i + 1] == '?')
			count++;
		i++;
	}
	return (count);
}

void	ft_join(char *s, char *str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		s[g_status.g_j] = str[j];
		j++;
		g_status.g_j++;
	}
	g_status.g_i++;
}

void	skiping_sqoute(char *s, char *str)
{
	s[g_status.g_j++] = str[g_status.g_i++];
	while (str[g_status.g_i] != 39 && str[g_status.g_i])
	{
		s[g_status.g_j++] = str[g_status.g_i];
		g_status.g_i++;
	}
	s[g_status.g_j++] = str[g_status.g_i];
}

void	expand_status_dqoutes(char *s, char *str, char *string)
{
	s[g_status.g_j++] = str[g_status.g_i++];
	while (str[g_status.g_i] != '"' && str[g_status.g_i])
	{
		if (str[g_status.g_i] == '$' && str[g_status.g_i + 1] == '?')
			ft_join(s, string);
		else
			s[g_status.g_j++] = str[g_status.g_i];
		g_status.g_i++;
	}
	s[g_status.g_j++] = str[g_status.g_i];
}

char	*expand_status(char *str)
{
	char	*s;
	char	*string;

	string = ft_itoa(g_status.g_status);
	s = malloc((ft_strlen(str) - (g_status.g_i * 2))
			+ (g_status.g_i * ft_strlen(string)) + 1);
	g_status.g_i = 0;
	g_status.g_j = 0;
	while (str[g_status.g_i])
	{
		if (str[g_status.g_i] == 39)
			skiping_sqoute(s, str);
		else if (str[g_status.g_i] == '"')
			expand_status_dqoutes(s, str, string);
		else if (str[g_status.g_i] == '$' && str[g_status.g_i + 1] == '?')
			ft_join(s, string);
		else
			s[g_status.g_j++] = str[g_status.g_i];
		g_status.g_i++;
	}
	s[g_status.g_j] = '\0';
	free(str);
	free(string);
	return (s);
}
