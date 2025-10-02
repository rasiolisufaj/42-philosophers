/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raisufaj <raisufaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 21:35:16 by raisufaj          #+#    #+#             */
/*   Updated: 2025/10/02 15:39:23 by raisufaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define PHILO_MAX 200

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}					t_program;

// init.c
int					check_valid_args(char **argv);
void				init_input(t_philo *philos, char **argv);
void				init_philos(t_philo *philos, t_program *program,
						pthread_mutex_t *forks, char **argv);
void				init_forks(t_program *program, pthread_mutex_t *forks);
void				init_program(t_program *program, t_philo *philos);

// threads.c
int					dead_loop(t_philo *philo);
void				*philo_routine(void *pointer);
int					thread_create(t_program *program);

// monitor.c
void				print_message(char *str, t_philo *philo, int id);
int					philosopher_dead(t_philo *philo, size_t time_to_die);
int					check_if_dead(t_philo *philos);
int					check_meals(t_philo *philos);
void				*monitor(void *arg);

// actions.c
void				think(t_philo *philo);
void				sleeping(t_philo *philo);
void				eat(t_philo *philo);

// utils.c
int					is_number(char *str);
int					ft_atoi(char *str);
void				destroy_all(t_program *program, pthread_mutex_t *forks,
						char *message);
size_t				get_current_time(void);
int					ft_usleep(size_t time_in_ms);

#endif