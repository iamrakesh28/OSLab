#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

const int size = 16;
int main() {

  char buff[size];
  int p[2], pid;
  if (pipe(p) < 0)
    return 1;
  if (fork()) {
    close(p[0]);
    fgets(buff, size, stdin);
    write(p[1], buff, size);

    close(p[1]);
    wait(NULL);
  }
  else {
    int byte;
    close(p[0]);
    while ((byte = read(p[0], buff, size)) > 0) {
      //printf("%d\n", byte);
      puts(buff);
    }
    close(p[0]);
    puts("Reading Finished");
  }
  return 0;
}
