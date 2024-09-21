#include "./nist_purge/ata/ata_sanitize.h"
#include "./nist_purge/nvme/nvme_sanitize.h"
#include "fetch_drives.h"
#include <iostream>

int main() {
    auto drives = list_drives();

    // do all hard drives
    for (auto const& hdd : drives[0]) {
        if(ata_sanitize(hdd)) {
            dd(hdd);
        }
    }

    // do all sata ssds
    for (auto const& sssd : drives[1]) {
        if (ata_sanitize(sssd)) std::cout << sssd + "could not be erased" << std::endl;
    }

    // do all nvme ssds
    for (auto const& nvme : drives[2]) {
        if (nvme_sanitize(nvme)) std::cout << nvme + "could not be erased" << std::endl;
    }
}