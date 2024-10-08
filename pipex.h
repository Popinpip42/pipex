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
int execute_commands(t_command **commands, char *infile, char *outfile, int commands_len);
int free_cmd_arr(t_command ***commands_arr);

//Not needed
void  print_cmd_arr(t_command **commands);
#endif
