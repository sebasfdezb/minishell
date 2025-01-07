/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:16:53 by sebferna          #+#    #+#             */
/*   Updated: 2024/11/13 18:42:01 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_gnl(const char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_strchr_gnl(const char *str, int len)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == (char)len)
			return (1);
		i++;
	}
	return (0);
}

void	*ft_calloc_gnl(size_t count, size_t size)
{
	char	*ptr;
	size_t	i;

	ptr = (char *)malloc(count * size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < (count * size))
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}

char	*ft_strjoin_gnl(char *str1, char *str2)
{
	int		i;
	char	*str3;
	int		size;

	if (!str1)
	{
		str1 = ft_calloc_gnl(1, sizeof(char));
		if (!str1)
			return (free(str1), str1 = NULL, NULL);
	}
	if (!str2)
		return (free(str1), str1 = NULL, NULL);
	size = ft_strlen_gnl(str1) + ft_strlen_gnl(str2);
	str3 = (char *)ft_calloc((size + 1), sizeof(char));
	if (!str3)
		return (free(str1), str1 = NULL, NULL);
	i = -1;
	while (str1[++i])
		str3[i] = str1[i];
	i = -1;
	while (str2[++i])
		str3[ft_strlen_gnl(str1) + i] = str2[i];
	str3[ft_strlen_gnl(str1) + i] = '\0';
	return (free(str1), str1 = NULL, str3);
}
