/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:21:36 by hlucie            #+#    #+#             */
/*   Updated: 2021/12/26 18:34:16 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

long	ms_watch(struct timeval time)
{
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(long duration, t_philosophers *philosophers)
{
	struct timeval	current_time;
	long			is_over;
	long			begin;

	if (gettimeofday(&current_time, NULL) != 0)
		return (-1);
	begin = ms_watch(current_time);
	is_over = begin + duration;
	pthread_mutex_lock(&(philosophers->env->status_update));
	while (philosophers->env->status == 0 && begin < is_over
		&& philosophers->env->status == 0)
	{
		pthread_mutex_unlock(&(philosophers->env->status_update));
		if (gettimeofday(&current_time, NULL) != 0)
			return (-1);
		begin = ms_watch(current_time);
		usleep(300);
		pthread_mutex_lock(&(philosophers->env->status_update));
	}
	pthread_mutex_unlock(&(philosophers->env->status_update));
	return (0);
}
