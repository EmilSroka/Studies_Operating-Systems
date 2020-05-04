#include <string.h>
#include <termios.h>
#include <unistd.h>

int main(void) {
  struct termios terminalSettings, rawSettings;
  char *kod[]={".- ","-... ","-.-. ","-.. ",". ","..-. ","--. ",".... ",".. ",".--- ",
	        "-.- ",".-.. ","-- ","-. ","--- ",".--. ","--.- ",".-. ","... ","- ",
	        "..- ","...- ",".-- ","-..- ","-.-- ","--.. "};
  char bufor[6] = "";
  char znak;


  cfmakeraw(&rawSettings);
  tcgetattr(STDIN_FILENO, &terminalSettings);
  tcsetattr(STDIN_FILENO, TCSANOW, &rawSettings);
  
  while(read(0,&znak,1) && znak != '\003') {
    if(znak == '\n' || znak == '\r'){
      write(1, "\n\r", 2);
      continue;
    } else if (znak > 'z' || znak < 'a'){
      write(1, "     ", 5);
      continue;
    }

    strcpy(bufor,kod[znak-'a']);
    write(1,bufor, 6);
  }

  write(1, "\n\r", 2);
  tcsetattr(STDIN_FILENO, TCSANOW, &terminalSettings);
  
  return 0;
}