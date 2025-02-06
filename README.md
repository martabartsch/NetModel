# NetModel

NetModel implements several algorithms for constructing graphs in either adjacency list or adjacency matrix form and calculates the sum of all distances between pairs of vertices.

### Implemented Models

The program supports the following network models:

| **Index** | **Model Name** | **Parameters**                           | **Description** |
|-----------|--------------|------------------------------------------|----------------|
| 0 | **Barabási–Ravasz–Vicsek (BRV)** | number of iterations                     | Generates a hierarchical scale-free network. |
| 1 | **Lu–Su–Guo** | number of vertices                       | Constructs a deterministic network with small-world properties. |
| 2 | **Iterative Growth** | number of iterations, `r`                | Expands a network by iteratively adding new vertices to existing edges. |
| 3 | **DCN (Deterministic Complex Network)** | number of vertices                       | Creates a deterministic hierarchical network. |
| 4 | **Kronecker Graph** | exponent, adjacency matrix (as a string) | Uses the Kronecker product to generate a self-similar network. |

Each model allows the user to choose between two representations:

1. adjacency list
2. adjacency matrix (except for Iterative Growth)

### Init in Ubuntu

1. Clone the repository
```bash
    git clone https://github.com/martabartsch/NetModel.git
    cd NetModel
```

2. Compilation and execution
```bash
    mkdir -p build
    cd build
    cmake ..
    cmake --build .
```
3. Run the project
```bash
    ./NetModel
```

### Usage

**Input Format**
1. Enter the **model index** followed by the required **parameters** (refer to the table above for details).
2. Choose the **graph representation**:
    - **1:** Adjacency List
    - **2:** Adjacency Matrix (not available for Iterative Growth)

**Output Format**
- The program outputs the **sum of all distances** in the generated graph and graph representation.

#### Detailed Example Breakdown

1. BRV Model
```
    0 4
    11664
```

2. Lu–Su–Guo Model
```
    1 348
    177472
```

3. Iterative Growth Model
```bash
    3 2 1
    13
```

4. DCN Model
```
    4 91
    7764
```
5. Kronecker
```
   6 4 0111110101110011000111110
   293072
```