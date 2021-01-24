# pixel3D
Extension of the pixel engine for rendering 3D obj files. Use 'a' and 's' to change your field of view and the arrow keys to move. Rotate the cube using the 'r' and a key correspoding to the three axes ('x', 'y', 'z') together. Use LShift to revers the rotation's direction.

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

