#include "pipex.h"

int is_cmd(char *str)
{
  char *path_env = getenv("PATH");
  char *path_dup = strdup(path_env);
  char *dir = strtok(path_dup, ":");
  char full_path[256];

  while (dir != NULL) {
      snprintf(full_path, sizeof(full_path), "%s/%s", dir, str);
      if (access(full_path, X_OK) == 0) {
          free(path_dup);
          return (1);
      }
      dir = strtok(NULL, ":");
  }
  free(path_dup);
  return (0);
}

int parse_commands(t_command ***commands_arr, char **argv, int argv_len)
{
  int       i;
  int       cmd_index;
  int       cmd_args_index;
  t_command *current_command;

  printf("Abut to parse...\n");
  (*commands_arr) = NULL;
  if (!(*commands_arr))
  {
    printf("Not init array_commd\n");
    (*commands_arr) = malloc((argv_len + 1) * sizeof(t_command *));
    if (!(*commands_arr))
      return (-1);
  }
  i = 2;
  cmd_index = 0;
  while (i < argv_len)
  {
    if (is_cmd(argv[i]))
    {
      cmd_args_index = 0;
      current_command = (t_command *) malloc(sizeof(t_command));
      if (!current_command)
        return (-1);
      current_command->command = strdup(argv[i]);
      current_command->cmd_args[cmd_args_index] = NULL;
      (*commands_arr)[cmd_index++] = current_command;
      (*commands_arr)[cmd_index] = NULL;
    }
    else
    {
      current_command->cmd_args[cmd_args_index++] = strdup(argv[i]);
      current_command->cmd_args[cmd_args_index] = NULL;
    }
    i++;
  }
  return (0);
}
