/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:58:27 by sebferna          #+#    #+#             */
/*   Updated: 2024/12/17 16:18:56 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ex_exit(t_data *data, t_parser *node, int i, int fd)
{
	ft_printf(fd, "exit\n");
	if (node->all_cmd[1] != NULL && node->all_cmd[2] != NULL)
		return (ft_printf(fd, "error exit"));
	else if (node->all_cmd[1] != NULL)
	{
		i = -1;
		if (node->all_cmd[1][0] == '+' || node->all_cmd[1][0] == '-')
			i++;
		while (node->all_cmd[1][++i])
		{
			if (ft_isdigit(node->all_cmd[1][i]) == 0)
			{
				ft_printf(fd, "error: exit");
				break ;
			}
		}
	}
	if (data->path != NULL)
	{
		free_split(data->path);
		data->path = NULL;
	}
	exit(data->status);
}
