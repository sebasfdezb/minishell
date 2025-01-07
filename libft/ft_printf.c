/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:29:21 by sebferna          #+#    #+#             */
/*   Updated: 2024/11/26 18:10:32 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_filter(char const *str, int i, va_list *args, int fd)
{
	int	filtrated_c;

	filtrated_c = 0;
	if (str[i] == 'c')
		filtrated_c += ft_printchar(va_arg(*args, int), fd);
	if (str[i] == 's')
		filtrated_c += ft_printstr(va_arg(*args, char *), fd);
	if (str[i] == 'x' || str[i] == 'X')
		filtrated_c += ft_printhexa(va_arg(*args, unsigned int), str[i], fd);
	if (str[i] == 'p')
		filtrated_c += ft_printptr(va_arg(*args, unsigned long long), fd);
	if (str[i] == 'd')
		filtrated_c += ft_printdec(va_arg(*args, int), fd);
	if (str[i] == 'i')
		filtrated_c += ft_printdec(va_arg(*args, int), fd);
	if (str[i] == '%')
		filtrated_c += ft_printchar('%', fd);
	if (str[i] == 'u')
		filtrated_c += ft_printunsigned(va_arg(*args, unsigned int), fd);
	return (filtrated_c);
}

int	ft_printf(int fd, char const *str, ...)
{
	va_list	args;
	int		i;
	int		c;

	i = 0;
	c = 0;
	va_start (args, str);
	while (str[i] != 0)
	{
		if (str[i] != '%')
		{
			ft_printchar(str[i], fd);
			c++;
		}
		else
		{
			i++;
			c += ft_filter(str, i, &args, fd);
		}
		i++;
	}
	va_end (args);
	return (c);
}

/* int	main(void)
{
	printf(" %d\n %s\n %d\n %lx\n %%\n 
		Mi printf:\n", 15, "UWU ONICHAN", 2000000, 1092939798378);
	ft_printf(" %d\n %s\n %p\n %x\n %%\n", 
		15, "UWU ONICHAN", 2000000, 1092939798378);
	return (0);
} */
