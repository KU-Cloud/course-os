/**
 * Basic execl() Usage.
 *
 * By walking through this example you’ll learn:
 * - How to use execl().
 * - What happens to the process that invoked execl().
 * 
 * execl은 현재의 프로세스 이미지를 새로운 프로세스 이미지로 덮어쓴다.
 * 프로세스의 이미지는 실행 파일을 실행해서 얻으므로, 이 함수는 실행 파일의 경로정보를 가진다.
 * execl(실행파일 있는 곳 까지의 전체 경로이름, 프로그램 이름, 인수들, NULL)
 */

#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    printf("%s executing `ls -l`.\n", "Before");

    // HINT: The /bin/ls -l should be executed.
    execl("/bin/ls", "ls", "-l", NULL);

    printf("%s executing `ls -l`.\n", "After");

    return 0;
}
