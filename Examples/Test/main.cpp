#include <iostream>

#include "Momentus.h"

int main() {
    DateTime dt;

    std::string formattedDate = dt.toString("%Y-%m-%d %H:%M:%S");
    std::cout << "Current Date and Time: " << formattedDate << std::endl;

    dt.doEvery(DateTime::Period::Second, 2, []()
    {
        std::cout << "Executing action every 2 seconds..." << std::endl;
    });

    bool running = true;

    dt.doAfter(DateTime::Period::Second, 10, [&]()
    {
        std::cout << "\n\nMain Thread has been stopped!\n\n";
        running = false;
    });

    while (running)
    {
        std::cout << "---------------------------------\n";
        std::cout << "Main Thread is not blocked, see!\n";
        std::cout << "---------------------------------\n";

        std::this_thread::sleep_for(std::chrono::seconds(4));
    }

    return 0;
}
