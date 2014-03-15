#include "aixen.h"

int row = 0;
char screen[80][36];
void control()
{
    while (1)
    {

        char s[100];
        fgets(s,sizeof(s),stdin);
        int len = strlen(s);
        s[len-1] = 0;
        printf("\033[2J"); // Clear terminal
        redraw();
        draw();
        if(!strcasecmp(s,"status")) // TODO: Better command handling.
        {
            writeline("running...");
        }
        else
        {
            writeline("command not found!");
        }
        printf("\033[37;7H");
    }

}

void redraw(void)
{
    printf("\033[0;0H\033[0;37;44mHeartbeat:     Peer listen:     Main Server:     Connected: %d",config.connected);
    printf("\033[0;12H\033[0;37;4%s%s%s",(config.status.heartbeat == 0 ? "1" : "2"),"m",(config.status.heartbeat == 0 ? "OFF" : "OK "));
    printf("\033[0;29H\033[0;37;4%s%s%s",(config.status.peer == 0 ? "1" : "2"),"m",(config.status.peer == 0 ? "OFF" : "OK "));
    printf("\033[0;46H\033[0;37;4%s%s%s",(config.status.main == 0 ? "1" : "2"), "m",(config.status.main == 0 ? "OFF" : "OK "));
    printf("\033[37;0H\033[0;30;47maixen>\033[0;37;40m");
    printf("\033[2;0H");
}

int doCommand(char* comm) // Work In Progress
{
    if(!strcasecmp(comm,"status"))
    {

    }
}
//Please help from this line down - i think the problem is in draw().
void writeline(char* line)
{
    if(row = 36)
    {
        int tmp = 0;
        while (tmp != 36)
        {
            strcpy(screen[tmp],screen[tmp+1]);
            tmp++;
        }
        row = 0;
    }
    strcpy(screen[row],line);
    row++;
}

void draw(void)
{
    int x = 1;
    int y = 2;
    while (y != 38)
    {
        printf("\003[%d;%dH%c",y,x,screen[y]);
        y++;
    }
}
