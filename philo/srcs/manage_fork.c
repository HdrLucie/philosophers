/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 14:23:03 by hlucie            #+#    #+#             */
/*   Updated: 2021/12/29 18:19:28 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

void	drop_fork(t_philosophers *philosophers)
{
	if (philosophers->id % 2 == 0)
	{
		if (philosophers->flag_fork == 1)
			pthread_mutex_unlock(philosophers->right_fork);
		if (philosophers->flag_fork == 2)
		{
			pthread_mutex_unlock(philosophers->right_fork);
			pthread_mutex_unlock(philosophers->left_fork);
		}
	}
	else
	{
		if (philosophers->flag_fork == 1)
			pthread_mutex_unlock(philosophers->left_fork);
		if (philosophers->flag_fork == 2)
		{
			pthread_mutex_unlock(philosophers->left_fork);
			pthread_mutex_unlock(philosophers->right_fork);
		}
	}
	philosophers->flag_fork = 0;
}

int	manage_even_fork(t_philosophers *philosophers)
{
	if (should_die(philosophers) == 1)
		return (1);
	pthread_mutex_lock(philosophers->right_fork);
	philosophers->flag_fork = 1;
	if (print_step(philosophers->id, 'f', philosophers))
		return (1);
	pthread_mutex_lock(philosophers->left_fork);
	philosophers->flag_fork = 2;
	if (print_step(philosophers->id, 'f', philosophers))
		return (1);
	return (0);
}

int	manage_uneven_fork(t_philosophers *philosophers)
{
	if (should_die(philosophers) == 1)
		return (1);
	pthread_mutex_lock(philosophers->left_fork);
	philosophers->flag_fork = 1;
	if (print_step(philosophers->id, 'f', philosophers))
		return (1);
	if (philosophers->t_nb_philo == 1)
		return (1);
	pthread_mutex_lock(philosophers->right_fork);
	philosophers->flag_fork = 2;
	if (print_step(philosophers->id, 'f', philosophers))
		return (1);
	return (0);
}

int	manage_fork(t_philosophers *philosophers)
{
	if (philosophers->id % 2 == 0)
	{
		if (manage_even_fork(philosophers) != 0)
			return (1);
	}
	else
	{
		if (manage_uneven_fork(philosophers) != 0)
			return (1);
	}
	return (0);
}
