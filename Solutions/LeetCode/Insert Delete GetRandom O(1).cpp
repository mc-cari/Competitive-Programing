
//https://leetcode.com/explore/challenge/card/june-leetcoding-challenge/540/week-2-june-8th-june-14th/3358/
class RandomizedSet {
public:
    /** Initialize your data structure here. */
    int siz = 0;
    vector<int>hashes;
    unordered_map<int,pair<int, int> >vis;
    RandomizedSet() {

        
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if(vis[val].first)
        {
            return 0;
        }
        else
        {
            if(siz + 1 > hashes.size())
            {
                hashes.push_back(val);
            }
            else
            {
                hashes[siz] = val;
            }
            vis[val] = {1, siz};
            siz ++;
            return 1;
        }
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        if (!vis[val].first)
        {
            return 0;
        }
        else
        {
            vis[val].first = 0;
            if(vis[val].second < siz - 1)
            {
                hashes[vis[val].second] = hashes[siz - 1];
                vis[hashes[siz - 1]] = {1, vis[val].second};
            }
            
            siz --;
            return 1;
        }
        
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        return hashes[(rand() % siz)];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
