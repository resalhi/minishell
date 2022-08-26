/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ressalhi <ressalhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 18:33:34 by ressalhi          #+#    #+#             */
/*   Updated: 2022/08/21 18:36:37 by ressalhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dollar_dqoutes3(char *s, char *str, t_parse *parse)
{
	char	*s1;

	s1 = NULL;
	parse->i++;
	if (str[parse->i] == '\0' || !ft_isalnum(str[parse->i]))
	{
		s[parse->j++] = str[parse->i - 1];
		if (!ft_isalnum(str[parse->i]) && str[parse->i] != '\0')
		{
			while (str[parse->i] != '$' && str[parse->i])
			{
				s[parse->j++] = str[parse->i];
				parse->i++;
			}
			parse->i--;
			return (1);
		}
		return (0);
	}
	s1 = dollar_fill(str, parse, s1);
	fill_str(s1, s, parse);
	return (1);
}

void	dollar_dqoutes(char *s, char *str, t_parse *parse)
{
	s[parse->j++] = str[parse->i++];
	while (str[parse->i] != '"' && str[parse->i])
	{
		if (str[parse->i] == '$' && str[parse->i + 1] != '"'
			&& str[parse->i + 1] != 39)
		{
			if (!dollar_dqoutes3(s, str, parse))
				return ;
		}
		else
			s[parse->j++] = str[parse->i];
		parse->i++;
	}
	if (str[parse->i] == '"')
		s[parse->j++] = str[parse->i];
}

int	dollar_status(char *s, char *str, t_parse *parse)
{
	if (str[parse->i] == '\0' || !ft_isalnum(str[parse->i]))
	{
		s[parse->j++] = str[parse->i - 1];
		if (!ft_isalnum(str[parse->i]) && str[parse->i] != '\0')
		{
			while (str[parse->i] != '$' && str[parse->i])
			{
				s[parse->j++] = str[parse->i];
				parse->i++;
			}
			parse->i--;
			return (1);
		}
		return (0);
	}
	return (2);
}

int	dollar_dqoutes2(char *s, char *str, t_parse *parse)
{
	int		h;
	char	*s1;

	s1 = NULL;
	parse->i++;
	h = dollar_status(s, str, parse);
	if (!h)
		return (0);
	else if (h == 1)
		return (1);
	if (str[parse->i] == '"')
		fill_str2(s, str, parse, '"');
	else if (str[parse->i] == 39)
		fill_str2(s, str, parse, 39);
	else
	{
		s1 = dollar_fill(str, parse, s1);
		fill_str(s1, s, parse);
	}
	return (1);
}

char	**expanding(char **tab)
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
		t[i] = expand(tab[i]);
		if (!t[i])
			return (0);
		i++;
	}
	t[i] = 0;
	free(tab);
	return (t);
}
