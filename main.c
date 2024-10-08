#include "pipex.h"

int get_cmds_len(t_command **commands)
{
  int len;

  len = 0;
  while (commands[len])
    len++;
  return (len);
}

void  print_cmd_arr(t_command **commands)
{
  for (int j = 0; commands[j]; j++)
  {
    printf("%s\n", commands[j]->command);
    for (int m = 0; commands[j]->cmd_args[m]; m++)
      printf("%d - %s\n", m, commands[j]->cmd_args[m]);
  }
}

int main(int argc, char **argv)
{
  /*
   *  archivo1 comando 1 | comando2 archivo 2
  *  archivo1 comando 1 | comando2 > archivo 2
   *
   *  EXAMPLES :
   *  $> ./pipex infile "ls -l" "wc -l" outfile
   *  $> ./pipex infile "grep a1" "wc -w" outfile
   * */
  /*
   *  Si teienes alguna duda, gestiona los errores como lo 
   *  hace el comando de shell: <file1 cmd1 | cmd2 >file2
   * */
  /*
   *  Gestionar multiples pipes
   *  $> ./pipex archivo1 comando1 comando2 comando3 ... comandon archivo2
   *  $> < archivo1 comando1 | comando2 | comando3 ... | comandon > archivo2
   * */
  /*
   *  Aceptar << y >> cuando el primer parámetro es “here_doc”:
   *  $> ./pipex here\_doc LIMITADOR comando comando1 archivo1
   *   comando << LIMITADOR | comando1 >> archivo
   * */

  t_command **commands;
  char  *infile;
  char  *outfile;

  if (argc < 4)
  {
    printf("Use infile command command outfile OR infile command command\n");
    return (1);
  }
  infile = argv[1];
  outfile = argv[argc - 1];
  commands = NULL;
  parse_commands(&commands, argv, argc - 1);
  printf("----- Success parsing commands\n");
  print_cmd_arr(commands);
  int cmds_len = get_cmds_len(commands);
  printf("----- CMDS_LEN BEFORE EXECUTING %d\n", cmds_len);
  if (cmds_len < 2)
    return (-1);
  print_cmd_arr(commands);

  //Execute all concurrently and use only two fds from pipes interchangeably
  execute_commands(commands, infile, outfile, get_cmds_len(commands));

  int cleaned_cmds = free_cmd_arr(&commands);
  printf("----- CLEANED COMMANDS %d\n", cleaned_cmds);
}
