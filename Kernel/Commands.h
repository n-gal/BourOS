#ifndef COMMANDS_H
#define COMMANDS_H

#define INVALID_COMMAND "Is not a recognised command\n"
#define INVALID_ARGUMENTS "Invalid command arguments\n"

void CMHelp(char* command, char* args);
void CMClear(char* command, char* args);
void CMColor(char* command, char* args);
void CMSetLayout(char* command, char* args);

#endif