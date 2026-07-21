# 🏙️ City Simulation in C

![Academic Project](https://img.shields.io/badge/Academic_Project-Sakarya_University-blue)

![Course](https://img.shields.io/badge/Course-Principles_of_Programming_Languages-blue)

> 🎓 Part of my **[Computer Engineering Academic Portfolio](https://github.com/Lucaskatalahali/computer-engineering-projects)**.

This project implements a hierarchical city population simulation in **C**, recreating object-oriented programming concepts such as inheritance, polymorphism, composition, and encapsulation using only language features like `struct`, function pointers, and dynamic memory management. This implementation demonstrates how a complex object-oriented architecture can be reproduced in a procedural language.

---

## 🛠️ Technologies

- C
- GCC
- Makefile

---

## 📌 Overview

The simulation starts from a sequence of two-digit numbers entered by the user.

Each number represents the initial population structure of a city.

Before the simulation begins, the input is automatically validated and adjusted to satisfy all simulation constraints.

During each round:


- Population grows according to the city's current growth rate.
- New citizens are randomly generated.
- Neighborhood, district and city populations are recalculated.
- Cities reaching a population of **1000 or more** are automatically divided into new cities.

After all rounds are completed, the user can inspect any city by entering its row and column coordinates.

---

## ✨ Features

- Object-oriented programming simulation in **C**.
- Inheritance emulation using a shared base structure.
- Polymorphism through function pointers.
- Dynamic memory management using malloc, realloc, and free.
- Hierarchical city model using composition.
- Recursive population updates throughout the hierarchy.
- Automatic city splitting based on population threshold.
- Three different city splitting strategies.
- Dynamic creation and destruction of every administrative unit.
- Coordinate-based inspection of any city after the simulation.
- Makefile-based project compilation.

---

## 🧠 Simulating Object-Oriented Programming in C

Since C does not provide classes, inheritance or virtual methods, object-oriented programming was manually recreated using core language features.

The project simulates OOP through:

- `struct` acting as objects.
- Function pointers acting as virtual methods.
- A shared base structure representing inheritance.
- `super` pointers providing access to parent behavior.
- Constructors implemented as allocation functions.
- Recursive destructors responsible for releasing allocated memory.

This approach demonstrates how object-oriented design principles can be implemented in a low-level language without native OOP support.

---

## 🏛️ Architecture

The administrative hierarchy is modeled using composition, while inheritance is simulated through a shared base structure.

```text
Main
 │
 ▼
Game (Oyun)
 │
 └── List<City>

              ▲
              │
        Base Structure
          Settlement
              ▲
      ┌───────┼────────┐
      │       │        │
    City    District  Neighborhood
      │         │          │
      │         │          └── List<Person>
      │         │
      │         └── List<Neighborhood>
      │
      └── List<District>

Person (Independent Object)
```

Each administrative unit owns a pointer named `super`, allowing it to access the shared fields and methods defined in `Settlement`, effectively reproducing inheritance in C.

---

## 💾 Memory Management

Every object in the simulation is dynamically allocated.

The project includes:

- Constructors for every structure.
- Recursive destructors (`Delete`) for automatic cleanup.
- Dynamic array resizing using `realloc`.
- Explicit ownership of allocated resources.
- Complete memory deallocation before program termination.

---


---

## 🌆 Dynamic City Splitting

One of the project's core features is the automatic division of cities when they reach four-digit populations.

Depending on the city's structure, one of three strategies is applied.

### 1. District-based splitting

If a city contains multiple districts, half of its districts are transferred to a newly created city.

### 2. Neighborhood-based splitting

If the city contains only one district but multiple neighborhoods, neighborhoods are divided between the original and the new city.

### 3. Population-based splitting

If the city contains only one district and one neighborhood, citizens are divided directly, creating an entirely new administrative hierarchy.

All new administrative units are generated dynamically during execution.

---

## ⚖️ Java vs C Version

This project was also implemented in **Java** as part of the same university assignment, preserving the same simulation rules and data structures.

The Java implementation of this project can be found in **[City Simulation in Java](https://github.com/Lucaskatalahali/city-simulation-java)**

Using the same input sequence and the same number of simulation rounds, the C implementation completed the execution significantly faster.

| Implementation | Language | Simulation Rounds | Approximate Execution Time |
|----------------|----------|-------------------|----------------------------|
| This repository | C | 4 | ~3 seconds |
| Java implementation | Java | 4 | ~15 seconds |

➡️ The Java implementation can be found in the **[City Simulation in Java](https://github.com/Lucaskatalahali/city-simulation-java)** repository.

---

## ▶️ How to Build

### Requirements

- GCC
- Make

### Compile

```bash
make
```

or

```bash
make derle
```

### Run

```bash
make calistir
```

---

## 📄 Documentation

The `docs` folder contains:

- Project specification
- Development report

---

## 🎓 Academic Information

- **University:** Sakarya University
- **Faculty:** Faculty of Computer and Information Sciences
- **Department:** Computer Engineering
- **Course:** Principles of Programming Languages
- **Academic Year:** 2025–2026
- **Project Grade:** 100/100

---

## 📌 Notes

This repository preserves the original academic project exactly as it was submitted and evaluated.

The objective of the assignment was not only to implement the simulation itself, but also to demonstrate that object-oriented programming concepts can be faithfully reproduced in pure **C language** through careful software design.

For more academic projects, visit my **[Computer Engineering Academic Portfolio](https://github.com/Lucaskatalahali/computer-engineering-projects)**.
