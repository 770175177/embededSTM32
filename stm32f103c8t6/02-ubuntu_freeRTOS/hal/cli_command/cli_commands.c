/*
 * FreeRTOS V202212.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */


/******************************************************************************
*
* https://www.FreeRTOS.org/cli
*
******************************************************************************/


/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Standard includes. */
// #include <stdint.h>
// #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mini_printf.h"
#include "cli_commands.h"
#include "pid.h"
#include "log_module.h"

#ifndef  configINCLUDE_TRACE_RELATED_CLI_COMMANDS
    #define configINCLUDE_TRACE_RELATED_CLI_COMMANDS    0
#endif

#ifndef configINCLUDE_QUERY_HEAP_COMMAND
    #define configINCLUDE_QUERY_HEAP_COMMAND    1
#endif

#define PID_WRITE_FLAG      0xA5
#define PID_CLEAR_FLAG      0x00
extern pid_calc_t *ppid;

/*
 * The function that registers the commands that are defined within this file.
 */
void vRegisterSampleCLICommands( void );

/*
 * Implements the task-stats command.
 */
static BaseType_t prvTaskStatsCommand( char * pcWriteBuffer,
                                       size_t xWriteBufferLen,
                                       const char * pcCommandString );

/*
 * Implements the run-time-stats command.
 */
#if ( configGENERATE_RUN_TIME_STATS == 1 )
    static BaseType_t prvRunTimeStatsCommand( char * pcWriteBuffer,
                                              size_t xWriteBufferLen,
                                              const char * pcCommandString );
#endif /* configGENERATE_RUN_TIME_STATS */

/*
 * Implements the echo-three-parameters command.
 */
static BaseType_t prvThreeParameterEchoCommand( char * pcWriteBuffer,
                                                size_t xWriteBufferLen,
                                                const char * pcCommandString );

/*
 * Implements the echo-parameters command.
 */
static BaseType_t prvParameterEchoCommand( char * pcWriteBuffer,
                                           size_t xWriteBufferLen,
                                           const char * pcCommandString );

/*
 * Implements the "query heap" command.
 */
#if ( configINCLUDE_QUERY_HEAP_COMMAND == 1 )
    static BaseType_t prvQueryHeapCommand( char * pcWriteBuffer,
                                           size_t xWriteBufferLen,
                                           const char * pcCommandString );
#endif

/*
 * Implements the "trace start" and "trace stop" commands;
 */
#if ( configINCLUDE_TRACE_RELATED_CLI_COMMANDS == 1 )
    static BaseType_t prvStartStopTraceCommand( char * pcWriteBuffer,
                                                size_t xWriteBufferLen,
                                                const char * pcCommandString );
#endif

static BaseType_t prvPidParametersOperationCommand( char * pcWriteBuffer,
                                                    size_t xWriteBufferLen,
                                                    const char * pcCommandString );

static BaseType_t prvPrintLogCommand( char * pcWriteBuffer,
                                                    size_t xWriteBufferLen,
                                                    const char * pcCommandString );

/* Structure that defines the "task-stats" command line command.  This generates
 * a table that gives information on each task in the system. */
static const CLI_Command_Definition_t xTaskStats =
{
    "task-stats",        /* The command string to type. */
    "\r\ntask-stats:\r\n\tDisplays a table showing the state of each FreeRTOS task\r\n",
    prvTaskStatsCommand, /* The function to run. */
    0                    /* No parameters are expected. */
};

/* Structure that defines the "echo_3_parameters" command line command.  This
 * takes exactly three parameters that the command simply echos back one at a
 * time. */
static const CLI_Command_Definition_t xThreeParameterEcho =
{
    "echo-3-parameters",
    "\r\necho-3-parameters <param1> <param2> <param3>:\r\n\tExpects three parameters, echos each in turn\r\n",
    prvThreeParameterEchoCommand, /* The function to run. */
    3                             /* Three parameters are expected, which can take any value. */
};

/* Structure that defines the "echo_parameters" command line command.  This
 * takes a variable number of parameters that the command simply echos back one at
 * a time. */
static const CLI_Command_Definition_t xParameterEcho =
{
    "echo-parameters",
    "\r\necho-parameters <...>:\r\n\tTake variable number of parameters, echos each in turn\r\n",
    prvParameterEchoCommand, /* The function to run. */
    -1                       /* The user can enter any number of commands. */
};

#if ( configGENERATE_RUN_TIME_STATS == 1 )

