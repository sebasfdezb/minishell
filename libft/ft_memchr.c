/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 12:20:31 by sebferna          #+#    #+#             */
/*   Updated: 2023/11/28 17:30:24 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*buffer;

	buffer = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (buffer[i] == (unsigned char)c)
			return ((void *)&buffer[i]);
		i++;
	}
	return (NULL);
}

/* int	main(void)
{
	char s[] = "Hola que tal";
	int	c = 'x';
	size_t n = 7;
	printf("%s", ft_memchr(s, c, n));
	return (0);
} */
