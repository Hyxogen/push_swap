int	ft_isspace(int c);
int	ft_isdigit(int c);

int
	ft_atoi(const char *str)
{
	int	ret;
	int	sign;

	ret = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		ret = ret * 10 + (*str - '0');
		str++;
	}
	return (ret * sign);
}
