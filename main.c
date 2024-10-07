#include "pipex.h"

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
  
  // 1- ARG[0] MUST ALWAYS BE A VALID FILE ELSE return error
  // 2- ARG[1] MUST ALWAYS BE A VALID COMMAND
  // child process execute Left side of the pipe and sends output ot parent process
  // parent process executes Right side of the pipe, recieve the input over a pipe
  //        and execute the given command,
  //        THE LAST ARGUMENT WILL ALWAYS BE THE OUTPUT_FILE PARENT PROCESS WRITES TO
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
  parse_commands(&commands, argv, argc - 1);

  for (int j = 0; commands[j]; j++)
  {
    printf("%s\n", commands[j]->command);
    for (int m = 0; commands[j]->cmd_args[m]; m++)
      printf("%d - %s\n", m, commands[j]->cmd_args[m]);
  }
  //Execute all concurrently and use only two fds from pipes interchangeably

}
