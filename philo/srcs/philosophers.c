/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 22:00:46 by hlucie            #+#    #+#             */
/*   Updated: 2021/12/26 22:51:50 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.h"

int	parse_arg(char **argv, t_env **env)
{
	if (set_env(env) == -1)
		return (-1);
	(*env)->nb_of_philosophers = ft_atoi(argv[1]);
	(*env)->time_to_die = ft_atoi(argv[2]);
	(*env)->time_to_eat = ft_atoi(argv[3]);
	(*env)->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		(*env)->nb_of_meal = ft_atoi(argv[5]);
	if ((*env)->nb_of_philosophers <= 0 || (*env)->nb_of_philosophers > 500
		|| (*env)->time_to_die <= 0 || (*env)->time_to_eat <= 0
		|| (*env)->time_to_sleep <= 0
		|| ((*env)->nb_of_meal && (*env)->nb_of_meal <= 0))
		return (-1);
	if (init(*env) == -1)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_env	*env;

	env = NULL;
	if (argc < 5 || argc > 6)
	{
		write(2, "Error\nWrong number of args\n", 27);
		return (-1);
	}
	if (argc == 5 || argc == 6)
	{
		if (parse_arg(argv, &env) == -1)
		{
			ft_exit(env, 0);
			write(2, "Error\nWrong args\n", 17);
			return (-1);
		}
		else if (create_thread(env) == -1)
		{
			ft_exit(env, 1);
			return (-1);
		}
	}
	ft_exit(env, 1);
	return (0);
}
