/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:26:37 by sebferna          #+#    #+#             */
/*   Updated: 2025/01/07 18:12:55 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_heredoc(t_data *data, t_parser **node, char *str)
{
	(*node)->filein = open("here_doc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if ((*node)->filein == -1)
		return ;
	while (1)
	{
		write(1, "heredoc> ", 9);
		str = get_next_line(data->dup_stdin);
		if (!str)
			error_msg("Get Next Line Error");
		if (!ft_strncmp(data->filein, str, ft_strlen(data->filein)))
		{
			free(str);
			close(data->dup_stdin);
			break ;
		}
		ft_putstr_fd(str, (*node)->filein);
		free(str);
	}
	close((*node)->filein);
	(*node)->filein = open("here_doc.tmp", O_RDONLY);
	data->dup_stdin = dup(STDIN_FILENO);
	if ((*node)->filein == -1)
		error_msg("Here DOc open file1 Error");
}
