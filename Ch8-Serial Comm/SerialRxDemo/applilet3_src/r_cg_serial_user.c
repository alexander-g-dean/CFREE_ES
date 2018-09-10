/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized. This 
* software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING 
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT 
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE 
* AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR 
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE 
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software 
* and to discontinue the availability of this software.  By using this software, 
* you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2010, 2011 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_serial_user.c
* Version      : Applilet3 for RL78/G13 V1.03.01 [11 Oct 2011]
* Device(s)    : R5F100LE
* Tool-Chain   : IAR Systems iccrl78
* Description  : This file implements device driver for Serial module.
* Creation Date: 7/11/2012
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_serial.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern uint8_t * gp_uart0_tx_address;         /* uart0 send buffer address */
extern uint16_t  g_uart0_tx_count;            /* uart0 send data number */
extern uint8_t * gp_uart0_rx_address;         /* uart0 receive buffer address */
extern uint16_t  g_uart0_rx_count;            /* uart0 receive data number */
extern uint16_t  g_uart0_rx_length;           /* uart0 receive data length */
extern uint8_t * gp_csi10_rx_address;         /* csi10 receive buffer address */
extern uint16_t  g_csi10_rx_length;           /* csi10 receive data length */
extern uint16_t  g_csi10_rx_count;            /* csi10 receive data count */
extern uint8_t * gp_csi10_tx_address;         /* csi10 send buffer address */
extern uint16_t  g_csi10_send_length;         /* csi10 send data length */
extern uint16_t  g_csi10_tx_count;            /* csi10 send data count */
/* Start user code for global. Do not edit comment generated here */
volatile uint8_t G_UART_SendingData = 0;
volatile uint8_t G_UART_ReceivingData = 0;
volatile uint8_t G_SPI_SendingData = 0;
volatile uint8_t G_SPI_ReceivingData = 0;
volatile uint8_t G_IIC_SendingData = 0;
volatile uint8_t G_IIC_ReceivingData = 0;
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: r_uart0_interrupt_receive
* Description  : This function is INTSR0 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma vector = INTSR0_vect
__interrupt static void r_uart0_interrupt_receive(void)
{
    uint8_t rx_data;

    rx_data = RXD0;

    if (g_uart0_rx_length > g_uart0_rx_count)
    {
        *gp_uart0_rx_address = rx_data;
        gp_uart0_rx_address++;
        g_uart0_rx_count++;

        if (g_uart0_rx_length == g_uart0_rx_count)
        {
            r_uart0_callback_receiveend();
        }
    }
}

/***********************************************************************************************************************
* Function Name: r_uart0_interrupt_error
* Description  : This function is INTSRE0 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma vector = INTSRE0_vect
__interrupt static void r_uart0_interrupt_error(void)
{
    uint8_t err_type;

    *gp_uart0_rx_address = RXD0;
}

/***********************************************************************************************************************
* Function Name: r_uart0_interrupt_send
* Description  : This function is INTST0 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma vector = INTST0_vect
__interrupt static void r_uart0_interrupt_send(void)
{
    if (g_uart0_tx_count > 0U)
    {
        TXD0 = *gp_uart0_tx_address;
        gp_uart0_tx_address++;
        g_uart0_tx_count--;
    }
    else
    {
        r_uart0_callback_sendend();
    }
}

/***********************************************************************************************************************
* Function Name: r_uart0_callback_receiveend
* Description  : This function is a callback function when UART0 finishes reception.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_uart0_callback_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
		G_UART_ReceivingData = 0;
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_uart0_callback_sendend
* Description  : This function is a callback function when UART0 finishes transmission.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_uart0_callback_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
		G_UART_SendingData = 0;
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_csi10_interrupt
* Description  : This function is INTCSI10 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma vector = INTCSI10_vect
__interrupt static void r_csi10_interrupt(void)
{
    uint8_t err_type;

    err_type = (uint8_t)(SSR02 & _0001_SAU_OVERRUN_ERROR);
    SIR02 = (uint16_t)err_type;

    if (1U == err_type)
    {
        r_csi10_callback_error(err_type);    /* overrun error occurs */
    }
    else
    {
        if (g_csi10_tx_count > 0U)
        {
            *gp_csi10_rx_address = SIO10;
            gp_csi10_rx_address++;
            SIO10 = *gp_csi10_tx_address;
            gp_csi10_tx_address++;
            g_csi10_tx_count--;
        }
        else 
        {
            if (0U == g_csi10_tx_count)
            {
                *gp_csi10_rx_address = SIO10;
            }

            r_csi10_callback_sendend();    /* complete send */
            r_csi10_callback_receiveend();    /* complete receive */
        }
    }
}

/***********************************************************************************************************************
* Function Name: r_csi10_callback_receiveend
* Description  : This function is a callback function when CSI10 finishes reception.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_csi10_callback_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    G_SPI_ReceivingData = 0;
		/* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_csi10_callback_error
* Description  : This function is a callback function when CSI10 reception error occurs.
* Arguments    : err_type -
*                    error type value
* Return Value : None
***********************************************************************************************************************/
static void r_csi10_callback_error(uint8_t err_type)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_csi10_callback_sendend
* Description  : This function is a callback function when CSI10 finishes transmission.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_csi10_callback_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
  G_SPI_SendingData = 0;
	/* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
