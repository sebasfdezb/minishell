/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:48:11 by sebferna          #+#    #+#             */
/*   Updated: 2025/01/07 17:23:07 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	free_envp_node(t_envp *remove)
{
	free(remove->name);
	if (remove->content != NULL)
		free(remove->content);
	free(remove);
	remove = NULL;
	g_status = 0;
}

void	ex_unset(t_data *data, char *str)
{
	t_envp	*del_node;
	t_envp	*prev_node;
	t_envp	*curr_node;

	if (!str)
		return ;
	curr_node = data->envp;
	prev_node = NULL;
	while (curr_node)
	{
		if (!ft_strncmp(curr_node->name, str, ft_strlen(str)))
		{
			del_node = curr_node;
			if (prev_node)
				prev_node->next = curr_node->next;
			else
				data->envp = curr_node->next;
			free_envp_node(del_node);
			return ;
		}
		prev_node = curr_node;
		curr_node = curr_node->next;
	}
	check_path(data);
	g_status = 1;
}
