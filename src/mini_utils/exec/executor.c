/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:06:21 by sebferna          #+#    #+#             */
/*   Updated: 2024/12/18 15:42:18 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ex_builts(t_data *data, t_parser *n)
{
	if (!(n->all_cmd))
		return (EXIT_FAILURE);
	else if (n->all_cmd[0] && ft_strncmp(n->all_cmd[0], "cd\0", 3) == 0)
		ex_cd(data, n->all_cmd, 0);
	else if (n->all_cmd[0] && ft_strncmp(n->all_cmd[0], "echo\0", 4) == 0)
		ex_echo(n->all_cmd, 0, n->fileout, data);
	else if (n->all_cmd[0] && ft_strncmp(n->all_cmd[0], "env\0", 4) == 0)
		ex_envp(data, n->fileout);
	else if (n->all_cmd[0] && ft_strncmp(n->all_cmd[0], "pwd\0", 4) == 0)
		ex_pwd(n->fileout);
	else if (n->all_cmd[0] && ft_strncmp(n->all_cmd[0], "unset\0", 6) == 0)
		ex_unset(data, n->all_cmd[1]);
	else if (n->all_cmd[0] && ft_strncmp(n->all_cmd[0], "export\0", 7) == 0)
	{
		data->tmp_envp = data->envp;
		ex_export(data, n->all_cmd, 1, n->fileout);
	}
	else if (n->all_cmd[0] && ft_strncmp(n->all_cmd[0], "exit\0", 5) == 0)
	{
		if (ex_exit(data, n, n->fileout, 0) == EXIT_FAILURE)
			return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	catnls(t_data *data, char **envp)
{
	int		j;
	t_list	*tmp;
	char	*line;

	tmp = data->nodes;
	if (tmp->next != NULL && tmp->next->next != NULL
		&& !ft_strncmp(((t_parser *)(tmp->content))->all_cmd[0],
		"car\0", 4) == 0
		&& ((t_parser *)(tmp->next->content))->all_cmd[1] == NULL
		&& ((t_parser *)(tmp->next->content))->filein == 0
		&& ((t_parser *)(tmp->next->content))->fileout == 1
		&& ft_strncmp(((t_parser *)(tmp->next->next->content))->all_cmd[0],
		"ls\0", 3) == 0)
	{
		ex_route(data, ((t_parser *)(tmp->next->next->content)), envp);
		line = get_next_line(0);
		j = 0;
		while (line && ++j < 2)
		{
			free(line);
			line = get_next_line(0);
		}
		return (free(line), EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	execute(t_data *data, t_parser *node, char **envp, t_list *aux)
{
	signal(SIGINT, sig_ctrlc);
	signal(SIGQUIT, sig_ctrlslash);
	if (node && node->all_cmd && node->all_cmd[0])
	{
		if (data->flag_pipe == 1)
		{
			if ((!ft_strncmp(node->all_cmd[0], "cat\0", 4)
					&& node->all_cmd[1] == NULL && node->filein == 0)
				&& catnls(data, envp) == 0)
				return (EXIT_SUCCESS);
			while (aux)
			{
				if (aux->next == NULL
					&& !ft_strncmp(((t_parser *)(aux->content))->route,
					"b\0", 2))
					ex_builts(data, ((t_parser *)aux->content));
				else
					ex_routepipes(data, ((t_parser *)aux->content), envp, aux);
				aux = aux->next;
			}
		}
		else if (data->flag_pipe == 0)
			ex_route(data, node, envp);
	}
	return (EXIT_SUCCESS);
}
