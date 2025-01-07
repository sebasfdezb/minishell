/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:24:14 by sebferna          #+#    #+#             */
/*   Updated: 2024/12/18 15:35:44 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	counts(t_data *data, char const **str, char c, int *j)
{
	while ((**str == c || **str == '\'' || **str == '\"')
		&& **str != data->quote
		&& **str != '\0')
	{
		if (data->flag == 0 && (**str == '\'' || **str == '\"'))
		{
			data->flag = !data->flag;
			data->quote = **str;
		}
		if (++(*str) && **str != '\0' && **str == data->quote)
			break ;
	}
	if (**str != '\0' && **str != data->quote && **str != c)
		(*j)++;
	if (data->flag)
	{
		while (**str != data->quote && **str != '\0')
			(*str)++;
		data->flag = !data->flag;
	}
}

int	count_words(t_data *data, char const *str, char c, int j)
{
	while (*str != '\0')
	{
		data->quote = '\0';
		counts(data, &str, c, &j);
		while (*str != c && *str != '\0' && *(str)++)
			if (*str == '\'' || *str == '\"')
				break ;
	}
	return (j);
}

static void	handle_quotes(t_data *data, char const *str, int *d, char c)
{
	while ((str[*d] == '\'' || str[*d] == '\"') && data->quote == '\0'
		&& str[*d] != '\0')
	{
		if (data->quote == '\0' || str[*d] == data->quote)
		{
			data->flag = !data->flag;
			data->quote = str[*d];
		}
		(*d)++;
		while (!data->flag && str[*d] == c)
			(*d)++;
	}
}

int	size_words(t_data *data, char const *str, char c, int *d)
{
	while (str[*d] != '\0' && str[*d] != c)
	{
		while ((str[*d] == '\'' || str[*d] == '\"')
			&& str[(*d) + 1] == str[*d] && ++(*d) && ++(*d))
			while (str[*d] == c)
				(*d)++;
		handle_quotes(data, str, d, c);
		while ((data->flag || str[*d] != c) && str[*d] != data->quote
			&& str[*d] != '\0' && ++(*d) && ++(data->size))
		{
			if (!data->flag && (str[*d] == '\'' || str[*d] == '\"'))
				return (data->size);
		}
		if (str[*d] == data->quote)
			return (data->size);
	}
	return (data->size);
}

void	split_words(t_data *data, char const *str, char c)
{
	if (str[data->d] != c)
	{
		if (str[data->d] == data->quote && data->flag == 1)
			data->d++;
		while (str[data->d] == c)
			data->d++;
	}
	while (str[data->d] == c)
		data->d++;
}
