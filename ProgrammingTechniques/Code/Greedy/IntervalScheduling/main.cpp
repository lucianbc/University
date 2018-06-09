#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct activity {
    int id, start, finish;
};

vector<activity> read() {
    return {{1, 10, 14}, {2, 12, 16}, {3, 17, 18}};
}

struct comp {
    bool operator()(const vector<activity> &lhs, const vector<activity> &rhs) {
        return lhs[lhs.size() - 1].finish > rhs[rhs.size() - 1].finish;
    }
};


typedef priority_queue<vector<activity>, vector<vector<activity>>, comp> pq;
typedef vector<activity> room;

bool incompatible(const pq &slots, const activity &a) {
    vector<activity> earlyRoom = slots.top();
    return earlyRoom[earlyRoom.size() - 1].finish > a.start;
}

ostream& operator<<(ostream& os, const vector<activity> & acts) {
    for (auto a : acts) {
        cout<<a.id<<" "<<a.start<<" "<<a.finish<<endl;
    }

    return os;
}

vector<room> solve(room activities) {
    sort(activities.begin(), activities.end(), [](activity a1, activity a2) -> bool { return a1.finish < a2.finish; });
    pq slots;
    for (auto a : activities) {
        if (slots.empty() || incompatible(slots, a)) {
            room newRoom;
            newRoom.push_back(a);
            slots.push(newRoom);
        } else {
            room firstRoom = slots.top();
            firstRoom.push_back(a);
            slots.pop();
            slots.push(firstRoom);
        }
    }
    vector<room> rooms;
    while (!slots.empty()) {
        rooms.push_back(slots.top());
        slots.pop();
    }

    return rooms;
}

ostream& operator<<(ostream& os, const vector<room> & rooms) {
    os<<rooms.size()<<endl;
    for (auto s : rooms) {
        for (auto a : s) {
            os<<a.id<<" ";
        }
        os<<endl;
    }
    return os;
}

int main() {
    room in = read();

    vector<room> sol = solve(in);

    cout<<sol;

    return 0;
}