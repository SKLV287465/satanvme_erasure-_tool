// assumes that the drive is not frozen
#include <string>
#include <iostream>
/**
 * runs secure erase or erase on drive.
 * return -1 on failure
 * return 0 for success.
*/
// return -1 on failure
int ata_sanitize(std::string drive) {
    std::string command;
    
    command = "hdparm -w " + drive;
    if (not system(command.c_str())) {
        std::cout << "reset failed" << std::endl;
        return -1;
    } 

    command = "hdparm --user-master u --security-set-pass password " + drive;
    if (not system(command.c_str())) {
        std::cout << "password set failed" << std::endl;
        return -1;
    }

    // i need to do some testing to see which code is returned on success and failure.
    command = "hdparm --user-master u --security-erase-enhanced password " + drive;
    if (not system(command.c_str())) {
        std::cout << "secure erase completed" << std::endl;
        return 0;
    }

    command = "hdparm --user-master u --security-erase password " + drive;
    return system(command.c_str());
    
}

// only do this for hdd's useless for ssd's
int dd(std::string hdd) {
    std::string command = "dd if=/dev/zero of=" + hdd + " bs=1M status=progress";
    return system(command.c_str());
}