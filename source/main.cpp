// TUGAS KECIL 1 IF2211 STRATEGI ALGORITMA
// NAMA : Yasmin Farisah Salma
// NIM  : 13522140

#include <iostream> // I/O operations
#include <vector>   // dynamic arrays to store matrix & paths
#include <string>   // string class
#include <sstream>  // sequence generator
#include <map>      // mapping sequence to its reward
#include <fstream>  // file I/O
#include <random>   // randomized inputs
#include <chrono>   // duration
#include <cstdlib>  // system()
#include <set>      // for storing unique sequences
using namespace std;

// ---------- GLOBAL VARIABLES
int n, m, u, numOfSequences;      // n = rows, m = buffer size, u = column
int maxReward = INT_MIN;          // global variable to track the maximum reward found
vector<int> maxRewardPath;        // store the path of maximum reward
vector<vector<int>> allPaths;     // store all the possible paths
vector<vector<string>> matrix;    // matrix to store strings
map<string, int> sequenceRewards; // mapping sequence to its reward

// ---------- MAIN FUNCTIONS
// FUNCTION: To enter the inputs manually
void manualInput()
{
    cout << "\n   === MANUAL INPUT ===\n\n"
         << ">> Buffer size\t\t\t: ";
    cin >> m;

    int width, height;
    cout << ">> Matrix dimension (w h)\t: ";
    cin >> width >> height;

    // adjusting to the global variables
    u = width;
    n = height;

    matrix.resize(n, vector<string>(u));
    vector<vector<bool>> visited(n, vector<bool>(u, false));
    cout << ">> Matrix elements\t\t:\n";
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < u; ++j)
        {
            cin >> matrix[i][j];
        }
    }

    cout << "\n>> Number of sequences\t\t: ";
    cin >> numOfSequences;
    cin.ignore();

    set<string> uniqueSequences; // store unique sequences using set
    for (int i = 1; i <= numOfSequences; ++i)
    {
        string sequence;
        int reward;
        bool validInput = false;

        while (!validInput)
        {
            cout << ">> Sequence " << i << "\t\t\t: ";
            getline(cin, sequence);
            // make sure the sequence is unique
            if (uniqueSequences.find(sequence) != uniqueSequences.end())
            {
                cout << "!! This sequence already exist.\n!! Please enter a different sequence." << endl;
                system("pause");
                continue;
            }

            istringstream iss(sequence);
            string token;
            validInput = true;

            // validate tokens (alphanumeric & capital letters)
            while (iss >> token)
            {
                if (token.size() != 2 || !isalnum(token[0]) || !isalnum(token[1]) ||
                    (isalpha(token[0]) && !isupper(token[0])) || (isalpha(token[1]) && !isupper(token[1])))
                {
                    validInput = false;
                    cout << "!! Each token must consist of exactly 2 alphanumeric & in uppercase.\n!! Please re-enter sequence " << i << "! " << endl;
                    break;
                }
            }
        }

        if (validInput)
        {
            cout << ">> Sequence " << i << " reward\t\t: ";
            cin >> reward;
            cin.ignore();
            sequenceRewards[sequence] = reward;
            uniqueSequences.insert(sequence);
        }
    }
}

