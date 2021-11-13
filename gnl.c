#include <unistd.h>
#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_is_new_line(char *str)
{
	int	i = 0;

	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int	i = 0;
	int	j = 0;
	char	*new_s = NULL;

	new_s = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new_s)
		return (NULL);
	while (s1[i])	
	{
		new_s[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		new_s[i] = s2[j];
		i++;
		j++;
	}
	new_s[i] = '\0';
	free(s1);
	return (new_s);
}

void	cut_buf(char *buf)
{
	int	i = 0;
	int	j = 0;

	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i])
		i++;
	while (buf[i])
	{
		buf[j] = buf[i];
		i++;
		j++;
	}
	buf[j] = '\0';
}

char	*cut_line(char *actual_line)
{
	int	i = 0;
	int	j = 0;
	char	*new_s = NULL;

	while (actual_line[i] && actual_line[i] != '\n')
		i++;
	if (actual_line[i])
		i++;
	new_s = malloc(sizeof(char) * (i + 1));
	if (!new_s)
	{
		free(actual_line);
		return (NULL);
	}
	while (j < i)
	{
		new_s[j] = actual_line[j];
		j++;
	}
	new_s[j] = '\0';
	free(actual_line);
	return (new_s);
}

char	*get_next_line(int fd)
{
	int		i = 0;
	static char	*buf = NULL;
	char		*actual_line;
	int		ret = 1;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	actual_line = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!actual_line)
		return (NULL);
	if (!buf)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf)
			return (NULL);
	}
	while (buf[i])
	{
		actual_line[i] = buf[i];
		i++;
	}
	actual_line[i] = '\0';
	while (!ft_is_new_line(actual_line) && ret > 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret < 0)
		{
			if (actual_line)
			{
				free(actual_line);
				free(buf);
				actual_line = NULL;
			}
			return (NULL);
		}
		buf[ret] = '\0';
		actual_line = ft_strjoin(actual_line, buf);
		if (!actual_line)
		{
			free(buf);
			return (NULL);
		}
	}
	if (actual_line[0] == '\0' && ret == 0)
	{
		free(buf);
		free(actual_line);
		return (NULL);
	}
	cut_buf(buf);
	actual_line = cut_line(actual_line);
	if (!actual_line)
	{
		free(buf);
		return (NULL);
	}
	return (actual_line);
}
