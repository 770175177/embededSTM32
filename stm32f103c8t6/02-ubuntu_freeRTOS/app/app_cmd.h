#ifndef __APP_CMD__
#define __APP_CMD__

#define EMBEDDED_CLI_IMPL
#include "embedded_cli.h"

// 164 bytes is minimum size for this params on Arduino Nano
#define CLI_BUFFER_SIZE     166
#define CLI_RX_BUFFER_SIZE  16
#define CLI_CMD_BUFFER_SIZE 32
#define CLI_HISTORY_SIZE    32
#define CLI_BINDING_COUNT   16

void embeddedCliBing(EmbeddedCli *cli);
void onCommand(EmbeddedCli *embeddedCli, CliCommand *command);
void writeChar(EmbeddedCli *embeddedCli, char c);
void onHello(EmbeddedCli *cli, char *args, void *context);
void onLed(EmbeddedCli *cli, char *args, void *context);
void onAdc(EmbeddedCli *cli, char *args, void *context);

void cmd_setup(void);
void embeddedCliLoop(void);

#endif	/* end __APP_CMD__ */