/* Structure that defines the "run-time-stats" command line command.   This
 * generates a table that shows how much run time each task has */
    static const CLI_Command_Definition_t xRunTimeStats =
    {
        "run-time-stats",       /* The command string to type. */
        "\r\nrun-time-stats:\r\n Displays a table showing how much processing time each FreeRTOS task has used\r\n",
        prvRunTimeStatsCommand, /* The function to run. */
        0                       /* No parameters are expected. */
    };
#endif /* configGENERATE_RUN_TIME_STATS */

#if ( configINCLUDE_QUERY_HEAP_COMMAND == 1 )
    /* Structure that defines the "query_heap" command line command. */
    static const CLI_Command_Definition_t xQueryHeap =
    {
        "query-heap",
        "\r\nquery-heap:\r\n Displays the free heap space, and minimum ever free heap space.\r\n",
        prvQueryHeapCommand, /* The function to run. */
        0                    /* The user can enter any number of commands. */
    };
#endif /* configQUERY_HEAP_COMMAND */

#if configINCLUDE_TRACE_RELATED_CLI_COMMANDS == 1

/* Structure that defines the "trace" command line command.  This takes a single
 * parameter, which can be either "start" or "stop". */
    static const CLI_Command_Definition_t xStartStopTrace =
    {
        "trace",
        "\r\ntrace [start | stop]:\r\n Starts or stops a trace recording for viewing in FreeRTOS+Trace\r\n",
        prvStartStopTraceCommand, /* The function to run. */
        1                         /* One parameter is expected.  Valid values are "start" and "stop". */
    };
#endif /* configINCLUDE_TRACE_RELATED_CLI_COMMANDS */

/* Structure that defines the "pid-params" command line command.  This
 * takes exactly three parameters that the command show or read or write pid
 * parameters. */
static const CLI_Command_Definition_t xPidParametersOps =
{
    "pid-params",
    "\r\npid-params <read/write> <kp/ki/kd> <value>:\r\n\tread/write kp/ki/kd, only write support parameter\r\n",
    prvPidParametersOperationCommand, /* The function to run. */
    -1                                /* Three parameters are expected, which can take any value. */
};

/* Structure that defines the "print-log" command line command.  This
 * takes exactly three parameters that the command show or read or write pid
 * parameters. */
static const CLI_Command_Definition_t xPrintLogModuleOps =
{
    "print-log",
    "\r\nprint-log <all/task_main/task_motor/adxl345> <on/off>:\r\n\tset print log off or on\r\n",
    prvPrintLogCommand, /* The function to run. */
    -1                  /* Three parameters are expected, which can take any value. */
};

/*-----------------------------------------------------------*/

void CLIRegisterCommands( void )
{
    /* Register all the command line commands defined immediately above. */
    FreeRTOS_CLIRegisterCommand( &xTaskStats );
    FreeRTOS_CLIRegisterCommand( &xThreeParameterEcho );
    FreeRTOS_CLIRegisterCommand( &xParameterEcho );

    #if ( configGENERATE_RUN_TIME_STATS == 1 )
    {
        FreeRTOS_CLIRegisterCommand( &xRunTimeStats );
    }
    #endif

    #if ( configINCLUDE_QUERY_HEAP_COMMAND == 1 )
    {
        FreeRTOS_CLIRegisterCommand( &xQueryHeap );
    }
    #endif

    #if ( configINCLUDE_TRACE_RELATED_CLI_COMMANDS == 1 )
    {
        FreeRTOS_CLIRegisterCommand( &xStartStopTrace );
    }
    #endif

    FreeRTOS_CLIRegisterCommand(&xPidParametersOps);
    FreeRTOS_CLIRegisterCommand(&xPrintLogModuleOps);
}
/*-----------------------------------------------------------*/

