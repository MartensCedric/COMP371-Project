# COMP371-Project
Git Repository for the project

## Windows

### Building with VisualStudio 2017

0. When installing VS2017, make sure that you include the installation of the Windows SDK version 10.0.16299.0
1. Start VisualStudio 2017, open the .sln file in `VS2017` folder.
2. In the 'Solution Explorer' click the 'Solutions and Folders' button so that you can see all the folders/files.

![img_0](https://i.imgur.com/aBwSKr0.png)

3. Click the `371A1.cpp` inside the `Source` folder.

4. You should see the `Local Windows Debugger` button at the top, clicking this should build the project and launch the executable. If you don't see this option or it doesn't work, continue with the steps below:

5. Click the dropdown next to the green arrow at the top, make sure it has 'Current Document (371A1.cpp)' selected.

![img_1](https://i.imgur.com/85hzUmy_d.webp?maxwidth=728&fidelity=grand)

6. If you already built the project before, delete the executable `COMP371-Project/Bin/Labs-Debug`

![img_3](https://i.imgur.com/n0xEreA_d.webp?maxwidth=728&fidelity=grand)

7. Click the green arrow to build and launch the code.

NOTE: The automatic running of the executable may not work (error message contains: "Unable to start program...").

![img_2](https://i.imgur.com/W1ytNYT_d.webp?maxwidth=728&fidelity=grand)

If the above steps do not result in a new window popping up to render the graphics, then navigate to and run the newly generated executable `COMP371-Project/Bin/Labs-Debug` by double clicking it.

## Linux

### To compile from the CLI
`make`

## Controls

### Keyboard inputs

- `shift + w` --> move model forward (continuous)
- `shift + a` --> move model left (continuous)
- `shift + s` --> move model backward (continuous)
- `shift + d` --> move model right (continuous)

- `ctrl + w` --> move lower model part forward (continuous)
- `ctrl + a` --> move lower model part left (continuous)
- `ctrl + s` --> move lower model part backward (continuous)
- `ctrl + d` --> move lower model part right (continuous)

- `alt + w` --> move upper model part forward (continuous)
- `alt + a` --> move upper model part left (continuous)
- `alt + s` --> move upper model part backward (continuous)
- `alt + d` --> move upper model part right (continuous)

- `ctrl + ↑` --> move model forward (discrete)
- `ctrl + ↓` --> move model left (discrete)
- `ctrl + ←` --> move model backward (discrete)
- `ctrl + →` --> move model right (discrete)

- `alt + ↑` --> move lower model part forward (discrete)
- `alt + ↓` --> move lower model part left (discrete)
- `alt + ←` --> move lower model part backward (discrete)
- `alt + →` --> move lower model part right (discrete)

- `shift + ↑` --> move upper model part forward (discrete)
- `shift + ↓` --> move upper model part left (discrete)
- `shift + ←` --> move upper model part backward (discrete)
- `shift + →` --> move upper model part right (discrete)

- `u` --> scale up model
- `j` --> scale down model

- `shift + q` --> move model up
- `shift + e` --> move model down

- `a` --> rotate left about Y axis
- `d` --> rotate right about Y axis
- `q` --> rotate left about X axis
- `e` --> rotate right about X axis
- `z` --> rotate left about Z axis
- `c` --> rotate right about Z axis

- `enter + a` --> rotate left about Y axis (discrete)
- `enter + d` --> rotate right about Y axis (discrete)

- `↑` --> rotate world anti-clockwise about y axis
- `↓` --> rotate world clockwise about y axis
- `←` --> rotate world clockwise about x axis
- `→` --> rotate world anti-clockwise about x axis
- `page up` --> move world forward
- `page down` --> move world backward
- `home` --> set world orientation to home position

- `Left Mouse Click + Move Mouse up/down` --> Zoom out/in
- `Right Mouse Click + Move Mouse left/right` --> Pan
- `Middle Mouse Click + Move Mouse up/down` --> Tilt

- `l` --> switch to lines rendering mode
- `p` --> switch to points rendering mode
- `t` --> switch to triangles rendering mode

- `b` --> toggle light and shadow rendering
- `x` --> toggle texture rendering

- `Esc` --> terminate program

### To run MangoHud
`MANGOHUD_DLSYM=1 mangohud ./exec`

# Credits
- learnopengl.com (Light code, shadows, skybox)
- Noise library FastNoise (MIT)
