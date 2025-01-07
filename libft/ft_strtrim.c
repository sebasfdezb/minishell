/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:44:16 by sebferna          #+#    #+#             */
/*   Updated: 2023/12/12 11:16:06 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		start;
	size_t		end;
	size_t		size;
	char		*s2;

	s2 = 0;
	if (s1 == 0 && set == 0)
		return (0);
	if (!*s1 || ((!*s1 && !*set)))
		return (ft_strdup(s1));
	if (s1 != 0)
	{
		start = 0;
		end = ft_strlen(s1);
		while (s1[start] && (ft_strchr(set, s1[start])))
			start++;
		while (s1[end - 1] && (ft_strchr(set, s1[end - 1])) && (end > start))
			end--;
		size = end - start;
		s2 = malloc(sizeof(char) * (size + 1));
		if (!s2)
			return (0);
		ft_strlcpy(s2, &s1[start], size + 1);
	}
	return (s2);
}

/* int	main(void)
{
	char const	a[] = "Hola que tal";
	char const	b[] = "Hola";
	printf("%s", ft_strtrim(a, b));
	return (0);
} */
