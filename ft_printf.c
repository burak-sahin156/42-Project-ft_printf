#include "ft_printf.h"

int	ft_putchar(char ch)
{
	return (write(1, &ch, 1));
}

int	ft_putstr(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (ft_putstr("(null)"));
	while (*str)
	{
		len += write(1, str, 1);
		str++;
	}
	return (len);
}

int	write_output(char *base_set, int base, long long arg, char id)
{
	int	len;

	len = 0;
	if (arg < 0 && (id == 'd' || id == 'i'
			|| id == 'x' || id == 'X' || id == 'u'))
	{
		len += ft_putchar('-');
		if (arg <= (-1 * base))
			len += write_output(base_set, base, (arg / base) * -1, id);
		len += ft_putchar((base_set[-1 * (arg % base)]));
	}
	else if (id == 'p')
	{
		if ((unsigned long)arg >= (unsigned)base)
			len += write_output(base_set, base, (unsigned long)arg / base, id);
		len += ft_putchar(base_set[(unsigned long)arg % base]);
	}
	else
	{
		if (arg >= base)
			len += write_output(base_set, base, arg / base, id);
		len += ft_putchar((base_set[arg % base]));
	}
	return (len);
}

int	sort_output(va_list arg_ptr, char id)
{
	int	len;

	len = 0;
	if (id == '%')
		len += write(1, "%", 1);
	else if (id == 'c')
		len += ft_putchar((char)va_arg(arg_ptr, int));
	else if (id == 's')
		len += ft_putstr(va_arg(arg_ptr, char *));
	else if (id == 'd' || id == 'i')
		len += write_output(DEC, 10, va_arg(arg_ptr, int), id);
	else if (id == 'u')
		len += write_output(DEC, 10, va_arg(arg_ptr, unsigned), id);
	else if (id == 'p')
	{
		len += write(1, "0x", 2);
		len += write_output(X_S, 16, va_arg(arg_ptr, unsigned long), id);
	}
	else if (id == 'x')
		len += write_output(X_S, 16, va_arg(arg_ptr, unsigned), id);
	else if (id == 'X')
		len += write_output(X_C, 16, va_arg(arg_ptr, unsigned), id);
	return (len);
}

int	ft_printf(const char *input_str, ...)
{
	int		len;
	va_list	arg_ptr;

	len = 0;
	va_start(arg_ptr, input_str);
	while (*input_str)
	{
		if (*input_str == '%')
			len += sort_output(arg_ptr, *(++input_str));
		else
			len += write(1, input_str, 1);
		input_str++;
	}
	va_end(arg_ptr);
	return (len);
}
