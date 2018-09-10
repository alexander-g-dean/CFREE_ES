/*===========================================================================*
 * FILE:  Console.c
 *===========================================================================*
 * Description:
 *     Provides basic control of a serial port in the form of input
 *     through lines (with some editing).  All output can be directed
 *     through the console commands (ConsolePrintf).
 *===========================================================================*/
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "Console.h"

#include "CG_macrodriver.h"
#include "CG_system.h"
#include "CG_serial.h"


/*---------------------------------------------------------------------------*
 * Globals
 *---------------------------------------------------------------------------*/
typedef struct {

  // Current line being built by the console
    char iCmd[Console_MAX_LINE_LENGTH+1];
    char iLastCmd[Console_MAX_LINE_LENGTH+1];

    // Current length of line being built by console
    uint32_t iCmdLen;

    // Flag to note if prompt should be shown on the next call to ConsoleUpdate().
    bool iNeedPrompt;

    // Simple flags to determine if we are/have stopping/stopped
    volatile bool iStop;
    volatile bool iStopped;

    // Pointer to a list of console commands
    const T_consoleCmdEntry *iCommandTable;
} T_ConsoleWorkspace;

static void strupr(char *string)
{
    while (*string)  {
        *string = toupper(*string);
        string++;
    }
}

extern volatile UCHAR G_UART_SendingData; //uart busy flag
extern volatile UCHAR G_UART_ReceivingData; //uart busy flag

#define COM_Send  UART0_SendData
T_ConsoleWorkspace G_ConsoleWorkspace;

/*---------------------------------------------------------------------------*
 * Routine:  ConsoleUValue
 *---------------------------------------------------------------------------*
 * Description:
 *      Convert the given string into a 32-bit unsigned value.  If the prefix
 *      is "0x" or "$", use hex, otherwise parse as a decimal value.
 * Inputs:
 *      const char *aArg          -- String with argument to convert
 * Outputs:
 *      uint32_t                   -- Value of string
 *---------------------------------------------------------------------------*/
uint32_t ConsoleUValue(const char *aArg)
{
    uint8_t isHex=0;
    uint32_t v=0;

    if ((aArg[0] == '0') && (aArg[1] == 'x')) {
        aArg += 2;
        isHex = 1;
    } else if (aArg[0] == '$') {
        aArg++;
        isHex = 1;
    }
    if (isHex)
        sscanf(aArg, "%x", &v);
    else
        sscanf(aArg, "%d", &v);

    return v;
}

/*---------------------------------------------------------------------------*
 * Routine:  ConsoleSendString
 *---------------------------------------------------------------------------*
 * Description:
 *      Output string of characters to the default console.
 * Inputs:
 *      const char *aString       -- Character string to output.
 * Outputs:
 *      T_uezError
 *---------------------------------------------------------------------------*/
void ConsoleSendString(void *aWorkspace, const char *aString)
{
    //T_ConsoleWorkspace *p = (T_ConsoleWorkspace *)aWorkspace;
    char c;
    //uint32_t numWritten;

    // Go through the line character by character
    // and convert \n into \r\n for proper standard conversion and
    // ignore extra \r's
    while ((c=*aString++)!=0)  {
        if (c == '\n') {
         int i = atoi("123");
            // Convert \n into \r\n
         
            // ********** UART print \r\n two characters
            G_UART_SendingData = 1;
            COM_Send("\r\n", 2);
            while(G_UART_SendingData){
              NOP();
            }
         
        } else if (c == '\r') {
            // Ignore \r
        } else {
            // Output all other characters individually

            //********** UART print character c
            G_UART_SendingData = 1;
            COM_Send((UCHAR *)&c, 1);
            while(G_UART_SendingData){
              NOP();
            }
          
        }
    }
}

/*---------------------------------------------------------------------------*
 * Routine:  ConsolePrintf
 *---------------------------------------------------------------------------*
 * Description:
 *      General command similar to printf but directs the output to the
 *      current console device.
 * Inputs:
 *      const char *aFormat       -- printf formatted text.
 *---------------------------------------------------------------------------*/
void ConsolePrintf(const char *aFormat, ...)
{
    char buffer[Console_PRINTF_BUFFER_SIZE];
    va_list marker;

    // Convert to a string for output
    va_start(marker, aFormat);
    vsprintf(buffer, aFormat, marker);
    va_end(marker);
    
    G_UART_SendingData = 1;
    COM_Send((UCHAR*)buffer, strlen(buffer));
    while(G_UART_SendingData){
      NOP();
    }
}

