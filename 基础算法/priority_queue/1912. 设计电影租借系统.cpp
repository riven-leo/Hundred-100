#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

class MovieRentingSystem {
    // 哈希表把(shop, movie)->price对应起来
    unordered_map<long long, int> shop_movie_to_price;

    // 哈希表把没出租的movie->有序集合(price, shop)对应起来
    unordered_map<int, set<pair<int, int>>> unrented_movie_to_price_shop;

    // 有序集合把出租的(price, shop, movie)存下来
    set<tuple<int, int, int>> rented_movies;

public:
    MovieRentingSystem(int, vector<vector<int>>& entries) {
        for (auto& e : entries) {
            int shop = e[0], movie = e[1], price = e[2];

            // 把 shop 和 movie 存储到一个 long long 中，方便作为 unordered_map 的 key
            // 如果是我，我会直接存(shop, movie)
            shop_movie_to_price[1LL * shop << 32 | movie] = price;

            unrented_movie_to_price_shop[movie].emplace(price, shop);
        }
    }

    // 获取 unrented_movie_to_price_shop[movie] 的前 5 个 shop
    vector<int> search(int movie) {
        // 在哈希表中的一个迭代器it.first = movie
        // 如果是我，我会用unrented_movie_to_price_shop[movie]，但是会有个小副作用
        auto it = unrented_movie_to_price_shop.find(movie);
        if (it == unrented_movie_to_price_shop.end()) {
            return {};
        }
        vector<int> ans;
        for (auto& [_, shop] : it->second) {
            ans.push_back(shop);
            if (ans.size() == 5) {
                break;
            }
        }
        return ans;
    }

    // 借电影
    void rent(int shop, int movie) {

        int price = shop_movie_to_price[1LL * shop << 32 | movie];

        // 从 unrented_movie_to_price_shop 移到 rented_movies
        unrented_movie_to_price_shop[movie].erase({price, shop});
        rented_movies.emplace(price, shop, movie);
    }

    // 还电影
    void drop(int shop, int movie) {
        int price = shop_movie_to_price[1LL * shop << 32 | movie];
        
        // 从 rented_movies 移到 unrented_movie_to_price_shop
        rented_movies.erase({price, shop, movie});
        unrented_movie_to_price_shop[movie].emplace(price, shop);
    }

    // 获取 rented_movies 的前 5 个 shop 和 movie
    vector<vector<int>> report() {
        vector<vector<int>> ans;
        for (auto& [_, shop, movie] : rented_movies) {
            ans.push_back({shop, movie});
            if (ans.size() == 5) {
                break;
            }
        }
        return ans;
    }
};
