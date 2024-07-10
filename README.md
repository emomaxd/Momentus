Momentus
========

Momentus is a C++ library for handling date and time operations, including performing periodic actions and delayed actions without blocking the main thread. It provides functionality to manipulate date and time values and execute functions at specified intervals.

Features
--------

- Perform actions while not blocking the main thread 
- Date and time manipulation (add days, months, years)
- Retrieve date components (day of week, day of month, month, year)
- Format date and time to string
- Perform actions periodically at specified intervals
- Perform actions after a specified delay

Installation
------------

1. Clone the repository:
    ```sh
    git clone https://github.com/EmomaxD/Momentus.git
    ```

2. Include the library in your project:
    - Include "Momentus.h" files to your project.

Usage
-----

```cpp
#include "Momentus.h"

int main() {
    DateTime dt; // Initialize with current date and time

    DateTime specificDate(2023, 7, 10, 15, 30, 0); // Initialize with specific date and time


    dt.addDays(5); // Add 5 days
    dt.addMonths(2); // Add 2 months
    dt.addYears(1); // Add 1 year


    int dayOfWeek = dt.getDayOfWeek();
    int dayOfMonth = dt.getDayOfMonth();
    int month = dt.getMonth();
    int year = dt.getYear();


    std::string formattedDate = dt.toString("%Y-%m-%d %H:%M:%S");
    std::cout << "Current Date and Time: " << formattedDate << std::endl;

    
    // Perform action every 2 seconds
    dt.doEvery(DateTime::Period::Second, 2, []() {
        std::cout << "Executing action every 2 seconds..." << std::endl;
    });

    
    // Perform action after 5 seconds
    dt.doAfter(DateTime::Period::Second, 5, []() {
        std::cout << "Executing action after 5 seconds..." << std::endl;
    });

    return 0;
}
```