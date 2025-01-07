/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:39:29 by sebferna          #+#    #+#             */
/*   Updated: 2025/01/07 17:23:14 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	error_msg_pipe(char *error)
{
	unlink("here_doc.tmp");
	g_status = 1;
	perror(error);
	exit(EXIT_FAILURE);
}

void	error_msg(char *error)
{
	unlink("here_doc.tmp");
	g_status = 1;
	perror(error);
	exit(EXIT_FAILURE);
}
