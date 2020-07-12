# COMP371-Project
Git Repository for the project

## Windows

### Building with VisualStudio 2017

0. When installing VS2017, make sure that you include the installation of the Windows SDK version 10.0.16299.0
1. Start VisualStudio 2017, open the .sln file in `VS2017` folder.
2. In the 'Solution Explorer' click the 'Solutions and Folders' button so that you can see all the folders/files.

![img_0](https://i.imgur.com/aBwSKr0.png)

3. Click the `371A1.cpp` inside the `Source` folder.
4. Click the dropdown next to the green arrow at the top, make sure it has 'Current Document (371A1.cpp)' selected.

![img_1](https://i.imgur.com/85hzUmy_d.webp?maxwidth=728&fidelity=grand)

5. If you already built the project before, delete the executable `COMP371-Project/Bin/Labs-Debug`

![img_3](https://i.imgur.com/n0xEreA_d.webp?maxwidth=728&fidelity=grand)

6. Click the green arrow to build and launch the code.

NOTE: The automatic running of the executable may not work (error message contains: "Unable to start program...").

![img_2](https://i.imgur.com/W1ytNYT_d.webp?maxwidth=728&fidelity=grand)

If the above steps do not result in a new window popping up to render the graphics, then navigate to and run the newly generated executable `COMP371-Project/Bin/Labs-Debug` by double clicking it.

## Linux

### To compile from the CLI
`make`

## Controls

### Keyboard inputs

- `Lshift + w` --> move model forward
- `Lshift + a` --> move model left
- `Lshift + s` --> move model backward
- `Lshift + d` --> move model right

- `u` --> scale up model
- `j` --> scale down model

- `Lshift + q` --> move model up
- `Lshift + e` --> move model down

- `a` --> rotate left about Y axis
- `d` --> rotate right about Y axis
- `q` --> rotate left about X axis
- `e` --> rotate right about X axis
- `z` --> rotate left about Z axis
- `c` --> rotate right about Z axis

- `home` --> set world orientation to home position

- `Right Mouse Click + Move Mouse left/right` --> Pan
- `Middle Mouse Click + Move Mouse up/down` --> Tilt

- `Esc` --> terminate program
