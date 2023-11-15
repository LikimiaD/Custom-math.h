# Custom math.h
## About the Project

This project presents a custom implementation of mathematical functions similar to those in the standard math.h library in C. It aims to replicate the functionality of standard math functions while adhering to strict precision and testing requirements.
### **Key Features**

* Custom implementations of various mathematical functions.
* No use of the standard math.h library except in unit tests.
* Strict adherence to the logic of the standard library in terms of checks, memory management, and behavior in exceptional cases.
* Comprehensive unit tests comparing custom functions with their standard library counterparts.
* Coverage of at least 80% of each function through unit tests.
* Generation of a gcov report in HTML format for test coverage analysis.
* Makefile provided for easy compilation and testing.
* Precision up to 16 significant figures and a maximum of 6 decimal places for fractional parts.

### **Installation and Usage**

1. **Cloning the Repository:**

    Clone the repository to your local machine using:
    ```bash
    git clone [repository-url]
    ```
2. **Compilation:**

    Navigate to the project directory and run the following command to compile the library and tests:

    ```bash
    make all
    ```
3. **Running Tests:**

    To execute the unit tests and validate the implementation, use:

    ```bash
    make test
    ```
4. **Generating gcov Report:**

    For a detailed test coverage report, run:

    ```bash
    make gcov_report
    ```

    This will generate an HTML report which can be viewed in a web browser.

5. **Cleaning Up:**

    To clean up the compiled files, you can use:

    ```bash
        make clean
    ```

## **File Structure**

```bash
.
├── Makefile
├── custom_math.c         # Source file for custom math functions
├── custom_math.h         # Header file with function declarations
└── s21_test_math.c       # Unit tests for custom math functions
```
## Contributing

Contributions, issues, and feature requests are welcome. Feel free to check the issues page if you want to contribute.

## License

This project is licensed under the MIT License.

## Contact

LikimiaD - likimiad@gmail.com