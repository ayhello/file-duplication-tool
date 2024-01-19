#include <iostream>
#include<conio.h>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class FileHandler {
public:
    void createFile(const string& filename) {
        if (fileExists(filename)) {
            cout << "Error: File already exists." << endl;
            return;
        }

        ofstream file(filename);
        if (file.is_open()) {
            cout << "File created successfully." << endl;
        }
        else {
            cout << "Error creating file." << endl;
        }
        file.close();
        
    }

    bool fileExists(const string& filename) {
        ifstream file(filename);
        return file.is_open();
    }

    void addContent(const string& filename, const string& content) {
        ofstream file(filename, ios_base::app);
        if (file.is_open()) {
            file << content << endl;
            cout << "Content added successfully." << endl;
        }
        else {
            cout << "Error adding content to file." << endl;
        }
        file.close();
        
    }

    void displayContent(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                cout << line << endl;
            }
            file.close();
        }
        else {
            cout << "Error reading file." << endl;
        }
        
    }

    bool compareFiles(const string& filename1, const string& filename2) {
        ifstream file1(filename1);
        ifstream file2(filename2);

        if (file1.is_open() && file2.is_open()) {
            string line1, line2;

            // Get the first line from each file
            bool eof1 = !getline(file1, line1);
            bool eof2 = !getline(file2, line2);

            // Check if the files are the same based on the first line
            if (eof1 || eof2) {
                if (eof1 && eof2) {
                    cout << "\n Files are same";
                    return true;
                }
                else {
                    cout << "\n Files are different";
                    return false;
                }
            }
            else if (line1 != line2) {
                cout << "\n Files are different";
                file1.close();
                file2.close();
                return false;
            }

            // Get the rest of the lines from each file
            while (getline(file1, line1) && getline(file2, line2)) {
                if (line1 != line2) {
                    cout << "\n Files are different";
                    file1.close();
                    file2.close();
                    return false;
                }
            }

            // If both files are at the end, they are the same
            if (file1.eof() && file2.eof()) {
                cout << "\n Files are same";
                file1.close();
                file2.close();
                return true;
            }

            // If one file is longer than the other, they are different
            if (file1.eof() || file2.eof()) {
                cout << "\n Files are different";
                file1.close();
                file2.close();
                return false;
            }

        }
        else {
            cout << "Error reading files." << endl;
            return false;
        }
        
    }

    void replaceWord(const string& filename, const string& oldWord, const string& newWord) {
        ifstream file(filename);
        ofstream tempFile("temp.txt");

        if (file.is_open() && tempFile.is_open()) {
            string line;
            while (getline(file, line)) {
                size_t startPos = 0;
                while ((startPos = line.find(oldWord, startPos)) != string::npos) {
                    line.replace(startPos, oldWord.length(), newWord);
                    startPos += newWord.length();
                }
                tempFile << line << endl;
            }
            file.close();
            tempFile.close();

            remove(filename.c_str());
            rename("temp.txt", filename.c_str());

            cout << "Word replaced successfully." << endl;
            displayContent(filename);

        }
        else {
            cout << "Error reading or writing to files." << endl;
        }
       
    }

    void replaceCharacter(const string& filename, char oldChar, char newChar) {
        ifstream file(filename);
        ofstream tempFile("temp.txt");

        if (file.is_open() && tempFile.is_open()) {
            string line;
            while (getline(file, line)) {
                for (char& c : line) {
                    if (c == oldChar) {
                        c = newChar;
                    }
                }
                tempFile << line << endl;
            }
            file.close();
            tempFile.close();

            remove(filename.c_str());
            rename("temp.txt", filename.c_str());

            cout << "Character replaced successfully." << endl;
            displayContent(filename);

        }
        else {
            cout << "Error reading or writing to files." << endl;
        }
        
    }

    void clearContent(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            file.clear();
            cout << "File content cleared successfully." << endl;
        }
        else {
            cout << "Error clearing file content." << endl;
        }
        file.close();
        
    }
};

int main() {
    FileHandler fileHandler;
    string filename, content, oldWord, newWord, tempFilename;
    char oldChar, newChar;
    int choice;

    while (true) {
        cout << "\n============== FILE MODIFICATION TOOL=====================\n";
        cout << "\n Choose An Option:\n1. Create file\n2. Add content\n3. Display content\n4. Compare files" <<
            "\n5. Replace word\n6. Replace character\n7. Clear content\n8. Exit" <<
            "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            system("CLS");
            cout << "Enter filename: ";
            cin >> filename;
            fileHandler.createFile(filename);
            system(cls);
            break;
        case 2:
            system("CLS");
            cout << "Enter filename: ";
            cin >> filename;
            cout << "Enter content: ";
            cin.ignore();
            getline(cin, content);
            fileHandler.addContent(filename, content);
            
            break;
        case 3:
            system("CLS");
            cout << "Enter filename: ";
            cin >> filename;
            fileHandler.displayContent(filename);
            break;
        case 4:
            system("CLS");
          
            cout << "Enter first filename: ";
            cin >> filename;
            cout << "Enter second filename: ";
            cin >> tempFilename;
            fileHandler.compareFiles(filename, tempFilename);
            break;
        case 5:
            system("CLS");
            cout << "Enter filename: ";
            cin >> filename;
            cout << "Enter old word: ";
            cin >> oldWord;
            cout << "Enter new word: ";
            cin >> newWord;
            fileHandler.replaceWord(filename, oldWord, newWord);
            break;
        case 6:
            system("CLS");
            cout << "Enter filename: ";
            cin >> filename;
            cout << "Enter old character: ";
            cin >> oldChar;
            cout << "Enter new character: ";
            cin >> newChar;
            fileHandler.replaceCharacter(filename, oldChar, newChar);
            break;
        case 7:
            system("CLS");
            cout << "Enter filename: ";
            cin >> filename;
            fileHandler.clearContent(filename);
            break;
        case 8:
            return 0;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }
}
