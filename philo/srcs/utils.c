/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:07:57 by hlucie            #+#    #+#             */
/*   Updated: 2021/12/29 18:21:12 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

char	*ft_strcat(char *str, char *action, char *id, char *time)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (time && time[j])
		str[i++] = time[j++];
	str[i] = ' ';
	str[i + 1] = 'm';
	str[i + 2] = 's';
	str[i + 3] = ' ';
	i += 4;
	j = 0;
	while (id && id[j])
		str[i++] = id[j++];
	j = 0;
	while (action && action[j])
		str[i++] = action[j++];
	str[i] = '\0';
	return (str);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*search_step(char c)
{
	if (c == 'f')
		return (" has taken a fork\n");
	else if (c == 'e')
		return (" is eating\n");
	else if (c == 's')
		return (" is sleeping\n");
	else if (c == 't')
		return (" is thinking\n");
	else if (c == 'd')
		return (" died\n");
	return (NULL);
}

int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		i++;
	}
	return (0);
}

int	ft_atoi(char *str)
{
	int				i;
	long long int	res;

	res = 0;
	i = is_digit(str);
	if (i == -1 || str[i] == '\0')
		return (-1);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if (res < INT_MIN || res > INT_MAX)
			return (-1);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res);
}
