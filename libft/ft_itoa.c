/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 13:20:48 by sebferna          #+#    #+#             */
/*   Updated: 2023/12/11 13:45:35 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_countnbr(int n)
{
	unsigned int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		count = 1;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char				*s;
	unsigned int		nbr;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	nbr = ft_countnbr(n);
	s = (char *) malloc(sizeof(char) * (nbr + 1));
	if (!s)
		return (0);
	if (n == 0)
		ft_strlcpy(s, "0", nbr + 1);
	if (n < 0)
	{
		s[0] = '-';
		n = -n;
	}
	s[nbr] = '\0';
	while (n != 0)
	{
		s[nbr - 1] = (n % 10) + '0';
		n = n / 10;
		nbr--;
	}
	return (s);
}

/* int	main(void)
{
	printf("%d\n", ft_countnbr(-2147483648));
	printf("%s", ft_itoa(-2147483648));
	return (0);
} */
