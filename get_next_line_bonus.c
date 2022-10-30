/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obektas <obektas@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 16:53:54 by obektas           #+#    #+#             */
/*   Updated: 2022/10/30 17:16:50 by obektas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*parse(char *s, char c)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i] && s[i] != c)
		i++;
	if (!s[i])
	{
		free(s);
		return (NULL);
	}
	str = (char *)malloc(1 * (ft_strlen(s) - i) + 1);
	if (!str)
		return (NULL);
	i++;
	while (s[i])
		str[j++] = s[i++];
	str[j] = '\0';
	free(s);
	return (str);
}

static char	*new_line(char *s, char c)
{
	char	*str;
	int		i;

	i = 0;
	if (!s[i])
		return (NULL);
	while (s[i] != '\0' && s[i] != c)
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		str[i] = s[i];
		i++;
	}
	if (s[i] == c)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*next_line(int fd, char *line)
{
	char	*str;
	int		i;

	str = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!str)
		return (NULL);
	i = 1;
	while (!ft_strchr(line, '\n') && i != 0)
	{
		i = read(fd, str, BUFFER_SIZE);
		if (i == -1)
		{
			free(str);
			return (NULL);
		}
		str[i] = '\0';
		line = ft_strjoin(line, str);
	}
	free(str);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*str;
	static char	*line[4096];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line[fd] = next_line(fd, line[fd]);
	if (line[fd])
	{
		str = new_line(line[fd], '\n');
		line[fd] = parse(line[fd], '\n');
		return (str);
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <fcntl.h>
int main()
{
	int k = open(".o",O_RDONLY);
	int j = open(".o_2",O_RDONLY);
	int i = 0;
	while (i < 1)
	{
		printf("%s", get_next_line(k));
		printf("%s", get_next_line(j));	
		i++;
	}
	close(k);
	close(j);
}*/