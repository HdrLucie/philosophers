/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 04:00:35 by hlucie            #+#    #+#             */
/*   Updated: 2021/12/29 18:41:41 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

int	join_thread(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->nb_of_philosophers)
	{
		if (pthread_join(env->philosophers[i].thread, NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}

int	click_click(t_env *env, int i)
{
	pthread_mutex_unlock(&(env->philosophers[i].meal_mutex));
	pthread_mutex_lock(&(env->status_update));
	env->status = 1;
	pthread_mutex_unlock(&(env->status_update));
	if (print_dead(env->philosophers[i].id, 'd', env->philosophers) == -1)
		return (-1);
	env->schrodinger = 0;
	return (0);
}

int	check_death(t_env *env)
{
	int				i;
	struct timeval	time;

	i = -1;
	while (env->schrodinger)
	{
		while (++i < env->nb_of_philosophers)
		{
			gettimeofday(&time, NULL);
			usleep(100);
			env->schrodinger = manage_nb_of_meal(env, i);
			pthread_mutex_lock(&(env->philosophers[i].meal_mutex));
			if (ms_watch(time) - ms_watch(env->philosophers[i].last_meal)
				>= env->time_to_die)
			{
				if (click_click(env, i) == -1)
					return (-1);
				break ;
			}
			pthread_mutex_unlock(&(env->philosophers[i].meal_mutex));
		}
		i = -1;
	}
	return (0);
}

int	create_thread(t_env *env)
{
	int				i;
	struct timeval	start_time;

	i = 0;
	if (gettimeofday(&(start_time), NULL) != 0)
		return (-1);
	while (i < env->nb_of_philosophers)
	{
		env->philosophers[i].thread_time = start_time;
		env->philosophers[i].last_meal = start_time;
		if (pthread_create(&(env->philosophers[i].thread), NULL,
				(void *)eternal_recurrence,
				(void *)&(env->philosophers[i])) != 0)
			return (-1);
		i++;
	}
	if (check_death(env) == -1 || join_thread(env) == -1)
		return (-1);
	return (0);
}
