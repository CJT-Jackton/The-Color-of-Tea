# The Color of Tea

This program use OpenGL to create an 3D virtual scene, approximated a picture of still life photography. 

![target image](https://raw.githubusercontent.com/CJT-Jackton/The-Color-of-Tea/master/screenshots/the_colour_of_tea_1024x870.jpg "The color of tea")
    *Target image (The color of tea)*

## Methodology

### Model

All models created by 3ds Max.

### Shading

The shading approach for the static objects in the scene is classic Phong-shading model. By modify the coefficient of ambient, diffuse and specular reflection for different object, the program can simulate different material.

As for the rendering for transparent object (glass), this program use a Fresnel value to control the alpha value so the glass will be more transparent when the viewing vecotr is more closer to the normal of the surface, and the glass will show its color when the viewing angle is big.

### Texture mapping

There are two different approach of texture mapping in this program. For the object model has UV coordinate, the program will directly import the texture coordinate. For those doesn't, the program will generate the texture coordinate by apply a texture mapping on the model. In this particular scene, the tea cup model doesn't have UV coordinate and the program applied a cylindrical texture mapping on it.

## Result

![screenshot 1](https://raw.githubusercontent.com/CJT-Jackton/The-Color-of-Tea/master/screenshots/screenshot_1.png "Screenshot 1")
    *Screenshot of the view from camera #1*
    
## Control

- `1` - switch to the camera #1
- `2` - switch to the camera #2
- `3` - switch to the camera #3
- `a` - start animating (rotate the camera #1)
- `s` - stop animating
- `r` - reset camera #1
- `esc` or `q` - quit the program

## Requirement

OpenGL 3.0

GLEW 

GLFW

GLM (math library)

SOIL (image handle library)

## TODO

- Shadow mapping
- Reflection
- Advanced shading model (PBR)
