#include <string>
#include <iostream>

int main(int argc, char* argv[]) {
    std::string command;

    // command = "sudo nvme format " + std::string{argv[1]} + " --ses=1 --force";
    command = "sudo hdparm -I /dev/sda";
    std::cout << system(command.c_str()) << std::endl;
}