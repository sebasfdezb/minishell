/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_route.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:25:11 by sebferna          #+#    #+#             */
/*   Updated: 2025/01/07 18:08:52 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_cargs(t_parser *node)
{
	struct stat	file_inf;
	int			i;
	int			j;

	i = 1;
	j = 0;
	while (node->all_cmd[i] && ft_strchr(node->all_cmd[i], '-'))
		i++;
	if (node->all_cmd[i - 1])
	{
		while (node->all_cmd[i - 1][j])
		{
			if (ft_isdigit(node->all_cmd[i - 1][j]))
				g_status = 1;
			j++;
		}
	}
	if (stat(node->all_cmd[i], &file_inf) == 0 || !node->all_cmd[i])
		return ;
	g_status = 1;
}

void	route_child_ex(t_data *data, t_parser *node, char **envp)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (data->flag_hered == 1)
	{
		if (dup2(node->filein, STDIN_FILENO) == -1)
			error_msg("Here_doc read error\n");
		unlink("here_doc.tmp");
	}
	else if (node->filein != 0)
	{
		if (dup2(node->filein, STDIN_FILENO) == -1)
			error_msg("Infile read error\n");
	}
	if (node->fileout != 1)
	{
		if (dup2(node->fileout, STDOUT_FILENO) == -1)
			error_msg("Wrt error\n");
	}
	g_status = execve(node->route, node->all_cmd, envp);
}

void	default_execute(t_parser *node, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		g_status = 1;
		error_msg("Fork error\n");
	}
	if (pid == 0)
		g_status = execve(node->route, node->all_cmd, envp);
	else
		waitpid(pid, NULL, 0);
	check_cargs(node);
}

void	ex_route(t_data *data, t_parser *node, char **envp)
{
	pid_t	pid;
	t_list	*lst;

	if (ex_builts(data, node) == 0)
		return ;
	else if (node->filein == 0 && node->fileout == 1)
		default_execute(node, envp);
	else
	{
		lst = data->nodes;
		node = ((t_parser *)lst->content);
		pid = fork();
		if (pid == -1)
		{
			g_status = 1;
			error_msg("Fork error\n");
		}
		if (pid == 0)
			route_child_ex(data, node, envp);
		else
			waitpid(pid, NULL, 0);
		check_cargs(node);
	}
}
