// assumes that the drive is not frozen
#include <string>
#include <iostream>

// returns 0 on success, 1 on failure.
int nvme_sanitize(std::string drive) {
    std::string command;
    int counter = 0;
    command = "nvme reset " + drive;
    if (not system(command.c_str())) {
        std::cout << "unfreeze unsuccessfull" << std::endl;
    }

    command = "nvme format " + drive + " --ses=2 -- force";
    if (not system(command.c_str())) {
        std::cout << "crypto erase successfull" << std::endl;
    }

    command = "nvme format " + drive + " --ses=1";
    if (not system(command.c_str())) {
        std::cout << "secure erase successfull" << std::endl;
    }
    return !counter;
}