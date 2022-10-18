#include "libft/libft.h"

int main(void)
{
	ft_putendl_fd("env", 1);
	sleep (1);
	ft_putendl_fd("export", 1);
	sleep (1);
	ft_putendl_fd("$HOME", 1);
	sleep (1);
	ft_putendl_fd(" a$USERv", 1);
	sleep (1);
	ft_putendl_fd("a$USER$$", 1);
	sleep (1);
}