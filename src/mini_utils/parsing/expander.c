/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:33:28 by sebferna          #+#    #+#             */
/*   Updated: 2024/12/17 16:38:29 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*envp_content(t_data *d, char *str)
{
	char	*status;
	char	*next;
	t_envp	*tmp;

	tmp = d->envp;
	if (ft_strncmp(str, "?", 1) == EXIT_SUCCESS)
	{
		status = ft_itoa(d->status);
		return (status);
	}
	while (tmp)
	{
		if (ft_strncmp(tmp->name, str, ft_strlen(tmp->name)) == EXIT_SUCCESS)
		{
			next = ft_substr(tmp->content, 1, ft_strlen(tmp->content) - 1);
			return (next);
		}
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

void	next_expand(t_data *d, int *i, int *flag, char **expand)
{
	if (!*flag && d->cmd[d->i][d->j] != '~')
	{
		*i = d->j;
		while ((d->cmd[d->i][d->j] != '$' || *flag)
				&& d->cmd[d->i][d->j] && d->cmd[d->i][d->j] != '~')
		{
			if (d->cmd[d->i][d->j] == '\'')
				*flag = !*flag;
			d->j++;
		}
		d->aux = ft_substr(d->cmd[d->i], *i, d->j - *i);
		*expand = ft_strjoin_gnl(*expand, d->aux);
	}
	else
	{
		*i = d->j;
		while ((d->cmd[d->i][d->j] != '$' || *flag)
				&& d->cmd[d->i][d->j] && ++(d->j))
		{
			if (d->cmd[d->i][d->j] == '\'')
				*flag = !*flag;
		}
		d->aux = ft_substr(d->cmd[d->i], *i, d->j - *i);
		*expand = ft_strjoin_gnl(*expand, d->aux);
	}
}

static void	prime_expand(t_data *d, int *i, int *flag, char **expand)
{
	char	*next;

	while ((d->cmd[d->i][d->j] != '$' || *flag) && d->cmd[d->i][d->j])
	{
		if ((!*flag && d->cmd[d->i][d->j] == '~')
			&& ((d->cmd[d->i][d->j - 1] == ' '
			&& d->cmd[d->i][d->j + 1] == ' ')
			|| (d->cmd[d->i][d->j + 1] == '\0')
			|| (d->cmd[d->i][d->j + 1] == '/')))
		{
			if (d->cmd[d->i][d->j] == '\'')
				*flag = !(*flag);
			next = envp_content(d, "HOME");
			*expand = ft_strjoin_gnl(*expand, next);
			free(next);
			d->j++;
		}
		else
			next_expand(d, i, flag, expand);
		if (d->aux != NULL)
		{
			free(d->aux);
			d->aux = NULL;
		}
	}
}

static void	dollar_expand(t_data *d, int *i, int *flag, char **expand)
{
	char	*aux;

	if (d->cmd[d->i][d->j] == '$' && !*flag)
	{
		if (d->cmd[d->i][d->j + 1] == '\0' || d->cmd[d->i][d->j + 1] == ' ')
		{
			*expand = ft_strjoin_gnl(*expand, ft_strdup("$"));
			d->j++;
		}
		else
		{
			d->j++;
			*i = d->j;
			while ((d->cmd[d->i][d->j] != ' ' && d->cmd[d->i][d->j] != '$' &&
				d->cmd[d->i][d->j]) && d->cmd[d->i][d->j] != '\''
				&& d->cmd[d->i][d->j] != '\"')
				d->j++;
			aux = ft_substr(d->cmd[d->i], *i, d->j - *i);
			*expand = ft_strjoin_gnl(*expand, envp_content(d, aux));
			free(aux);
			aux = NULL;
		}
	}
}

void	expand(t_data *d)
{
	int		i;
	int		flag;
	char	*expand;

	flag = 0;
	expand = NULL;
	while (d->cmd[d->i])
	{
		d->j = 0;
		i = 0;
		while (d->cmd[d->i][d->j])
		{
			dollar_expand(d, &i, &flag, &expand);
			prime_expand(d, &i, &flag, &expand);
		}
		free(d->cmd[d->i]);
		d->cmd[d->i] = NULL;
		d->cmd[d->i] = ft_strdup(expand);
		free(expand);
		expand = NULL;
		d->i++;
	}
	d->i = 0;
}
