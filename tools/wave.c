/* make wave executable */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#ifdef __linux__
#include <sys/utsname.h>
#endif

#define LINUX64 "x86_64"
#define WINDOWS64 "PROGRAMFILES(x86)"

int main() {

#if defined __linux__
  struct utsname my_uname;
  if (uname(& my_uname) == 0 && strcmp(LINUX64, my_uname.machine) == 0) {
    printf("This is 64-bit Linux\n");
    system("runtime/linux/jdk/bin/java --module-path runtime/linux/jfx/lib --add-modules javafx.controls,javafx.fxml,javafx.web -jar runtime/bin/wave > /dev/null 2>&1 &");
  } else {
    printf("This is 32-bit Linux, unsupported\n");
  }
#endif

#if defined _WIN32 || defined _WIN64
  char * env = getenv(WINDOWS64);
  if (env != NULL) {
    printf("This is 64-bit Windows\n");
    system("start runtime\\win\\jdk\\bin\\javaw.exe --module-path runtime\\win\\jfx\\lib --add-modules javafx.controls,javafx.fxml,javafx.web -jar runtime\\bin\\wave > nul 2>&1 &");
  } else {
    printf("This is 32-bit Windows, unsupported\n");
  }
#endif

  return 0;
}
