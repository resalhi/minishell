/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanouze <mmanouze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 19:14:47 by ressalhi          #+#    #+#             */
/*   Updated: 2022/08/25 16:59:29 by mmanouze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_index(char *str, char **env)
{
	int	i;
	int	j;
	int	index;

	j = 0;
	while (str[j])
	{
		if (str[j] == '=')
			break ;
		j++;
	}
	index = 0;
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(str, env[i], j))
		{
			if (env[i][j] == '=' || env[i][j] == '\0')
				return (i);
		}
		i++;
	}
	return (-1);
}

char	**add_variables(char *str, char **env)
{
	char	**t;
	int		i;

	i = 0;
	while (env[i])
		i++;
	t = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (env[i])
	{
		t[i] = ft_strdup(env[i]);
		free(env[i]);
		i++;
	}
	free(env);
	t[i] = ft_strdup(str);
	i++;
	t[i] = 0;
	return (t);
}

void	modify_variable(char *str, char **env, int index)
{
	int	i;

	if (!ft_strchr(str, '='))
		return ;
	i = 0;
	while (env[i])
	{
		if (i == index)
		{
			free(env[i]);
			env[i] = ft_strdup(str);
		}
		i++;
	}
}

void	ft_export2(char **tab, t_parse *parse)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		if (check_valid(tab[i]))
		{
			j = get_index(tab[i], parse->env);
			if (j == -1)
				parse->env = add_variables(tab[i], parse->env);
			else
				modify_variable(tab[i], parse->env, j);
		}
		else
		{
			printf("bash: export: `%s': not a valid identifier\n", tab[i]);
			g_status.g_status = 1;
			if (g_status.g_id)
				exit(1);
		}
		i++;
	}
}

void	ft_export(char **tab, t_parse *parse)
{
	g_status.g_status = 0;
	sort_env(parse->env);
	if (!tab[0])
	{
		add_print_declare(parse->env);
		return ;
	}
	ft_export2(tab, parse);
}
