# Description of planning algorithm

## 1. Track limits are known at compile-time

### General idea

- We have track limits for left and right track limits in data files
- Starting from any point on the track, the driving direction is clear due to knowing which border is the left / right one 

### Center line planner

- Find points in map with distance of 0.01 that maximize the mean squared distance to the closest point from each border

## 2. Track limits are gathered during run-time by a perception unit

To be implemented.