/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:17:31 by sebferna          #+#    #+#             */
/*   Updated: 2023/11/28 17:25:51 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	a;

	i = 0;
	while (s[i])
		i++;
	a = (char)c;
	while (i >= 0)
	{
		if (s[i] == a)
			return ((char *)(s + i));
		i--;
	}
	return (0);
}

/* char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i--;
	}
	return (0);
} */
/* int main(void)
{
	char str[] = "Hello, world!";
    char find_char = 'w';
	int	i;

	i = 0;
    char *result = ft_strrchr(str, find_char);

    if (result != 0)
    {
        printf("El carácter '%c' fue encontrado en la posición: %ld\n", 
			find_char, result - str);
		while (result[i])
		{
			printf("%c", result[i]);
			i++;
		}
    }
    else
        printf("'%c' no fue encontrado en la cadena.\n", find_char);
    return (0);
} */