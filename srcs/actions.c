/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raisufaj <raisufaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 21:35:16 by raisufaj          #+#    #+#             */
/*   Updated: 2025/10/09 13:29:57 by raisufaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// With an odd count, wait until our turn comes back around (cycle = 3 meals)
// so a freshly fed philosopher can't steal forks from a hungrier neighbour.
void	think(t_philo *philo)
{
	long	t;

	print_message("is thinking", philo, philo->id);
	if (philo->num_of_philos % 2 == 0)
		return ;
	t = (long)philo->time_to_eat * 2 - (long)philo->time_to_sleep;
	if (t > 0)
		ft_usleep(t);
}

void	sleeping(t_philo *philo)
{
	print_message("is sleeping", philo, philo->id);
	ft_usleep(philo->time_to_sleep);
}

// A lone philosopher holds its only fork until the monitor declares it dead.
void	eat_alone(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_message("has taken a fork", philo, philo->id);
	while (!dead_loop(philo))
		usleep(500);
	pthread_mutex_unlock(philo->l_fork);
}

// Forks are always locked lowest-address first (resource hierarchy),
// so a circular wait (and therefore a deadlock) is impossible.
void	eat(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	first = philo->l_fork;
	second = philo->r_fork;
	if (first > second)
	{
		first = philo->r_fork;
		second = philo->l_fork;
	}
	pthread_mutex_lock(first);
	print_message("has taken a fork", philo, philo->id);
	pthread_mutex_lock(second);
	print_message("has taken a fork", philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	print_message("is eating", philo, philo->id);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
}