static BaseType_t prvTaskStatsCommand( char * pcWriteBuffer,
                                       size_t xWriteBufferLen,
                                       const char * pcCommandString )
{
    const char * const pcHeader = " State   Priority  Stack   #\r\n************************************************\r\n";
    BaseType_t xSpacePadding;

    /* Remove compile time warnings about unused parameters, and check the
     * write buffer is not NULL.  NOTE - for simplicity, this example assumes the
     * write buffer length is adequate, so does not check for buffer overflows. */
    ( void ) pcCommandString;
    ( void ) xWriteBufferLen;
    configASSERT( pcWriteBuffer );

    /* Generate a table of task stats. */
    strcpy( pcWriteBuffer, "Task" );
    pcWriteBuffer += strlen( pcWriteBuffer );

    /* Minus three for the null terminator and half the number of characters in
     * "Task" so the column lines up with the centre of the heading. */
    configASSERT( configMAX_TASK_NAME_LEN > 3 );

    for( xSpacePadding = strlen( "Task" ); xSpacePadding < ( configMAX_TASK_NAME_LEN - 3 ); xSpacePadding++ )
    {
        /* Add a space to align columns after the task's name. */
        *pcWriteBuffer = ' ';
        pcWriteBuffer++;

        /* Ensure always terminated. */
        *pcWriteBuffer = 0x00;
    }

    strcpy( pcWriteBuffer, pcHeader );
    vTaskList( pcWriteBuffer + strlen( pcHeader ) );

    /* There is no more data to return after this single string, so return
     * pdFALSE. */
    return pdFALSE;
}
/*-----------------------------------------------------------*/

#if ( configINCLUDE_QUERY_HEAP_COMMAND == 1 )

    static BaseType_t prvQueryHeapCommand( char * pcWriteBuffer,
                                           size_t xWriteBufferLen,
                                           const char * pcCommandString )
    {
        /* Remove compile time warnings about unused parameters, and check the
         * write buffer is not NULL.  NOTE - for simplicity, this example assumes the
         * write buffer length is adequate, so does not check for buffer overflows. */
        ( void ) pcCommandString;
        ( void ) xWriteBufferLen;
        configASSERT( pcWriteBuffer );

        snprintf( pcWriteBuffer, xWriteBufferLen, "Current free heap %d bytes, minimum ever free heap %d bytes\r\n", ( int ) xPortGetFreeHeapSize(), ( int ) xPortGetMinimumEverFreeHeapSize() );

        /* There is no more data to return after this single string, so return
         * pdFALSE. */
        return pdFALSE;
    }

#endif /* configINCLUDE_QUERY_HEAP */
/*-----------------------------------------------------------*/

#if ( configGENERATE_RUN_TIME_STATS == 1 )

    static BaseType_t prvRunTimeStatsCommand( char * pcWriteBuffer,
                                              size_t xWriteBufferLen,
                                              const char * pcCommandString )
    {
        const char * const pcHeader = "  Abs Time      % Time\r\n****************************************\r\n";
        BaseType_t xSpacePadding;

        /* Remove compile time warnings about unused parameters, and check the
         * write buffer is not NULL.  NOTE - for simplicity, this example assumes the
         * write buffer length is adequate, so does not check for buffer overflows. */
        ( void ) pcCommandString;
        ( void ) xWriteBufferLen;
        configASSERT( pcWriteBuffer );

        /* Generate a table of task stats. */
        strcpy( pcWriteBuffer, "Task" );
        pcWriteBuffer += strlen( pcWriteBuffer );

        /* Pad the string "task" with however many bytes necessary to make it the
         * length of a task name.  Minus three for the null terminator and half the
         * number of characters in	"Task" so the column lines up with the centre of
         * the heading. */
        for( xSpacePadding = strlen( "Task" ); xSpacePadding < ( configMAX_TASK_NAME_LEN - 3 ); xSpacePadding++ )
        {
            /* Add a space to align columns after the task's name. */
            *pcWriteBuffer = ' ';
            pcWriteBuffer++;

            /* Ensure always terminated. */
            *pcWriteBuffer = 0x00;
        }

        strcpy( pcWriteBuffer, pcHeader );
        vTaskGetRunTimeStats( pcWriteBuffer + strlen( pcHeader ) );

        /* There is no more data to return after this single string, so return
         * pdFALSE. */
        return pdFALSE;
    }

#endif /* configGENERATE_RUN_TIME_STATS */
/*-----------------------------------------------------------*/

