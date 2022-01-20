# Context Steering
## Introduction
Context steering is an improved steeringbehaviour in which you have a specified number of rays pointing outwards from your agent. (usually saved in an array or a vector)
Based on the context, these rays will be assigned an interest value, or a danger value if needed. The latter could be applied when the ray hits an obstacle. This would mean the agent could possibly ignore this direction in it's final calculation, or instead, subtract this danger value from it's original interest value.

The biggest improvement context steering offers, is the fact that you don't need to make tons of different steeringbehaviours.
Meaning, you're code will be much more limited, and possible more readable as well.

## The Algorithm Explained!
The Context-Based Steering algorithm is quite a simple one, but before we get started, let's have a quick overview!
Imagine your agent has 8 arrows around him, each in a different direction.
![image](https://user-images.githubusercontent.com/45370607/150368152-db7c2f1a-f087-46bf-af3c-21419dc17085.png)
Image comes from [KidScancode](https://kidscancode.org/godot_recipes/ai/context_map/)
These arrows will hold the interest value, or in other words, the more-likely the agent is to move in that direction.
We can then visualize these arrows as follows: 
![image](https://user-images.githubusercontent.com/45370607/150368536-a418c582-6d90-45e4-9dc1-30b037c79653.png)
Image comes from [KidScancode](https://kidscancode.org/godot_recipes/ai/context_map/)
But as you can imagine, if this were the case, the agent would be willing to move in all directions, meaning they will cancel each other out, and your agent will remain stationary. We want the agent to be moving forward, so we will say that the less forward the arrow points, the less interest this direction should get. This leads us to the following interest vector: 
![image](https://user-images.githubusercontent.com/45370607/150368955-f09c9236-8de7-4373-904a-8381bf0d15a5.png)
Image comes from [KidScancode](https://kidscancode.org/godot_recipes/ai/context_map/)
The last thing we want to cover in this algorithm, is avoiding obstacles. To handle this, we will create a second vector, let's call it the danger vector. 
For each arrow, we will check if the arrow is colliding with an obstacle. If so, we will simply ignore the interest value for this direction.
![image](https://user-images.githubusercontent.com/45370607/150369429-f8d6f34a-60bb-4b82-a6be-cfe59620cf06.png)
Image comes from [KidScancode](https://kidscancode.org/godot_recipes/ai/context_map/)

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

![Danger_1](/Footage/DangerValue.gif?raw=true "DangerValue")

If you want to, you can make it a little more complex, by actually interpolating this danger between 0 and 1, depending on the range of the obstacle.
This will make the movement a little bit smoother than before. But depending on the use case, this may or may not be the result you want to achieve.

Once we're done calculating the danger values, we want to subtract these from the interest values. Meaning that, if we have an interest value of 1, and a danger value of 1 for that same direction. We'll end up with an interest value of 0. This will make sure that this direction is ignored in the final direction's calculation.

![Danger_2](/Footage/DangerValue_2.gif?raw=true "DangerValue_2")

### 4. How To Get The Final Direction
Finally, we have to merge all of these together, so we can calculate the desired direction of the agent.
To do this, we basically sum up all the desired directions multiplied by their interest value and then divide these again by the number of arrows used in all previous calculations. If done correctly, this will ignore the directions headed to the obstacle(s). Or, if you're using the interpolating danger calculations, it will smoothly go around the object.

And that's basically it! It's a very simple and quick way to implement a basic, but sufficient steering behaviour in your games!

## References
- [KidScancode](https://kidscancode.org/godot_recipes/ai/context_map/)
- [JamesKeats](https://jameskeats.com/portfolio/contextbhvr.html)

## Author
![ThankYou](https://media.giphy.com/media/3oEdva9BUHPIs2SkGk/giphy.gif)

- Name: Sasha Vigneron
- Group: 2GD07
- Institute: Digital Arts & Entertainment @ Howest Kortrijk, Belgium
