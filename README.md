# GalacticChessOlympicSolver
This project implements Quantum Chess board operations, including row-wise sorting, inversion counting, and closest pair detection in a 2D plane. It uses efficient divide-and-conquer algorithms for optimal performance. Commands allow matrix creation, sorting, inversion calculation, display, and closest pair identification.

## Overview
The Intergalactic Chess Federation (ICF) introduces Quantum Chess, where quantum states are arranged on an `n x n` board. The ICF also needs to pair players efficiently for the Galactic Chess Olympics. This project provides efficient solutions for:

- **Sorting the quantum states row-wise** (ascending or descending)
- **Counting total inversions** in the board
- **Finding the closest pair of players** in a 2D space using Euclidean distance

All algorithms use **Divide and Conquer** for optimal efficiency.

---

## Features
- **`sortRows(Comparator comparator)`**: Sorts each row in ascending or descending order.
- **`countInversions()`**: Counts the number of inversions in the entire board by flattening it into a 1D array.
- **`display()`**: Prints the matrix row-wise.
- **`closestPair()`**: Finds and returns the closest pair of players based on Euclidean distance and specified tie-breakers.

---

## Input Commands

### 1. Create 2D Matrix
```
CREATE_2D size
```
Followed by `size` lines of `size` integers each.

### 2. Sort the Matrix
```
SORT_2D ascending
SORT_2D descending
```
Sorts each row in ascending or descending order.

### 3. Count Inversions
```
INVERSION_2D
```
Outputs a single integer representing the total number of inversions.

### 4. Display the Matrix
```
DISPLAY_2D
```
Prints the matrix row-wise.

### 5. Find Closest Pair of Players
```
CLOSEST_2D num_points
```
Followed by `num_points` lines, each containing two integers representing player coordinates.
Outputs the closest pair of points.

### 6. End Input
```
END
```

---

## Output Format
- `DISPLAY_2D`: Prints the matrix row-wise, with values separated by spaces.
- `INVERSION_2D`: Outputs a single integer for total inversions.
- `CLOSEST_2D`: Outputs four integers representing the closest pair of players.

---

## Example
### **Input**
```
CREATE_2D 4
1 2 2 1
2 1 1 2
3 4 3 4
4 3 3 4
DISPLAY_2D
INVERSION_2D
SORT_2D ascending
DISPLAY_2D
CLOSEST_2D 4
8 7
-3 9
-5 -9
-10 7
END
```

### **Expected Output**
```
1 2 2 1
2 1 1 2
3 4 3 4
4 3 3 4
15
1 1 2 2
1 1 2 2
3 3 4 4
3 3 4 4
-3 9 -10 7
```

---

## Algorithmic Approach
### **Sorting Rows**
- Each row is sorted individually using a custom comparator (ascending or descending).
- **Time Complexity**: `O(n log n)` per row, leading to `O(n² log n)` for the full matrix.

### **Counting Inversions**
- The 2D matrix is flattened into a 1D array.
- The inversion count is found using **Merge Sort** (Divide & Conquer approach).
- **Time Complexity**: `O(n² log n²)`.

### **Finding Closest Pair**
- Uses **Divide & Conquer Closest Pair Algorithm**.
- Sorting by x-coordinates and using recursion to divide and conquer.
- **Time Complexity**: `O(n log n)`.

---

## Constraints
- `1 <= n <= 10^3`
- `-10^18 <= quantum_values <= 10^18 - 1`
- `-10^9 <= coordinates_of_points <= 10^9`
- Maximum **50** commands per test case.
- `O(10^5)` total coordinate pairs.

---

## Tie-Breakers for Closest Pair
1. **Ascending Squared Distance**
2. **If distances match, sort by ascending x-coordinate of the first point**
3. **If first x-coordinates match, sort by ascending y-coordinate of the first point**
4. **If first points are identical, sort by ascending x-coordinate of the second point**
5. **If second x-coordinates match, sort by ascending y-coordinate of the second point**
6. **If all are equal, maintain original input order**

---


