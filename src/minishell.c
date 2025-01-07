/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:48:38 by sebferna          #+#    #+#             */
/*   Updated: 2025/01/07 17:14:31 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_status = 0;

static void	init_struct(t_data *data)
{
	data->prompt = NULL;
	data->path = NULL;
	data->i = 0;
	data->j = 0;
	data->flag = 0;
	data->d = 0;
	data->dup_stdin = dup(STDIN_FILENO);
	data->cnt = NULL;
}

int	inputs(t_data *data, char **envp)
{
	if (lexer(data->prompt) == EXIT_FAILURE)
		return (printf("Error: Unclosed Quotes\n"), EXIT_SUCCESS);
	if (get_path(data) == EXIT_FAILURE)
		return (EXIT_SUCCESS);
	if (get_cmds(data) == EXIT_FAILURE)
		return (EXIT_SUCCESS);
	expand(data);
	if (parsing(data, 0, 0) == EXIT_FAILURE)
		return (EXIT_SUCCESS);
	if (data->nodes == NULL)
		return (EXIT_SUCCESS);
	if (process_route(data, 0) == EXIT_FAILURE)
		return (EXIT_SUCCESS);
	if (execute(data, (t_parser *)data->nodes->content, envp, data->nodes) == 1)
		return (EXIT_SUCCESS);
	unlink("here_doc.tmp");
	return (EXIT_SUCCESS);
}

int	getprompt(t_data *data)
{
	char	direc[500];
	char	*direcf;

	if (getcwd(direc, sizeof(direc)) == NULL)
		return (EXIT_FAILURE);
	direcf = ft_strjoin(direc, " % ");
	if (direcf == NULL)
		return (EXIT_FAILURE);
	data->prompt = readline(direcf);
	free(direcf);
	direcf = NULL;
	if (!data->prompt)
	{
		printf("exit\n");
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	minishell(t_data *data, char **env)
{
	while (1)
	{
		signal(SIGINT, signals);
		signal(SIGQUIT, SIG_IGN);
		if (getprompt(data) == EXIT_FAILURE)
			exit (EXIT_FAILURE);
		if (ft_strncmp(data->prompt, "\0", 1) == EXIT_FAILURE)
			add_history(data->prompt);
		if (inputs(data, env) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (data->nodes != NULL)
			free_node(&data->nodes);
		if (data->cmd != NULL)
		{
			free_split(data->cmd);
			data->cmd = NULL;
		}
		if (data->prompt != NULL)
		{
			free(data->prompt);
			data->prompt = NULL;
		}
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	if (argc > 1)
		return (EXIT_FAILURE);
	(void)argc;
	(void)argv;
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (EXIT_FAILURE);
	init_struct(data);
	get_envp(data, envp, -1);
	if (minishell(data, envp) == EXIT_FAILURE)
		return (free_all(data), EXIT_FAILURE);
	return (free_all(data), EXIT_SUCCESS);
}
