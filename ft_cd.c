/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ressalhi <ressalhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 13:34:04 by ressalhi          #+#    #+#             */
/*   Updated: 2022/08/23 18:54:45 by ressalhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	modify_oldpwd(char **env)
{
	int		i;
	char	*s;
	char	*s1;

	s = getcwd(NULL, 0);
	if (!s)
		return ;
	s1 = ft_strjoin2("OLDPWD=", s);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp("OLDPWD", env[i], 6))
		{
			free(env[i]);
			env[i] = ft_strdup(s1);
		}
		i++;
	}
	free(s1);
}

void	modify_pwd(char **env)
{
	int		i;
	char	*s;
	char	*s1;

	s = getcwd(NULL, 0);
	if (!s)
		return ;
	s1 = ft_strjoin2("PWD=", s);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp("PWD", env[i], 3))
		{
			free(env[i]);
			env[i] = ft_strdup(s1);
		}
		i++;
	}
	free(s1);
}

void	ft_cd_home(t_parse *parse)
{
	char	*s;
	int		i;

	if (cher_home("HOME", parse->env) == -1)
	{
		cher_home_err();
		return ;
	}
	else
	{
		modify_oldpwd(parse->env);
		s = env_cher2("HOME", parse->env);
		if (!s)
			return ;
		i = chdir(s);
		free(s);
		if (i != 0)
		{
			g_status.g_status = 1;
			printf("bash: cd: %s: No such file or directory\n", s);
			if (g_status.g_id)
				exit(1);
		}
		modify_pwd(parse->env);
	}
}

void	ft_cd_dir(char **tab, t_parse *parse)
{
	int	i;

	modify_oldpwd(parse->env);
	i = chdir(tab[0]);
	if (i != 0)
	{
		printf("bash: cd: %s: No such file or directory\n", tab[0]);
		g_status.g_status = 1;
		if (g_status.g_id)
			exit(1);
		return ;
	}
	modify_pwd(parse->env);
}

void	ft_cd(char **tab, t_parse *parse)
{
	char	*s;

	g_status.g_status = 0;
	if (!tab[0])
		ft_cd_home(parse);
	else if (!ft_strcmp(tab[0], "."))
	{
		s = getcwd(NULL, 0);
		if (!s)
		{
			free(s);
			printf("cd: error retrieving current directory: getcwd:cannot");
			printf(" access parent directories: No such file or directory\n");
		}
		free(s);
	}
	else
		ft_cd_dir(tab, parse);
}
