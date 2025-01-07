/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:54:35 by sebferna          #+#    #+#             */
/*   Updated: 2023/12/12 12:42:47 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while ((char)c != s[i])
	{
		if (s[i] == '\0')
			return (0);
		i++;
	}
	return ((char *)&s[i]);
}

/* int main(void)
{
	 char str[] = "Hello, world!";
    char find_char = 'w';
	int	i;

	i = 0;
    char *result = ft_strchr(str, find_char);

    if (result != 0)
    {
        printf("El carácter '%c' fue encontrado en 
			la posición: %ld\n", find_char, result - str);
		while (result[i])
		{
			printf("%c", result[i]);
			i++;
		}
    }
    else
        printf("'%c' no fue encontrado en la cadena.\n", find_char);
    return 0;
} */