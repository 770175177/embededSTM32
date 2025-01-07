/**
 * Simple example of using embedded-cli in arduino.
 * To compile copy embedded-cli.h (single header version) to sketch directory.
 *
 * With specified settings:
 * 32 bytes for cmd buffer, 16 for RX buffer,
 * 32 bytes for history,
 * 3 binding functions and no dynamic allocation
 * Total size of firmware is 7538 bytes, 654 bytes of RAM are used.
 * Not everything is used by library, some memory is used by Serial, for
 * example.
 * Most of RAM space is taken up by char arrays so size can be reduced if
 * messages are discarded.
 * For example, by removing code inside onHelp and onUnknown functions inside
 * library (and replacing help strings in bindings by nullptr's) size of FW is
 * reduced by 688 bytes of ROM and 190 bytes of RAM. Total usage is then
 * 6850 of ROM and 464 of RAM.
 */
#include <stddef.h>
#include "usart.h"
#include "app_cmd.h"

EmbeddedCli *cli;
CLI_UINT cliBuffer[BYTES_TO_CLI_UINTS(CLI_BUFFER_SIZE)];

void cmd_setup(void)
{
    EmbeddedCliConfig *config = embeddedCliDefaultConfig();

    config->cliBuffer = cliBuffer;
    config->cliBufferSize = CLI_BUFFER_SIZE;
    config->rxBufferSize = CLI_RX_BUFFER_SIZE;
    config->cmdBufferSize = CLI_CMD_BUFFER_SIZE;
    config->historyBufferSize = CLI_HISTORY_SIZE;
    config->maxBindingCount = CLI_BINDING_COUNT;
    cli = embeddedCliNew(config);

    if (cli == NULL) {
        usart_printf("Cli was not created. Check sizes!");
        return;
    }
    usart_printf("Cli has started. Enter your commands.");

    embeddedCliBing(cli);

    cli->onCommand = onCommand;
    cli->writeChar = writeChar;
}

void embeddedCliBing(EmbeddedCli *cli)
{
    struct CliCommandBinding bing[] = {
        {
            "get-led",
            "Get led status",
            false,
            NULL,
            onLed
        }, {
            "get-adc",
            "Read adc value",
            false,
            NULL,
            onAdc
        }, {
            "hello",
            "Print hello message",
            true,
            (void *) "World",
            onHello
        }
    };

    for (int i = 0; i < (sizeof(bing) / sizeof(bing[0])); i++)
        embeddedCliAddBinding(cli, bing[i]);
}

void embeddedCliLoop(void)
{
    char c;

    if (cli == NULL)
        return;

    while (usart_getc(&c)) {
        embeddedCliReceiveChar(cli, c);
    }

    embeddedCliProcess(cli);
}

void onCommand(EmbeddedCli *embeddedCli, CliCommand *command) {
    usart_printf("Received command:");
    usart_printf("%s", command->name);
    embeddedCliTokenizeArgs(command->args);
    for (int i = 1; i <= embeddedCliGetTokenCount(command->args); ++i) {
        usart_printf("arg ");
        usart_printf("%c", '0' + i);
        usart_printf(": ");
        usart_printf(embeddedCliGetToken(command->args, i));
    }
}

void onHello(EmbeddedCli *cli, char *args, void *context) {
    usart_printf("Hello ");
    if (embeddedCliGetTokenCount(args) == 0)
        usart_printf((const char *) context);
    else
        usart_printf(embeddedCliGetToken(args, 1));
    usart_printf("\r\n");
}

void onLed(EmbeddedCli *cli, char *args, void *context) {
    usart_printf("LED: ");
    usart_printf("%d", 256);
    usart_printf("\r\n");
}

void onAdc(EmbeddedCli *cli, char *args, void *context) {
    usart_printf("ADC: ");
    usart_printf("%d", 1024);
    usart_printf("\r\n");
}

void writeChar(EmbeddedCli *embeddedCli, char c) {
    usart_printf("%c", c);
}
