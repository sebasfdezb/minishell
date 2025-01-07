/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:23:55 by sebferna          #+#    #+#             */
/*   Updated: 2023/12/04 15:45:38 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
} */

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*a;

	a = (char *)s;
	i = 0;
	while (i < n)
	{
		a[i] = 0;
		i++;
	}
}

/* int	main(void)
{
	char a[20] = "Holaaa que tal";
	int	i = 0;
	int	b = strlen(a);
	ft_bzero(a, 4);
	while (i < b)
	{
		printf("%c", a[i]);
		i++;
	}
	return (0);
} */
