/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 06:06:58 by hlucie            #+#    #+#             */
/*   Updated: 2021/12/29 16:31:32 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

int	should_die(t_philosophers *philosophers)
{
	pthread_mutex_lock(&(philosophers->env->status_update));
	if (philosophers->env->status == 1)
	{
		pthread_mutex_unlock(&(philosophers->env->status_update));
		return (1);
	}
	pthread_mutex_unlock(&(philosophers->env->status_update));
	return (0);
}

int	ft_exit(t_env *env, int flag)
{
	int	i;

	i = 0;
	if (flag == 1)
	{
		while (i < env->nb_of_philosophers)
		{
			pthread_mutex_destroy(&(env->fork[i]));
			pthread_mutex_destroy(&(env->philosophers[i].nb_eat));
			pthread_mutex_destroy(&(env->philosophers[i].meal_mutex));
			i++;
		}
		pthread_mutex_destroy(&(env->write));
		pthread_mutex_destroy(&(env->time_mutex));
		pthread_mutex_destroy(&(env->status_update));
		if (env->fork)
			free(env->fork);
		if (env->philosophers)
			free(env->philosophers);
	}
	if (env)
		free(env);
	return (0);
}
