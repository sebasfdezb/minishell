/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:39:46 by sebferna          #+#    #+#             */
/*   Updated: 2024/12/16 12:56:45 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_node(t_data *data, char **str)
{
	t_envp	*tmp;

	tmp = data->envp;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, str[0], ft_strlen(str[0])) == EXIT_SUCCESS)
		{
			if (tmp->content)
			{
				free(tmp->content);
				if (str[1] == NULL)
					tmp->content = ft_strjoin("=", "\"\"");
				else
					tmp->content = ft_strjoin("=", str[1]);
			}
			else
				tmp->content = ft_strdup(str[1]);
			return (EXIT_SUCCESS);
		}
		else
			tmp = tmp->next;
	}
	return (EXIT_FAILURE);
}

void	check_path(t_data *data)
{
	t_envp	*tmp;

	tmp = data->envp;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, "PATH", 4))
		{
			data->flag_path = 1;
			return ;
		}
		else
		{
			data->flag_path = 0;
			if (data->path != NULL)
			{
				free_split(data->path);
				data->path = NULL;
			}
		}
		tmp = tmp->next;
	}
}

int	check_builts(t_parser *node)
{
	if (node->all_cmd[0] && ft_strncmp(node->all_cmd[0], "cd\0", 3) == 0)
		return (node->route = ft_strdup("b"), EXIT_FAILURE);
	if (node->all_cmd[0] && ft_strncmp(node->all_cmd[0], "echo\0", 5) == 0)
		return (node->route = ft_strdup("b"), EXIT_FAILURE);
	if (node->all_cmd[0] && ft_strncmp(node->all_cmd[0], "env\0", 4) == 0)
		return (node->route = ft_strdup("b"), EXIT_FAILURE);
	if (node->all_cmd[0] && ft_strncmp(node->all_cmd[0], "pwd\0", 4) == 0)
		return (node->route = ft_strdup("b"), EXIT_FAILURE);
	if (node->all_cmd[0] && ft_strncmp(node->all_cmd[0], "unset\0", 6) == 0)
		return (node->route = ft_strdup("b"), EXIT_FAILURE);
	if (node->all_cmd[0] && ft_strncmp(node->all_cmd[0], "export\0", 7) == 0)
		return (node->route = ft_strdup("b"), EXIT_FAILURE);
	if (node->all_cmd[0] && ft_strncmp(node->all_cmd[0], "exit\0", 5) == 0)
		return (node->route = ft_strdup("b"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	lexer(char	*str)
{
	int	i;
	int	qsimple;
	int	qdoubles;

	i = 0;
	qsimple = 0;
	qdoubles = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' && !qdoubles)
			qsimple = !qsimple;
		else if (str[i] == '\"' && !qsimple)
			qdoubles = !qdoubles;
		i++;
	}
	if (qsimple || qdoubles)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
