/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ressalhi <ressalhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:32:31 by ressalhi          #+#    #+#             */
/*   Updated: 2022/08/21 18:33:54 by ressalhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollar_hundle2(char *s, char *str, t_parse *parse)
{
	while (str[parse->i])
	{
		if (str[parse->i] == '"')
			dollar_dqoutes(s, str, parse);
		else if (str[parse->i] == 39)
			fill_str2(s, str, parse, 39);
		else if (str[parse->i] == '$')
		{
			if (!dollar_dqoutes2(s, str, parse))
				break ;
		}
		else
			s[parse->j++] = str[parse->i];
		if (str[parse->i] == '\0')
			break ;
		parse->i++;
	}
	free(str);
}

void	count_status2(char *str, int *i, int *count)
{
	(*i)++;
	while (str[(*i)] != '"' && str[(*i)])
	{
		if (str[(*i)] == '$' && str[(*i) + 1] == '?')
			(*count)++;
		(*i)++;
	}
}

char	*dollar_hundler(char *str, t_parse *parse)
{
	char	*s;

	if (!str)
		return (NULL);
	parse->j = variable_count(str, parse);
	if (!parse->j)
		return (NULL);
	s = malloc(parse->j + 1);
	parse->i = 0;
	parse->j = 0;
	dollar_hundle2(s, str, parse);
	s[parse->j] = '\0';
	g_status.g_i = count_status(s);
	if (!g_status.g_i)
		return (s);
	s = expand_status(s);
	return (s);
}

int	dollar(t_parse *p, int len)
{
	int	i;
	int	j;

	i = 0;
	while (i < len)
	{
		p->data[i].cmd = dollar_hundler(p->data[i].cmd, p);
		j = 0;
		while (p->data[i].args[j])
		{
			p->data[i].args[j] = dollar_hundler(p->data[i].args[j], p);
			j++;
		}
		i++;
	}
	return (1);
}
