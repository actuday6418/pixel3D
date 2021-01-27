# pixel3D
Extension of pixel for rendering 3D obj files. Use 'a' and 's' to change your field of view and the arrow keys to move. Rotate the cube using the 'r' and a key correspoding to the three axes ('x', 'y', 'z') together. Use LShift to revers the rotation's direction.

# Usage
1. Press S with an axis key (X,Y,Z) for scaling. Hold LShiftto reverse the scale transform.
2. Press R with an axis key for rotation, and LShift for the reverse transform.
3. Use O and P together to toggle orthographic / perspective mode (Disclaimer: Rotated mesh is rendered broken in perspective mode)
4. Scroll to transform mesh along Z (depth) axis. (Effect is obviously apparent only in perspective view)
5. Use K, L to change the field of view in perspective view

# Building
    chmod a+x give_me_exec.sh
    mkdir build
    cd build
    cmake ..
    cmake --build .
    
#  Incremental builds
```./give_me_exec.sh```

# Primitive cube render
(Each face is rendered as two triangles. Adjacent faces have shared double edges.)
![Screenshot_20210110_150941](https://user-images.githubusercontent.com/56124831/104119571-38ca3180-5356-11eb-94d6-9de9330ff77b.png)

# Update
![simplescreenrecorder](https://user-images.githubusercontent.com/56124831/105610819-ab67f200-5dd7-11eb-926a-9c60e63a8ef1.gif)

# Final Result
High poly objects don't render properly because of the glitchy drawLine function in `include/A1/application3D.h`. Time complexity is nlogn, for n as the number of polygons. Triangles, actually, cause this program only works with triangles, and not qith quads or anything else. This can be improved to linear time by adding a depth byte to each pixel instead of sorting the entire mesh before each frame. 

![simplescreenrecorder (1)](https://user-images.githubusercontent.com/56124831/106021281-a1513680-60ea-11eb-98b8-c2a9f7450020.gif)


