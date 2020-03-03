//
// Created by Grass Emerald on 03/03/2020.
//

#include "asm.h"

void    print_alone_byte(t_dsm *src_code)
{
	char *itoa;

	itoa = ft_itoa_base((unsigned char)src_code->input[src_code->current_position], 16);
	if (itoa[0] == '0')
		ft_printf("00 ");
	else
	{
		if (ft_strlen(itoa) == 1)
			ft_putchar('0');
		ft_printf("%s ", itoa);
	}
	free(itoa);
}

void  print_binary_stdout(t_dsm *src_code)
{
	char *itoa;
	int i;

	i = -1;
	while (++i < src_code->file_len)
	{
		itoa = ft_itoa_base((unsigned char)src_code->input[i], 16);
		if (itoa[0] == '0')
			ft_printf("00 ");
		else
		{
			if (ft_strlen(itoa) == 1)
				ft_putchar('0');
			ft_printf("%s ", itoa);
		}
		free(itoa);
		if ((i % 64) == 63)
			ft_putchar('\n');
	}
}