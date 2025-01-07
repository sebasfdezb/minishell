/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:08:20 by sebferna          #+#    #+#             */
/*   Updated: 2024/12/17 16:37:04 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_dir(char *aux)
{
	DIR	*dir;

	dir = opendir(aux);
	if (dir != NULL)
	{
		closedir(dir);
		return (1);
	}
	else
		return (0);
}

int	get_route(t_data *data, t_parser *node, int i)
{
	char	*aux1;
	char	*aux2;

	if (node->all_cmd[0] == NULL)
		return (printf("error"), 1);
	if (check_builts(node) == 1)
		return (EXIT_SUCCESS);
	while (data->path != NULL && data->path[++i] != NULL)
	{
		aux1 = ft_strjoin(data->path[i], "/");
		aux2 = ft_strjoin(aux1, node->all_cmd[0]);
		free(aux1);
		if (access(aux2, F_OK) == 0 && access(aux2, X_OK) == 0)
		{
			node->route = ft_strdup(aux2);
			return (free(aux2), aux2 = NULL, EXIT_SUCCESS);
		}
		free(aux2);
	}
	if (get_dir(node->all_cmd[0]) == 0 && access(node->all_cmd[0], F_OK) == 0
		&& access(node->all_cmd[0], X_OK) == 0)
		node->route = ft_strdup(node->all_cmd[0]);
	if (node->route == NULL)
		return (printf("error"), 1);
	return (EXIT_SUCCESS);
}

int	process_route(t_data *data, int i)
{
	t_list	*tmp;

	tmp = data->nodes;
	data->flag_pipe = 0;
	while (data->cmd[i] != NULL && ((t_parser *)(tmp->content))->all_cmd)
	{
		if (get_route(data, ((t_parser *)(tmp->content)), -1) == 1)
			return (data->status = 127, EXIT_FAILURE);
		if (i == 1)
			data->flag_pipe = 1;
		i++;
		if (tmp->next != NULL)
			tmp = tmp->next;
	}
	if (((t_parser *)(tmp->content))->all_cmd == NULL)
		((t_parser *)(tmp->content))->route = NULL;
	return (EXIT_SUCCESS);
}
