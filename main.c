/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanouze <mmanouze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 12:52:39 by ressalhi          #+#    #+#             */
/*   Updated: 2022/08/25 16:22:50 by mmanouze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	excute_builtins(char **comd, t_parse *parse)
{
	if (!ft_strcmp(comd[0], "echo"))
		ft_echo(comd + 1);
	else if (!ft_strcmp(comd[0], "export"))
		ft_export(comd + 1, parse);
	else if (!ft_strcmp(comd[0], "env"))
		print_env(parse);
	else if (!ft_strcmp(comd[0], "unset"))
		ft_unset(comd + 1, parse);
	else if (!ft_strcmp(comd[0], "pwd"))
		ft_pwd(parse);
	else if (!ft_strcmp(comd[0], "cd"))
		ft_cd(comd + 1, parse);
	else if (!ft_strcmp(comd[0], "exit"))
		ft_exit(comd + 1);
}

void	ft_free(t_parse *parse)
{
	int	i;
	int	j;

	i = 0;
	while (i < parse->num_data)
	{
		free(parse->data[i].cmd);
		j = 0;
		while (parse->data[i].args[j])
		{
			free(parse->data[i].args[j]);
			j++;
		}
		free(parse->data[i].args);
		j = 0;
		while (j < parse->data[i].num_red)
		{
			free(parse->data[i].red[j].file);
			j++;
		}
		if (parse->data[i].num_red >= 0)
			free(parse->data[i].red);
		i++;
	}
	free(parse->data);
}

void	ft_print_exit(char *str)
{
	printf("%s", str);
	exit(g_status.g_status);
}

void	ft_loop(char *str, t_parse *parse, t_pipex *t_pipe)
{
	while (1)
	{
		signal(SIGINT, sig_int);
		signal(SIGQUIT, SIG_IGN);
		str = readline("bash-0.2$ ");
		if (!str)
			ft_print_exit("exit\n");
		if (check(str) || check_space(str))
			continue ;
		add_history(str);
		if (!parser(str, parse))
			continue ;
		wait_cmd(t_pipe, parse);
		if (check_for_builtins(parse, t_pipe))
		{
			ft_default(t_pipe);
			ft_free(parse);
			g_status.g_conti = 0;
			continue ;
		}
		ft_begin(parse, t_pipe);
		ft_free(parse);
		ft_default(t_pipe);
	}
}

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_parse	*parse;
	t_pipex	*t_pipe;

	(void)ac;
	(void)av;
	str = NULL;
	parse = malloc(sizeof(t_parse));
	t_pipe = malloc(sizeof(t_pipex));
	initializing(t_pipe, parse, env);
	ft_loop(str, parse, t_pipe);
}
