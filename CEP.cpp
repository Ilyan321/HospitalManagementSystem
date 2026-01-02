#include <iostream>
#include <string>

using namespace std;

// Basic class for patient details
class Patient {
public:
    int id;
    string name;
    int priority;

    Patient() {
        id = 0;
        name = "";
        priority = 3;
    }

    Patient(int i, string n, int p) {
        id = i;
        name = n;
        priority = p;
    }
};

// Linked list node for hash table
class Node {
public:
    Patient data;
    Node* next;
    Node(Patient p) {
        data = p;
        next = NULL;
    }
};

// Patient registry using Hash Table (Array of Nodes)
class PatientRegistry {
public:
    Node* table[10];

    PatientRegistry() {
        for (int i = 0; i < 10; i++) {
            table[i] = NULL;
        }
    }

    void addPatient(Patient p) {
        int index = p.id % 10;
        Node* newNode = new Node(p);
        newNode->next = table[index];
        table[index] = newNode;
    }

    void findPatient(int searchId) {
        int index = searchId % 10;
        Node* temp = table[index];
        bool found = false;

        while (temp != NULL) {
            if (temp->data.id == searchId) {
                cout << "Record Found: " << temp->data.name << " (Priority: " << temp->data.priority << ")" << endl;
                found = true;
                break;
            }
            temp = temp->next;
        }
        if (!found) cout << "ID not found." << endl;
    }
};


class ManualTriage {
public:
    Patient queueArray[50];
    int count;

    ManualTriage() {
        count = 0;
    }

    // Adds patient and keeps array sorted by priority
    void push(Patient p) {
        if (count < 50) {
            queueArray[count] = p;
            count++;

            // Basic bubble sort to keep highest priority at the end (index count-1)

            for (int i = 0; i < count - 1; i++) {
                for (int j = 0; j < count - i - 1; j++) {
                    if (queueArray[j].priority < queueArray[j+1].priority) {
                        Patient temp = queueArray[j];
                        queueArray[j] = queueArray[j+1];
                        queueArray[j+1] = temp;
                    }
                }
            }
        }
    }

    Patient pop() {
        Patient p = queueArray[count - 1];
        count--;
        return p;
    }

    bool isEmpty() {
        return count == 0;
    }
};

class ResourceManager {
public:
    int totalBeds;
    int totalVents;

    ResourceManager() {
        totalBeds = 5;
        totalVents = 2;
    }
};

int main() {
    ManualTriage triage;
    PatientRegistry reg;
    ResourceManager res;

    int choice, p_id, p_pri;
    string p_name;

    cout << "--- SMART HOSPITAL MANAGEMENT---" << endl;

    while (true) {
        cout << "\n1. Add Patient\n2. Treat Next\n3. Search\n4. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1:{

                cout << "ID: "; cin >> p_id;
                cout << "Name: "; cin >> p_name;
                cout << "Priority (1-High, 3-Low): "; cin >> p_pri;
                {
                    Patient newP(p_id, p_name, p_pri);
                    triage.push(newP);
                    reg.addPatient(newP);
                }}
                break;

            case 2:
                if (triage.isEmpty()) {
                    cout << "No patients!" << endl;
                } else {
                    Patient current = triage.pop();
                    cout << "Treating: " << current.name << endl;

                    if (current.priority == 1 && res.totalVents > 0) {
                        res.totalVents--;
                        cout << "Ventilator assigned. Vents left: " << res.totalVents << endl;
                        cout<<"Patient treated.\n";
                    } else if (res.totalBeds > 0) {
                        res.totalBeds--;
                        cout << "Bed assigned. Beds left: " << res.totalBeds << endl;
                          cout<<"Patient treated.\n";
                    } else {
                        cout << "No resources available!" << endl;
                    }
                }
                break;

            case 3:
                int s_id;
                cout << "Enter ID: "; cin >> s_id;
                reg.findPatient(s_id);
                break;

            case 4:
                return 0;

            default:
                cout << "Invalid choice." << endl;
        }
    }
    return 0;
}
