#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# define DEC	"0123456789"
# define X_S	"0123456789abcdef"
# define X_C	"0123456789ABCDEF"

int	ft_putchar(char ch);
int	ft_putstr(char *str);
int	write_output(char *base_set, int base, long long int arg, char type);
int	sort_output(va_list arg_ptr, char id);
int	ft_printf(const char *input_str, ...);

#endif
