#include <iostream>
#include <vector>
#include <cctype>

using namespace std;

// Function to split the message to letters
vector<char> string_to_char(const string& message) {
    vector<char> letters;
    for (char c : message) {
        // Making sure the char is a letter
        if (isalpha(c)) {
            letters.push_back(toupper(c));    // Adding the letter to the vector
        }
    }
    return letters;
}

// Function to read the matrix clockwise for encryption
void Encryption(const vector<vector<char>>& matrix, int rows, int cols, string& encrypted_message) {
    int i, start_row = 0, start_column = 0;
    //while in the matrix
    while (start_row < rows && start_column < cols) {

        // Read the right column from top to bottom
        for (i = start_row; i < rows; ++i) {
            encrypted_message += matrix[i][cols - 1];
        }
        cols--;

        // Read the bottom row from right to left
        if (start_row < rows) {
            for (i = cols - 1; i >= start_column; --i) {
                encrypted_message += matrix[rows - 1][i];
            }
            rows--;
        }

        // Read the left column from bottom to top
        if (start_column < cols) {
            for (i = rows - 1; i >= start_row; --i) {
                encrypted_message += matrix[i][start_column];
            }
            start_column++;
        }

        // Read the top row from left to right
        for (i = start_column; i < cols; ++i) {
            encrypted_message += matrix[start_row][i];
        }
        start_row++;
    }
}

// Function to fill the matrix with letters clockwise for decryption
void FillMatrix(vector<vector<char>>& matrix, const vector<char>& letters, int rows, int cols) {
    int index = 0;
    int start_row = 0, start_col = 0, end_row = rows - 1, end_col = cols - 1;

    while (start_row <= end_row && start_col <= end_col && index < letters.size()) {

        // Fill the rightmost column from top to bottom
        for (int i = start_row; i <= end_row && index < letters.size(); ++i) {
            matrix[i][end_col] = letters[index++];
        }
        end_col--;

        // Fill the bottom row from right to left
        for (int i = end_col; i >= start_col && index < letters.size(); --i) {
            matrix[end_row][i] = letters[index++];
        }
        end_row--;

        // Fill the leftmost column from bottom to top
        for (int i = end_row; i >= start_row && index < letters.size(); --i) {
            matrix[i][start_col] = letters[index++];
        }
        start_col++;

        // Fill the top row from left to right
        for (int i = start_col; i <= end_col && index < letters.size(); ++i) {
            matrix[start_row][i] = letters[index++];
        }
        start_row++;
    }
}

// Function to read the matrix normally for decryption (top left to bottom right)
void Decryption(const vector<vector<char>>& matrix, int rows, int cols, string& decrypted_message) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
                decrypted_message += matrix[i][j];
            }
        }
    }


//function to make sure the input is integer
int no_string(string num){
    while (true){
        try {
            return stoi(num);       //changing from string to integer
        }
        catch (invalid_argument const&) {
            cout << "Please enter a valid number: \n";
            cin >> num;
        }
    }
}

int main() {
    string message;
    string menu;
    cout << "Choose\n A)Route Cipher Encryption \n B)Route Cipher Decryption \n";
    cin >> menu;

    while (menu != "A" && menu != "a" && menu != "b" && menu != "B") {
        cout << "Please enter a valid option: ";
        cin >> menu;
    }

    if (menu == "A" || menu == "a") {

        cin.ignore();
        cout << "Enter the message you want to encrypt: \n";
        getline(cin, message);
        //recalling the function to split the letters of the message
        vector<char> letters = string_to_char(message);

        string col;
        int secret_key;
        cout << "Enter the secret key: \n";
        cin >> col;
        secret_key = no_string(col);

        //making sure the secret key is greater than half the letters length
        while (secret_key > (letters.size()*0.5) || secret_key <=1){
            cout << "Please enter a valid secret key: ";
            cin >> col;
            secret_key = no_string(col);
        }

        //calculating the number of rows of the matrix
        int rows_num = (letters.size() + (secret_key - 1)) / secret_key;

        //initializing the matrix with X in the secret key (no.of columns) and rows dimensions
        vector<vector<char>> matrix(rows_num, vector<char>(secret_key, 'X'));

        //Adding the letters to the matrix
        int index = 0;
        for (int i = 0; i < rows_num; ++i) {
            for (int j = 0; j < secret_key && index < letters.size(); ++j) {
                matrix[i][j] = letters[index++];
            }
        }

        string encrypted_message = "";
        //recall the function to encrypt the message
        Encryption(matrix, rows_num, secret_key, encrypted_message);
        cout << "Encrypted Message:" << encrypted_message << endl;

    } else if (menu == "B" || menu == "b") {

        cin.ignore();
        cout << "Enter the message you want to decrypt: \n";
        getline(cin, message);
        vector<char> letters = string_to_char(message);

        string col;
        int secret_key;
        cout << "Enter the secret key: \n";
        cin >> col;
        secret_key = no_string(col);

        while (secret_key >= (letters.size()*0.5) || secret_key <=1){
            cout << "Please enter a valid secret key: ";
            cin >> col;
            secret_key = no_string(col);
        }
        string decrypted_message = "";
        int rows_num = (letters.size() + (secret_key - 1)) / secret_key;

        vector<vector<char>> matrix(rows_num, vector<char>(secret_key, 'X'));

        //Recalling the function to fill the matrix with letters clockwise
        FillMatrix(matrix, letters, rows_num, secret_key);
        //recall the function to decrypt the message
        Decryption(matrix, rows_num, secret_key, decrypted_message);
        cout << "Decrypted Message: " << decrypted_message << endl;
    }
    return 0;
}
