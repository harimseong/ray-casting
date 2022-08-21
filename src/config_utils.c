#include "libft.h"
#include "read_config.h"

void	free_splited_arr(char **splited_words)
{
	int idx;

	idx = 0;
	while (splited_words[idx])
	{
		free(splited_words[idx]);
		idx++;
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

char*	sub_newline(char *read_line)
{
	char	*ret;

	if (!read_line || !ft_strncmp(read_line, "\n", 1))
		return (read_line);
	ret = ft_substr(read_line, 0, ft_strlen(read_line) - 1);
	free(read_line);
	return (ret);
}
