// #include <crystal_constructor/crystal_model/crystal_model.h>
#include <iostream>
#include <string>
#include <crystal_constructor/crystal_model/crystal_model.h>

enum UserCommand {
    PRINT,
    HELP,
    EXIT,
    INVALID
};

UserCommand userCommandStringToEnum(std::string const& usrCmdStr){
    if (usrCmdStr == "print") return UserCommand::PRINT;
    if (usrCmdStr == "help") return UserCommand::HELP;
    if (usrCmdStr == "exit") return UserCommand::EXIT;

    return UserCommand::INVALID;   
}

int main(){
    std::string user_command;
    bool end_program = false;

    crystal_constructor::crystal_model::CrystalModel crystal_model{};

    while (!end_program)
    {
        std::cout << "Enter a command (enter help for options):\n";
        std::cin >> user_command;
        std::cout << '\n';

        switch (userCommandStringToEnum(user_command))
        {
        case UserCommand::PRINT:
            crystal_model.PrintPOSCAR();
            break;

        case UserCommand::HELP:
            std::cout << "print - Prints crystal model state\n";
            std::cout << "help - Shows command options\n";
            std::cout << "exit - Ends program\n\n";
            break;

        case UserCommand::EXIT:
            end_program = true;
            break;

        case UserCommand::INVALID:
        default:
            std::cout << "Your entry was invalid.\n\n";
            break;
        }
    }
    
    std::cout << "Exiting...\n";

    return 0;
}