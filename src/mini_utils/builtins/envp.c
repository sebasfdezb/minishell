/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:44:28 by sebferna          #+#    #+#             */
/*   Updated: 2024/12/17 16:37:13 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ex_envp(t_data *data, int fd)
{
	t_envp	*tmp;

	tmp = data->envp;
	while (tmp != NULL)
	{
		if ((tmp->content[1] != '"') && (tmp->content[2] != '"'))
			ft_printf(fd, "%s%s\n", tmp->name, tmp->content);
		tmp = tmp->next;
	}
}

void	lst_addenv_back(t_envp **lst, t_envp *new)
{
	t_envp	*tmp;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		tmp = *lst;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	get_envp(t_data *data, char **envp, int i)
{
	char	**curr;
	t_envp	*tmp;

	while (envp[++i] != NULL)
	{
		tmp = ft_calloc(1, sizeof(t_envp));
		if (!tmp)
			exit (EXIT_FAILURE);
		curr = ft_split(envp[i], '=');
		tmp->name = ft_strdup(curr[0]);
		if (curr[1] == NULL)
			tmp->content = ft_strdup("=");
		else
			tmp->content = ft_strjoin("=", curr[1]);
		tmp->ind = 0;
		tmp->next = NULL;
		lst_addenv_back(&data->envp, tmp);
		free_split(curr);
		curr = NULL;
	}
	set_envp_index(data);
}
