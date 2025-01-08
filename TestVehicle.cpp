#include <iostream>
#include <vector>
#include <string>
using namespace std;
 
// Base class: Vehicle
class Vehicle {
public:
    string Name;
    int MaxLoadCapacity; // in kilograms
    string Type; // e.g., Car, Truck, Bike
 
    Vehicle(string name, int maxLoadCapacity, string type)
        : Name(name), MaxLoadCapacity(maxLoadCapacity), Type(type) {}
 
    void DisplayInfo() {
        cout << "Vehicle: " << Name << ", Type: " << Type
             << ", Max Load: " << MaxLoadCapacity << " kg" << endl;
    }
};
 
// Test Result encapsulating results
class TestResult {
public:
    string ScenarioName;
    bool Passed;
    string Comments;
 
    TestResult(string scenarioName, bool passed, string comments)
        : ScenarioName(scenarioName), Passed(passed), Comments(comments) {}
 
    void Display() {
        cout << "Test: " << ScenarioName << " - " << (Passed ? "PASS" : "FAIL") << endl;
        cout << "Comments: " << Comments << endl << endl;
    }
};
 
// Abstract class for test scenarios
class TestScenario {
public:
    string ScenarioName;
 
    TestScenario(string scenarioName) : ScenarioName(scenarioName) {}
 
    virtual TestResult RunTest(Vehicle* vehicle) = 0; // Pure virtual function
};
 
// Load Test
class LoadTest : public TestScenario {
private:
    int TestLoad;
 
public:
    LoadTest(int testLoad) : TestScenario("Load Test"), TestLoad(testLoad) {}
 
    TestResult RunTest(Vehicle* vehicle) override {
        bool passed = TestLoad <= vehicle->MaxLoadCapacity;
        return TestResult(
            ScenarioName,
            passed,
            passed ? "Load test passed." : "Load exceeds capacity!"
        );
    }
};
 
// Terrain Test
class TerrainTest : public TestScenario {
private:
    string TerrainType;
 
public:
    TerrainTest(string terrainType) : TestScenario("Terrain Test"), TerrainType(terrainType) {}
 
    TestResult RunTest(Vehicle* vehicle) override {
        // Simplified logic: Trucks are suitable for rough terrain
        bool passed = vehicle->Type == "Truck" || TerrainType != "Rough";
        return TestResult(
            ScenarioName,
            passed,
            passed ? "Terrain test passed." : "Vehicle not suitable for rough terrain!"
        );
    }
};
 
// Main function
int main() {
    // Vehicles
    Vehicle* car = new Vehicle("Sedan", 500, "Car");
    Vehicle* truck = new Vehicle("Pickup", 1500, "Truck");
 
    car->DisplayInfo();
    truck->DisplayInfo();
 
    vector<TestScenario*> tests; //test scenarios

    string input;
    while (true) {
        cout << "Enter load value (or type 'end' to finish): ";
        getline(cin, input);
        
        if (input == "end") {
            break; 
        }

        int loadValue;
        try {
            loadValue = stoi(input); 
        } catch (invalid_argument&) {
            cout << "Invalid input. Please enter a valid integer for load." << endl;
            continue; 
        }

        cout << "Enter terrain type (e.g., 'Rough', 'Smooth'): ";
        string terrainType;
        getline(cin, terrainType);


        tests.push_back(new LoadTest(loadValue));
        tests.push_back(new TerrainTest(terrainType));
        
        // Run tests
        vector<Vehicle*> vehicles = { car, truck };
        for (auto vehicle : vehicles) {
            cout << "\nTesting " << vehicle->Name << "...\n" << endl;
            for (auto test : tests) {
                TestResult result = test->RunTest(vehicle);
                result.Display();
            }
        }
    }

     //cleanup
    delete car;
    delete truck;
  
 
    return 0;
}
