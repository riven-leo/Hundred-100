#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <set>
using namespace std;

class MovieRentingSystem {
    set<tuple<int, int, int>> rented;
    unordered_map<pair<int, int>, int> unrented;
    unordered_map<int, pair<int, int>> mtops;


public:
    MovieRentingSystem(int n, vector<vector<int>>& entries) {
        
    }
    
    vector<int> search(int movie) {
        vector<int> v = {};
    }
    
    void rent(int shop, int movie) {
        
    }
    
    void drop(int shop, int movie) {
        
    }
    
    vector<vector<int>> report() {
        
    }
};

