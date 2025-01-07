/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:54:37 by sebferna          #+#    #+#             */
/*   Updated: 2025/01/07 17:14:57 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	up_currdir(t_data *data)
{
	char	currdir[500];
	t_envp	*tmp;

	tmp = data->envp;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "PWD", 3) == EXIT_SUCCESS)
		{
			free(tmp->content);
			tmp->content = ft_strdup(getcwd(currdir, 500));
			if (!tmp->content)
				return ;
			break ;
		}
		tmp = tmp->next;
	}
	g_status = 0;
}

void	home_path(t_data *data, char *str)
{
	t_envp	*tmp;
	char	**cnt;

	tmp = data->envp;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, str, ft_strlen(str)) == EXIT_SUCCESS)
		{
			cnt = ft_split(tmp->content, '=');
			data->aux = cnt[0];
			break ;
		}
		tmp = tmp->next;
	}
}

void	up_prevdir(t_data *data, char *dir)
{
	t_envp	*tmp;

	tmp = data->envp;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "ODLPWD", 6) == EXIT_SUCCESS)
		{
			free(tmp->content);
			if (!dir)
				tmp->content = ft_strdup(getcwd(dir, 500));
			else
				tmp->content = ft_strdup(dir);
			if (!tmp->content)
				return ;
			break ;
		}
		tmp = tmp->next;
	}
}

void	update_cd(t_data *data)
{
	up_prevdir(data, NULL);
	home_path(data, "HOME\0");
	chdir(data->aux);
	up_currdir(data);
	g_status = 0;
}

void	ex_cd(t_data *data, char **str, int flag)
{
	char	currdir[500];

	if (ft_strncmp(str[0], "cd\0", 3) == EXIT_SUCCESS && !str[1])
		update_cd(data);
	else if (!ft_strncmp(str[0], "cd\0", 3) && str[1])
	{
		getcwd(currdir, 500);
		flag = chdir(str[1]);
		if (flag == 0)
		{
			up_prevdir(data, currdir);
			up_currdir(data);
		}
		else if (flag == -1)
		{
			data->aux = ft_strjoin("error cd", str[1]);
			if (!data->aux)
				return ;
			data->error_cd = ft_strjoin(data->aux, " no directoryu");
			if (!data->error_cd)
				return ;
			ft_putendl_fd(data->error_cd, 2);
			free_cd(data);
		}
	}
}
