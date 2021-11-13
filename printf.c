#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

va_list	va;
int	z;
int	count;
int	field;
int	prec;

void	ft_putchar(char c)
{
	write(1, &c, 1);
	count++;
}

void	ft_putstr(char *str)
{
	int	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

void	ft_putstr_n(char *str, int n)
{
	int	i = 0;
	while (n > 0)
	{
		ft_putchar(str[i]);
		i++;
		n--;
	}
}

long	ft_strlen(char *str)
{
	long	i = 0;
	while (str[i])
		i++;
	return (i);
}

long	ft_atoi(char *str)
{
	long	res = 0;
	while (str[z] >= '0' && str[z] <= '9')
	{
		res *= 10;
		res += str[z] - '0';
		z++;
	}
	return (res);
}

int	ft_len_nbr(long x, char *base)
{
	int	len_nbr = 0;
	if (x <= 0)
	{
		x *= -1;
		len_nbr++;
	}
	while (x > 0)
	{
		x /= ft_strlen(base);
		len_nbr++;
	}
	return (len_nbr);
}

void	ft_putnbr(long x, char *base)
{
	if (x < 0)
	{
		x *= -1;
		ft_putchar('-');
	}
	if (x >= ft_strlen(base))
	{
		ft_putnbr((x / ft_strlen(base)), base);
	}
	ft_putchar(base[x % ft_strlen(base)]);
}

int	ft_treat_d(int d)
{
	z++;
	char	*base = "0123456789";
	int	len_nbr = ft_len_nbr((long)d, base);

	if (prec > len_nbr)
		field -= prec - len_nbr;
	if (field > len_nbr)
	{
		field -= len_nbr;
		while (field-- > 0)
			ft_putchar(' ');
	}
	if (prec > len_nbr)
	{
		prec -= len_nbr;
		while (prec-- > 0)
			ft_putchar('0');
	}
	ft_putnbr((long)d, base);
	return (0);
}

int	ft_treat_x(unsigned int x)
{
	z++;
	char	*base = "0123456789abcdef";
	int	len_nbr = ft_len_nbr((long)x, base);

	if (prec > len_nbr)
		field -= prec - len_nbr;
	if (field > len_nbr)
	{
		field -= len_nbr;
		while (field-- > 0)
			ft_putchar(' ');
	}
	if (prec > len_nbr)
	{
		prec -= len_nbr;
		while (prec-- > 0)
			ft_putchar('0');
	}
	ft_putnbr((long)x, base);
	return (0);
}

int	ft_treat_s(char *s)
{
	z++;
	char	*s1;
	if (!s)
	{
		s1 = malloc(sizeof(char) * 7);
		if (!s1)
			return (-1);
		s1[0] = '(';
		s1[1] = 'n';
		s1[2] = 'u';
		s1[3] = 'l';
		s1[4] = 'l';
		s1[5] = ')';
		s1[6] = '\0';
		if (field > 0)
		{
			if (prec >= 0 && prec < ft_strlen(s1))
				field += ft_strlen(s1) - prec;
			field -= ft_strlen(s1);
			while (field-- > 0)
				ft_putchar(' ');
		}
		if (prec >= 0 && prec < ft_strlen(s1))
			ft_putstr_n(s1, prec);
		else
			ft_putstr(s1);
	}
	else
	{
		if (field > 0)
		{
			if (prec >= 0 && prec < ft_strlen(s))
				field += ft_strlen(s) - prec;
			field -= ft_strlen(s);
			while (field-- > 0)
				ft_putchar(' ');
		}
		if (prec >= 0 && prec < ft_strlen(s))
			ft_putstr_n(s, prec);
		else
			ft_putstr(s);
	}
	return (0);
}

int	ft_parse(char *s)
{
	z++;
	field = -1;
	prec = -1;

	if (s[z] <= '9' && s[z] >= '0')
		field = ft_atoi(s);
	if (s[z] == '.')
	{
		z++;
		prec = ft_atoi(s);
	}
	if (s[z] == 'd')
	{
		if (ft_treat_d(va_arg(va, int)) == -1)
			return (-1);
		return (0);
	}
	else if (s[z] == 'x')
	{
		if (ft_treat_x(va_arg(va, unsigned int)) == -1)
			return (-1);
		return (0);
	}
	else if (s[z] == 's')
	{
		if (ft_treat_s(va_arg(va, char *)) == -1)
			return (-1);
		return (0);
	}
	return (-1);
}

int	ft_printf(const char *s, ...)
{
	z = 0;
	count = 0;
	va_start(va, s);

	while (s[z])
	{
		if (s[z] != '%')
		{
			ft_putchar(s[z]);
			z++;
		}
		else
		{
			if (ft_parse((char *)s) == -1)
				return (-1);
		}
	}
	return (count);
}
/*
#include <stdio.h>

int	main(void)
{
	printf("salut les %d %s, hexa %x\n", 3, "amis", 15);
	ft_printf("salut les %d %s, hexa %x\n", 3, "amis", 15);
}
*/
