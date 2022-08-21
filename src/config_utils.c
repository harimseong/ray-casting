#include "read_config.h"

void	free_splited_arr(char **splited_words)
{
	while (*splited_words)
	{
		free(*splited_words);
		splited_words++;
	}
	free(splited_words);
}

int	count_splited_words(char **splited_words)
{
	int cnt;

	cnt = 0;
	while (splited_words[cnt])
		cnt++;
	return (cnt);
}