static BaseType_t prvThreeParameterEchoCommand( char * pcWriteBuffer,
                                                size_t xWriteBufferLen,
                                                const char * pcCommandString )
{
    const char * pcParameter;
    BaseType_t xParameterStringLength, xReturn;
    static UBaseType_t uxParameterNumber = 0;

    /* Remove compile time warnings about unused parameters, and check the
     * write buffer is not NULL.  NOTE - for simplicity, this example assumes the
     * write buffer length is adequate, so does not check for buffer overflows. */
    ( void ) pcCommandString;
    ( void ) xWriteBufferLen;
    configASSERT( pcWriteBuffer );

    if( uxParameterNumber == 0 )
    {
        /* The first time the function is called after the command has been
         * entered just a header string is returned. */
        snprintf( pcWriteBuffer, xWriteBufferLen, "The three parameters were:\r\n" );

        /* Next time the function is called the first parameter will be echoed
         * back. */
        uxParameterNumber = 1U;

        /* There is more data to be returned as no parameters have been echoed
         * back yet. */
        xReturn = pdPASS;
    }
    else
    {
        /* Obtain the parameter string. */
        pcParameter = FreeRTOS_CLIGetParameter
                      (
            pcCommandString,        /* The command string itself. */
            uxParameterNumber,      /* Return the next parameter. */
            &xParameterStringLength /* Store the parameter string length. */
                      );

        /* Sanity check something was returned. */
        configASSERT( pcParameter );

        /* Return the parameter string. */
        memset( pcWriteBuffer, 0x00, xWriteBufferLen );
        snprintf( pcWriteBuffer, xWriteBufferLen, "%d: ", ( int ) uxParameterNumber );
        strncat( pcWriteBuffer, pcParameter, ( size_t ) (xParameterStringLength + 1) );
        strncat( pcWriteBuffer, "\r\n", strlen( "\r\n" ) + 1 );

        /* If this is the last of the three parameters then there are no more
         * strings to return after this one. */
        if( uxParameterNumber == 3U )
        {
            /* If this is the last of the three parameters then there are no more
             * strings to return after this one. */
            xReturn = pdFALSE;
            uxParameterNumber = 0;
        }
        else
        {
            /* There are more parameters to return after this one. */
            xReturn = pdTRUE;
            uxParameterNumber++;
        }
    }

    return xReturn;
}
/*-----------------------------------------------------------*/

static BaseType_t prvParameterEchoCommand( char * pcWriteBuffer,
                                           size_t xWriteBufferLen,
                                           const char * pcCommandString )
{
    const char * pcParameter;
    BaseType_t xParameterStringLength, xReturn;
    static UBaseType_t uxParameterNumber = 0;

    /* Remove compile time warnings about unused parameters, and check the
     * write buffer is not NULL.  NOTE - for simplicity, this example assumes the
     * write buffer length is adequate, so does not check for buffer overflows. */
    ( void ) pcCommandString;
    ( void ) xWriteBufferLen;
    configASSERT( pcWriteBuffer );

    if( uxParameterNumber == 0 )
    {
        /* The first time the function is called after the command has been
         * entered just a header string is returned. */
        snprintf( pcWriteBuffer, xWriteBufferLen, "The parameters were:\r\n" );

        /* Next time the function is called the first parameter will be echoed
         * back. */
        uxParameterNumber = 1U;

        /* There is more data to be returned as no parameters have been echoed
         * back yet. */
        xReturn = pdPASS;
    }
    else
    {
        /* Obtain the parameter string. */
        pcParameter = FreeRTOS_CLIGetParameter
                      (
            pcCommandString,        /* The command string itself. */
            uxParameterNumber,      /* Return the next parameter. */
            &xParameterStringLength /* Store the parameter string length. */
                      );

        if( pcParameter != NULL )
        {
            /* Return the parameter string. */
            memset( pcWriteBuffer, 0x00, xWriteBufferLen );
            snprintf( pcWriteBuffer, xWriteBufferLen, "%d: ", ( int ) uxParameterNumber );
            strncat( pcWriteBuffer, ( char * ) pcParameter, ( size_t ) (xParameterStringLength + 1) );
            strncat( pcWriteBuffer, "\r\n", strlen( "\r\n" ) + 1 );

            /* There might be more parameters to return after this one. */
            xReturn = pdTRUE;
            uxParameterNumber++;
        }
        else
        {
            /* No more parameters were found.  Make sure the write buffer does
             * not contain a valid string. */
            pcWriteBuffer[ 0 ] = 0x00;

            /* No more data to return. */
            xReturn = pdFALSE;

            /* Start over the next time this command is executed. */
            uxParameterNumber = 0;
        }
    }

    return xReturn;
}
/*-----------------------------------------------------------*/

