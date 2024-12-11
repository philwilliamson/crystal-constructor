// #include <crystal_constructor/crystal_model/crystal_model.h>
#include <iostream>
#include <string>
#include <crystal_constructor/crystal_model/crystal_model.h>

enum class UserCommand {
    CHANGE_A_HAT,
    CHANGE_B_HAT,
    CHANGE_C_HAT,
    PRINT,
    HELP,
    EXIT,
    INVALID
};

UserCommand userCommandStringToEnum(std::string const& usrCmdStr){
    if (usrCmdStr == "change_a_hat") return UserCommand::CHANGE_A_HAT;
    if (usrCmdStr == "change_b_hat") return UserCommand::CHANGE_B_HAT;
    if (usrCmdStr == "change_c_hat") return UserCommand::CHANGE_C_HAT;
    if (usrCmdStr == "print") return UserCommand::PRINT;
    if (usrCmdStr == "help") return UserCommand::HELP;
    if (usrCmdStr == "exit") return UserCommand::EXIT;

    return UserCommand::INVALID;   
}

int main(){
    std::string user_command;
    bool end_program = false;

    float user_x{};
    float user_y{};
    float user_z{};

    crystal_constructor::crystal_model::CrystalModel crystal_model{};

    while (!end_program)
    {
        std::cout << "Enter a command (enter help for options):\n";
        std::cin >> user_command;
        std::cout << '\n';

        switch (userCommandStringToEnum(user_command))
        {
        case UserCommand::CHANGE_A_HAT:
            std::cout << "Enter the x, y, and z components of the new a-hat basis vector separated by spaces (e.g. 0.2 0.6 2.3)\n";
            std::cin >> user_x >> user_y >> user_z;
            std::cout << '\n';

            crystal_model.UpdateAHat(crystal_constructor::crystal_model::Vector3{user_x, user_y, user_z});

            break;

        case UserCommand::CHANGE_B_HAT:
            std::cout << "Enter the x, y, and z components of the new b-hat basis vector separated by spaces (e.g. 0.2 0.6 2.3)\n";
            std::cin >> user_x >> user_y >> user_z;
            std::cout << '\n';

            crystal_model.UpdateBHat(crystal_constructor::crystal_model::Vector3{user_x, user_y, user_z});

            break;

        case UserCommand::CHANGE_C_HAT:
            std::cout << "Enter the x, y, and z components of the new c-hat basis vector separated by spaces (e.g. 0.2 0.6 2.3)\n";
            std::cin >> user_x >> user_y >> user_z;
            std::cout << '\n';

            crystal_model.UpdateCHat(crystal_constructor::crystal_model::Vector3{user_x, user_y, user_z});

            break;
        
        case UserCommand::PRINT:
            crystal_model.PrintPOSCAR();
            break;

        case UserCommand::HELP:
            std::cout << "change_a_hat - Update the a-hat basis vector\n";
            std::cout << "change_b_hat - Update the b-hat basis vector\n";
            std::cout << "change_c_hat - Update the c-hat basis vector\n";
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