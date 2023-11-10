/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 02:03:00 by hlucie            #+#    #+#             */
/*   Updated: 2021/12/29 18:44:25 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

static char	*ft_strrev(char *str)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	j = ft_strlen(str);
	j--;
	while (j > i)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		i++;
		j--;
	}
	return (str);
}

char	*int_to_char(long nb, char *str)
{
	int	i;

	i = 0;
	if (nb < 0)
	{
		str[i] = '0';
		str[i + 1] = '\0';
		return (ft_strrev(str));
	}
	if (nb == 0)
	{
		str[i] = nb + '0';
		str[i + 1] = '\0';
		return (ft_strrev(str));
	}
	while (nb > 0)
	{
		str[i] = (nb % 10) + '0';
		nb = nb / 10;
		i++;
	}
	str[i] = '\0';
	return (ft_strrev(str));
}

int	print(int name, char action, t_philosophers *philo, char *id)
{
	struct timeval	current_time;
	char			*str;
	char			time_ms[255];
	long			time;

	str = NULL;
	time = 0;
	gettimeofday(&current_time, NULL);
	time = ms_watch(current_time) - ms_watch(philo->thread_time);
	str = malloc(sizeof(char) * (ft_strlen(search_step(action))
				+ counter_nb(name) + counter_nb(time) + 5));
	if (!str)
		return (-1);
	int_to_char(time, time_ms);
	str = ft_strcat(str, search_step(action), id, time_ms);
	write(1, str, ft_strlen(str));
	pthread_mutex_unlock(&(philo->env->write));
	free(str);
	return (0);
}

int	print_dead(int name, char action, t_philosophers *philo)
{
	long			time;
	char			*str;
	char			id[255];
	char			time_ms[255];
	struct timeval	current_time;

	time = 0;
	str = NULL;
	int_to_char(name, id);
	pthread_mutex_lock(&(philo->env->write));
	gettimeofday(&current_time, NULL);
	time = ms_watch(current_time) - ms_watch(philo->thread_time);
	str = malloc(sizeof(char) * (ft_strlen(search_step(action))
				+ counter_nb(name) + counter_nb(time) + 5));
	if (!str)
		return (-1);
	int_to_char(time, time_ms);
	str = ft_strcat(str, search_step(action), id, time_ms);
	write(1, str, ft_strlen(str));
	pthread_mutex_unlock(&(philo->env->write));
	free(str);
	return (0);
}

int	print_step(int name, char action, t_philosophers *philo)
{
	char			id[255];

	int_to_char(name, id);
	if (should_die(philo) == 1)
		return (1);
	pthread_mutex_lock(&(philo->env->write));
	if (should_die(philo) == 1)
	{
		pthread_mutex_unlock(&(philo->env->write));
		return (1);
	}
	else if (print(name, action, philo, id) == -1)
		return (-1);
	return (0);
}