#if configINCLUDE_TRACE_RELATED_CLI_COMMANDS == 1

    static BaseType_t prvStartStopTraceCommand( char * pcWriteBuffer,
                                                size_t xWriteBufferLen,
                                                const char * pcCommandString )
    {
        const char * pcParameter;
        BaseType_t lParameterStringLength;

        /* Remove compile time warnings about unused parameters, and check the
         * write buffer is not NULL.  NOTE - for simplicity, this example assumes the
         * write buffer length is adequate, so does not check for buffer overflows. */
        ( void ) pcCommandString;
        ( void ) xWriteBufferLen;
        configASSERT( pcWriteBuffer );

        /* Obtain the parameter string. */
        pcParameter = FreeRTOS_CLIGetParameter
                      (
            pcCommandString,        /* The command string itself. */
            1,                      /* Return the first parameter. */
            &lParameterStringLength /* Store the parameter string length. */
                      );

        /* Sanity check something was returned. */
        configASSERT( pcParameter );

        /* There are only two valid parameter values. */
        if( strncmp( pcParameter, "start", strlen( "start" ) ) == 0 )
        {
            /* Start or restart the trace. */
            vTraceStop();
            vTraceClear();
            vTraceStart();

            snprintf( pcWriteBuffer, xWriteBufferLen, "Trace recording (re)started.\r\n" );
        }
        else if( strncmp( pcParameter, "stop", strlen( "stop" ) ) == 0 )
        {
            /* End the trace, if one is running. */
            vTraceStop();
            snprintf( pcWriteBuffer, xWriteBufferLen, "Stopping trace recording.\r\n" );
        }
        else
        {
            snprintf( pcWriteBuffer, xWriteBufferLen, "Valid parameters are 'start' and 'stop'.\r\n" );
        }

        /* There is no more data to return after this single string, so return
         * pdFALSE. */
        return pdFALSE;
    }

#endif /* configINCLUDE_TRACE_RELATED_CLI_COMMANDS */
/*-----------------------------------------------------------*/

static float stringToFloat(const char *s)
{
    float value = 0.0f;
    float decVal = 0.1f;
    uint8_t dotFlag = 0;
    char *p = (char *)s;

    while(*p != '\0') {
        if (!dotFlag && (*p >= '0') && (*p <= '9'))
            value = (float)((value * 10) + (*p - '0'));
        else if (!dotFlag && (*p == '.'))
            dotFlag = 1;
        else if (dotFlag && (*p >= '0') && (*p <= '9')) {
            value = (float)(value + ((*p - '0') * decVal));
            decVal *= 0.1f;
        } else
            break;
        p++;
    }

    return value;
}

static BaseType_t prvPidParametersOperationCommand( char * pcWriteBuffer,
                                                    size_t xWriteBufferLen,
                                                    const char * pcCommandString )
{
    const char * pcParameter;
    BaseType_t xParameterStringLength, xReturn;
    static UBaseType_t uxParameterNumber = 0;
    static uint8_t writeFlag = PID_CLEAR_FLAG;
    static float *pPidKey = NULL;

    /* Remove compile time warnings about unused parameters, and check the
     * write buffer is not NULL.  NOTE - for simplicity, this example assumes the
     * write buffer length is adequate, so does not check for buffer overflows. */
    ( void ) pcCommandString;
    ( void ) xWriteBufferLen;
    configASSERT( pcWriteBuffer );
    /* Return the parameter string. */
    memset( pcWriteBuffer, 0x00, xWriteBufferLen );

    if( uxParameterNumber == 0 )
    {
        /* Next time the function is called the first parameter will be echoed
         * back. */
        uxParameterNumber = 1U;

        /* There is more data to be returned as no parameters have been echoed
         * back yet. */
        xReturn = pdPASS;
    }
    else
    {
        /* Obtain the parameter string. */
        pcParameter = FreeRTOS_CLIGetParameter
                      (
            pcCommandString,        /* The command string itself. */
            uxParameterNumber,      /* Return the next parameter. */
            &xParameterStringLength /* Store the parameter string length. */
                      );

        if( pcParameter != NULL )
        {
            if (!strncasecmp(pcParameter, "read", strlen("read"))) {
                snprintf(pcWriteBuffer, xWriteBufferLen,
                        "PID Params Show:\r\n\tKp=%d.%02d, Ki=%d.%02d, Kd=%d.%02d\r\n",
                    (int)ppid->Kp, ((int)(ppid->Kp * 100)) % 100,
                    (int)ppid->Ki, ((int)(ppid->Ki * 100)) % 100,
                    (int)ppid->Kd, ((int)(ppid->Kd * 100)) % 100);
            } else if (!strncasecmp(pcParameter, "write", strlen("write"))) {
                writeFlag = PID_WRITE_FLAG;
                pPidKey = NULL;
            } else if (!strncasecmp(pcParameter, "kp", strlen("kp")) && (writeFlag & PID_WRITE_FLAG)) {
                pPidKey = &ppid->Kp;
            } else if (!strncasecmp(pcParameter, "ki", strlen("ki")) && (writeFlag & PID_WRITE_FLAG)) {
                pPidKey = &ppid->Ki;
            } else if (!strncasecmp(pcParameter, "kd", strlen("kd")) && (writeFlag & PID_WRITE_FLAG)) {
                pPidKey = &ppid->Kd;
            } else if (pPidKey && (writeFlag & PID_WRITE_FLAG)) {
                *pPidKey = stringToFloat(pcParameter);
                writeFlag = PID_CLEAR_FLAG;
                pPidKey = NULL;
            }

            /* There might be more parameters to return after this one. */
            xReturn = pdTRUE;
            uxParameterNumber++;
        }
        else
        {
            /* No more parameters were found.  Make sure the write buffer does
             * not contain a valid string. */
            pcWriteBuffer[ 0 ] = 0x00;

            /* No more data to return. */
            xReturn = pdFALSE;

            /* Start over the next time this command is executed. */
            uxParameterNumber = 0;
        }
    }

    return xReturn;
}
/*-----------------------------------------------------------*/