// FUNCTION: To randomized the inputs
void randomizedInput()
{
    int jumlah_token_unik, ukuran_buffer, ukuran_matriks_x, ukuran_matriks_y, jumlah_sekuens, ukuran_maksimal_sekuens;

    cout << "\n   === RANDOMIZED INPUT ===\n\n"
         << ">> Number of unique tokens\t: ";
    cin >> jumlah_token_unik;

    if (jumlah_token_unik <= 0) // error handling
    {
        cerr << "!! Number of unique tokens must be positive." << endl;
        return;
    }

    vector<string> tokens;
    tokens.reserve(jumlah_token_unik);
    cout << ">> Tokens (must be unique)\t: ";
    // validate tokens (alphanumeric & capital letters)
    for (int i = 0; i < jumlah_token_unik; ++i)
    {
        string token;
        while (true)
        {
            cin >> token;
            if (token.size() != 2 || !isalnum(token[0]) || !isalnum(token[1]) ||
                (isalpha(token[0]) && !isupper(token[0])) || (isalpha(token[1]) && !isupper(token[1])))
            {
                cout << "!! Invalid token.\n>> Please re-enter token\t: ";
                continue;
            }

            tokens.push_back(token);
            break;
        }
    }

    cout << ">> Buffer size\t\t\t: ";
    cin >> ukuran_buffer;
    cout << ">> Matrix dimension (w h)\t: ";
    cin >> ukuran_matriks_x >> ukuran_matriks_y;
    cout << ">> Number of sequences\t\t: ";
    cin >> jumlah_sekuens;
    cout << ">> Maximum tokens in sequences\t: ";
    cin >> ukuran_maksimal_sekuens;
    if (ukuran_maksimal_sekuens < 2)
        ukuran_maksimal_sekuens = 2;

    random_device rd;
    mt19937 gen(rd());

    n = ukuran_matriks_y;
    u = ukuran_matriks_x;
    m = ukuran_buffer;
    matrix.resize(n, vector<string>(u));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < u; ++j)
        {
            matrix[i][j] = tokens[gen() % jumlah_token_unik];
        }
    }

    set<string> uniqueSequences;
    sequenceRewards.clear();
    for (int i = 0; i < jumlah_sekuens; ++i)
    {
        stringstream sequence;
        string seqStr;
        bool uniqueSequenceFound = false;

        while (!uniqueSequenceFound)
        {
            sequence.str("");
            int sequenceLength = gen() % (ukuran_maksimal_sekuens - 1) + 2; // make sure that a sequence at least contains 2 tokens

            for (int j = 0; j < sequenceLength; ++j)
            {
                if (j > 0)
                    sequence << " ";
                sequence << tokens[gen() % jumlah_token_unik];
            }
            seqStr = sequence.str();

            if (uniqueSequences.find(seqStr) == uniqueSequences.end())
            {
                uniqueSequenceFound = true;
                uniqueSequences.insert(seqStr);
                int reward = gen() % 100 + 1;
                sequenceRewards[seqStr] = reward;
            }
        }
    }

    cout << "\n\n   === RESULT: ===\n\n";
    cout << ukuran_buffer << "\n"
         << ukuran_matriks_x << " " << ukuran_matriks_y << "\n";
    for (const auto &row : matrix)
    {
        for (const auto &elem : row)
        {
            cout << elem << " ";
        }
        cout << "\n";
    }
    cout << sequenceRewards.size() << "\n";
    for (const auto &seq : sequenceRewards)
    {
        cout << seq.first << "\n"
             << seq.second << "\n";
    }

    char proceed;
    cout << "\n   === CONFIRM INPUT ===\n"
         << ">> Proceed with this input? (y/n)"
         << ">> ";
    cin >> proceed;
    system("pause");

    if (proceed == 'n' || proceed == 'N')
    {
        exit(0);
    }
}

// FUNCTION: To read inputs from a .txt file in inputs folder
void fileInput()
{
    ifstream inputFile;
    string filename;
    string filePath;

    while (true)
    {
        cout << "\n   === FILE INPUT ===\n\n"
             << ">> .txt filename (without extension)\t: ";
        cin >> filename;
        filePath = "../inputs/" + filename + ".txt"; // make sure that it's a .txt file

        inputFile.open(filePath);
        if (inputFile.is_open())
        {
            break;
        }
        else
        {
            cerr << "File not found: " << filePath << ". Please try again." << endl;
            system("pause");
            system("cls");
        }
    }

    inputFile >> m;      // buffer size
    inputFile >> n >> u; // matrix dimension
    matrix.resize(n, vector<string>(u));

    // matrix elements
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < u; ++j)
        {
            inputFile >> matrix[i][j];
        }
    }

    // number of sequences
    inputFile >> numOfSequences;
    inputFile.ignore();

    // sequences and & rewards
    for (int i = 0; i < numOfSequences; ++i)
    {
        string sequence;
        int reward;
        getline(inputFile, sequence); // sequence
        inputFile >> reward;          // reward
        inputFile.ignore();
        sequenceRewards[sequence] = reward;
    }

    inputFile.close();
}

