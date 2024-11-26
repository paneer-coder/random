#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <ctime>
#include <limits> // for INT_MIN and INT_MAX

using namespace std;

struct Date {
    int day, month, year;
};

class User {
public:
    string name;
    Date dob; // date of birth
    int comments;

    User(string n, Date d, int c) : name(n), dob(d), comments(c) {}
};

class SocialNetwork {
private:
    unordered_map<int, User*> users; // stores users by ID
    unordered_map<int, vector<int>> adjacencyList; // adjacency list to represent graph

public:
    void addUser(int id, string name, Date dob, int comments) {
        users[id] = new User(name, dob, comments);
    }

    void addFriendship(int id1, int id2) {
        adjacencyList[id1].push_back(id2);
        adjacencyList[id2].push_back(id1);
    }

    void findUserWithMaxFriends() {
        int maxFriends = 0;
        int userIdWithMaxFriends = -1;
        
        for (const auto& user : adjacencyList) {
            int friendCount = user.second.size();
            if (friendCount > maxFriends) {
                maxFriends = friendCount;
                userIdWithMaxFriends = user.first;
            }
        }

        if (userIdWithMaxFriends != -1) {
            cout << "User with maximum friends: " << users[userIdWithMaxFriends]->name << " with " << maxFriends << " friends.\n";
        }
    }

    void findUsersWithMaxAndMinComments() {
        if (users.empty()) return;

        int maxComments = numeric_limits<int>::min();
        int minComments = numeric_limits<int>::max();
        User* userWithMaxComments = nullptr;
        User* userWithMinComments = nullptr;

        for (const auto& userPair : users) {
            int comments = userPair.second->comments;
            if (comments > maxComments) {
                maxComments = comments;
                userWithMaxComments = userPair.second;
            }
            if (comments < minComments) {
                minComments = comments;
                userWithMinComments = userPair.second;
            }
        }

        cout << "User with maximum comments: " << userWithMaxComments->name << " with " << maxComments << " comments.\n";
        cout << "User with minimum comments: " << userWithMinComments->name << " with " << minComments << " comments.\n";
    }

    void findUsersWithBirthdayThisMonth() {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        int currentMonth = 1 + ltm->tm_mon;

        cout << "Users with birthdays in this month:\n";
        for (const auto& userPair : users) {
            if (userPair.second->dob.month == currentMonth) {
                cout << userPair.second->name << " has a birthday on " << userPair.second->dob.day << "/" << userPair.second->dob.month << "\n";
            }
        }
    }

    void DFS(int startId) {
        unordered_map<int, bool> visited;
        DFSUtil(startId, visited);
    }

    void BFS(int startId) {
        unordered_map<int, bool> visited;
        queue<int> queue;

        visited[startId] = true;
        queue.push(startId);

        while (!queue.empty()) {
            int id = queue.front();
            cout << users[id]->name << " ";
            queue.pop();

            for (int friendId : adjacencyList[id]) {
                if (!visited[friendId]) {
                    visited[friendId] = true;
                    queue.push(friendId);
                }
            }
        }
        cout << "\n";
    }

private:
    void DFSUtil(int id, unordered_map<int, bool>& visited) {
        visited[id] = true;
        cout << users[id]->name << " ";

        for (int friendId : adjacencyList[id]) {
            if (!visited[friendId]) {
                DFSUtil(friendId, visited);
            }
        }
    }
};

int main() {
    SocialNetwork sn;
    int numUsers, numFriendships;

    cout << "Enter the number of users: ";
    cin >> numUsers;

    for (int i = 0; i < numUsers; ++i) {
        int id, comments;
        string name;
        Date dob;

        cout << "Enter user ID: ";
        cin >> id;
        cout << "Enter user name: ";
        cin >> name;
        cout << "Enter date of birth (day month year): ";
        cin >> dob.day >> dob.month >> dob.year;
        cout << "Enter the number of comments: ";
        cin >> comments;

        sn.addUser(id, name, dob, comments);
    }

    cout << "Enter the number of friendships: ";
    cin >> numFriendships;

    for (int i = 0; i < numFriendships; ++i) {
        int id1, id2;
        cout << "Enter the IDs of the two friends: ";
        cin >> id1 >> id2;

        sn.addFriendship(id1, id2);
    }

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Find user with maximum friends\n";
        cout << "2. Find users with maximum and minimum comments\n";
        cout << "3. Find users with birthdays this month\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                sn.findUserWithMaxFriends();
                break;
            case 2:
                sn.findUsersWithMaxAndMinComments();
                break;
            case 3:
                sn.findUsersWithBirthdayThisMonth();
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 4);

    return 0;
}

