# Beamforming with Phased Array Dipoles using NSB Algorithm

## Overview

This project implements a beamforming simulation using a one-dimensional phased array of dipole antennas. The objective is to steer the beam towards a desired user while nulling (placing zeroes) in the direction of interfering or undesired users. The system employs the Null-Steering Beamforming (NSB) algorithm to achieve directional accuracy and interference suppression.

## Key Features

- **Phased Array Configuration**: Linear array of dipoles with customizable element count.
- **NSB Algorithm Implementation**: Steers the main lobe toward a target user and places nulls towards undesired users.
- **Angular Sweeping**: Evaluates system performance across a sweep of azimuthal angles.
- **Multi-User Scenarios**: Supports varying numbers of desired and interfering users.
- **Performance Evaluation**: Includes a `DataManager` class to:
  - Extract and manage simulation results.
  - Quantify angle errors for null and main beam placement.
  - Evaluate overall accuracy of beamforming performance.

## Structure

