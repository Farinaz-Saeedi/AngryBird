# Angry Birds

This project simulates a strategic version of *Angry Birds* , where flocks of birds aim to inflict the **maximum possible destruction** on pig cities .  
Each bird must respect its **flight distance limits per launch** and avoid or deal with **spies positioned along the paths** between cities .  

The challenge is to find the **optimal assignment of birds to enemy cities** while ensuring they can actually reach their targets . To achieve this , the project uses:
- **Hungarian Algorithm:** for maximizing overall destruction through bird-to-city assignment .  
- **Astar:** pathfinding to navigate the map , considering distance and obstacles .  

Scenarios with different configurations of cities , birds , and spies are supported , making the problem both dynamic and challenging .
