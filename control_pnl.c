#include "aixen.h"

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
        if(!strcasecmp(s,"status")) // TODO: Better command handling.
        {
            printf("running...\n");
            printf("connected: %d",cfg.connected);
        }
        else
        {
            printf("command not found!");
        }
        sleep(1);
    }

}

void redraw()
{
    printf("\033[0;0H\033[0;37;44mHeartbeat:     Peer listen:     Main Server:     Connected: %d",cfg.connected);
    printf("\033[0;11H\033[0;37;4"+ (cfg.heartbeatStatus == 0 ? "1" : "2") + "m" + (cfg.heartbeatStatus == 0 ? "OFF" : "OK "));
    printf("\033[0;28H\033[0;37;4"+ (cfg.peerStatus == 0 ? "1" : "2") + "m" + (cfg.peerStatus == 0 ? "OFF" : "OK "));
    printf("\033[0;45H\033[0;37;4"+ (cfg.mainStatus == 0 ? "1" : "2") + "m" + (cfg.mainStatus == 0 ? "OFF" : "OK "));
    printf("\033[37;0H\033[0;30;47maixen>\033[0;37;40m");
    printf("\033[1;0H");
}

int doCommand(char* comm) // Work In Progress
{
    if(!strcasecmp(comm,"status"))
    {

    }
}
