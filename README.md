# Coursework on "Data structures". 1 course, 2 semester, IC of SPBSTU

## It is "Space Impact" game made on C with OpenGL

### Authors

    Devs: 
        Mishenev Nikita (clowixdev)
        Kvashennikova Veronika (sssauerkraut)

    Artists (Textures): 
        Kvashennikova Veronika (sssauerkraut)

    Artists (Sounds, Music): 
        Toby Fox (Undertale game)

### About

This is a copy of old mobile game Space Impact with our own ideas for some
game mechanics. All the development was conducted in C language with OpenGL,
especially using freeglut. To load textures, we used STB_IMAGE library that
we found in the Ithernet

### Compiling

You can compile our game by using compile task from tasks.json.
All the dependencies that should be located in ../dependecies:

    1. STB_IMAGE
    2. GLFW
    3. FREEGLUT
    4. GLEW

You should also add to your /system32/ directory these .dll files:

    1. freeglut.dll
    2. glew32.dll
    3. glfw3.dll

All the needed files you can find in your lovely browser ~ (^-^ ~)
The compiled file will wait you in ./builds/windows/ directory

> You can compile program in Linux using build.sh script.

Have fun testing our project!

### TODO

    1. "Boss" on level 4 - DONE!
    2. 50% chance to drop heart on small asteroid kill - DONE!
    3. Add textures to all objects - DONE!
    4. Add sounds - DONE!
    5. Rework objects system ( 
        - create global lists that will store objects and their data,
        - create object with create_<obj> func and push in the global list,
        - change objects state with foreach_obj(...) func,
        - add ability to shoot multiple bullets
    )

### ACCEPTED!
