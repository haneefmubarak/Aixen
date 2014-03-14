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
    cout << "\033[0;0H\033[0;37;44mHeartbeat:     Peer listen:     Main Server:    ";
    cout << "\033[11;0H\033[0;37;42mOK ";
    cout << "\033[28;0H\033[0;37;42mOK ";
    cout << "\033[45;0H\033[0;37;42mOK ";
}
