#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <iomanip>
#include <string>
using namespace std;

class MiceAndHoles {
private:
    vector<int> mice_pos;
    vector<int> holes_pos;

    void print_vector(const vector<int>& vec, const string& label) const 
    {
        cout << label << " [";
        for (int i = 0; i < vec.size(); ++i) 
        {
            cout << vec[i];
            if (i < vec.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
    }

    void input_positions(vector<int>& positions, const string& entity_name) 
    {
        cout << "Enter " << entity_name << " positions: " <<endl;
        for (int& pos : positions) cin >> pos;
    }

    void calculate_distances() const 
    {
        vector<int> distances;
        for (int i = 0; i < mice_pos.size(); i++) 
        {
            int dist = abs(mice_pos[i] - holes_pos[i]);
            cout << "Mice " << mice_pos[i] << " -> Hole at " << holes_pos[i] << " | Distance: " << dist << endl;
            distances.push_back(dist);
        }

        int max_distance = *max_element(distances.begin(), distances.end());
        cout << "\nThe minimum time required for all mice to reach holes is: " << max_distance << endl;
    }

public:
   
    void RunMH() {
        int m, h;
        cout << "Enter number of mice: ";
        cin >> m;
        cout << "Enter number of holes: ";
        cin >> h;

        if (m != h) {
            cout << "Number of mice and holes must be the same!" << endl;
            return;
        }

        mice_pos.resize(m);
        holes_pos.resize(h);

        input_positions(mice_pos, "mice");
        input_positions(holes_pos, "holes");

        cout << "\nGiven positions:" << endl;
        print_vector(mice_pos, "Mice positions");
        print_vector(holes_pos, "Holes positions");

        sort(mice_pos.begin(), mice_pos.end());
        sort(holes_pos.begin(), holes_pos.end());

        cout << "\nSorted positions:" << endl;
        print_vector(mice_pos, "Mice positions");
        print_vector(holes_pos, "Holes positions");
        cout << "\n";
        calculate_distances();
    }
};
class Knapsack
{
public:
    struct Items
    {
        int profit;
        int weight;
    };

    int knapsack(int capacity, vector<Items>& items, vector<int>& selectedItems)
    {
        int n = items.size();
        vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

        for (int i = 1; i <= n; i++)
        {
            for (int w = 1; w <= capacity; w++)
            {
                if (items[i - 1].weight <= w)
                {
                    dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - items[i - 1].weight] + items[i - 1].profit);
                }
                else
                {
                    dp[i][w] = dp[i - 1][w];
                }
            }
        }

        int w = capacity;
        for (int i = n; i > 0 && w > 0; i--)
        {
            
            if (dp[i][w] != dp[i - 1][w])
            {
                selectedItems.push_back(i - 1); 
                w -= items[i - 1].weight;      
            }
        }

        return dp[n][capacity];
    }

    void RunKS()
    {
        int capacity;
        cout << "Enter the capacity of the knapsack: ";
        cin >> capacity;

        vector<Items> items;
        int n;

        cout << "Enter the number of items: ";
        cin >> n;

       
        for (int i = 0; i < n; i++)
        {
            Items item;
            system("cls");
            cout << "Knapsack capacity - " << capacity <<endl;
            cout << "Number of items - " << n << endl;
            cout << "Enter profit for item " << i + 1 << ": ";
            cin >> item.profit;
            cout << "Enter weight for item " << i + 1 << ": ";
            cin >> item.weight;
            items.push_back(item);
           
        }

        vector<int> selectedItems;
        int maxProfit = knapsack(capacity, items, selectedItems);
        system("cls");
        cout << "Maximum profit: " << maxProfit << endl;
        cout << "Selected items:" << endl;
        for (int i = selectedItems.size() - 1; i >= 0; i--) // Reverse order for correct item sequence
        {
            int index = selectedItems[i];
            cout << "Item " << index + 1 << " (Profit: " << items[index].profit
                << ", Weight: " << items[index].weight << ")" << endl;
        }
    }
};
class JobSequencing
{
public:
    struct Job {
        int id;
        int profit;
        int deadline;
    };

    static bool compare(const Job& a, const Job& b) {
        return a.profit > b.profit;
    }

    void RunJS() {
        int n;
        cout << "Enter the number of jobs: ";
        cin >> n;

        vector<Job> jobs(n);
        for (int i = 0; i < n; i++) {
            cout << "Enter profit and deadline for job " << i + 1 << ": ";
            jobs[i].id = i + 1;
            cin >> jobs[i].profit >> jobs[i].deadline;
        }

        sort(jobs.begin(), jobs.end(), compare);

        int maxDeadline = 0;
        for (const auto& job : jobs) {
            maxDeadline = max(maxDeadline, job.deadline);
        }

        vector<int> result(maxDeadline + 1, -1);
        int totalProfit = 0;

        for (const auto& job : jobs) {
            for (int j = job.deadline; j > 0; j--) {
                if (result[j] == -1) {
                    result[j] = job.id;
                    totalProfit += job.profit;
                    break;
                }
            }
        }

        cout << "Max profit: " << totalProfit << endl;
        cout << "Selected jobs in sequence: ";
        for (int i = 1; i <= maxDeadline; i++) {
            if (result[i] != -1)
                cout << "Job " << result[i] << " ";
        }
        cout << endl;
    }
};
class ActivitySelection {
public:
    struct Activity {
        int start;
        int finish;
        int index;
    };

