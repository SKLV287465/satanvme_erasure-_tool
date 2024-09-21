// first try cryptographic erase

/**
 * Notes:
 * - Need to test code
 * - nsid and opcode is dubious, chatgpt generated.
 * - testcase with multiple partitions, need to see if all partitions have been deleted.
*/
#include <iostream>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/nvme_ioctl.h>
int crypto_erase(std::string path) {
    int fd = open(path.c_str(), O_RDONLY);
    // if fd < 0, then throw error, no such file.
    struct nvme_passthru_cmd cmd{};
    cmd.opcode = 0x80; // NVMe Format NVM command opcode
    cmd.nsid = 1; // Namespace ID, typically 1 for most consumer drives
    cmd.cdw10 = 0x4; // Secure Erase Action: 4 corresponds to cryptographic erase
    
    if (ioctl(fd, NVME_IOCTL_ADMIN_CMD, &cmd) < 0) {
        std::cerr << "Failed to send Format NVM command" << std::endl;
        close(fd);
        return false;
    }
    std::cout << "Cryptographic erase completed successfully on " << path << std::endl;
    return true;
}
// Then try User data erase command
int user_data_erase(std::string path) {
    int fd = open(path.c_str(), O_RDONLY);
    // if fd < 0 then throw error no such file.

    struct nvme_passthru_cmd cmd{};
    cmd.opcode = 0x80; // NVMe Format NVM command opcode
    cmd.nsid = 1; // Namespace ID, typically 1 for most consumer drives
    cmd.cdw10 = 0x4; // Secure Erase Action: 4 corresponds to cryptographic erase

    if (ioctl(fd, NVME_IOCTL_ADMIN_CMD, &cmd) < 0) {
        std::cerr << "Failed to send Format NVM command" << std::endl;
        close(fd);
        return false;
    }
    std::cout << "Cryptographic erase completed successfully on " << path << std::endl;
    return true;
}