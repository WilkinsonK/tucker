#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include <iostream>
#include <string>

namespace tucker
{
    namespace ioutil
    {
        // Character codes which invoke some kind of
        // action.
        enum ControlChar : u_int32_t
        {
            BACKSPACE = 127,
            RETURN = 10
        };

        // Capture character code from user input.
        int getChar()
        {
            int chCode; struct termios oTerm, nTerm;

            tcgetattr(STDIN_FILENO, &oTerm);
            nTerm = oTerm;
            nTerm.c_lflag &= ~(ICANON | ECHO);
            tcsetattr(STDIN_FILENO, TCSANOW, &nTerm);

            chCode = getchar();
            tcsetattr(STDIN_FILENO, TCSANOW, &oTerm);
            return chCode;
        }

        // Prompt the user for input, which is
        // masked, either by not revealing the input
        // to stdout or replacing input with a given
        // character.
        std::string getPassword(const char *prompt, const char repl = 0)
        {
            std::string inBuffer; unsigned char inChar;

            // Ready the input buffer. Assume that
            // another input buffer were used;
            // std::cin, another tucker::getChar or
            // some other input recipe. This prevents
            // a premature break of our capture.
            std::cout << prompt;

            while (true)
            {
                inChar = getChar();

                // Flush the stream and bail if the
                // user sends the RETURN char.
                if (inChar == ControlChar::RETURN)
                {
                    std::cout << std::endl;
                    break;
                }

                // Append user input to inBuffer. If
                // a repl (replacement) char is
                // supplied, append that char to the
                // stream.
                if (inChar != ControlChar::BACKSPACE)
                {
                    inBuffer.push_back(inChar);
                    if (repl != 0)
                        std::cout << repl;
                    continue;
                }

                // If user sends the BACKSPACE char,
                // remove last entered char from
                // buffer and remove replacement char
                // that might represent it.
                if (inBuffer.length() == 0)
                    continue;
                if (repl != 0)
                    std::cout << "\b \b";
                inBuffer.pop_back();
            }

            return inBuffer;
        }
    }
}
