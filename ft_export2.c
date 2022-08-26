/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ressalhi <ressalhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:49:19 by ressalhi          #+#    #+#             */
/*   Updated: 2022/08/23 18:56:16 by ressalhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_env(char **env)
{
	int		i;
	int		j;
	int		h;
	char	*s;

	h = 0;
	while (env[h])
		h++;
	i = 0;
	while (i < h)
	{
		j = i + 1;
		while (j < h)
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				s = env[i];
				env[i] = env[j];
				env[j] = s;
			}
			j++;
		}
		i++;
	}
}

void	add_print_qoutes(char **env, int i)
{
	int	j;

	j = 0;
	printf("declare -x ");
	while (env[i][j])
	{
		if (env[i][j] == '=')
		{
			printf("%c", env[i][j]);
			break ;
		}
		printf("%c", env[i][j]);
		j++;
	}
	printf("%c%s%c\n", '"', env[i] + j + 1, '"');
}

void	add_print_declare(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (!ft_strchr(env[i], '='))
			printf("declare -x %s\n", env[i]);
		else
			add_print_qoutes(env, i);
		i++;
	}
}

int	check_valid(char *str)
{
	int	i;

	i = 0;
	if (!((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')
			|| str[i] == '_'))
		return (0);
	while (str[i] != '=' && str[i])
	{
		if (!((str[i] >= 'a' && str[i] <= 'z')
				|| (str[i] >= 'A' && str[i] <= 'Z')
				|| (str[i] >= '0' && str[i] <= '9')
				|| str[i] == '_' || str[i] == '='))
			return (0);
		i++;
	}
	return (1);
}