/*---------------------------------------------------------------------------*
 * Routine:  IConsoleBuildCmd
 *---------------------------------------------------------------------------*
 * Description:
 *      User entered a character.  Add the character to the end of the line,
 *      or process the special control character.  If time to process the
 *      command, return TRUE.
 * Inputs:
 *      char c                    -- Character to process on command line
 * Outputs:
 *     bool                      -- TRUE if command ready (end of line char)
 *                                   else FALSE.
 *---------------------------------------------------------------------------*/
static bool IConsoleBuildCmd(void *aWorkspace, char c)
{
    T_ConsoleWorkspace *p = (T_ConsoleWorkspace *)aWorkspace;
    char echo[2];

    // Read one character at a time
    // Put into the string
    if ((c == '\r') || (c == '\n')) {
        // End of line entered, return here
        ConsoleSendString(aWorkspace, "\r\n");
        return true;
    } else if ((c == '\b') || (c == 127)) {
        // Backspace hit
        if (p->iCmdLen > 0) {
            // Overwrite last character with a space if backing up
            ConsoleSendString(aWorkspace, "\b \b");
            p->iCmdLen--;
            p->iCmd[p->iCmdLen] = '\0';
        }
    } else {
        // Add if we have room, else do nothing
        if (p->iCmdLen < Console_MAX_LINE_LENGTH) {
            // Show we are adding the character (echo)
            echo[0] = c;
            echo[1] = 0;
            ConsoleSendString(aWorkspace, echo);
            p->iCmd[p->iCmdLen++] = c;
            p->iCmd[p->iCmdLen] = '\0';
        }
    }
    return false;
}

/*---------------------------------------------------------------------------*
 * Internal Routine:  IFindCommand
 *---------------------------------------------------------------------------*
 * Description:
 *      Find a command (by string name) in the command table
 *      that matches the given name (case sensitive).
 * Inputs:
 *      const char *aCmd          -- Command name to find
 * Outputs:
 *      T_consoleCmd              -- Pointer to command or 0
 *---------------------------------------------------------------------------*/
static T_consoleCmd IFindCommand(void *aWorkspace, const char *aCmd)
{
    T_ConsoleWorkspace *p = (T_ConsoleWorkspace *)aWorkspace;
    const T_consoleCmdEntry *p_node = p->iCommandTable;
    while (p_node->iName)  {
        if (strcmp(p_node->iName, aCmd) == 0)
            return p_node->iFunction;
        p_node++;
    }
    return 0;
}

/*---------------------------------------------------------------------------*
 * Routine:  ConsoleProcessCmd
 *---------------------------------------------------------------------------*
 * Description:
 *      A command was entered in the form of a line of characters.
 *      Break the line down to it's component elements, look for a command,
 *      and if found, run it.  Otherwise, report the command not found.
 * Inputs:
 *      const char *aCmd          -- Command line to process
 * Outputs:
 *      int                       -- Result code from processing command.
 *---------------------------------------------------------------------------*/
uint32_t ConsoleProcessCmd(void *aWorkspace, const char *aCmd)
{
    char *argv[Console_MAX_PARAMETERS];
    char line[Console_MAX_LINE_LENGTH+1];
    uint32_t argc = 0;
    char *p;
    uint32_t quote = 0;
    uint32_t started = 0;
    uint32_t result = -1;
    T_consoleCmd cmd;

    // Copy the line, we'll be modifying it
    strcpy(line, aCmd);

    // Parse the line into parameters
    p = line;
    while (*p)  {
        if (quote)  {
            // If inside a quote, just keep going
            if (*p == '\"')  {
                // Ending quote, zero it out and finish up this param
                quote = 0;
                *p = '\0';
                argc++;
                started = 0;
                // Stop here if too many parameters
                if (argc >= Console_MAX_PARAMETERS)
                    break;
            }
        } else {
            if (isspace(*p))  {
                // Got a space
                // Zero out spaces as we move
                // to the next line
                *p = '\0';
                if (started)  {
                    // We are done with this parameter,
                    // move to the next
                    argc++;
                    started = 0;
                    // Stop here if too many parameters
                    if (argc >= Console_MAX_PARAMETERS)
                        break;
                }
            } else {
                // Not a space, keep moving past it
                if (*p == '\"') {
                    // If we see a quote, note it, and skip over it
                    quote = 1;
                    p++;
                }
                if (!started)  {
                    // Found the start of a parameter
                    started = 1;
                    argv[argc] = p;
                }
            }
        }
        p++;
    }

    // Finish out last parameter
    if (started)  {
        argc++;
    }

    // Do we have any arguments?
    if (argc)  {
        // Find the matching command (case insensitive)
        strupr(argv[0]);
        cmd = IFindCommand(aWorkspace, argv[0]);
        if (cmd)  {
            // Run the command
            result = cmd(aWorkspace, argc, argv);
        } else {
            ConsolePrintf("Unknown command: %s\n", argv[0]);
        }
    }

    return result;
}

