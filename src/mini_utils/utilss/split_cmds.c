/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:19:55 by sebferna          #+#    #+#             */
/*   Updated: 2024/12/16 17:13:57 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	size_cmd(char const *str, char c, int j)
{
	int		size;
	char	s;

	size = 0;
	while (str[j] != '\0' && str[j] != c)
	{
		if (str[j] == '\'' || str[j] == '\"')
		{
			s = str[j];
			j++;
			size++;
			while (str[j] != s)
			{
				j++;
				size++;
			}
		}
		size++;
		j++;
	}
	return (size);
}

int	counts_extend(char const **s1, char c, char *s2)
{
	if (**s1 == c)
		return (printf("Error: Syntax token `|'\n"), -2);
	while (**s1 != c && **s1 != '\0')
	{
		if ((**s1 == '<' || **s1 == '>') && (*s1)++)
		{
			while (**s1 == ' ')
				(*s1)++;
			if (**s1 == c)
				return (printf("Error: Syntax token `|'\n"));
		}
		if (**s1 == '\'' || **s1 == '\"')
		{
			*s2 = **s1;
			(*s1)++;
			while (**s1 != *s2)
				(*s1)++;
		}
		(*s1)++;
	}
	return (EXIT_SUCCESS);
}

static int	count_cmd(char const *str, char c, int i)
{
	char	s;

	while (*str != '\0')
	{
		if (counts_extend(&str, c, &s) == -2)
			return (-2);
		if (*str == c && str++)
		{
			while (*str == ' ')
				str++;
			if (*str == c || *str == '\0')
				return (printf("Error: Syntax Pipes\n"), -2);
		}
		i++;
	}
	return (i);
}

char	**splits_cmd(char const *str, char c)
{
	int		i;
	int		j;
	char	**s;

	i = -1;
	j = 0;
	s = malloc(sizeof(char *) * (count_cmd(str, c, 0) + 1));
	if (!s)
		return (0);
	while (++i < count_cmd(str, c, 0))
	{
		while (str[j] == c)
			j++;
		while (str[j] == ' ')
			j++;
		s[i] = ft_substr(str, j, size_cmd(str, c, j));
		if (!(s[i]))
		{
			free_split(s);
			return (0);
		}
		j = j + size_cmd(str, c, j);
	}
	s[i] = 0;
	return (s);
}
