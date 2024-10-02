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

  //if (argc != 4)
  //  return (EXIT_FAILURE);
  
  // 1- ARG[0] MUST ALWAYS BE A VALID FILE ELSE return error
  // 2- ARG[1] MUST ALWAYS BE A VALID COMMAND
  // child process execute Left side of the pipe and sends output ot parent process
  // parent process executes Right side of the pipe, recieve the input over a pipe
  //        and execute the given command,
  //        THE LAST ARGUMENT WILL ALWAYS BE THE OUTPUT_FILE PARENT PROCESS WRITES TO
  int c_id = fork();
  if (c_id == 0){
    printf("IM the child process %d - P_id:  %d\n", c_id, getpid());

  }
  else{
    printf("IM the parent process %d - P_id %d \n", c_id, getpid());
  }

}
