# philosophers

Go to [french version](#a-propos)

## About
Philosophers project is a simulation of the [dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem). This project allows us to think about synchronisation and concurrency problem and how to implement an efficient solution using threads and mutexes. 

## What's the problem 
The dining philosophers problem involves a scenario where a number of philosophers sit around a dining table. Each philosopher alternates between thinking and eating. To eat, a philosopher needs two forks, one on the left and one on the right. The challenge lies in preventing deadlock and ensuring that each philosopher gets a chance to eat without conflicting with others.

# Getting Started
## Usage
How to run the program 
```
make
./philo [number_of_philosopher] [time_to_die] [time_to_eat] [time_to_sleep] [optional : number_of_meals]
```

Feel free to explore the source code to understand its detailed workings.

# Authors
- [Houdeyer Lucie](github.com/HdrLucie)


## A propos
Philosophers est une simulation du [dîner des philosophes](https://fr.wikipedia.org/wiki/D%C3%AEner_des_philosophes). Ce projet nous permet d'aborder la synchronisation et le problème de concurrence et comment implémenter une solution efficace avec l'aide des threads et des mutex. 

## Quel est le problème
Le problème du dîner des philosophes est exposé tel que : nous avons X nombres de philosophes assis autour d'une table. Chacun d'entre eux alternent entre manger et penser. Pour manger, un philosophe a besoin de deux fourchettes, une à droite et l'autre à gauche. Il faut donc s'assurer, tout en empêchant les deadlock et datarace, que chaque philosophe puisse manger à sa faim. 

# Pour commencer
## Utilisation
Pour exécuter le programme : 
```
make
./philo [nombre_de_philosophes] [temps_avant_mort] [temps_pour_manger] [temps_pour_dormir] [optionnel : nombre_de_repas]
```

N'hésitez pas à explorer le code source pour comprendre en détail son fonctionnement.

# Auteur
- [Houdeyer Lucie](github.com/HdrLucie)
