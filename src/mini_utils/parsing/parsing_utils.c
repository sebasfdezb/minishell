/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:19:55 by sebferna          #+#    #+#             */
/*   Updated: 2024/12/17 16:38:54 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_last_token_util(t_data *data, t_parser **node, int *i, int *j)
{
	if (data->flag_hered == 0 && data->flag_token == 1)
		(*node)->filein = open(data->filein, O_RDONLY);
	if (data->flag_add == 0 && data->flag_token == 2)
		(*node)->fileout = open(data->fileout, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
	if (data->flag_hered == 1 && data->flag_token == 1)
		ft_heredoc(data, node, NULL);
	if (data->flag_add == 1 && data->flag_token == 2)
		(*node)->fileout = open(data->fileout, O_WRONLY | O_CREAT | O_APPEND,
				0644);
	if ((*node)->filein == -1 || (*node)->fileout == -1)
		return (data->status = 1, printf("error"), EXIT_FAILURE);
	if (data->flag_token == 1)
		free(data->filein);
	if (data->flag_token == 2)
		free(data->fileout);
	while (data->cmd[*i][*j] == ' ')
		(*j)++;
	return (EXIT_SUCCESS);
}

int	get_last_token(t_data *d, t_parser **node, int *i, int *j)
{
	d->size = 0;
	d->a = 0;
	while (d->cmd[*i][*j] != ' ' && d->cmd[*i][*j] != '\0'
			&& ++(d->size) && ++(*j))
		if (d->cmd[*i][*j] == '<' || d->cmd[*i][*j] == '>')
			return (printf("syntax error"), EXIT_FAILURE);
	if (d->flag_token == 1)
		d->filein = ft_calloc((d->size) + 1, sizeof(char));
	if (d->flag_token == 2)
		d->fileout = ft_calloc((d->size) + 1, sizeof(char));
	d->size = (*j) - (d->size);
	while (d->cmd[*i][d->size] != ' ' && d->cmd[*i][d->size] != '\0')
	{
		if (d->flag_token == 1)
			d->filein[d->a] = d->cmd[*i][d->size];
		if (d->flag_token == 2)
			d->fileout[d->a] = d->cmd[*i][d->size];
		(d->a)++;
		(d->size)++;
	}
	if (get_last_token_util(d, node, i, j) == 1)
		return (free(d->filein), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	get_next_token(t_data *data, int *i, int *j)
{
	if (data->cmd[*i][*j] == '\0')
		return (printf("syntax error"), EXIT_FAILURE);
	if (data->cmd[*i][*j] == '<')
		return (printf("syntax error"), EXIT_FAILURE);
	if (data->cmd[*i][*j] == '>')
		return (printf("syntax error"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	get_token_fileout(t_data *data, t_parser **node, int *i, int *j)
{
	data->flag_add = 0;
	data->flag_token = 2;
	if (data->cmd[*i][*j] == '>' && ++(*j))
	{
		if (data->cmd[*i][*j] == '\0')
			return (printf("syntax error"), EXIT_FAILURE);
		if (data->cmd[*i][*j] == '<')
			return (printf("syntax error"), EXIT_FAILURE);
		if (data->cmd[*i][*j] == '>' && ++(*j))
			data->flag_add = 1;
		if (data->flag_add == 1 && data->cmd[*i][*j] == '\0')
			return (printf("syntax error"), EXIT_FAILURE);
		if (data->flag_add == 1 && data->cmd[*i][*j] == '<')
			return (printf("syntax error"), EXIT_FAILURE);
		if (data->flag_add == 1 && data->cmd[*i][*j] == '>')
			return (printf("syntax error"), EXIT_FAILURE);
		while (data->cmd[*i][*j] == ' ' && ++(*j))
			if (get_next_token(data, i, j) == 1)
				return (EXIT_FAILURE);
		if (get_last_token(data, node, i, j) == 1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	get_token_filein(t_data *data, t_parser **node, int *i, int *j)
{
	data->flag_hered = 0;
	data->flag_token = 1;
	if (data->cmd[*i][*j] == '<' && ++(*j))
	{
		if (data->cmd[*i][*j] == '\0')
			return (printf("Error: Syntax token newline\n"), EXIT_FAILURE);
		if (data->cmd[*i][*j] == '>')
			return (printf("Error: Syntax token `>'\n"), EXIT_FAILURE);
		if (data->cmd[*i][*j] == '<' && ++(*j))
			data->flag_hered = 1;
		if (data->flag_hered == 1 && data->cmd[*i][*j] == '\0')
			return (printf("Error: Syntax token newline\n"), EXIT_FAILURE);
		if (data->flag_hered == 1 && data->cmd[*i][*j] == '<')
			return (printf("Error: Syntax token <<\n"), EXIT_FAILURE);
		if (data->flag_hered == 1 && data->cmd[*i][*j] == '>')
			return (printf("Error: Syntax token >>\n"), EXIT_FAILURE);
		while (data->cmd[*i][*j] == ' ' && ++(*j))
			if (get_next_token(data, i, j) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		if (get_last_token(data, node, i, j) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
