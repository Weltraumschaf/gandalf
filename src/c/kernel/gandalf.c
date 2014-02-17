#include "gandalf.h"
#include "tty.h"
#include "../util/util.h"
#include "../libc/include/stdio.h"

void gandalf_prepareScreen() {
    tty_clear();
    tty_setEnableBlinkingCursor(false);
}

void gandalf_unprepareScreen() {
    tty_clear();
    tty_setEnableBlinkingCursor(true);
}

void gandalf_showBootScreen() {
    gandalf_prepareScreen();

    // From http://ascii.co.uk/art/gandalf
    println(
        "    ,                      _,-\n"
        "   (\\                  _,-','\n"
        "    \\\\              ,-\"  ,'\n"
        "     \\\\           ,'   ,'\n"
        "      \\\\        _:.----__.-.\"-._,-._\n"
        "       \\\\    .-\".:--`:::::.:.:'  )  `-.\n"
        "        \\\\   `. ::L .::::::'`-._  (  ) :\n"
        "         \\\\    \":::::::'  `-.   `-_ ) ,'\n"
        "          \\\\.._/_`:::,' `.     .  `-:\n"
        "          :\" _   \"\\\"\" `-_    .    `  `.\n"
        "           \"\\\\\"\":--\\     `-.__ ` .     `.\n"
        "             \\\\'::  \\    _-\"__`--.__ `  . `.     _,--..-\n"
        "              \\\\ ::  \\_-\":)(        \"\"-._ ` `.-''\n"
        "               \\\\`:`-\":::/ \\\\ .   .      `-.  :\n"
        "               :\\\\:::::::'  \\\\     `    .   `. :\n"
        "                :\\\\:':':'  . \\\\           `,  : :\n"
        "                : \\\\     .    \\\\      .       `. :       ,-\n"
        "               __`:\\\\      .   \\\\ .   `  ,'    ,: :   ,-'\n"
        "        _,---\"\"  :  \\\\ '        \\\\  .          :-\"  ,'\n"
        "    ,-\"\"        :    \\\\:  .  :   \\\\  `  '     ,'   /\n"
        "   '            :  :  \\       .   \\\\   .   _,'  ,-'\n"
        "               :  .   '       :   :`   `,-' ,--'\n"
        "                :     :   :      ,'-._,' ,-'\n"
        "                _:     :        :8:  ,--'\n"
        "               :dd`-._,'-._.__-\"\"' ,'");

//    gandalf_unprepareScreen();
}

void gandalf_showWelcomeScreen() {
    gandalf_prepareScreen();

    // From http://ascii.co.uk/art/gandalf
    println(
        "  .....  $   $\n"
        "   : :  .'  .'\n"
        "   : :.'  .'\n"
        "   : :  .'\n"
        "   : :.'\n"
        "   : :\n"
        "   : :\n"
        "   : :\n"
        "  '''''");

    gandalf_unprepareScreen();
}
