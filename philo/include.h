/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlucie <hlucie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:15:45 by hlucie            #+#    #+#             */
/*   Updated: 2022/01/03 15:31:37 by hlucie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_H
# define INCLUDE_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <time.h>
# include <sys/time.h>
# include <pthread.h>

# define INT_MIN -2147483648
# define INT_MAX 2147483647

/***************************/
/*         STRUCTURES      */
/***************************/

typedef struct s_env	t_env;

typedef struct s_philosophers
{
	int				id;
	int				nb_meal;
	int				flag_fork;
	int				i_have_eat;
	long			t_time_eat;
	long			t_nb_philo;
	long			t_time_sleep;
	t_env			*env;
	pthread_t		thread;
	struct timeval	last_meal;
	struct timeval	thread_time;
	pthread_mutex_t	nb_eat;
	pthread_mutex_t	i_eaten;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_philosophers;

typedef struct s_env
{
	int				status;
	int				nb_of_meal;
	int				schrodinger;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nb_of_philosophers;
	struct timeval	current_time;
	pthread_mutex_t	write;
	pthread_mutex_t	*fork;
	pthread_mutex_t	time_mutex;
	pthread_mutex_t	status_update;
	t_philosophers	*philosophers;
}					t_env;

/***************************/
/*         UTILS           */
/***************************/

int		ft_atoi(char *str);
size_t	ft_strlen(char *str);
int		counter_nb(long nb);
char	*search_step(char c);
int		ft_exit(t_env *env, int flag);
long	ms_watch(struct timeval time);
int		ft_usleep(long duration, t_philosophers *philosophers);
int		print_step(int name, char action, t_philosophers *philo);
int		print_dead(int name, char action, t_philosophers *philo);
char	*ft_strcat(char *str, char *action, char *id, char *time);

/***************************/
/*         INIT            */
/***************************/

int		init(t_env *env);
int		set_env(t_env **env);

/***************************/
/*         PROCESS         */
/***************************/

int		nb_meal(t_env *env);
int		meal_mutex(t_env *env);
int		check_death(t_env *env);
int		create_thread(t_env *env);
int		eternal_recurrence(void *args);
int		manage_nb_of_meal(t_env *env, int i);
int		should_die(t_philosophers *philosophers);
void	drop_fork(t_philosophers *philosophers);
int		manage_fork(t_philosophers *philosophers);

#endif