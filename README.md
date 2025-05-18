# NSB Beamforming with 1D Phased Array in C++

## Project Description

This project implements a beamforming simulation using a **one-dimensional phased array** of dipole antennas. It is written in **modern C++** and uses the **Eigen** library for efficient linear algebra operations.

The system simulates beam steering towards a **single desired user** while placing **nulls** in the directions of **interfering users** using the **Null-Steering Beamforming (NSB)** algorithm. The simulation sweeps across all possible angles to evaluate performance and accurately forms beams and nulls based on array geometry and user distribution.

After computation, the results are analyzed using the `DataManager` class to extract metrics such as **angle error** for the main lobe and nulls, as well ass side lobe levelss.

---

## Features

- ✅ **Phased Array Simulation**: Linear array of dipole elements.
- 🎯 **Null-Steering Beamforming (NSB)**: Places directional nulls at interfering user angles and maximizes gain toward the desired user.
- 🔁 **Angle Sweeping**: Simulates performance over a full angular range.
- 👥 **Multi-User Support**: Works with different numbers and placements of desired and undesired users.
- 📊 **Performance Evaluation**: 
  - Main lobe accuracy
  - Null direction accuracy
  - Visualization-ready data output

---

## Dependencies

- [Eigen](https://eigen.tuxfamily.org/) (header-only linear algebra library)

Make sure Eigen is available on your system. You can install it using a package manager (e.g., `apt`, `brew`) or by downloading it manually.

---

## Build Instructions

1. **Clone the Repository**

```bash
git clone https://github.com/your-username/Beamforming.git
cd Beamforming
