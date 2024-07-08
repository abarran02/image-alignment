# Image Alignment Tool

Requires Qt 5. Developed and tested using Qt 5.12.2

## Instructions

To open an image, go to File -> Open Image or Open Directory.

Click an image to select and drag it.
Once an image is selected, it will be outlined in red and you may use the following keyboard commands:
- WASD or Arrow keys to move it up/down/left/right
- Z/X to lower/raise the layer, respectively
- N/M to decrease/increase the layer opacity, respectively
- Delete to remove the image from the grid

Once the images are aligned, go to File -> Generate Grid.

### Preferences

Under File -> Preferences, you may set the thumbnail size (default 200px) and tolerance for detecting image rows (default 100px).
The row tolerance is recommended to be less than or equal to 50% of the thumbnail size.
