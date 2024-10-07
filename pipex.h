#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>

# ifndef ARG_MAX
#   define ARG_MAX 1048576
# endif
typedef struct s_command
{
  char  *command;
  char  *cmd_args[ARG_MAX];
} t_command;

int is_cmd(char *str);
int parse_commands(t_command ***commands_arr, char **argv, int arg_len);

#endif
