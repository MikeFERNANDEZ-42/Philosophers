#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
    int         id;
    int         eat;
    long int    t_start;
    long int    last_eat;

}              t_philo;

typedef struct s_global
{
    int         nb_philos;
    int         threads;
    int         die;
    long int    time_to_die;
    long int    time_to_eat;
    long int    time_to_sleep;
    int                 maxeats;
    pthread_mutex_t     talk;
    pthread_mutex_t     *keys;
    t_philo             *philos;
}             t_global;

long int    get_time(long int type);
void        ft_putnbr(int n);
void        ft_putstr(char *str, int fd);
void        ft_putchar(char caract, int fd);
int         ft_check(char **str);
int         ft_isnum(char *str);
long long   ft_atoi(const char *str);
void        ft_start(void *global);
void        osleep(long int time);
void	ft_messages2(int id, long int timestamp, t_global *global, char *message);
void	ft_sleep(long int	time);

#endif