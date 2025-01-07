/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:39:10 by sebferna          #+#    #+#             */
/*   Updated: 2025/01/07 17:24:51 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_t_parser(t_parser *node)
{
	if (node == NULL)
		return ;
	if (node->all_cmd != NULL)
	{
		free_split(node->all_cmd);
		node->all_cmd = NULL;
	}
	if (node->route != NULL)
		free(node->route);
	if (node->filein != 0)
		close(node->filein);
	if (node->fileout != 1)
		close(node->fileout);
	free(node);
}

static void	free_command(t_list **lst)
{
	free(((t_parser *)((*lst)->content))->all_cmd);
	((t_parser *)((*lst)->content))->all_cmd = NULL;
	free(((t_parser *)((*lst)->content))->route);
	((t_parser *)((*lst)->content))->route = NULL;
	if (((t_parser *)((*lst)->content))->filein != 0)
		close(((t_parser *)((*lst)->content))->filein);
	if (((t_parser *)((*lst)->content))->fileout != 1)
		close(((t_parser *)((*lst)->content))->fileout);
	free(((t_parser *)((*lst)->content)));
	(*lst)->content = NULL;
}

void	free_node(t_list **lst)
{
	int		i;
	t_list	*tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		i = -1;
		if (((t_parser *)((*lst)->content))->all_cmd)
		{
			while (((t_parser *)((*lst)->content))->all_cmd[++i])
			{
				free(((t_parser *)((*lst)->content))->all_cmd[i]);
				((t_parser *)((*lst)->content))->all_cmd[i] = NULL;
			}
		}
		free_command(lst);
		free((*lst));
		*lst = tmp;
	}
	*lst = NULL;
}

void	free_cd(t_data *data)
{
	free(data->aux);
	free(data->error_cd);
	g_status = 1;
}

void	free_split(char **tmp)
{
	int	i;

	i = 0;
	while (tmp != NULL && tmp[i] != NULL)
	{
		free(tmp[i]);
		tmp[i] = NULL;
		i++;
	}
	if (tmp != NULL)
	{
		free(tmp);
		tmp = NULL;
	}
	tmp = NULL;
}
