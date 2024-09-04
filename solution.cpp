#include <bits/stdc++.h>
using namespace std;

// Global variable to store initial power of Abhimanyu
int initialPower;

// Memorization to check if Abhimanyu can cross the Chakravyuha
bool isPossibleforAbhimanyuToCrossChakravyuha(
    int circleIndex, 
    int circles, 
    vector<int>& enemies, 
    int currentPower, 
    int skipsLeft,
    int rechargesLeft, 
    vector<vector<vector<vector<int>>>>& dp 
) {    
    // If Abhimanyu has crossed all circles
    if (circleIndex == circles) {
        return currentPower >= 0;
    }

    // If the state is already computed, return the stored result
    if (dp[circleIndex][currentPower][skipsLeft][rechargesLeft] != -1) {
        return dp[circleIndex][currentPower][skipsLeft][rechargesLeft];
    }

    bool canReach = false;

    // If Abhimanyu has enough power to defeat the enemy in the current circle
    if (currentPower >= enemies[circleIndex]) {
        canReach |= isPossibleforAbhimanyuToCrossChakravyuha(
            circleIndex + 1, 
            circles, 
            enemies, 
            currentPower - enemies[circleIndex], 
            skipsLeft, 
            rechargesLeft, 
            dp
        );
    }

    // Special case for enemies with regeneration power
    if (circleIndex == 2 || circleIndex == 6) {
        enemies[circleIndex + 1] += enemies[circleIndex] / 2;
    }

    // If Abhimanyu can skip this enemy
    if (skipsLeft > 0) {
        canReach |= isPossibleforAbhimanyuToCrossChakravyuha(
            circleIndex + 1, 
            circles, 
            enemies, 
            currentPower, 
            skipsLeft - 1, 
            rechargesLeft, 
            dp
        );
    }

    // If Abhimanyu can recharge his power
    if (rechargesLeft > 0) {
        currentPower = initialPower;
        canReach |= isPossibleforAbhimanyuToCrossChakravyuha(
            circleIndex + 1, 
            circles, 
            enemies, 
            currentPower, 
            skipsLeft, 
            rechargesLeft - 1, 
            dp
        );
    }

    // Store and return the result for the current state
    return dp[circleIndex][currentPower][skipsLeft][rechargesLeft] = canReach;
}


int main() {
    int testCases ;

    cout<<"Enter no of test-cases: ";
    cin >> testCases;

    for(int i = 0; i < testCases; i++) {

        int circles = 11, power, skips, recharges;
        
        cout<<"Enter input values: power, skip, recharge respectively: ";
        cin >> power >> skips >> recharges;

        initialPower = power;
        
        vector<int> enemies(circles, 0);
        
        cout<<"Enter values for each enemies power in 11 circles: ";
        for (int i = 0; i < circles; i++) {
            cin >> enemies[i];
        }

        // DP table to store results of subproblems
        vector<vector<vector<vector<int>>>> dp(
            12, vector<vector<vector<int>>>(
                205, vector<vector<int>>(
                    20, vector<int>(20, -1)
                )
            )
        );

        // Check if Abhimanyu can cross the Chakravyuha
        bool canAbhimanyuCross = isPossibleforAbhimanyuToCrossChakravyuha(
            0, circles, enemies, power, skips, recharges, dp
        );

        cout << (
            canAbhimanyuCross 
                ? 
            "Abhimanyu can cross: WIN\n" 
                : 
            "Abhimanyu can not cross: LOST\n"
        );
    }
    
    return 0;
}