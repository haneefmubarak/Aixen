/* ========================================================================== */
/*                                                                            */
/*   control_pnl.c                                                            */
/*   (c) 2014 Jano Varga                                                      */
/*                                                                            */
/*   Terminal control panel                                                   */
/*                                                                            */
/* ========================================================================== */
#include "aixen.h"

void control()
{
    while (1)
    {
        printf("\033[2J"); // Clear terminal
        redraw();
        char s[100];
        fgets(s,sizeof(s),stdin);
        int len = strlen(s);
        s[len-1] = "\0";
        printf("\033[2J");
        redraw();
        printf("\033[1;0H");
        if(!strcmp(s,"status")) // TODO: Better command handling.
        {
            printf("running...");
            printf("connected: %d",connected);
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
    printf("\033[0;0H\033[0;37;44mHeartbeat:     Peer listen:     Main Server:     Connected: %d",connected);
    printf("\033[0;11H\033[0;37;42mOK ");
    printf("\033[0;28H\033[0;37;42mOK ");
    printf("\033[0;45H\033[0;37;42mOK ");
    printf("\033[37;0H\033[0;37;40maixen>");
}
