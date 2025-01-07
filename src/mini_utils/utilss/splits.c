/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:07:11 by sebferna          #+#    #+#             */
/*   Updated: 2024/12/16 17:18:12 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**get_words(t_data *data, char const *str, char c, int i)
{
	char	**s;
	int		j;

	data->d = 0;
	data->flag = 0;
	data->quote = '\0';
	j = count_words(data, str, c, 0);
	s = malloc(sizeof(char *) * (j + 1));
	if (!s)
		return (0);
	while (++i < j)
	{
		data->flag = 0;
		data->quote = '\0';
		data->size = 0;
		data->size = size_words(data, str, c, &data->d);
		s[i] = ft_substr(str, (data->d - (data->size)), data->size);
		split_words(data, str, c);
		if (!(s[i]))
		{
			free_split(s);
			return (0);
		}
	}
	return (s[i] = NULL, s);
}

int	get_cmds(t_data *d)
{
	int	i;

	i = 0;
	while (d->prompt[i] == ' ' || d->prompt[i] == '	')
		i++;
	if (d->prompt[i] == '\0')
		return (EXIT_FAILURE);
	d->cmd = splits_cmd(d->prompt, '|');
	if (d->cmd == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	get_path(t_data *d)
{
	t_envp	*tmp;

	tmp = d->envp;
	if (d->path != NULL)
	{
		free_split(d->path);
		d->path = NULL;
	}
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "PATH", 4) == 0)
		{
			d->path = ft_split(tmp->content + 1, ':');
			break ;
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
