int	ft_size_nb(int nb)
{
	int	size;

	size = 1;
	while (nb >= 10)
	{
		nb /= 10;
		size++;
	}
	return (size);
}
