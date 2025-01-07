/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:56:01 by sebferna          #+#    #+#             */
/*   Updated: 2023/11/29 15:13:57 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*a;
	size_t			i;
	size_t			x;

	if (!s)
		return (0);
	i = 0;
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	x = 0;
	x = ft_strlen(s) - start;
	if (x > len)
		x = len;
	a = malloc(sizeof(char) * (x + 1));
	if (!a)
		return (0);
	while (i < len && s[start] != '\0')
	{
		a[i] = s[start];
		i++;
		start++;
	}
	a[i] = '\0';
	return ((char *)a);
}

/* int	main(void)
{
	char	a[] = "Hola que tal";
	printf("%s", ft_substr(a, 3, 5));
	return (0);
} */