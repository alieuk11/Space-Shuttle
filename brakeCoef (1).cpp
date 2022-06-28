#include <iostream>
using namespace std;

int main() {

    // Prompts the user to enter a value for the initial velocity
    cout << "v0 (m/s): " ;
    double v0;
    cin >> v0;
    
    // Prompts the user to enter a value for the atmospheric drag coefficient
    cout << "c_d (1/m): " ;
    double c_d;
    cin >> c_d;
    
    // Prompts the user to enter a value for the runway length
    cout << "runwayLength (m): " ;
    double runwayLength;
    cin >> runwayLength;
    
    // Sets the initial range of bMid and initializes all the other variables when needed
    double bMax = (v0 * v0) / (2 * runwayLength);
    double bMin = 0;
    double bMid = (bMax + bMin) / 2;
    double simDist;
    double tolerance = 0.000001;
    double deltaT = 0.00001;
    double v_new = 1;
    double x_old = 0;
    double a_old; 
    
    // Creates the outer loop that will continuously run whenever bMax - bMin is greater than the tolerance
    while (bMax - bMin > tolerance) {
       v_new = v0;
       simDist = 0;
       x_old = 0;

        // Creates the inner loop that will run whenever the shuttle is in motion
        while (v_new > 0) {
            
            // Update equations that will calculate new positions and velocities while the shuttle is in motion and save the new position as old
            a_old = -bMid - c_d * v_new * v_new;
            v_new = v_new + a_old * deltaT;
            simDist = x_old + v_new * deltaT;
            x_old = simDist;
        
        }

        // If loop that runs if the shuttle stops too early, setting the new upper bound to be bMid instead of bMax and recalculating the distance
        if (simDist < runwayLength  ) {
            bMax = bMid;
            bMid = (bMin + bMax) / 2;
        }

        // If loop that runs if the shuttle takes too long to stop, setting the new lower bound to be bMid instead of bMin and recalculating the distance
        if (simDist >= runwayLength) {
            bMin = bMid;
            bMid = (bMin + bMax) / 2;
            
        }
    }
    
// Displays the optimal braking coefficient once the outer loop condition is false
cout << "b_optimal = " << bMid << endl;

return 0;

}