/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:24:28 by mbjaghou          #+#    #+#             */
/*   Updated: 2022/02/23 15:27:11 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

void	ft_putchar(char c, int *cp)
{
	write(1, &c, 1);
	*cp = *cp + 1;
}

void	ft_hexa(unsigned int n, const char *base, int *cp)
{
	if (n < 16)
		ft_putchar(base[n], cp);
	else
	{
		ft_hexa(n / 16, base, cp);
		ft_putchar(base[n % 16], cp);
	}
}

void	ft_putstr(char *str, int *cp)
{
	int	i;

	if (!str)
	{
		ft_putstr("(null)", cp);
		return ;
	}
	i = 0;
	while (str[i])
	{
		ft_putchar(str[i], cp);
		i++;
	}
}

void	ft_putnbr(int n, int *cp)
{
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		*cp = *cp + 11;
		return ;
	}
	else if (n < 0)
	{
		ft_putchar('-', cp);
		n = -n;
	}
	if (n < 10)
	{
		ft_putchar(n + '0', cp);
	}
	else
	{
		ft_putnbr(n / 10, cp);
		ft_putchar(n % 10 + 48, cp);
	}
}

void	my_printf(const char *tmp, va_list av, int i, int *cp)
{
	i++;
	if (tmp[i] == 's')
		ft_putstr(va_arg(av, char *), cp);
	if (tmp[i] == 'd')
		ft_putnbr(va_arg(av, int), cp);
	if (tmp[i] == 'x')
		ft_hexa(va_arg(av, unsigned long), "0123456789abcdef", cp);
}

int	ft_printf(const char *tmp, ...)
{
	int		i;
	int		cp;
	va_list	av;

	i = 0;
	cp = 0;
	va_start(av, tmp);
	while (tmp[i])
	{
		if (tmp[i] != '%')
			ft_putchar(tmp[i], &cp);
		else
		{
			my_printf(tmp, av, i, &cp);
			i++;
		}
		i++;
	}
	va_end(av);
	return (cp);
}
