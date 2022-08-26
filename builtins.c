/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ressalhi <ressalhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:30:14 by ressalhi          #+#    #+#             */
/*   Updated: 2022/08/23 18:49:18 by ressalhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cher_home(char *s, char **env)
{
	int		i;
	int		j;

	i = 0;
	while (env[i])
	{
		j = ft_strncmp(s, env[i], ft_strlen(s));
		if (j == 0)
		{
			if (env[i][ft_strlen(s)] == '=' || env[i][ft_strlen(s)] == '\0')
				return (i);
		}
		i++;
	}
	return (-1);
}

char	*env_cher2(char *s1, char **env)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	while (env[i])
	{
		j = ft_strncmp(s1, env[i], (ft_strlen(s1)));
		if (j == 0)
		{
			s = ft_strdup(env[i] + ft_strlen(s1) + 1);
			return (s);
		}
		i++;
	}
	return (0);
}
