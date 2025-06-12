#include "philos.h"

static void	ph_think(t_philo *philo);
static void	ph_take_forks_and_eat(t_philo *philo);
//static void	ph_release_forks(t_philo *philo);
static void	ph_sleep(t_philo *philo);


void	ph_print(char *print, t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->print_lock);
	if (!data->dead && data->sated < data->ph_count)
		printf("%ld %zu %s\n", ph_time_to_ms() - data->start_ms, philo->index, print);
	pthread_mutex_unlock(&data->print_lock);
}

void	run_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (philo->data->start_ms > ph_time_to_ms())
		usleep(500);
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal = philo->data->start_ms;
	pthread_mutex_unlock(&philo->data->meal_lock);
	ph_think(philo);
	if (philo->index % 2 != 0)
		usleep((philo->data->eat_ms / 2) * 1000);
	while (1)
	{
		if (philo->data->dead)
			return ;
		ph_take_forks_and_eat(philo);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		//ph_release_forks(philo);
		//printf("ID: %zu, Eaten: %zu, Must eat: %zu\n", philo->index, philo->meals_eaten, philo->data->must_eat);
		//if (philo->meals_eaten == philo->data->must_eat)
		//	break ;
		ph_sleep(philo);
		ph_think(philo);
		philo->meals_eaten++;
	}
}

static void	ph_think(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	ph_print(THINKING, philo, data);
}

static void	ph_take_forks_and_eat(t_philo *philo)
{
	t_data *data;

	data = philo->data;
	if (data->ph_count % 2 != 0)// && philo->index == data->ph_count)
	{
		pthread_mutex_lock(philo->r_fork);
		ph_print(FORKING, philo, data);
		pthread_mutex_lock(philo->l_fork);
		ph_print(FORKING, philo, data);
		ph_print(EATING, philo, data);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		ph_print(FORKING, philo, data);
		pthread_mutex_lock(philo->r_fork);
		ph_print(FORKING, philo, data);
		ph_print(EATING, philo, data);
	}
	philo->last_meal = ph_time_to_ms();
	usleep(data->eat_ms * 1000);
}

//static void	ph_release_forks(t_philo *philo)
//{
//	pthread_mutex_unlock(philo->r_fork);
//	pthread_mutex_unlock(philo->l_fork);
//}

static void	ph_sleep(t_philo *philo)
{
	t_data *data;

	data = philo->data;
	ph_print(SLEEPING, philo, data);
	usleep(data->sleep_ms * 1000);
}
