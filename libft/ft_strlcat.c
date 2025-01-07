/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:02:45 by sebferna          #+#    #+#             */
/*   Updated: 2023/12/13 14:53:10 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	longdest;
	size_t	longsrc;

	i = 0;
	longdest = ft_strlen(dst);
	longsrc = ft_strlen(src);
	if (longdest >= dstsize)
		return (longsrc + dstsize);
	while (src[i] && i < dstsize - 1 - longdest)
	{
		dst[longdest + i] = src[i];
		i++;
	}
	dst[longdest + i] = '\0';
	return (longdest + longsrc);
}
/* int	main(void)
{
	char a[] = "hola";
	char b[] = "mundo";
	int	size = 3;
	printf("%zu\n", ft_strlcat(b, a, size));
	printf("%lu", strlcat(b, a, size));
	return (0);
} */