#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <sstream>
#include <string.h>


/**
 * Function to return all non-removable drives in the system
 * 0 index for ata hdds
 * 1 index for ata ssds
 * 2 index for nvme ssds
*/

std::vector<std::vector<std::string>> get_lsblk_output() {
    auto output = std::vector<std::vector<std::string>>{};
    // MOUNTPOINT not required but used in order to skip removing \n from TRAN.
    std::string command = "lsblk -d -o NAME,ROTA,TRAN,MOUNTPOINT";
    auto ret = popen(command.c_str(), "r");
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), ret) != NULL) {
        std::stringstream ss(buffer);
        std::string s;
        auto line = std::vector<std::string>{};
        while(std::getline(ss, s, ' ')) {
            line.push_back(s);
        }
        output.push_back(line);

    }
    return output;
}

std::array<std::vector<std::string>, 3> list_drives() {
    auto drives = std::array<std::vector<std::string>, 3>{};
    
    auto unparsed_drive_info = get_lsblk_output();

    
    for (int i = 1; i < unparsed_drive_info.size(); i++) {
        
        auto const line = unparsed_drive_info[i];
        if (line[1] == "1") {
            drives[0].push_back("/dev/" + line[0]);
        } else if (line[6] == "sata") {
            drives[1].push_back("/dev/" + line[0]);
        } else if (line[6] == "nvme"){
            drives[2].push_back("/dev/" + line[0]);
        }
    }

    return drives;
} 

// int main() {
//     auto ret = list_drives();
//     std::cout << ret[1][0] << std::endl;
// }

