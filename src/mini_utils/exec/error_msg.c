/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:39:29 by sebferna          #+#    #+#             */
/*   Updated: 2024/12/17 16:19:52 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	error_msg_pipe(char *error, t_data *data)
{
	unlink("here_doc.tmp");
	data->status = 1;
	perror(error);
	exit(EXIT_FAILURE);
}

void	error_msg(char *error, t_data *data)
{
	unlink("here_doc.tmp");
	data->status = 1;
	perror(error);
	exit(EXIT_FAILURE);
}
