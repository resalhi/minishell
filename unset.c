/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ressalhi <ressalhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 22:03:12 by ressalhi          #+#    #+#             */
/*   Updated: 2022/08/24 21:46:00 by ressalhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_valid2(char *str)
{
	int	i;

	i = 0;
	if (!((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_'))
		return (0);
	while (str[i])
	{
		if (!((str[i] >= 'a' && str[i] <= 'z')
				|| (str[i] >= 'A' && str[i] <= 'Z')
				|| (str[i] >= '0' && str[i] <= '9') || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

void	ft_unset3(char **t, char **env, int j)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (env[i])
	{
		if (i != j)
		{
			t[k++] = ft_strdup(env[i]);
			free(env[i]);
		}
		else
			free(env[i]);
		i++;
	}
	t[k] = 0;
	free(env);
}

char	**ft_unset2(char *str, char **env)
{
	int		i;
	int		j;
	char	**t;

	j = cher_home(str, env);
	if (j == -1)
		return (env);
	i = 0;
	while (env[i])
		i++;
	t = malloc(sizeof(char *) * (i + 1));
	if (!t)
		return (NULL);
	ft_unset3(t, env, j);
	return (t);
}

void	ft_unset(char **tab, t_parse *parse)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (!check_valid2(tab[i]))
		{
			printf("bash: unset: `%s': not a valid identifier\n", tab[i]);
			g_status.g_status = 1;
		}
		else
		{
			parse->env = ft_unset2(tab[i], parse->env);
			g_status.g_status = 0;
		}
		i++;
	}
}

void	ft_pwd(t_parse *p)
{
	char	*s;
	char	*str;

	s = getcwd(NULL, 0);
	if (!s)
	{
		str = env_cher(ft_strdup("PWD"), p->env);
		if (!str)
			printf("bash: PWD not set\n");
		else
			printf("%s/.\n", str);
		free(str);
	}
	else
		printf("%s\n", s);
	free(s);
	g_status.g_status = 0;
}