// FUNCTION: To calculate rewards in every path
int calculateReward(const vector<int> &path)
{
    string pathStr;
    for (int num : path)
    {
        if (!pathStr.empty())
            pathStr += " ";
        pathStr += matrix[num / u][num % u];
    }

    int totalReward = 0;
    for (const auto &seqReward : sequenceRewards)
    {
        if (pathStr.find(seqReward.first) != string::npos)
        {
            totalReward += seqReward.second;
        }
    }
    return totalReward;
}

// FUNCTION: To store every path
void storePath(const vector<int> &path)
{
    allPaths.push_back(path);
}

// FUNCTION: To print the optimum path, its reward, and its coordinates
void printPath(const vector<int> &path, bool printReward = true)
{
    int reward = calculateReward(path);
    if (printReward)
    {
        cout << endl;
        cout << endl;
        cout << "   === RESULT: ===\n\n";
        cout << reward; // print total reward
    }
    cout << endl;
    for (int num : path)
    {
        int x = num / u;
        int y = num % u;
        cout << matrix[x][y] << " ";
    }

    // print tokens coordinates
    cout << endl;
    for (int num : path)
    {
        int x = num / u;
        int y = num % u;
        cout << y + 1 << ", " << x + 1 << endl;
    }
}

// FUNCTION: to validate a coordinate whether it's in range & hasn't been visited yet in the current path
bool isValid(int x, int y, vector<vector<bool>> &visited)
{
    return x >= 0 && x < n && y >= 0 && y < u && !visited[x][y];
}

// FUNCTION: brute force algorithm to find all the possible paths & rewards
void findPaths(int x, int y, vector<int> &path, vector<vector<bool>> &visited, bool horizontal)
{
    visited[x][y] = true;
    path.push_back(x * u + y);

    if (path.size() == m)
    {
        int currentReward = calculateReward(path);
        if (currentReward > maxReward || maxRewardPath.empty())
        {
            maxReward = currentReward;
            maxRewardPath = path;
        }
        storePath(path);
    }
    else
    {
        if (!horizontal)
        {
            // move vertically down
            for (int i = x + 1; i < n; ++i)
            {
                if (isValid(i, y, visited))
                {
                    findPaths(i, y, path, visited, !horizontal);
                }
            }
            // move vertically up
            for (int i = x - 1; i >= 0; --i)
            {
                if (isValid(i, y, visited))
                {
                    findPaths(i, y, path, visited, !horizontal);
                }
            }
        }
        else
        {
            // move horizontally right & left
            for (int j = 0; j < u; ++j)
            {
                if (j != y && isValid(x, j, visited))
                {
                    findPaths(x, j, path, visited, !horizontal);
                }
            }
        }
    }

    visited[x][y] = false;
    path.pop_back();
}

// FUNCTION: Save the optimum path to a file with the specified format, asking user for file name
void saveOptimumPath(const vector<int> &path, const long long executionTime)
{
    string fileName;
    cout << ">> Filename (without extension): ";
    cin >> fileName;
    fileName = "../test/" + fileName + ".txt";

    ofstream file(fileName);
    if (!file.is_open())
    {
        cerr << "Failed to open file for writing." << endl;
        return;
    }

    int reward = calculateReward(path);
    file << reward << "\n";

    for (int num : path)
    {
        file << matrix[num / u][num % u] << " ";
    }
    file << "\n";

    for (int num : path)
    {
        int x = num / u;
        int y = num % u;
        file << y + 1 << ", " << x + 1 << "\n";
    }

    file << executionTime << " ms\n";

    file.close();
    cout << ">> Saved to " << fileName << endl;
}

