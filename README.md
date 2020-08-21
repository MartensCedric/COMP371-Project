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

1. `cd COMP371-Project/Source`
2. `make`

## Controls

### Keyboard inputs

- `w` --> walk forward
- `a` --> walk left
- `s` --> walk backward
- `d` --> walk right

- `u` --> scale up model
- `j` --> scale down model

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
- [Light code, shadows, skybox](https://learnopengl.com)
- [Noise library FastNoise (MIT)](https://github.com/Auburn/FastNoise)
- [bark texture](https://forums.rpgmakerweb.com/data/avatars/o/106/106252.jpg?1499807823)
- [box texture](https://www.deviantart.com/dactilardesign/art/Crate-generator-342135330)
- [wood texture](https://wallpapersafari.com/w/rgL7NY)
- [rock texture](http://textures101.com/view/439/next/Rock/Rock_Seamless)
- [leaves texture](https://www.lanrentuku.com/bg/a/green_4.html)
- [log texture](https://www.wildtextures.com/free-textures/wood/log-cabin-wall-texture/)
- [dark log texture](https://www.dreamstime.com/stock-photo-old-wooded-wall-fragment-logs-background-image77358585)
- [door texture](http://spiralgraphics.biz/packs/building_cottage/index.htm?1)
- [window texture](http://spiralgraphics.biz/packs/building_cottage/index.htm?4#anchor)
- [snow texture](https://www.deviantart.com/aniuk-storage/art/Snow-14-417975512)
- [grass texture](https://www.pinterest.ca/pin/277464027026735524/)
- [penguin black fur texture](https://i.pinimg.com/originals/76/cb/5b/76cb5b3cfc95a253b5da5095b3ea85e9.jpg)
- [penguin white fur texture](https://www.pinterest.ca/pin/827395762770844717/)
- [penguin orange beak texture](http://blackbirdsycamore.com/wp-content/uploads/2011/09/Hall-Paint.jpg)
- [penguin pearl white sclera texture](https://www.realmilkpaint.com/wp-content/uploads/Pearl_Edited_2018.jpg)
- [penguin pitch black pupil texture](https://lh3.googleusercontent.com/WQG2R-GsWuaGHlpSaZTzZhmD2iXJfl-9dI06G9W7nDKiojV4Tgy7uBeMWBg5zlLcN4eSbwgBCuQR3bpa8hf-=s400)

