# Circuit Simulator 🔌⚡

## Overview

A C++ circuit simulator that leverages modern C++ techniques and linear algebra to analyze electrical circuits.

### 🚀 Features

Supports multiple circuit element types

Efficient Modified Nodal Analysis (MNA)

Linear algebra computations using Eigen

Flexible parsing of circuit description files

## 📦 Prerequisites

C++20 compatible compiler

Eigen Linear Algebra Library

CMake (optional, for build management)

## 🛠 Installation

### Dependencies
```code
# Install Eigen (Ubuntu/Debian)
sudo apt-get install libeigen3-dev

# Install Eigen (macOS with Homebrew)
brew install eigen
```
### Building the project
```code
# Clone the repository
git clone https://github.com/azcem/CircuitSimulator.git
cd CircuitSimulator

# Build with CMake
make
```

## 📝 Usage
Circuit Description File Format

Create a .circuit file describing your circuit:
```code
V1 5 0 2
V2 3 2 0.2
V3 7 6 2
I1 4 8 1e-3
I2 0 6 1e-3

R1 1 5 1.5
R2 1 2 1
R3 5 2 50	G2 % this is a group 2 element
R4 5 6 0.1
R5 2 6 1.5
R6 3 4 0.1
R7 8 0 1e3
R8 4 0 10	G2 % this is a group 2 element

```

run the executable with
```code
./CircuitSimulator test.circuit
```

## 📊 Supported Elements

Voltage Sources ⚡

Current Sources ⚡

Resistors 🔌

(Future) Capacitors, Inductors, diodes, transistors

## 💡 Acknowledgments

Eigen Library

Open-source circuit simulation community
