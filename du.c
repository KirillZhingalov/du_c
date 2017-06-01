#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

int get_files_size(char *dir_name){
  DIR *d;
  int total_size;
  //int exists;
  struct dirent *de;
  struct stat buf;
  char *s;
 
  d = opendir(dir_name);
  if (d == NULL){
    perror("Error");
    exit(1);
  }

  //initialize
  s = (char *) malloc(sizeof(char)*(strlen(dir_name)+258));
  total_size = 0;

  for (de = readdir(d); de != NULL; de = readdir(d)){
    sprintf(s, "%s/%s", dir_name, de->d_name);
    stat(s, &buf);
    if (!S_ISDIR(buf.st_mode)){
      total_size += buf.st_size;
    }
    if (S_ISDIR(buf.st_mode) && (strcmp(de->d_name, ".") != 0) && (strcmp(de->d_name, "..") != 0)){
      int dir_size = get_files_size(s);
      printf("%d \t%s\n", dir_size, s);
      total_size += dir_size;
    }
    else{
      if (strcmp(de->d_name, ".") == 0){
        total_size += buf.st_size; 
      }
    }
  }
  
  closedir(d);
  free(s);
  return total_size;
}

int get_current_dir_size(char *dir_name){
  DIR *d;
  int total_size = 0;
  struct dirent *de;
  struct stat buf;

  d = opendir(dir_name);
  for (de = readdir(d); de != NULL; de = readdir(d)){
    stat(de->d_name, &buf);
    total_size += buf.st_size;
  }

  closedir(d);
  return total_size;
}

int main(int argc, char **argv){
  int total_size;
  printf("%d\n", argc);
  total_size = get_files_size(argv[1]);
  printf("%d \t%s\n", get_current_dir_size(argv[1]), argv[1]);
  printf("%d \tитого\n", total_size);
}

