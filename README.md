Final Project
Zachary Lamb
CSCI4229 Fall 2016
Description: This is a minigolf course with a windmill and some other obstacles. The hole is behind the Windmill.
I started off with making a windmill scene out of glut objects as a prototype for what I wanted my scene to look like. I tried porting to OpenGL ES for mobile game ,but that failed miserably. I started using Unity, Blender objects and the like ,but that wasn't working out how I planned.
I decided to just make this scene instead since it shows a little bit more of what I have learned. ALL the objects were made by me. There is no canned/glut objects used. The windmill is generated by a cube function called "brick"
as are the fence objects. Feel free to change the height of the windmill tower to how I created the main object.
Instructions to run:
1) make
2) ./minigolf

<h4>View of Simulation</h4>

![first](https://github.com/ZachLamb/MinigolfSim/blob/master/Screen%20Shot%202017-03-06%20at%207.45.39%20PM.png?raw=true)

![second](https://github.com/ZachLamb/MinigolfSim/blob/master/Screen%20Shot%202017-03-06%20at%207.45.50%20PM.png?raw=true)

![third](https://github.com/ZachLamb/MinigolfSim/blob/master/Screen%20Shot%202017-03-06%20at%207.45.59%20PM.png?raw=true)


Controls:

 'p' to switch modes (projections)
 'x' to toggle axes
 '0' snaps angles to 0,0
 arrows to rotate the world
 PgUp/PgDn zooms in/out
 +/- changes field of view of perspective
 F1 toggles smooth/flat shading
 F2 toggles local viewer mode
 F3 toggles light distance (1/5)
 F8 change ball increment
 F9 invert bottom normal
 'l' toggles lighting
 a/A decrease/increase ambient light
 d/D decrease/increase diffuse light
 s/S decrease/increase specular light
 e/E decrease/increase emitted light
 n/N decrease/increase shininess
 m  toggles light movement
 [] lower/rise light
