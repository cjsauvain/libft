#include "libft.h"

static void	display_error_shortoption(char *progname, char option)
{
	char	error_str[128];

	sprintf(error_str, "%s: invalid option -- '%c'\n", progname, option);
	write(2, error_str, ft_strlen(error_str));
}

static void	display_error_longoption(char *progname, char *option)
{
	char	error_str[128];

	sprintf(error_str, "%s: invalid option -- '%s'\n", progname, option);
	write(2, error_str, ft_strlen(error_str));
}

static bool	long_option(char *option, char *arg, char **optlong, t_opt *opt_struct)
{
	int	len;

	if (optlong == NULL || *optlong == NULL)
		return false;
	opt_struct->type = LONG;
	opt_struct->opt_str = option;
	for (int i = 0; i < ft_strlen_double(optlong); i++)
	{
		len = ft_strlen(optlong[i]);
		if (optlong[i][len - 1] == ':' && !strncmp(option, optlong[i], len - 1))
		{
			opt_struct->ft_optarg = arg;
			return true;
		}
		else if (!strcmp(option, optlong[i]))
			return true;
	}
	return false;
}

static bool	short_option(char *option, char *arg, char *optshort, t_opt *opt_struct)
{
	if (optshort == NULL || ft_strlen(option) > 1)
		return false;

	opt_struct->type = SHORT;
	opt_struct->opt_char = option[0];
	for (size_t i = 0; i < ft_strlen(optshort); i++)
	{
		if (optshort[i] == ':')
			continue ;
		if (*option == optshort[i] && optshort[i + 1] == ':')
		{
			opt_struct->ft_optarg = arg;
			return true;
		}
		else if (*option == optshort[i])
			return true;
	}
	return false;
}

t_opt	ft_getopt(int argc, char *argv[], char *optshort, char **optlong)
{
	t_opt		opt_struct;
	bool		option_validity;
	static int	i = 1;

	memset(&opt_struct, 0, sizeof(opt_struct));
	while (i < argc)
	{
		if (argv[i][0] == '-' && argv[i][1] == '-')
		{
			option_validity = long_option(&argv[i][2], argv[i + 1], optlong, &opt_struct);
			i++;
			if (opt_struct.ft_optarg)
				i++;
			if (option_validity == true)
				return opt_struct;
			display_error_longoption(argv[0], &argv[i - 1][2]);
			break ;
		}
		else if (argv[i][0] == '-')
		{
			option_validity = short_option(&argv[i][1], argv[i + 1], optshort, &opt_struct);
			i++;
			if (opt_struct.ft_optarg)
				i++;
			if (option_validity == true)
				return opt_struct;
			display_error_shortoption(argv[0], argv[i - 1][1]);
			break ;
		}
		i++;
	}
	opt_struct.type = NONE;
	opt_struct.ft_optarg = NULL;
	return opt_struct;
}
