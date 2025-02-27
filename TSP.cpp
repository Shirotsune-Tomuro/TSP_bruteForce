#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <windows.h>

using namespace std;

enum class Planet { A, B, G, D, E };

// Function to convert Planet enum to string
string planetToString(Planet planet) {
    switch (planet) {
        case Planet::A: return "A";
        case Planet::B: return "B";
        case Planet::G: return "G";
        case Planet::D: return "D";
        case Planet::E: return "E";
        default: return "";
    }
}

// Function to calculate the cost of a specific tour
int calculateTourCost(const vector<int>& tour, const vector<vector<int>>& distances, const vector<int>& cargoWeights) {
    int totalCost = 0;
    // Start with the cargo of the first planet in the tour
    int Cargo = cargoWeights[tour[0]]; 

    // Traverse the tour and calculate the cost
    for (int i = 0; i < tour.size() - 1; ++i) 
    {
        int planetFrom = tour[i];
        int planetTo = tour[i + 1];
        
        int distance = distances[planetFrom][planetTo];
        totalCost += distance * Cargo * 25;
        Cargo += cargoWeights[planetTo];
    }

    return totalCost;
}

// Brute force TSP solver
pair<vector<int>, int> solveTSP(const vector<vector<int>>& distances, const vector<int>& cargoWeights) {
    int n = distances.size();
    vector<int> planets(n);

    // Initialize planets as 0, 1, 2, ..., n-1
    for (int i = 0; i < n; ++i) 
    {
        planets[i] = i;
    }

    int minCost = INT_MAX;
    int iteration = 1;
    vector<int> bestTour;

    // Generate all possible tours (permutations of planets)
    do {

        vector<int> currentTour = planets;        

        // Calculate the cost of the current tour
        int currentCost = calculateTourCost(currentTour, distances, cargoWeights);

        // Print the current tour and its associated cost
        cout << "Tour " << iteration << ": ";
        for (int planet : currentTour) {
            cout << planetToString(static_cast<Planet>(planet)) << " ";
        }
        cout << " | Cost: " << currentCost << endl;
        Sleep(50);

        // Update the best tour and minimum cost
        if (currentCost < minCost) {
            minCost = currentCost;
            bestTour = currentTour;
        }

        iteration++;

    } while (next_permutation(planets.begin(), planets.end()));

    return { bestTour, minCost };
}

int main() {
    // Example distances between 5 planets (symmetric TSP)
    vector<vector<int>> distances = {
        {0, 10, 15, 12, 20},
        {10, 0, 12, 25, 14},
        {15, 12, 0, 16, 28},
        {12, 25, 16, 0, 17},
        {20, 14, 28, 17, 0}
    };

    // Cargo weights to be collected from each planet
    vector<int> cargoWeights = { 20, 40, 70, 10, 30 };

    // Solve the TSP using brute force
    pair<vector<int>, int> result = solveTSP(distances, cargoWeights);
    vector<int> bestTour = result.first;
    int bestCost = result.second;

    // Output the best tour and its cost
    cout << "Best tour: ";
    for (int planet : bestTour) {
        cout << planetToString(static_cast<Planet>(planet)) << " ";
    }
    
    cout << endl;
    
    cout << "Minimum cost: " << bestCost << endl;

    return 0;
}
