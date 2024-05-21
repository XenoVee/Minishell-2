#include<stdio.h>
#include<stdlib.h>
#include "input.h"

static char *input_read_line(void) 
{
  char *line = readline(">>"); // Use readline to get input

  if (line == NULL) 
  {
    exit(EXIT_SUCCESS); // We received an EOF or an error
  }
  return line;
}

void input_loop(void) 
{
  char *line;
  t_commands cmds;
  int status;

  while (1) 
  {
    line = input_read_line();
    printf("%s\n", line);
    cmds = input_parse(line);
    
    //Execute cmds here

    free(line);
    free_memory(cmds);
  }
}

void main ()
{
  input_loop();
}