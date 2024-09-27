# So you want to contribute to my little project...

## Bug Reports

Please submit an [issue](https://github.com/raging-loon/Simula-24/issues).

## Development

C++20 and CMake the primary tools in this project.

### Pull Requests
Steps for submitting a pull request
1. Fork the Repo
2. Make a new branch
3. Make your changes + tests
4. Make sure your changes actually work
5. Run the unit test build
6. Submit a pull request. Be clear with your description.
7. Wait
7. Wait some more
8. Pat yourself on the back for making an OSS contribution. Linus would be proud.

### General

- 4 spaces - make sure your editor replaces tabs with spaces
- Allman Style Bracing. Each brace should have its own line. 
    Not as picky with namespace declarations but try to keep it Allman.
- Header guards should be the full path to the file from the /simula24 directory.
    -   E.g. `/simula24/core/stl/array.h` would have the header guard `CORE_STL_ARRAY_H_`
- *Absolutely no explicit multiple inheritance or I will slash your tires*
    -  Multiple inheritence causes many many more problems than it solves. 
    -  Consider using composition or re-thinking your design instead
- NO C++ STL. Except for `<type_traits>`
    - Use the Simula Template Library instead (`core/stl`)
    - Exceptions can be made until an appropriate template class is made for what ever you are doing
- No exceptions
    - Favor return codes/booleans instead

### Documentation
We are using Doxygen to generate documentation. 
Make sure every 
- Class
- Function
- Variable
- Macro
Is appropriately documented. Exceptions are those that are inherently self-documenting

Use '@' instead of '\' for doxygen commands.

### Unit Testing

For Visual Studio, change the build to 'x64-unit-test' and run it.

For everything else, add the `-DENABLE_TESTS=YES` to your CMake command when building.

