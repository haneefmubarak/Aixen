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
        redraw();
        char s[100];
        fgets(s,sizeof(s),stdin);
        printf("\033[1,0H");
        if(!strcmp(s,"status")) // TODO: Compare non-casesensitive and better command handling. I will do it.
        {
            printf("running...");
            printf("connected: " + itoa(connected));
        }
        else
        {
            printf("command not found!");
        }
    }

}

void redraw()
{
    printf("\033[0;0H\033[0;37;44mHeartbeat:     Peer listen:     Main Server:     Connected: " + itoa(connected));
    printf("\033[0;11H\033[0;37;42mOK ");
    printf("\033[0;28H\033[0;37;42mOK ");
    printf("\033[0;45H\033[0;37;42mOK ");
    printf("\033[23;0H\033[0;37;40maixen>");
}