    static bool compare(const Activity& a, const Activity& b) {
        return a.finish < b.finish;
    }
    void RunAS() {
        int n;
        cout << "Enter the number of activities: ";
        cin >> n;

        vector<Activity> activities(n);
        system("cls");
        displayHeader(n);

        for (int i = 0; i < n; i++) {
            cout << "Enter start and finish time for activity " << i + 1 << ": ";
            cin >> activities[i].start >> activities[i].finish;
            activities[i].index = i + 1;

            system("cls");
            displayActivities(activities, n, i);
        }

        sort(activities.begin(), activities.end(), compare);

        cout << "\nSelected activities:\n";
        cout << "+-----------+---------------------+\n";
        cout << "| Activity  | Time (Start-Finish) |\n";
        cout << "+-----------+---------------------+\n";

        int lastFinishTime = -1;
        for (const auto& activity : activities) {
            if (activity.start >= lastFinishTime) {
                cout << "| " << setw(9) << activity.index
                    << " | " << setw(7) << activity.start
                    << " ------ " << setw(3) << activity.finish << "  |\n";
                lastFinishTime = activity.finish;
            }
        }
        cout << "+-----------+---------------------+\n";
    }

private:
    void displayHeader(int n) {
        cout << "+-----------+-----------+-----------+\n";
        cout << "| Activity  | Start     | Finish    |\n";
        cout << "+-----------+-----------+-----------+\n";

        for (int i = 0; i < n; i++) {
            cout << "| " << setw(9) << i + 1
                << " | " << setw(9) << "-"
                << " | " << setw(9) << "-" << " |\n";
        }
        cout << "+-----------+-----------+-----------+\n";
    }

    void displayActivities(const vector<Activity>& activities, int n, int filledRows) {
        displayHeader(n);
        system("cls");
        cout << "+-----------+-----------+-----------+\n";
        cout << "| Activity  | Start     | Finish    |\n";
        cout << "+-----------+-----------+-----------+\n";
        for (int i = 0; i < n; i++) {
            if (i <= filledRows) {
                cout << "| " << setw(9) << activities[i].index
                    << " | " << setw(9) << activities[i].start
                    << " | " << setw(9) << activities[i].finish << " |\n";
            }
            else {
                cout << "| " << setw(9) << i + 1
                    << " | " << setw(9) << "-"
                    << " | " << setw(9) << "-" << " |\n";
            }
        }
        cout << "+-----------+-----------+-----------+\n";
    }
};
class HuffmanCoding
{
    struct Node {
        char data;
        int freq;
        Node* left, * right;
        Node(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
    };

    struct compare {
        bool operator()(Node* left, Node* right) {
            return left->freq > right->freq;
        }
    };

    void printCodes(Node* root, string str, unordered_map<char, int>& codeLengths) {
        if (!root) return;

        if (root->data != '$') {
            cout << root->data << ": " << str << endl;
            codeLengths[root->data] = str.length(); 
        }

        printCodes(root->left, str + "0", codeLengths);
        printCodes(root->right, str + "1", codeLengths);
    }

public:
    void RunHC() {
        int n;
        cout << "Enter the number of characters: ";
        cin >> n;

        vector<char> chars(n);
        vector<int> freqs(n);
        for (int i = 0; i < n; i++) {
            cout << "Enter character and its frequency: ";
            cin >> chars[i] >> freqs[i];
        }

        priority_queue<Node*, vector<Node*>, compare> minHeap;
        for (int i = 0; i < n; i++) {
            minHeap.push(new Node(chars[i], freqs[i]));
        }

        while (minHeap.size() != 1) {
            Node* left = minHeap.top(); minHeap.pop();
            Node* right = minHeap.top(); minHeap.pop();

            Node* top = new Node('$', left->freq + right->freq);
            top->left = left;
            top->right = right;

            minHeap.push(top);
        }

        cout << "Huffman Codes:" << endl;
        unordered_map<char, int> codeLengths;
        printCodes(minHeap.top(), "", codeLengths);

        int totalBits = 0;
        for (int i = 0; i < n; i++) {
            totalBits += freqs[i] * codeLengths[chars[i]];
        }

        cout << "Total bit size with Huffman encoding: " << totalBits << " bits" << endl;
    }
};
void showMenu() {
    system("cls");
    cout << "Select an algorithm to run:" << endl;
    cout << "1. Mice and Holes" << endl;
    cout << "2. Knapsack" << endl;
    cout << "3. Job Sequencing" << endl;
    cout << "4. Activity Selection" << endl;
    cout << "5. Huffman Coding" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    int choice;
    MiceAndHoles miceAndHoles;
    Knapsack knapsack;
    JobSequencing jobSequencing;
    ActivitySelection activitySelection;
    HuffmanCoding huffmanCoding;
    do {
        showMenu();
        cin >> choice;

        switch (choice) 
        {
        case 1:
            system("cls");
            miceAndHoles.RunMH();
            cin.get();
            cin.ignore();
            break;
        case 2:
            system("cls");
            knapsack.RunKS();
            cin.get();
            cin.ignore();
            break;
        case 3:
            system("cls");
            jobSequencing.RunJS();
            cin.get();
            cin.ignore();
            break;
        case 4:
            system("cls");
            activitySelection.RunAS();
            cin.get();
            cin.ignore();
            break;
        case 5:
            system("cls");
            huffmanCoding.RunHC();
            cin.get();
            cin.ignore();
            break;
        case 0:
            system("cls");
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);

    return 0;
}