/*---------------------------------------------------------------------------*
 * Routine:  ConsoleTask
 *---------------------------------------------------------------------------*
 * Description:
 *      Sits on the stream and waits for incoming characters.
 *      Build a command line using the received characters.
 *      If <ENTER> is pressed, process the command.
 *      If just <ENTER> is pressed, then use the last command.
 *---------------------------------------------------------------------------*/
uint32_t ConsoleTask(void *aWorkspace)
{
    T_ConsoleWorkspace *p = (T_ConsoleWorkspace *)aWorkspace;
    char c;
        
    // Run until told to stop
    while (!p->iStop)  {
      
        if (p->iNeedPrompt)  {
            p->iNeedPrompt = false;
            p->iCmdLen = 0;
            ConsoleSendString(p, "\n# ");
        }

        G_UART_ReceivingData = 1;
        UART0_ReceiveData((UCHAR *)&c, 1);
        while(G_UART_ReceivingData)
        {
          NOP();
        }
        
        if (c == '?'){
			T_consoleCmd cmd;
		
			cmd = IFindCommand(aWorkspace, "?");
			if (cmd)  {
	            // Run the command
	            cmd(aWorkspace, 0, 0);
				ConsolePrintf("\r\n# ");
				if(strcmp(p->iCmd, p->iLastCmd) != 0)
					ConsolePrintf("%s", p->iCmd);
			}
			
		} else if (IConsoleBuildCmd(aWorkspace, c))  {
            // Only process lines with length
            if (p->iCmdLen)  {
                // Store the last command
                memcpy(p->iLastCmd, p->iCmd, sizeof(p->iLastCmd));
                ConsoleProcessCmd(aWorkspace, p->iCmd);
            } else {
                // User hit enter on a blank line.
                // Is there a last command waiting?
                if (p->iLastCmd[0])  {
                    // Yes, blank lines repeat the last command.
                    ConsolePrintf("REPEAT: %s\r\n", p->iLastCmd);
                    memcpy(p->iCmd, p->iLastCmd, sizeof(p->iLastCmd));
                    ConsoleProcessCmd(aWorkspace, p->iCmd);
                }
            }
            p->iNeedPrompt = true;
        }
    }
    return 0;
}


/*---------------------------------------------------------------------------*
 * Routine:  ConsoleTask
 *---------------------------------------------------------------------------*
 * Description:
 *      Initialize a task to use the given stream as a console.
 * Inputs:
 *      T_uezDevice *aStream        -- Open and configured stream device
 *      void **aWorkspace           -- Pointer to receive workspace pointer
 *                                     to be passed to ConsoleStop().  Pass 0
 *                                     if not needed.
 *      uint32_t aStackSizeBytes     -- Stack size in bytes.  All commands
 *                                     share the same stack.  Set this to
 *                                     the maximum size stack.
 *      const T_consoleCmdEntry *aCommandTable -- Pointer to an array of
 *                                      commands.
 * Outputs:
 *      T_uezError                  -- Error code. UEZ_ERROR_NOT_OPEN if
 *                                     stream is not open or 0.
 *                                     UEZ_ERROR_OUT_OF_MEMORY if out of
 *                                     memory.
 *---------------------------------------------------------------------------*/
void ConsoleStart(
     void **aWorkspace,
     const T_consoleCmdEntry *aCommandTable)
{
    T_ConsoleWorkspace *p = &G_ConsoleWorkspace;

    // Initialize the default parameters
    p->iCommandTable = aCommandTable;
    p->iCmdLen = 0;
    p->iNeedPrompt = true;
    p->iLastCmd[0] = '\0';
    p->iStop = false;
    p->iStopped = false;
    
    // Return the workspace pointer (if any)
    if (aWorkspace)
      *aWorkspace = (void *)p;
}


/*===========================================================================*
 * END OF FILE:  Console.c
 *===========================================================================*/
