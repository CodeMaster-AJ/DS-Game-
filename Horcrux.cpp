
#include <iostream>
#include <string>
using namespace std;

// ------------------ Queue: For Tasks ------------------
#define SIZE 5
class Queue {
    string arr[SIZE];
    int front, rear;

public:
    Queue() { front = rear = -1; }

    void enqueue(string task) {
        if (rear == SIZE - 1) return;
        if (front == -1) front = 0;
        arr[++rear] = task;
    }

    void dequeue() {
        if (front == -1 || front > rear) return;
        front++;
    }

    string peek() {
        if (front == -1 || front > rear) return "No tasks!";
        return arr[front];
    }

    bool empty() {
        return front == -1 || front > rear;
    }
};

// ------------------ Stack: For Room History ------------------
#define MAX 20
class Stack {
    string arr[MAX];
    int top;

public:
    Stack() { top = -1; }

    void push(string room) {
        if (top < MAX - 1) arr[++top] = room;
    }

    string pop() {
        if (top >= 0) return arr[top--];
        return "Gryffindor Common Room";
    }

    bool empty() { return top == -1; }
};

// ------------------ Linked List: For Inventory ------------------
struct Node {
    string item;
    Node* next;
};

class LinkedList {
    Node* head;

public:
    LinkedList() { head = nullptr; }

    void addItem(string item) {
        Node* newNode = new Node{item, head};
        head = newNode;
    }

    void showItems() {
        Node* temp = head;
        cout << "🧳 Inventory: ";
        if (!temp) {
            cout << "(Empty)\n";
            return;
        }
        while (temp) {
            cout << temp->item << " ";
            temp = temp->next;
        }
        cout << "\n";
    }

    bool hasItem(string item) {
        Node* temp = head;
        while (temp) {
            if (temp->item == item) return true;
            temp = temp->next;
        }
        return false;
    }
};

// ------------------ Game Class ------------------
class Game {
    string currentRoom;
    Stack history;
    Queue tasks;
    LinkedList inventory;

public:
    Game() {
        currentRoom = "Gryffindor Common Room";
        tasks.enqueue("Find the Elder Wand");
        tasks.enqueue("Destroy the Horcrux");
        tasks.enqueue("Defeat Voldemort");
    }

    void help() {
        cout << "\n📖 How to Play:\n";
        cout << "-----------------------------------\n";
        cout << "🔹 move [location]  → Go to another place\n";
        cout << "🔹 back             → Return to previous room\n";
        cout << "🔹 help             → Show help/instructions\n";
        cout << "🔹 exit             → Quit the game\n";
        cout << "-----------------------------------\n\n";
    }

    void showRoom() {
        cout << "\n📍 You are in: " << currentRoom << "\n";

        if (currentRoom == "Dumbledore's Office" && !inventory.hasItem("Elder Wand")) {
            cout << "✨ You found the Elder Wand!\n";
            inventory.addItem("Elder Wand");
            tasks.dequeue();
        } else if (currentRoom == "Forbidden Forest" && !inventory.hasItem("Horcrux")) {
            cout << "💀 You found a hidden Horcrux!\n";
            inventory.addItem("Horcrux");
            tasks.dequeue();
        } else if (currentRoom == "Chamber of Secrets") {
            if (inventory.hasItem("Elder Wand") && inventory.hasItem("Horcrux")) {
                cout << "⚔️ Using the Elder Wand, you destroyed the Horcrux and defeated Voldemort!\n";
                tasks.dequeue();
                cout << "🏆 Mission Accomplished. Game Over!\n";
                exit(0);
            } else {
                cout << "🚫 You need the Elder Wand and Horcrux to defeat Voldemort.\n";
            }
        }

        if (!tasks.empty())
            cout << "📝 Task: " << tasks.peek() << "\n";

        // Show options
        cout << "➡️ Paths you can take from here:\n";
        if (currentRoom == "Gryffindor Common Room") {
            cout << " - move office\n";
            cout << " - move library\n";
        } else if (currentRoom == "Dumbledore's Office") {
            cout << " - move forest\n";
            cout << " - move tower\n";
        } else if (currentRoom == "Library") {
            cout << " - move forest\n";
            cout << " - move hall\n";
        } else if (currentRoom == "Astronomy Tower") {
            cout << " - move chamber\n";
            cout << " - move forest\n";
        } else if (currentRoom == "Great Hall") {
            cout << " - move chamber\n";
            cout << " - move common\n";
        } else if (currentRoom == "Forbidden Forest") {
            cout << " - move chamber\n";
            cout << " - move hall\n";
        } else if (currentRoom == "Chamber of Secrets") {
            cout << " - Final Battle\n";
        }
    }

    void move(string room) {
        string destination = "";

        if (currentRoom == "Gryffindor Common Room") {
            if (room == "office") destination = "Dumbledore's Office";
            else if (room == "library") destination = "Library";
        } else if (currentRoom == "Dumbledore's Office") {
            if (room == "forest") destination = "Forbidden Forest";
            else if (room == "tower") destination = "Astronomy Tower";
        } else if (currentRoom == "Library") {
            if (room == "forest") destination = "Forbidden Forest";
            else if (room == "hall") destination = "Great Hall";
        } else if (currentRoom == "Astronomy Tower") {
            if (room == "chamber") destination = "Chamber of Secrets";
            else if (room == "forest") destination = "Forbidden Forest";
        } else if (currentRoom == "Great Hall") {
            if (room == "chamber") destination = "Chamber of Secrets";
            else if (room == "common") destination = "Gryffindor Common Room";
        } else if (currentRoom == "Forbidden Forest") {
            if (room == "chamber") destination = "Chamber of Secrets";
            else if (room == "hall") destination = "Great Hall";
        }

        if (!destination.empty()) {
            history.push(currentRoom);
            currentRoom = destination;
        } else {
            cout << "❌ Invalid path from here. Try again.\n";
        }
    }

    void goBack() {
        if (!history.empty()) {
            currentRoom = history.pop();
        } else {
            cout << "🔙 You're at the start!\n";
        }
    }

    void play() {
        string command, arg;
        cout << "⚡ Welcome to: Horcrux Hunt - A Harry Potter Text Game ⚡\n";
        help();

        while (true) {
            showRoom();
            inventory.showItems();
            cout << "\nCommand > ";
            cin >> command;

            if (command == "move") {
                cin >> arg;
                move(arg);
            } else if (command == "back") {
                goBack();
            } else if (command == "help") {
                help();
            } else if (command == "exit") {
                cout << "👋 Goodbye, Wizard!\n";
                break;
            } else {
                cout << "❓ Unknown command. Use 'help' to see options.\n";
            }
        }
    }
};

// ------------------ Main ------------------
int main() {
    Game game;
    game.play();
    return 0;
}
