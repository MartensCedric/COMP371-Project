# COMP371-Project
Git Repository for the project

## Windows

### Building with VisualStudio 2017

0. When installing VS2017, make sure that you include the installation of the Windows SDK version 10.0.16299.0
1. Start VisualStudio 2017, open the .sln file in `VS2017` folder.
2. In the 'Solution Explorer' click the 'Solutions and Folders' button so that you can see all the folders/files.
3. Click the `371A1.cpp` inside the `Source` folder.
4. Click the dropdown next to the green arrow at the top, make sure it has 'Current Document (371A1.cpp)' selected.
5. If you already built the project before, delete the executable `COMP371-Project/Bin/Labs-Debug`
6. Click the green arrow to build and launch the code.

NOTE: The automatic running of the executable may not work (error message contains: "Unable to start program...").
If the above steps do not result in a new window popping up to render the graphics, then navigate to and run the newly generated executable `COMP371-Project/Bin/Labs-Debug` by double clicking it.

## Linux

### To compile from the CLI
`g++ 371A1.cpp shader.cpp -lGL -lGLEW -lglfw`

