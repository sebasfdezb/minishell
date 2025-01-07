/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:17:48 by sebferna          #+#    #+#             */
/*   Updated: 2024/11/13 18:43:47 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_cleaner(char *str)
{
	int		i;
	int		j;
	char	*strtmp;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\0')
		return (free(str), NULL);
	strtmp = ft_calloc((ft_strlen_gnl(str) - i + 1), sizeof(char));
	if (!strtmp)
		return (free(str), NULL);
	i++;
	j = 0;
	while (str[i] != '\0')
		strtmp[j++] = str[i++];
	strtmp[j] = '\0';
	return (free(str), strtmp);
}

static char	*ft_line(char *str)
{
	int		i;
	char	*store;

	i = 0;
	if (str[i] == '\0')
		return (NULL);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	store = ft_calloc((i + 1 + (str[i] == '\n')), sizeof(char));
	if (!store)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		store[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		store[i++] = '\n';
	store[i] = '\0';
	return (store);
}

static char	*ft_read(int fd, char *str)
{
	char	*store;
	int		read_char;

	read_char = 1;
	store = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!store)
		return (free(str), NULL);
	while (read_char > 0 && !ft_strchr(store, '\n'))
	{
		read_char = read(fd, store, BUFFER_SIZE);
		if (read_char < 0)
			return (free(store), NULL);
		store[read_char] = '\0';
		str = ft_strjoin(str, store);
		if (!str)
			return (free(str), free(store), NULL);
	}
	return (free(store), str);
}

char	*get_next_line(int fd)
{
	static char	*str[2048];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, 0, 0) < 0)
	{
		if (str[fd] != NULL)
		{
			free(str[fd]);
			str[fd] = NULL;
		}
		return (NULL);
	}
	str[fd] = ft_read(fd, str[fd]);
	if (!str[fd])
		return (free(str[fd]), str[fd] = NULL, NULL);
	line = ft_line(str[fd]);
	if (!line)
		return (free(str[fd]), str[fd] = NULL, NULL);
	str[fd] = ft_cleaner(str[fd]);
	if (!str[fd])
		return (free(str[fd]), str[fd] = NULL, line);
	return (line);
}
