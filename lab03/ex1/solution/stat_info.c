#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <pwd.h>
#include <grp.h>

#define FULL_PERMS (S_IRWXU | S_IRWXG | S_IRWXO)
/* -------------------------------------------------------------------------------- */

static void print_type(struct stat *sb);
static void print_ino(const struct stat *sb);
static void print_perms(const struct stat *sb, char * path);
static void print_linkc(const struct stat *sb);
static void print_owner(const struct stat *sb);
static void print_size(const struct stat *sb);
static void print_laststch(const struct stat *sb);
static void print_lastacc(const struct stat *sb);
static void print_lastmod(const struct stat *sb);
static void print_name(const struct stat *sb, char *name);

double format(char ** postfix, time_t then);
/* -------------------------------------------------------------------------------- */

int  main(int argc, char *argv[])
{
  struct stat sb;
  
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  if (lstat(argv[1], &sb) == -1) {
    perror("stat");
    exit(EXIT_SUCCESS);
  }
  
  print_type(&sb);
  print_name(&sb, argv[1]);
  print_ino(&sb);
  print_perms(&sb, argv[1]);
  print_linkc(&sb);
  print_owner(&sb);
  print_size(&sb);
  print_laststch(&sb);
  print_lastacc(&sb);
  print_lastmod(&sb);
  
  exit(EXIT_SUCCESS);
}
/* -------------------------------------------------------------------------------- */

static void print_type(struct stat *sb){
  printf("File type:                ");
  switch (sb->st_mode & S_IFMT) {
  case S_IFBLK:  printf("block device\n");            break;
  case S_IFCHR:  printf("character device\n");        break;
  case S_IFSOCK: printf("socket\n");                  break;
  case S_IFLNK:  printf("symbolic link\n");           break;
  case S_IFREG:  printf("regular file\n");            break;
  case S_IFDIR:  printf("directory\n");               break;
  case S_IFIFO:  printf("FIFO\n");                    break;
  default:       printf("unknown?\n");                break;
  }
}
/* -------------------------------------------------------------------------------- */

static void print_ino(const struct stat *sb){
  printf("I-node number:            %ld\n", (long) sb->st_ino);
}
/* -------------------------------------------------------------------------------- */

static void print_perms(const struct stat *sb, char * path){
  int perms = sb->st_mode & FULL_PERMS;
  printf("Mode:                     %lo (octal)\n", (unsigned long) perms);

  char* read = access(path, R_OK) ? "no" : "yes";
  char* write = access(path, W_OK) ? "no" : "yes";
  char* exec = access(path, X_OK) ? "no" : "yes";
  printf("Your permisions:          read: %s, write: %s, execute: %s\n", read, write, exec);
}
/* -------------------------------------------------------------------------------- */

static void print_linkc(const struct stat *sb){
  printf("Link count:               %ld\n", (long) sb->st_nlink);
}
/* -------------------------------------------------------------------------------- */

static void print_owner(const struct stat *sb){
  long userID = sb->st_uid;
  char* userName = getpwuid(userID)->pw_name;
  long groupID = sb->st_gid;
  char* groupName = getgrgid(groupID)->gr_name;
  printf("Ownership:                UID=%s(%ld)   GID=%s(%ld)\n", userName, userID, groupName, groupID);
}
/* -------------------------------------------------------------------------------- */

static void print_size(const struct stat *sb){
  long long size = sb->st_size;
  char* postfix = "bytes";

  if(size > 1048576){
    size /= 1048576;
    postfix = "MiB";
  } else if(size >  1024){
    size /= 1024;
    postfix = "KiB";
  }

  printf("Preferred I/O block size: %ld bytes\n", (long) sb->st_blksize);
  printf("File size:                %lld %s\n",size, postfix);
  printf("Blocks allocated:         %lld\n",(long long) sb->st_blocks);
}
/* -------------------------------------------------------------------------------- */

static void print_laststch(const struct stat *sb){
  char * postfix;
  double value = format(&postfix, sb->st_ctime);
  printf("Last status change:       %.f %s\n", value, postfix);
}
/* -------------------------------------------------------------------------------- */

static void print_lastacc(const struct stat *sb){
  char * postfix;
  double value = format(&postfix, sb->st_atime);
  printf("Last file access:         %.f %s\n", value, postfix);
}
/* -------------------------------------------------------------------------------- */

static void print_lastmod(const struct stat *sb){
  char * postfix;
  double value = format(&postfix, sb->st_mtime);
  printf("Last file modification:   %.f %s\n", value, postfix);
}
/* -------------------------------------------------------------------------------- */

static void print_name(const struct stat *sb, char *name){
  char* bname = basename(name);
  char buff [512];
  if((sb -> st_mode & S_IFMT) == S_IFLNK){
    readlink(name,buff,512);
    char* oname = basename(buff);
    printf("Name of the file:         %s -> %s\n", bname, oname);
  } else {
    printf("Name of the file:         %s\n", bname);
  }
}
/* -------------------------------------------------------------------------------- */

double format(char ** postfix, time_t then){
  time_t now = time(NULL);
  double diff = difftime(now, then);
  *postfix = "second ago";

  if(diff > 172800){
    diff /= 86400;
    *postfix = "days ago";
  } else if (diff > 86400) {
    diff /= 86400;
    *postfix = "day ago";
  } else if(diff > 7200){
    diff /= 3600;
    *postfix = "hours ago";
  } else if(diff > 3600){
    diff /= 3600;
    *postfix = "hours ago";
  } else if(diff > 120){
    diff /= 60;
    *postfix = "minutes ago";
  } else if(diff > 60){
    diff /= 60;
    *postfix = "minute ago";
  } else if(diff > 2){
    *postfix = "seconds ago";
  }

  return diff;
}