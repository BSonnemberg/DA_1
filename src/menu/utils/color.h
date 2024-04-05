#pragma once

// foreground only
// 8 bit colors
#define BLACK "\x1B[0;30m"
#define RED "\x1B[0;31m"
#define GREEN "\x1B[0;32m"
#define YELLOW "\x1B[0;33m"
#define BLUE "\x1B[0;34m"
#define PURPLE "\x1B[0;35m"
#define CYAN "\x1B[0;36m"
#define WHITE "\x1B[0;37m"

// 16 bit support
#define LIGHT_BLACK "\x1B[0;90m"
#define LIGHT_RED "\x1B[0;91m"
#define LIGHT_GREEN "\x1B[0;92m"
#define LIGHT_YELLOW "\x1B[0;93m"
#define LIGHT_BLUE "\x1B[0;94m"
#define LIGHT_PURPLE "\x1B[0;95m"
#define LIGHT_CYAN "\x1B[0;96m"
#define LIGHT_WHITE "\x1B[0;97m"

#define RESET "\x1B[0m"
#define BOLD "\x1B[1m"
#define ITALIC "\x1B[3m"
#define UNDERLINED "\x1B[4m"
#define REVERSE "\x1B[7m"
// not supported in macOS
#define STRIKETHOUGH "\x1B[9m"

/* set background/ foreground colors using a color id
 ids -> https://user-images.githubusercontent.com/995050/47952855-ecb12480-df75-11e8-89d4-ac26c50e80b9.png*/
#define BGROUND(color_id) ("\x1B[48;5;" + std::to_string(color_id) + "m")
#define FGROUND(color_id) ("\x1B[38;5;" + std::to_string(color_id) + "m")
