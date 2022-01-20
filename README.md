# Context Steering
## Introduction
Context steering is an improved steeringbehaviour in which you have a specified number of rays pointing outwards from your agent. (usually saved in an array or a vector)
Based on the context, these rays will be assigned an interest value, or a danger value if needed. The latter could be applied when the ray hits an obstacle. This would mean the agent could possibly ignore this direction in it's final calculation, or instead, subtract this danger value from it's original interest value.

The biggest improvement context steering offers, is the fact that you don't need to make tons of different steeringbehaviours.
Meaning, you're code will be much more limited, and possible more readable as well.

## The Algorithm Explained!


## Let's Get Started!
### 1. Creating The Arrows
We start off by creating the arrows, this is a very simple for loop, calculating it's desired angle. (or direction)
Obviously, the size and the amount of arrows can be edited, experimenting with these variables can lead to different behaviours.
For example, if you want to have an enemy that's able to detect and avoid obstacles from afar, you might want to increase the size of each arrow.
But on the other hand, you might also want to increase the number of arrows, since, if you are looking far ahead, the gaps in between each direction grows, leading to potentially unseen obstacles, until your close. (See Image)

![Image_1](https://i.imgur.com/htM5qWv.png)

On the other hand you also have to account the performance aspect. Since increasing the number of arrows will require more computations. 
This however, does not apply to the size of the arrow, since my object detection is simply a distance check to the obstacle.

### 2. Calculating Interest Values
For this part we will use an std::vector of floats, each value in range of [0,1]. 
The higher the value, the more likely it is the agent will go that direction.

### 3. Calculating Danger Values
Of course we also have to account the actual obstacles in the scene. To do this we'll create another std::vector of floats, again with a value in range [0,1].
To keep it simple, we'll start off by simply checking if the arrow is colliding with the obstacle, we'll put that specific arrow's danger value to 1. 
If you want to, you can make it a little more complex, by actually interpolating this danger between 0 and 1, depending on the range of the obstacle.

![Danger_1](/Footage/DangerValue.gif?raw=true "DangerValue")

### 4. How To Get The Final Direction



## References
- [KidScancode](https://kidscancode.org/godot_recipes/ai/context_map/)

## Author
![This is an image](https://myoctocat.com/assets/images/base-octocat.svg)
Sasha Vigneron
