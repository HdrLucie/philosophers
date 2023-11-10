/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nb_meal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 16:00:08 by hlucie            #+#    #+#             */
/*   Updated: 2021/12/29 18:44:35 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

int	counter_nb(long nb)
{
	int	i;

	i = 0;
	if (nb < 0)
		nb *= -1;
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i + 1);
}

int	nb_meal(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->nb_of_philosophers)
	{
		pthread_mutex_lock(&(env->philosophers[i].i_eaten));
		if (env->philosophers[i].i_have_eat != env->nb_of_meal)
		{
			pthread_mutex_unlock(&(env->philosophers[i].i_eaten));
			return (0);
		}
		pthread_mutex_unlock(&(env->philosophers[i].i_eaten));
		i++;
	}
	return (1);
}

int	manage_nb_of_meal(t_env *env, int i)
{
	if (env->nb_of_meal != 0)
	{
		pthread_mutex_lock(&(env->philosophers[i].nb_eat));
		if (nb_meal(env) == 1)
		{
			pthread_mutex_lock(&(env->status_update));
			env->status = 1;
			pthread_mutex_unlock(&(env->status_update));
			pthread_mutex_unlock(&(env->philosophers[i].nb_eat));
			return (0);
		}
		pthread_mutex_unlock(&(env->philosophers[i].nb_eat));
	}
	return (1);
}
