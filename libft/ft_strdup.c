/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:30:27 by sebferna          #+#    #+#             */
/*   Updated: 2023/12/11 12:43:33 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		i;
	size_t	j;

	i = 0;
	j = ft_strlen(s1);
	s2 = (char *)malloc(sizeof(char) * j + 1);
	if (s2 == NULL)
		return (0);
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

/* int	main(void)
{
	char	s1[] = "Holaaa";
	printf("%s", ft_strdup(s1));
	return (0);
} */
