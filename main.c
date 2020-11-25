#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>

int main(int argc, char **argv) {
  DIR *directory;

  char input[128];
  char buffer[128];

  if (argc > 1) {
    strncpy(input, argv[1], sizeof(input) - 1);
  } else {
    printf("Enter a directory to scan: ");
    fgets(buffer, sizeof(buffer), stdin);
    strncpy(input, buffer, sizeof(input) - 1);
  }

  directory = opendir(input);

  if (!directory) {
    printf("error: %s\n", strerror(errno));
  }

  struct dirent *entry;
  entry = readdir(directory);

  struct stat file;

  printf("Statistics for directory: %s\n", entry->d_name);


  int size = 0;
  while (entry)
  {
      if (entry->d_type == DT_REG)
      {
          stat(entry->d_name, &file);
          size += file.st_size;
      }
      entry = readdir(directory);
  }
  printf("Total Directory Size: %d Bytes\n\n", size);

  printf("Directories:\n");
  rewinddir(directory);
  entry = readdir(directory);
  printf("%8s %8s %10s %20s %s\n", "UID", "GID", "SIZE", "NAME", "LAST MODIFIED");
  while (entry)
  {
      if (entry->d_type == DT_DIR)
      {
          stat(entry->d_name, &file);
          printf("%8d %8d %10ld %20s %s", file.st_uid, file.st_gid, file.st_size,entry->d_name, ctime(&(file.st_mtime)) );
      }
      entry = readdir(directory);
  }
  printf("\n");
  rewinddir(directory);

  printf("Regular Files:\n");
  rewinddir(directory);
  entry = readdir(directory);
  printf("%8s %8s %10s %20s %s\n", "UID", "GID", "SIZE", "NAME", "LAST MODIFIED");
  while (entry)
  {
      if (entry->d_type == DT_REG)
      {
        stat(entry->d_name, &file);
            printf("%8d %8d %10ld %20s %s", file.st_uid, file.st_gid, file.st_size, entry->d_name, ctime(&(file.st_mtime)));
      }
      entry = readdir(directory);
  }
  closedir(directory);


}
