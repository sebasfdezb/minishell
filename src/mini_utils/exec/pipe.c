/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:10:18 by sebferna          #+#    #+#             */
/*   Updated: 2024/12/17 16:33:17 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	process_pipe_out(t_parser *node, char **envp, t_data *data)
{
	if (node->fileout != STDOUT_FILENO)
	{
		if (dup2(node->fileout, STDOUT_FILENO) == -1)
			error_msg("Last command wrt error\n", data);
		close(node->fileout);
	}
	data->status = execve(node->route, node->all_cmd, envp);
}

void	process_final_pipe(t_data *data, t_parser *node, char **envp)
{
	if (node->filein != 0 && data->flag_hered == 1)
	{
		if (dup2(node->filein, STDIN_FILENO) == -1)
			error_msg_pipe("Here_doc read error\n", data);
	}
	else if (node->filein != 0 && data->flag_hered == 0)
	{
		if (dup2(node->filein, STDIN_FILENO) == -1)
			error_msg_pipe("Infile read error\n", data);
	}
	else if (data->fd[1] == STDOUT_FILENO)
	{
		if (dup2(data->fd[0], STDIN_FILENO) == -1)
			error_msg_pipe("Read error\n", data);
	}
	else if (node->filein == 0)
	{
		if (dup2(node->filein, STDIN_FILENO) == -1)
			error_msg_pipe("Infile read error\n", data);
	}
	close(node->filein);
	process_pipe_out(node, envp, data);
}

void	handle_child_command(t_data *d, t_parser *n, char **envp, t_list *tmp)
{
	if (n->fileout == 1)
	{
		if (dup2(d->fd[1], STDOUT_FILENO) == -1)
			error_msg_pipe("Outfile wrt error", d);
	}
	else if (n->fileout != 1)
	{
		if (dup2(n->fileout, STDOUT_FILENO) == -1)
			error_msg_pipe("Outfile wrt error", d);
		close(n->fileout);
	}
	close(d->fd[1]);
	if (ft_strncmp(n->route, "b\0", 2) == 0)
	{
		if (n->fileout == 1 && ((t_parser *)(tmp->next->content))->filein == 0)
			((t_parser *)(tmp->next->content))->fileout = d->fd[0];
		ex_builts(d, n);
		exit(1);
	}
	else
		d->status = execve(n->route, n->all_cmd, envp);
}

void	handle_child_pipe(t_data *d, t_parser *node, char **envp, t_list *tmp)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (d->flag_hered == 1)
	{
		if (dup2(node->filein, STDIN_FILENO) == -1)
			error_msg_pipe("Here_doc read error\n", d);
		unlink("here_doc.tmp");
		close(node->filein);
	}
	else if (node->filein != STDIN_FILENO)
	{
		if (dup2(node->filein, STDIN_FILENO) == -1)
			error_msg_pipe("Infile read error\n", d);
		close(node->filein);
	}
	close(d->fd[0]);
	handle_child_command(d, node, envp, tmp);
}

void	ex_routepipes(t_data *data, t_parser *n, char **envp, t_list *tmp)
{
	pid_t	pid;

	if (pipe(data->fd) == -1)
		error_msg("Pipe error\n", data);
	pid = fork();
	if (pid == -1)
	{
		close(data->fd[0]);
		close(data->fd[1]);
		error_msg("Fork error\n", data);
	}
	if (pid == 0)
	{
		if (tmp->next != NULL)
			handle_child_pipe(data, n, envp, tmp);
		else
			process_final_pipe(data, n, envp);
	}
	if (tmp->next && ((t_parser *)(tmp->next->content))->filein == 0)
		((t_parser *)(tmp->next->content))->filein = data->fd[0];
	else
		close(data->fd[0]);
	close(data->fd[1]);
	waitpid(pid, NULL, 0);
	check_cargs(n, data);
}
