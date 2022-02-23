/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbjaghou <mbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:21:22 by mbjaghou          #+#    #+#             */
/*   Updated: 2022/02/23 15:21:57 by mbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

char *ft_strdup(char *s)
{
    int i = 0;
    while (s[i])
        i++;
    char *t = malloc(i + 1);
    i = 0;
    while (s[i])
    {
        t[i] = s[i];
        i++;
    }
    t[i] = 0;
    return (t);
}

char *get_next_line(int fd)
{
    if (fd < 0)
        return (NULL);
    char buff[1];
    char line[1000000];
    line[0] = 0;
    int i = 0;
    int n;
    while ((n = read(fd, buff, 1)) && (n > 0))
    {
        line[i++] = buff[0];
        line[i] = '\0';
        if (buff[0] == '\n')
            return (ft_strdup(line));
    }
    if (!line[0])
        return (NULL);
    return (ft_strdup(line));
}

int main(int ac, char **av)
{
    char *str;
    ac = 0;
    int fd = open(av[1], O_RDONLY);
    while((str = get_next_line(fd)))
        printf("%s", str);
    
}
