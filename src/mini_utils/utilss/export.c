/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:16:51 by sebferna          #+#    #+#             */
/*   Updated: 2025/01/07 17:18:32 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	size_envp(t_envp *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

static t_envp	*get_first(t_data *data)
{
	t_envp	*first;
	t_envp	*tmp;

	tmp = data->envp;
	first = data->envp;
	while (tmp)
	{
		if (exp_cmp(first->name, tmp->name) < 0 && tmp->ind == 0)
			first = tmp;
		tmp = tmp->next;
	}
	return (first);
}

int	exp_cmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] > s2[i])
			return (1);
		else if (s1[i] < s2[i])
			return (-1);
		else
			i++;
	}
	return (0);
}

void	set_envp_index(t_data *data)
{
	int		i;
	t_envp	*first;
	t_envp	*tmp;

	i = 1;
	first = data->envp;
	tmp = data->envp;
	while (tmp)
	{
		tmp->ind = 0;
		tmp = tmp->next;
	}
	while (i <= size_envp(data->envp))
	{
		tmp = data->envp;
		while (tmp)
		{
			if (exp_cmp(first->name, tmp->name) > 0 && tmp->ind == 0)
				first = tmp;
			tmp = tmp->next;
		}
		first->ind = i;
		first = get_first(data);
		i++;
	}
}

void	ex_export(t_data *d, char **str, int i, int fd)
{
	set_envp_index(d);
	if (str[1])
		export_content(d, str[1], NULL, d->tmp_envp);
	else if (str[1] == NULL)
	{
		while (d->tmp_envp)
		{
			if (d->tmp_envp->ind == i && i++)
			{
				d->cnt = ft_split(d->tmp_envp->content, '=');
				if (ft_strncmp(d->tmp_envp->content, "\"\"\0", 3) == 0
					|| (d->cnt[0] && d->cnt[0][1] == '\"'))
					ft_printf(fd, "declare -x %s\n", d->tmp_envp->name);
				else
					ft_printf(fd, "declare -x %s=\"%s\"\n", d->tmp_envp->name,
						d->cnt[0]);
				d->tmp_envp = d->envp;
				if (d->cnt != NULL)
					free_split(d->cnt);
			}
			else if (d->tmp_envp->ind != i)
				d->tmp_envp = d->tmp_envp->next;
		}
	}
	g_status = 0;
}
