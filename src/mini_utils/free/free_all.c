/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:20:49 by sebferna          #+#    #+#             */
/*   Updated: 2024/12/17 16:35:59 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_all_envp(t_envp *lst)
{
	if (!lst)
		return ;
	free(lst->name);
	lst->ind = 0;
	free(lst->content);
	free(lst);
	lst = NULL;
}

void	free_envp(t_envp **lst)
{
	t_envp	*tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free_all_envp(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

void	free_all(t_data *data)
{
	if (data->path != NULL)
	{
		free_split(data->path);
		data->path = NULL;
	}
	if (data->prompt != NULL)
	{
		free(data->prompt);
		data->prompt = NULL;
	}
	if (data->envp != NULL)
		free_envp(&data->envp);
	if (data->nodes != NULL)
	{
		free_node(&data->nodes);
		data->nodes = NULL;
	}
	if (data->cmd != NULL)
	{
		free_split(data->cmd);
		data->cmd = NULL;
	}
	free(data);
}
