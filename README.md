# Context Steering
## Introduction
Context steering is an improved steeringbehaviour in which you have a specified number of rays pointing outwards from your agent. (usually saved in an array or a vector)
Based on the context, these rays will be assigned an interest value, or a danger value if needed. The latter could be applied when the ray hits an obstacle. This would mean the agent could possibly ignore this direction in it's final calculation, or instead, subtract this danger value from it's original interest value.

The biggest improvement context steering offers, is the fact that you don't need to make tons of different steeringbehaviours.
Meaning, you're code will be much more limited, and possible more readable as well.

## Summmary
Coming Soon

## References
- [KidScancode](https://kidscancode.org/godot_recipes/ai/context_map/)

## Author
![This is an image](https://myoctocat.com/assets/images/base-octocat.svg)
Sasha Vigneron
