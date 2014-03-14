/* ========================================================================== */
/*                                                                            */
/*   control_pnl.c                                                            */
/*   (c) 2014 Jano Varga                                                      */
/*                                                                            */
/*   Terminal control panel                                                   */
/*                                                                            */
/* ========================================================================== */
#include "aixen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void redraw()
{
    printf("\033[0;0H\033[0;37;44mHeartbeat:     Peer listen:     Main Server:    ");
    printf("\033[0;11H\033[0;37;42mOK ");
    printf("\033[0;28H\033[0;37;42mOK ");
    printf("\033[0;45H\033[0;37;42mOK ");
}
