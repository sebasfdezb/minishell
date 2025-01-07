/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:27:48 by sebferna          #+#    #+#             */
/*   Updated: 2024/12/17 16:34:30 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	prints_echo(char **str, int i, int fd)
{
	int	j;

	j = 0;
	while (str[i][j])
	{
		ft_printf(fd, "%c", str[i][j]);
		if (str[i][j] == '\0')
			break ;
		j++;
	}
}

void	echo_print_args(char **str, int i, int fd)
{
	while (str[i])
	{
		prints_echo(str, i, fd);
		if (str[i + 1] || str[i][0] == '\0')
			ft_printf(fd, " ");
		i++;
	}
}

void	ex_echo(char **str, int flag, int fd, t_data *d)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i > 1)
	{
		i = 0;
		if (str[1] && !ft_strncmp(str[1], "-n", 2))
		{
			flag = 1;
			i = 2;
			echo_print_args(str, i, fd);
		}
		else
		{
			i = 1;
			echo_print_args(str, i, fd);
		}
	}
	if (flag == 0)
		ft_printf(fd, "\n");
	d->status = 0;
}
