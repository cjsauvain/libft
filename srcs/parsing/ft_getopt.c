#define _POSIX_C_SOURCE 200809L  // pour POSIX.1-2008 (C23 est compatible POSIX)

#include "libft.h"

static bool	long_option(char **argv, char **optlong, t_opt *opt_struct, int *index)
{
	int	len;

	if (optlong == NULL || *optlong == NULL)
		return false;
	opt_struct->type = LONG;
	opt_struct->opt_str = &argv[*index][2];
	for (int i = 0; i < ft_strlen_double(optlong); i++)
	{
		len = ft_strlen(optlong[i]);
		if (optlong[i][len - 1] == ':' && !strncmp(&argv[*index][2], optlong[i], len - 1))
		{
			if (!argv[*index + 1])
			{
				dprintf(2, "%s: option requires an argument -- '%s'\n", argv[0], &argv[*index][2]);
				exit(1);
			}
			opt_struct->ft_optarg = argv[*index + 1];
			*index += 1;
			return true;
		}
		else if (!strcmp(&argv[*index][2], optlong[i]))
			return true;
	}
	return false;
}

static bool	short_option(char **argv, char *optshort, t_opt *opt_struct, int *index)
{
	if (optshort == NULL || ft_strlen(&argv[*index][1]) > 1)
		return false;

	opt_struct->type = SHORT;
	opt_struct->opt_char = argv[*index][1];
	for (size_t i = 0; i < ft_strlen(optshort); i++)
	{
		if (optshort[i] == ':')
			continue ;
		if (argv[*index][1] == optshort[i] && optshort[i + 1] == ':')
		{
			if (!argv[*index + 1])
			{
				dprintf(2, "%s: option requires an argument -- '%c'\n", argv[0], argv[*index][1]);
				exit(1);
			}
			opt_struct->ft_optarg = argv[*index + 1];
			*index += 1;
			return true;
		}
		else if (argv[*index][1] == optshort[i])
			return true;
	}
	return false;
}

t_opt	ft_getopt(int argc, char *argv[], char *optshort, char **optlong)
{
	t_opt		opt_struct;
	bool		option_validity;
	static int	i = 1;

	ft_memset(&opt_struct, 0, sizeof(opt_struct));
	while (i < argc)
	{
		if (argv[i][0] == '-' && argv[i][1] == '-')
		{
			option_validity = long_option(argv, optlong, &opt_struct, &i);
			i++;
			if (option_validity == true)
				return opt_struct;
			dprintf(2, "%s: invalid option -- '%s'\n", argv[0], &argv[i - 1][2]);
			exit(1);
		}
		else if (argv[i][0] == '-')
		{
			option_validity = short_option(argv, optshort, &opt_struct, &i);
			i++;
			if (option_validity == true)
				return opt_struct;
			dprintf(2, "%s: invalid option -- '%c'\n", argv[0], argv[i - 1][1]);
			exit(1);
		}
		i++;
	}
	opt_struct.type = NONE;
	opt_struct.ft_optarg = NULL;
	return opt_struct;
}
