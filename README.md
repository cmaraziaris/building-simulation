# Building Simulation

#### A C++ Ιmplementation, of the simulation of a public service building.
The main building consists of a ground floor, 4 more floors and an elevator. 
The ground floor consists of an entrance area. 
Each floor consists of an entrance hall and 10 offices.

Visitors attempt to enter the building.
Each visitor wants to visit 1 of the 10 offices, located in a specific floor. Afterwards, they leave the place.

Here, we try to emulate this process:
> - A visitor enters the building
> - waits for the elevator in the ground floor
> - enters the desired floor and office
> - leaves from the floor
> - exits the building

Each visitor has an assosiated priority so they're treated fairly in the process.
The simulation is terminated when the elevator completes a specific number of circles.

 **Note:** *All visitors attempt to enter at once, thus many visitors won't make their way inside.*

## Usage
#### Run

```cplusplus
cd ~/building-simulation/

make

./building_sim <max_cap> <floor_cap> <ground_cap> <office_cap> <elevator_cap> <number_of_visitors> <elevator_circles> 
```
#### Clean

```cplusplus
make clean
```
## Authors
- [Spiros Chalkias](https://github.com/spChalk)
- [Harry  Maraziaris](https://github.com/cMrzrs)
