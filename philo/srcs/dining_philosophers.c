/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining_philosophers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 03:51:54 by hlucie            #+#    #+#             */
/*   Updated: 2021/12/29 18:15:40 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

int	can_i_eat(t_philosophers *philosophers)
{
	if (manage_fork(philosophers))
	{
		drop_fork(philosophers);
		return (1);
	}
	if (philosophers->nb_meal != 0)
	{
		if (philosophers->i_have_eat < philosophers->nb_meal)
		{
			pthread_mutex_lock(&(philosophers->i_eaten));
			philosophers->i_have_eat += 1;
			pthread_mutex_unlock(&(philosophers->i_eaten));
		}
	}
	if (print_step(philosophers->id, 'e', philosophers))
	{
		drop_fork(philosophers);
		return (1);
	}
	pthread_mutex_lock(&(philosophers->meal_mutex));
	gettimeofday(&(philosophers->last_meal), NULL);
	pthread_mutex_unlock(&(philosophers->meal_mutex));
	ft_usleep(philosophers->t_time_eat, philosophers);
	drop_fork(philosophers);
	return (0);
}

int	thinking(t_philosophers *philosophers)
{
	if (should_die(philosophers) == 1)
		return (1);
	if (print_step(philosophers->id, 't', philosophers) == 1)
		return (1);
	return (0);
}

int	sleeping(t_philosophers *philosophers)
{
	if (should_die(philosophers) == 1)
		return (1);
	if (print_step(philosophers->id, 's', philosophers) == 1)
		return (1);
	ft_usleep(philosophers->t_time_sleep, philosophers);
	if (thinking(philosophers) == 1)
		return (1);
	if (philosophers->t_nb_philo % 2 != 0)
		ft_usleep(philosophers->t_time_eat * 2 - philosophers->t_time_sleep,
			philosophers);
	return (0);
}

void	manage_team(t_philosophers *philosophers)
{
	if (philosophers->id % 3 == 1)
		usleep(philosophers->t_time_eat);
	if (philosophers->id % 3 == 2)
		usleep(philosophers->t_time_eat * 2);
}

int	eternal_recurrence(void *args)
{
	t_philosophers	*philosophers;

	philosophers = args;
	pthread_mutex_lock(&(philosophers->env->status_update));
	while (philosophers->env->status == 0)
	{
		pthread_mutex_unlock(&(philosophers->env->status_update));
		if (philosophers->t_nb_philo % 2 != 0)
			manage_team(philosophers);
		if (can_i_eat(philosophers))
			return (1);
		pthread_mutex_lock(&(philosophers->env->status_update));
		if (philosophers->env->status == 1)
		{
			pthread_mutex_unlock(&(philosophers->env->status_update));
			return (1);
		}
		pthread_mutex_unlock(&(philosophers->env->status_update));
		if (sleeping(philosophers) == 1)
			return (1);
		pthread_mutex_lock(&(philosophers->env->status_update));
	}
	pthread_mutex_unlock(&(philosophers->env->status_update));
	return (0);
}