// ---------- DEBUGGING FUNCTIONS
// FUNCTION: to print all the possible paths based on inputs
void printAllPaths()
{
    cout << "All possible paths:\n";
    for (const auto &path : allPaths)
    {
        for (int num : path)
        {
            int x = num / u;
            int y = num % u;
            cout << matrix[x][y] << " ";
        }
        int reward = calculateReward(path);
        cout << "= " << reward << endl;
    }
}

// FUNCTION: to save all the possible paths based on inputs
void saveAllPathsToFile()
{
    string fileName;
    cout << ">> Filename (without extension): ";
    cin >> fileName;
    fileName = "../test/" + fileName + ".txt";
    ofstream file(fileName);
    if (!file.is_open())
    {
        cout << "Failed to open file for writing." << endl;
        return;
    }

    for (const auto &path : allPaths)
    {
        for (int num : path)
        {
            file << matrix[num / u][num % u] << " ";
        }
        int reward = calculateReward(path);
        file << "= " << reward << endl;
    }

    file.close();
    cout << "All paths saved to " << fileName << endl;
}

int main()
{
    using namespace std::chrono;

    int inputType;
    bool validInput = false;

    while (!validInput)
    {
        cout << "\n   === CYBERPUNK 2077 BREACH PROTOCOL===\n"
             << "___________________________________________\n"
             << "|                                          |\n"
             << "| Tugas Kecil 1 IF2211 Strategi Algoritma  |\n"
             << "| 2024 | 13522140, Yasmin Farisah Salma    |\n"
             << "|__________________________________________|\n\n"
             << "=== CHOOSE INPUT TYPE ===\n"
             << "  1. Manual input\n"
             << "  2. Randomized input\n"
             << "  3. File input\n"
             << "  4. Exit\n\n"
             << "Enter your choice (1-4): ";
        cin >> inputType;
        system("pause");
        system("cls");

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n>> Invalid input.\n>>Please enter a number between 1 and 4." << endl;
            continue;
        }

        cin.ignore();

        switch (inputType)
        {
        case 1:
            manualInput();
            validInput = true;
            break;
        case 2:
            randomizedInput();
            validInput = true;
            break;
        case 3:
            fileInput();
            validInput = true;
            break;
        case 4:
            cout << ">> Exiting program." << endl;
            return 0;
        default:
            cout << "\n>> Invalid choice.\n>>Please enter a number between 1 and 4." << endl;
        }
    }

    // start timing after all inputs are done
    auto start = high_resolution_clock::now();

    vector<vector<bool>> visited(n, vector<bool>(u, false));
    for (int i = 0; i < u; ++i)
    {
        vector<int> path;
        findPaths(0, i, path, visited, false);
    }

    // printAllPaths();

    // print and save the optimum path
    if (!maxRewardPath.empty())
    {
        printPath(maxRewardPath); // prints the path, reward, and coordinates
    }
    else
    {
        cout << ">> No paths found.\n";
    }

    // stop timing after printing the coordinates
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << endl;
    cout << duration.count() << " ms\n";

    char saveSolution;
    cout << endl;
    cout << endl;
    cout << "   === SAVE ===\n\n"
         << "Do you want to save the solution? (y/n)\n"
         //  << "Do you want to save all the paths? (y/n)\n"
         << ">> ";
    cin >> saveSolution;
    if (saveSolution == 'y' || saveSolution == 'Y')
    {
        saveOptimumPath(maxRewardPath, duration.count());
        // saveAllPathsToFile();
    }
    else
    {
        cout << ">> Solution's not saved." << endl;
    }

    return 0;
}