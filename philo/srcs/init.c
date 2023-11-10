/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 22:00:42 by hlucie            #+#    #+#             */
/*   Updated: 2021/12/29 16:02:46 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

int	set_env(t_env **env)
{
	*env = malloc(sizeof(t_env));
	if (!env)
		return (-1);
	(*env)->status = 0;
	(*env)->fork = NULL;
	(*env)->nb_of_meal = 0;
	(*env)->schrodinger = 1;
	(*env)->time_to_die = 0;
	(*env)->time_to_eat = 0;
	(*env)->time_to_sleep = 0;
	(*env)->nb_of_philosophers = 0;
	(*env)->current_time.tv_sec = 0;
	(*env)->current_time.tv_usec = 0;
	return (0);
}

void	init_philo_two(t_env *env, int i, int j)
{
	env->philosophers[i].id = j;
	env->philosophers[i].env = env;
	env->philosophers[i].flag_fork = 0;
	env->philosophers[i].i_have_eat = 0;
	env->philosophers[i].last_meal.tv_sec = 0;
	env->philosophers[i].last_meal.tv_usec = 0;
	env->philosophers[i].thread_time.tv_sec = 0;
	env->philosophers[i].thread_time.tv_usec = 0;
	env->philosophers[i].nb_meal = env->nb_of_meal;
	env->philosophers[i].t_time_eat = env->time_to_eat;
	env->philosophers[i].t_time_sleep = env->time_to_sleep;
	env->philosophers[i].t_nb_philo = env->nb_of_philosophers;
}

int	init_philosophers(t_env *env)
{
	int	i;
	int	j;

	i = -1;
	j = 1;
	env->philosophers = malloc(sizeof(t_philosophers)
			* env->nb_of_philosophers);
	if (!env->philosophers)
		return (-1);
	while (++i < env->nb_of_philosophers)
	{
		init_philo_two(env, i, j);
		env->philosophers[i].right_fork = &(env->fork[i]);
		if (i + 1 < env->nb_of_philosophers)
			env->philosophers[i].left_fork = &(env->fork[i + 1]);
		else
			env->philosophers[i].left_fork = &(env->fork[0]);
		if (pthread_mutex_init(&(env->philosophers[i].nb_eat), NULL) != 0
			|| pthread_mutex_init(&(env->philosophers[i].meal_mutex), NULL) != 0
			|| pthread_mutex_init(&(env->philosophers[i].i_eaten), NULL) != 0)
			return (-1);
		j++;
	}
	return (0);
}

int	init_fork(t_env *env)
{
	int	i;

	i = 0;
	env->fork = malloc(sizeof(pthread_mutex_t) * env->nb_of_philosophers);
	if (!env->fork || pthread_mutex_init(&(env->time_mutex), NULL) != 0
		|| pthread_mutex_init(&(env->status_update), NULL) != 0
		|| pthread_mutex_init(&(env->write), NULL) != 0)
		return (-1);
	while (i < env->nb_of_philosophers)
	{
		if (pthread_mutex_init(&(env->fork[i]), NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}

int	init(t_env *env)
{
	if (init_fork(env) != 0 || init_philosophers(env) != 0)
	{
		write(2, "ALLOCATION FAILED\n", 18);
		ft_exit(env, 1);
		return (-1);
	}
	return (0);
}
