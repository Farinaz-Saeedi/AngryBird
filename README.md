# Angry Birds 🐦


 
🎯 This project simulates a strategic version of *Angry Birds*, where flocks of birds aim to inflict the
    **maximum possible destruction** on pig 🐷 cities .


Each bird must :
- ✈️ Respect its flight distance limits 
- 🕵️ Avoid or deal with spies positioned along paths   


💥 The challenge is to find the **optimal assignment of birds to enemy cities** while ensuring they can
    actually reach their targets .



---



## ⚙️ Features


- ✅ **Hungarian Algorithm:** for maximizing overall destruction through bird-to-city assignment .  
- ✅ **Astar:** pathfinding to navigate the map , considering distance and obstacles .
- ✅ **Knapsack:** for finding the options which have the minimum cost .
- ✅ **Dynamic Scenarios**: supports multiple configurations of cities , birds , and spies making the problem  
      dynamic and challenging .



---



## 🚀 How It Works


1. **Scenario selection** → loads cities, birds, spies, and constraints .
2. **Assignment** → optimization algorithms pick which birds to launch toward which cities for max
    destruction under constraints .
3. **Astar** → checks reachability and builds the actual path from home city to target .
5. The final plan is executed and reported with **paths and damage** 💣.



---


*We hope you enjoy exploring this project ❤️*
