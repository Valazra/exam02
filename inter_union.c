#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	ft_isin(char c, char *str)
{
	int	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_prec(char c, char *str, int i)
{
	int	j = 0;
	while (j < i)
	{
		if (str[j] == c)
			return (1);
		j++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	int	i = 0;
	char	*s1 = av[1];
	char	*s2 = av[2];

	if (ac == 3)
	{
		while (s1[i])
		{
			if (ft_isin(s1[i], s2) && !ft_prec(s1[i], s1, i))
				ft_putchar(s1[i]);
			i++;
		}
	}
	ft_putchar('\n');
	return (0);
}

int	main(int ac, char **av)
{
	int	i = 0;
	int	j = 0;
	char	*s1 = av[1];
	char	*s2 = av[2];

	if (ac == 3)
	{
		while (s1[i])
		{
			if (!ft_prec(s1[i], s1, i))
				ft_putchar(s1[i]);
			i++;
		}
		while (s2[j])
		{
			if (!ft_prec(s2[j], s2, j) && !ft_isin(s2[j], s1))
				ft_putchar(s2[j]);
			j++;
		}
	}
	ft_putchar('\n');
	return (0);
}
