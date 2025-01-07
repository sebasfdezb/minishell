/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:37:40 by sebferna          #+#    #+#             */
/*   Updated: 2023/12/11 11:15:57 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] && s2[i])
	{
		if ((unsigned char)s1[i] < (unsigned char)s2[i])
			return (-1);
		else if (s1[i] > s2[i])
			return (1);
		i++;
	}
	if (i < n)
	{
		if (s1[i] == '\0' && s2[i] != '\0')
			return (-1);
		else if (s1[i] != '\0' && s2[i] == '\0')
			return (1);
	}
	return (0);
}

/* int	main(void)
{
	const char s1[4] = "Hola";
	const char s2[5] = "Holaa";
	size_t n = 5;
	printf("%d", ft_strncmp(s1, s2, n));
	return (0);
} */
