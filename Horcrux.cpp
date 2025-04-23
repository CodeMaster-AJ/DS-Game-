#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <list>
#include <unordered_map>

using namespace std;

// ---------- Inventory using Linked List ----------
class Inventory {
    list<string> items;
public:
    void addItem(string item) {
        items.push_back(item);
        cout << "✨ Collected: " << item << endl;
    }

    bool hasItem(string item) {
        for (string i : items) {
            if (i == item) return true;
        }
        return false;
    }

    void show() {
        cout << "\n📦 Inventory:\n";
        if (items.empty()) cout << " (empty)\n";
        else for (string i : items) cout << " - " << i << endl;
    }
};

// ---------- Room Structure ----------
struct Room {
    string name;
    string description;
    vector<int> connections; // Store connected room indices
};

// ---------- Game Title ----------
void printTitle() {
    cout << "\n";
    cout << "┌────────────────────────────────────────────┐\n";
    cout << "│                                            │\n";
    cout << "│         ✧ HORCRUX HUNT ✧                  │\n";
    cout << "│     A Harry Potter Adventure Game          │\n";
    cout << "│                                            │\n";
    cout << "└────────────────────────────────────────────┘\n";
    cout << "\n";
    cout << "\n";
}


// ---------- Help Menu ----------
void showHelp() {
    cout << "\n📜 Commands:\n";
    cout << " move [number]   - Go to a connected room\n";
    cout << " back            - Return to previous room\n";
    cout << " inventory       - Show items\n";
    cout << " help            - Show this menu\n";
    cout << " exit            - Quit game\n\n";
}

// ---------- Main Game ----------
int main() {
    printTitle();

    vector<Room> rooms = {
        {"Gryffindor Common Room", "Start your journey here.", {1, 2}},
        {"Dumbledore's Office", "A magical room full of wisdom.", {3, 4}},
        {"Hogwarts Library", "Old books and forgotten spells.", {5, 3}},
        {"Room of Requirement", "Appears when you need it.", {6, 7}},
        {"Astronomy Tower", "Stars might show your fate.", {8, 3}},
        {"Potions Classroom", "Bubbling brews everywhere.", {9, 7}},
        {"Forbidden Forest", "Dark, dangerous, mysterious.", {10, 8}},
        {"Great Hall", "Feasts and destiny.", {10, 11}},
        {"Chamber of Secrets", "The final battle awaits.", {}},
        {"Hogsmeade", "A cheerful wizarding village.", {10, 11}},
        {"Black Lake", "Still and deep water surrounds you.", {8, 10}},
        {"Exit", "Goodbye, brave wizard!", {}}
    };

    stack<int> history;
    queue<string> tasks;
    tasks.push("Find Elder Wand");
    tasks.push("Find Horcrux");
    tasks.push("Defeat Voldemort");

    Inventory inventory;
    int current = 0;

    showHelp();

    while (true) {
        cout << "\n🏰 You are in: " << rooms[current].name << "\n";
        cout << rooms[current].description << "\n";

        // Rewards
        if (current == 1 && !inventory.hasItem("Elder Wand")) {
            inventory.addItem("Elder Wand");
        } else if (current == 6 && !inventory.hasItem("Horcrux")) {
            inventory.addItem("Horcrux");
        } else if (current == 8) {
            if (inventory.hasItem("Elder Wand") && inventory.hasItem("Horcrux")) {
                cout << "\n🔥 You defeated Voldemort with your items!\n🏆 Mission Complete!\n";
                break;
            } else {
                cout << "❌ You need the Elder Wand and Horcrux!\n";
                current = history.top(); history.pop();
                continue;
            }
        }

        // Show next options
        if (!rooms[current].connections.empty()) {
            cout << "\n🔀 Paths:\n";
            for (int i = 0; i < rooms[current].connections.size(); ++i) {
                int idx = rooms[current].connections[i];
                cout << " " << i << " - " << rooms[idx].name << endl;
            }
        }

        // Show task
        if (!tasks.empty()) {
            cout << "🧩 Task: " << tasks.front() << endl;
            if ((tasks.front() == "Find Elder Wand" && inventory.hasItem("Elder Wand")) ||
                (tasks.front() == "Find Horcrux" && inventory.hasItem("Horcrux")))
                tasks.pop();
        }

        // User Input
        cout << "\n> ";
        string cmd;
        getline(cin, cmd);

        if (cmd == "help") showHelp();
        else if (cmd == "inventory") inventory.show();
        else if (cmd == "back") {
            if (!history.empty()) {
                current = history.top(); history.pop();
            } else cout << "🪄 No previous room.\n";
        } else if (cmd.substr(0, 5) == "move ") {
            int choice = stoi(cmd.substr(5));
            if (choice >= 0 && choice < rooms[current].connections.size()) {
                history.push(current);
                current = rooms[current].connections[choice];
            } else cout << "🚫 Invalid choice.\n";
        } else if (cmd == "exit") {
            cout << "👋 Exiting. Farewell!\n"; break;
        } else {
            cout << "❓ Invalid command. Type 'help' to see options.\n";
        }
    }

    return 0;
}
