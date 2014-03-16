#include "aixen.h"

int row = 0;
char screen[80][36];
void control()
{
    printf("\033[0;37;40m\033[2J");
    draw();
    redraw();
    printf("\033[37;7H");
    while (1)
    {

        char s[100];
        fgets(s,sizeof(s),stdin);
        int len = strlen(s);
        s[len-1] = 0;
        printf("\033[0;37;40m\033[2J"); // Clear terminal
        doCommand(s);
        draw();
        redraw();
        printf("\033[37;7H");
    }

}

void redraw(void)
{
    printf("\033[0;0H\033[0;37;44mHeartbeat:     Peer listen:     Main Server:     Connected: %d",config.connected);
    printf("\033[0;12H\033[0;37;4%s%s%s",(config.status.heartbeat == 0 ? "1" : "2"),"m",(config.status.heartbeat == 0 ? "OFF" : "OK "));
    printf("\033[0;29H\033[0;37;4%s%s%s",(config.status.peer == 0 ? "1" : "2"),"m",(config.status.peer == 0 ? "OFF" : "OK "));
    printf("\033[0;46H\033[0;37;4%s%s%s",(config.status.main == 0 ? "1" : "2"), "m",(config.status.main == 0 ? "OFF" : "OK "));
    printf("\033[37;0H\033[0;30;47maixen>\033[0;30;47m");
    printf("\033[2;0H");
}

int doCommand(char* comm) // Here add commands if you want
{
    if(!strcasecmp(comm,"refresh"))
    {
    }
    else if(!strcasecmp(comm,"heartbeat"))
    {
        config.status.heartbeat = config.status.heartbeat == 0 ? 1 : 0;
        writeline("Switched state of heartbeat.");
    }
    else if(!strcasecmp(comm,"exit"))
    {
        printf("\003[0;37;40");
        exit(0);
    }
    else if(!strcasecmp(comm,"main"))
    {
        config.status.main = config.status.main == 0 ? 1 : 0;
        writeline("Switched state of main.");
    }
    else if(!strcasecmp(comm,"peer"))
    {
        config.status.peer = config.status.peer == 0 ? 1 : 0;
        writeline("Switched state of peer.");
    }
    else
    {
    	writeline("command not found.");
    }
}
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
        row = 35;
    }
    strcpy(screen[row + 1],line);
    row++;
    draw();
}

void draw(void)
{
    int x = 1;
    int y = 2;
    while (y != 38)
    {
        printf("\033[%d;%dH%s",y,x,screen[y]);
        y++;
    }
}