static BaseType_t prvPrintLogCommand( char * pcWriteBuffer,
                                                size_t xWriteBufferLen,
                                                const char * pcCommandString )
{
    const char *pcParameter;
    BaseType_t xParameterStringLength, xReturn;
    static UBaseType_t uxParameterNumber = 0;
    static portSTACK_TYPE moduleSelect = 0;
    const char *pPcParameter = NULL;
    portCHAR i;

    /* Remove compile time warnings about unused parameters, and check the
     * write buffer is not NULL.  NOTE - for simplicity, this example assumes the
     * write buffer length is adequate, so does not check for buffer overflows. */
    ( void ) pcCommandString;
    ( void ) xWriteBufferLen;
    configASSERT( pcWriteBuffer );
    /* Return the parameter string. */
    memset( pcWriteBuffer, 0x00, xWriteBufferLen );

    if( uxParameterNumber == 0 )
    {
        /* Next time the function is called the first parameter will be echoed
         * back. */
        uxParameterNumber = 1U;

        /* There is more data to be returned as no parameters have been echoed
         * back yet. */
        xReturn = pdPASS;
    }
    else
    {
        /* Obtain the parameter string. */
        pcParameter = FreeRTOS_CLIGetParameter
                      (
            pcCommandString,        /* The command string itself. */
            uxParameterNumber,      /* Return the next parameter. */
            &xParameterStringLength /* Store the parameter string length. */
                      );

        if (moduleSelect) {
            if (!pcParameter) {     /* show module status */
                snprintf(pcWriteBuffer, xWriteBufferLen, "Status Of Module:\r\n\t%s: %s\r\n",
                        pPcParameter, (moduleSelect & print_flag) ? "ON" : "OFF");
            } else if(!strncasecmp(pcParameter, "on", strlen("on"))) {
                print_flag |= moduleSelect;
            } else if (!strncasecmp(pcParameter, "off", strlen("off"))) {
                print_flag &= ~moduleSelect;
            }
            moduleSelect = 0x0;
        }

        if (!strncasecmp(pcParameter, "all", strlen("all"))) {
            moduleSelect = PRINT_MODULE_ALL;
            pPcParameter = pcParameter;
        } else if (!strncasecmp(pcParameter, "task_main", strlen("task_main"))) {
            moduleSelect = PRINT_MODULE_TASK_MAIN;
            pPcParameter = pcParameter;
        } else if (!strncasecmp(pcParameter, "task_motor", strlen("task_motor"))) {
            moduleSelect = PRINT_MODULE_TASK_MOTOR;
            pPcParameter = pcParameter;
        } else if (!strncasecmp(pcParameter, "adxl345", strlen("adxl345"))) {
            moduleSelect = PRINT_MODULE_ADXL345;
            pPcParameter = pcParameter;
        } else {
            moduleSelect = 0x0;
        }

        /* If this is the last of the three parameters then there are no more
         * strings to return after this one. */
        if( uxParameterNumber == 2U )
        {
            /* If this is the last of the three parameters then there are no more
             * strings to return after this one. */
            xReturn = pdFALSE;
            uxParameterNumber = 0;
        }
        else
        {
            /* There are more parameters to return after this one. */
            xReturn = pdTRUE;
            uxParameterNumber++;
        }
    }

    return xReturn;
}

