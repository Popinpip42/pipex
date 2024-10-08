#include "pipex.h"

//Returns cleaned commands:
int free_cmd_arr(t_command ***commands_arr)
{
  int i;
  int j;

  i = 0;
  while ((*commands_arr)[i])
  {
    j = 0;
    while ((*commands_arr)[i]->cmd_args[j])
    {
      free((*commands_arr)[i]->cmd_args[j]);
      j++;
    }
    i++;
  }
  return (i);
}
int is_cmd(char *str)
{
  char *path_env = getenv("PATH");
  char *path_dup = strdup(path_env);
  char *dir = strtok(path_dup, ":");
  char full_path[256];

  printf("--- Checking if < %s > is a command \n ", str);
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

void  add_cmd(char  *str, t_command ***commands_arr, t_command **current_command)
{
  //TODO: reformat code
}

void add_arg_cmd(char *str); //TODO: reformat code

int parse_commands(t_command ***commands_arr, char **argv, int argv_len)
{
  int       i;
  int       cmd_index;
  int       cmd_args_index;
  t_command *current_command;

  printf("-- Abut to parse...\n");
  if (!(*commands_arr))
  {
    printf("-- Not init array_commd\n");
    (*commands_arr) = malloc((argv_len + 1) * sizeof(t_command *));
    if (!(*commands_arr))
      return (-1);
  }
  i = 2;
  cmd_index = 0;
  printf("-- Starting the parsing within parse_commands funciton\n");
  printf("-- This is the argv array\n");
  for( int i = 0; argv[i]; i++)
  {
    printf("%d - argument %s\n", i, argv[i]);
  }
 
  while (i < argv_len)
  {
    printf("--- Not segfault here %d\n", i);
    if (is_cmd(argv[i]))
    {
      printf("--- Not segfault here %d. This is a proper command %s \n", i, argv[i]);
      cmd_args_index = 0;
      current_command = (t_command *) malloc(sizeof(t_command));
      if (!current_command)
        return (-1);
      //add_cmd(argv[i], commands_arr, cuargvrrent_command);
      current_command->command = strdup(argv[i]);
      current_command->cmd_args[cmd_args_index++] = strdup(argv[i]);
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

int execute_commands(t_command **commands, char *infile, char *outfile, int num_commands)
{
  int i;
  int pipe_fds[2];
  int prev_pipe = -1;
  int input_fd, output_fd;
  pid_t pid;

  input_fd = open(infile, O_RDONLY);
  if (input_fd == -1) {
      perror("Error opening infile");
      return -1;
  }
  output_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (output_fd == -1) {
      perror("Error opening outfile");
      close(input_fd);
      return -1;
  }

  for (i = 0; i < num_commands; i++) {
      // Create a pipe for all but the last command
      if (i < num_commands - 1) {
          if (pipe(pipe_fds) == -1) {
              perror("Pipe failed");
              return -1;
          }
      }

      pid = fork();
      if (pid == -1) {
          perror("Fork failed");
          return -1;
      }

      if (pid == 0) {
          if (i == 0) {
              dup2(input_fd, STDIN_FILENO);
              close(input_fd);
          } else if (prev_pipe != -1) {
              dup2(prev_pipe, STDIN_FILENO);
              close(prev_pipe);
          }

          if (i == num_commands - 1) {
              dup2(output_fd, STDOUT_FILENO);
              close(output_fd);
          } else {
              close(pipe_fds[0]);
              dup2(pipe_fds[1], STDOUT_FILENO);
              close(pipe_fds[1]);
          }
          //Execute
          execvp(commands[i]->command, commands[i]->cmd_args);
          perror("Exec failed");
          exit(EXIT_FAILURE);
      }
      // Parent process
      if (prev_pipe != -1) {
          close(prev_pipe);
      }
      if (i < num_commands - 1) {
          close(pipe_fds[1]);  // Close write end of this pipe in parent
          prev_pipe = pipe_fds[0];  // Move read end to prev_pipe for the next command
      }
  }
  for (i = 0; i < num_commands; i++) {
      wait(NULL);
  }
  close(input_fd);
  close(output_fd);
  return (0);
}
