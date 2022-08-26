/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ressalhi <ressalhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 19:29:32 by mmanouze          #+#    #+#             */
/*   Updated: 2022/08/22 11:57:23 by ressalhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_file(t_parse *parse, t_pipex *t_pipe, int i, int c)
{
	if (parse->data[i].red[c].type == 1
		&& g_status.g_status != 1 && g_status.g_conti != 1)
	{
		g_status.g_status = 0;
		if (t_pipe->in_err != 9 && parse->data[i].cmd)
		{
			t_pipe->file_inpt = open(parse->data[i].red[c].file,
					O_RDONLY, 0644);
			dup2(t_pipe->file_inpt, 0);
		}
		input_permission(parse, t_pipe, i, c);
	}
}

void	output_file(t_parse *parse, t_pipex *t_pipe, int i, int c)
{
	if (parse->data[i].red[c].type == 2 && g_status.g_conti != 1)
	{
		if (t_pipe->in_err != 9 && t_pipe->out_err == 0
			&& g_status.g_status != 1)
		{
			g_status.g_status = 0;
			t_pipe->file_outpt = open(parse->data[i].red[c].file,
					O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (access(parse->data[i].red[c].file, W_OK) == -1)
			{
				printf("bash: %s: Permission denied\n",
					parse->data[i].red[c].file);
				t_pipe->out_err = 1;
				g_status.g_status = 1;
			}
			dup2(t_pipe->file_outpt, 1);
			t_pipe->out = 1;
		}
	}
}

void	append_file(t_parse *parse, t_pipex *t_pipe, int i, int c)
{
	if (parse->data[i].red[c].type == 4 && g_status.g_conti != 1)
	{
		if (t_pipe->in_err != 9 && t_pipe->out_err == 0
			&& g_status.g_status != 1)
		{
			g_status.g_status = 0;
			t_pipe->file_appnd = open(parse->data[i].red[c].file,
					O_CREAT | O_APPEND | O_RDWR, 0644);
			if (access(parse->data[i].red[c].file, W_OK) == -1)
			{
				printf("bash: %s: Permission denied\n",
					parse->data[i].red[c].file);
				t_pipe->out_err = 1;
				g_status.g_status = 1;
			}
			dup2(t_pipe->file_appnd, 1);
			t_pipe->out = 1;
		}
	}
}

void	input_permission(t_parse *parse, t_pipex *t_pipe, int i, int c)
{
	if (access(parse->data[i].red[c].file, F_OK) == -1)
	{
		dup2(t_pipe->save[1], 1);
		printf("bash: %s: No such file or directory\n",
			parse->data[i].red[c].file);
		g_status.g_status = 1;
		t_pipe->in_err = 9;
	}
	else if (access(parse->data[i].red[c].file, R_OK) == -1)
	{
		dup2(t_pipe->save[1], 1);
		printf("bash: %s: Permission denied\n", parse->data[i].red[c].file);
		g_status.g_status = 1;
		t_pipe->in_err = 9;
	}
}
