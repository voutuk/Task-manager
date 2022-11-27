#include <iostream>
#include <string>
//#include <Windows.h>
//#include <fstream>
using namespace std;
struct Date {
    int d;
    int m;
    int y;
    int size;
}; 
struct Task {
    int priority;
    int index;
    Date deadline;
    string name;
    string description;
};
struct TaskData {
    int size = 0;
    Task* tasks = new Task[size];
};


//void txtColor(HANDLE color, int fg, int bg, string txt) {
//    SetConsoleTextAttribute(color, fg | bg);
//    cout << txt;
//}

void pushBack(TaskData* task, Task newValue) {
    ++task->size;
    Task* tmpStruct = new Task[task->size];
    for (int i = 0; i < task->size - 1; i++) { tmpStruct[i] = task->tasks[i]; }
    tmpStruct[task->size - 1].priority = newValue.priority;
    tmpStruct[task->size - 1].index = newValue.index;
    tmpStruct[task->size - 1].deadline = newValue.deadline;
    tmpStruct[task->size - 1].name = newValue.name;
    tmpStruct[task->size - 1].description = newValue.description;
    delete[] task->tasks;
    task->tasks = tmpStruct;
}

int dateSize(int d, int m, int y) {
    int daysMax[12]{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int days = d;
    for (int i = y; i >= 1; i--) {
        for (int j = 0; j < m; j++) { days += daysMax[m - 1]; }
    }
    return days;
}

bool validateDate(string date, int& d, int& m, int& y) {
    string tmpD = date, tmpM = date, tmpY = date;
    char symbol[5]{ '.', ',', '/', '\\', '-' };
    int daysMax[12]{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }, tmp = 0;
    for (int i = 0; i < 5; i++) {
        int tmp1 = date.find(symbol[i]);
        if (tmp1 != -1) {
            tmpD.erase(tmp1, date.size() - tmp1), ++tmp;
            int tmp2 = date.find(symbol[i], tmp1);
            if (date.find(symbol[i], tmp1) != -1) {
                tmpM.erase(0, tmp1 + 1);
                tmpM.erase(date.find(symbol[i], tmp1), date.size() - date.find(symbol[i], tmp1)), ++tmp;
                if (date.find(symbol[i], tmp2 + 1) != -1) { tmpY.erase(0, date.find(symbol[i], tmp2 + 1) + 1); }
            }
        }
    }
    if (tmp != 2) { return false; }
    if (stoi(tmpY) % 4 == 0) { daysMax[1] = 29; }
    if (stoi(tmpM) < 1 || stoi(tmpM) > 12 || stoi(tmpD) < 1 || stoi(tmpD) > daysMax[stoi(tmpM) - 1] || stoi(tmpY) < 1) { return false; }
    d = stoi(tmpD), m = stoi(tmpM), y = stoi(tmpY);
    return true;
}

//
//void cout1(TaskData task, int i, HANDLE color, int thremeColor) {
//
//    int tmp = task.tasks[i].index;
//    int tmp2 = task.tasks[i].priority;
//    string deadline = to_string(task.deadline[0][i]) + "/" + to_string(task.deadline[1][i]) + "/" + to_string(task.deadline[2][i]);
//    string create = to_string(task.createDate[0][i]) + "/" + to_string(task.createDate[1][i]) + "/" + to_string(task.createDate[2][i]);
//
//    int str1 = 3 + task.name[i].length();
//    while ((tmp /= 10) > 0) str1++;
//    int str2 = task.description[i].length() + 2;
//    int str3 = 4 + deadline.length();
//    while ((tmp2 /= 10) > 0) str3++;
//    int str4 = create.length() + 2;
//    int max = max(str2, max(str3, max(str4, str1)));
//
//    cout << "+";
//    for (int i = 0; i < max; i++) { txtColor(color, rand() % 16, thremeColor, "-"); }
//    if (thremeColor == 240 || thremeColor == 224) { txtColor(color, 0, thremeColor, "+"); }
//    else { txtColor(color, 15, thremeColor, "+"); }
//    cout << endl << "| " << task.index[i] << " " << task.name[i];
//    for (int i = 0; i < max - str1; i++) { cout << " "; }
//    cout << "|" << endl << "| " << task.description[i];
//    for (int i = 0; i < max - str2; i++) { cout << " "; }
//    cout << " |" << endl << "| " << task.priority[i] << " " << deadline;
//    for (int i = 0; i < max - str3; i++) { cout << " "; }
//    cout << " |" << endl << "| " << create;
//    for (int i = 0; i < max - str4; i++) { cout << " "; }
//    cout << " |" << endl << "+";
//    for (int i = 0; i < max; i++) { txtColor(color, rand() % 16, thremeColor, "-"); }
//    if (thremeColor == 240 || thremeColor == 224) { txtColor(color, 0, thremeColor, "+"); }
//    else { txtColor(color, 15, thremeColor, "+"); }
//}
//
//void pushBack2D(int**& arr, int ROWS, int& COLS, int data1, int data2, int data3) {
//    int** tmp_arr = new int* [ROWS];
//    for (int i = 0; i < ROWS; i++) {
//        tmp_arr[i] = new int[COLS];
//        for (int j = 0; j < COLS - 1; j++) { tmp_arr[i][j] = arr[i][j]; }
//    }
//
//    tmp_arr[0][COLS - 1] = data1;
//    tmp_arr[1][COLS - 1] = data2;
//    tmp_arr[2][COLS - 1] = data3;
//
//    delete[] arr;
//    arr = tmp_arr;
//}

void delTask(TaskData& task, int index) {
    cout << "Index: " << index;
    --task.size;
    Task* tmpStruct = new Task[task.size];
    for (int i = 0; i < task.size; i++) {
        if (i < index) { tmpStruct[i] = task.tasks[i]; }
        else if (i >= index) { tmpStruct[i] = task.tasks[i + 1]; }
    }
    delete[] task.tasks;
    task.tasks = tmpStruct;
}

//void del2D(int**& arr, int ROWS, int& COLS, int ind) {
//    int** tmp_arr = new int* [ROWS];
//    for (int i = 0; i < ROWS; i++) {
//        tmp_arr[i] = new int[COLS];
//        for (int j = 0; j < COLS; j++) {
//            if (i < ind) { tmp_arr[i][j] = arr[i][j]; }
//            else if (i >= ind) { tmp_arr[i][j] = arr[i][j + 1]; }
//        }
//    }
//    delete[] arr;
//    arr = tmp_arr;
//}

//template <typename Type>
//bool sort(TaskData& task, Type data, int sort = 0) {
//    for (int step = 0; step < task.size - 1; ++step) {
//        for (int i = 0; i < task.size - 1; i++) {
//            if (sort == 0) {
//                if (data[i] > data[i + 1]) {
//                    swap(task.priority[i], task.priority[i + 1]);
//                    swap(task.index[i], task.index[i + 1]);
//                    swap(task.createDateSize[i], task.createDateSize[i + 1]);
//                    swap(task.deadlineSize[i], task.deadlineSize[i + 1]);
//                    swap(task.createDate[i], task.createDate[i + 1]);
//                    swap(task.deadline[i], task.deadline[i + 1]);
//                    swap(task.name[i], task.name[i + 1]);
//                    swap(task.description[i], task.description[i + 1]);
//                }
//            }
//            else {
//                if (data[i] < data[i + 1]) {
//                    swap(task.priority[i], task.priority[i + 1]);
//                    swap(task.index[i], task.index[i + 1]);
//                    swap(task.createDateSize[i], task.createDateSize[i + 1]);
//                    swap(task.deadlineSize[i], task.deadlineSize[i + 1]);
//                    swap(task.createDate[i], task.createDate[i + 1]);
//                    swap(task.deadline[i], task.deadline[i + 1]);
//                    swap(task.name[i], task.name[i + 1]);
//                    swap(task.description[i], task.description[i + 1]);
//                }
//            }
//        }
//    }
//    return true;
//}

//
//bool coutTask(TaskData task, HANDLE color, int thremeColor, string select) {
//    if (select.find("N") != -1 || select.find("n") != -1) {
//        if (select.find(">") != -1) { sort(task, task.name, 1); }
//        else { sort(task, task.name, 0); }
//    }
//    else if (select.find("C") != -1 || select.find("c") != -1) {
//        if (select.find(">") != -1) { sort(task, task.createDateSize, 1); }
//        else { sort(task, task.createDateSize, 0); }
//    }
//    else if (select.find("U") != -1 || select.find("u") != -1) {
//        if (select.find(">") != -1) { sort(task, task.index, 1); }
//        else { sort(task, task.index, 0); }
//    }
//    else if (select.find("E") != -1 || select.find("e") != -1) {
//        if (select.find(">") != -1) { sort(task, task.deadlineSize, 1); }
//        else { sort(task, task.deadlineSize, 0); }
//    }
//    int d = task.createDate[0][0], m = task.createDate[1][0], y = task.createDate[2][0], d1, m1, y1;
//    int daysMax[12]{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
//    if (y % 4 == 0) { daysMax[1] = 29; }
//    if (select.find("D") != -1 || select.find("d") != -1) {
//        for (int i = 0; i < task.size; i++) {
//            if (task.deadline[0][i] == d && task.deadline[1][i] == m && task.deadline[2][i] == y) {
//                cout1(task, i, color, thremeColor);
//                cout << endl;
//            }
//        }
//    }
//    else if (select.find("W") != -1 || select.find("w") != -1) {
//        if (d + 7 > daysMax[m - 1]) {
//            d1 = d + 7 - daysMax[m - 1], y1 = y;
//            if (m == 11) { m1 = 0, y1 = y + 1; }
//            else { m1 = m + 1; }
//            for (int i = 0; i < task.size; i++) {
//                if (task.deadline[0][i] >= d && task.deadline[0][i] < d1 && task.deadline[1][i] == m1 && task.deadline[2][i] == y1) {
//                    cout1(task, i, color, thremeColor);
//                    cout << endl;
//
//                }
//            }
//        }
//        else {
//            d1 = d + 7;
//            for (int i = 0; i < task.size; i++) {
//                if (task.deadline[0][i] > d && task.deadline[0][i] < d1 && task.deadline[1][i] == m && task.deadline[2][i] == y) {
//                    cout1(task, i, color, thremeColor);
//                    cout << endl;
//
//                }
//            }
//        }
//    }
//    else if (select.find("M") != -1 || select.find("M") != -1) {
//        y1 = y;
//        if (m == 11) { m1 = 0, y1 = y + 1; }
//        else { m1 = m + 1; }
//        for (int i = 0; i < task.size; i++) {
//            if (task.deadline[1][i] > m && task.deadline[1][i] < m1 && task.deadline[2][i] == y1) {
//                cout1(task, i, color, thremeColor);
//                cout << endl;
//            }
//        }
//    }
//    else {
//        for (int i = 0; i < task.size; i++) {
//
//            cout1(task, i, color, thremeColor);
//            cout << endl;
//        }
//    }
//
//    return true;
//}
//
//bool deleteTask(TaskData& task, int number) {
//    for (int i = 0; i < task.size; i++) {
//        if (task.index[i] == number) {
//            --task.size;
//            del(task.name, task.size, i);
//            del(task.description, task.size, i);
//            del(task.priority, task.size, i);
//            del2D(task.deadline, task.ROWS, task.size, i);
//            del2D(task.createDate, task.ROWS, task.size, i);
//            del(task.index, task.size, i);
//            del(task.createDateSize, task.size, i);
//            del(task.deadlineSize, task.size, i);
//            return true;
//        }
//    }
//    return false;
//}
//
//bool editTask(TaskData& task, int number, string editName, string editDescription, int editPriority, string editNewDate) {
//    for (int i = 0; i < task.size; i++) {
//        if (task.index[i] == number) {
//            if (editName != "-") { task.name[i] = editName; }
//            if (editDescription != "-") { task.description[i] = editDescription; }
//            if (editPriority != -1) {
//                if (editPriority < 1 || editPriority > 5) { return false; }
//                task.priority[i] = editPriority;
//            }
//            if (editNewDate != "-") {
//                int d1, m1, y1;
//                if (validateDate(editNewDate, d1, m1, y1) == false) { return false; }
//                task.deadline[0][i] = d1;
//                task.deadline[1][i] = m1;
//                task.deadline[2][i] = y1;
//            }
//            return true;
//        }
//
//    }
//    return false;
//}
//
//bool findTask(TaskData& task, HANDLE color, string search, int thremeColor) {
//    int d, m, y;
//    bool a = validateDate(search, d, m, y);
//    for (int i = 0; i < task.size; i++) {
//        if (task.name[i].find(search) != -1) { cout1(task, i, color, thremeColor); }
//        if (task.description[i].find(search) != -1) { cout1(task, i, color, thremeColor); }
//        //if (task.priority[i] == stoi(search)) { cout1(task, i, color, thremeColor); }
//        if (a == true) {
//            if (task.deadline[0][i] == d && task.deadline[1][i] == m && task.deadline[2][i] == y) { cout1(task, i, color, thremeColor); }
//            if (task.createDate[0][i] == d && task.createDate[1][i] == m && task.createDate[2][i] == y) { cout1(task, i, color, thremeColor); }
//        }
//    }
//    cout << endl;
//    return true;
//}

//bool saveFile(ofstream& fouts, TaskData task) {
//    if (fouts.is_open()) {
//        fouts << task.size << endl;
//        for (int i = 0; i < task.size; i++) {
//            fouts << task.priority[i] << endl;
//            fouts << task.index[i] << endl;
//            fouts << task.createDateSize[i] << endl;
//            fouts << task.deadlineSize[i] << endl;
//            fouts << task.name[i] << endl;
//            fouts << task.description[i] << endl;
//
//            /*fouts << task.deadline[i] << endl;
//            fouts << task.createDate[i] << endl;
//            for (int j = 0; j < task.ROWS; j++) {
//                fouts << task.deadline[i][j] << endl;
//            }
//            for (int g = 0; g < task.ROWS; g++) {
//                fouts << task.createDate[i][g] << endl;
//            }*/
//        }
//        return true;
//    }
//    else { return false; }
//}

//bool openFile(ifstream& fin, TaskData task) {
//    if (fin.is_open()) {
//        string tmp;
//        getline(fin, tmp);
//        int tmps = stoi(tmp), tmp1, tmp2, tmp3;
//        for (int i = 0; i < tmps; i++) {
//            getline(fin, tmp);
//            pushBack(task.priority, task.size, stoi(tmp));
//            getline(fin, tmp);
//            pushBack(task.index, task.size, stoi(tmp));
//            getline(fin, tmp);
//            pushBack(task.createDateSize, task.size, stoi(tmp));
//            getline(fin, tmp);
//            pushBack(task.deadlineSize, task.size, stoi(tmp));
//            getline(fin, tmp);
//            pushBack(task.name, task.size, tmp);
//            getline(fin, tmp);
//            pushBack(task.description, task.size, tmp);
//            ++task.size;
//            //getline(fin, tmp);
//            //pushBack(task.deadline, task.size, tmp);
//            //getline(fin, tmp);
//            //pushBack(task.createDate, task.size, tmp);
//            //
//            //tmp1 = getline(fin, tmp), tmp2 = getline(fin, tmp), tmp3 = getline(fin, tmp);
//            //pushBack2D(task.deadline, task.ROWS, task.size, stoi(tmp1), stoi(tmp2), stoi(tmp3));
//            //tmp1 = getline(fin, tmp), tmp2 = getline(fin, tmp), tmp3 = getline(fin, tmp);
//            //pushBack2D(task.createDate, task.ROWS, task.size, stoi(tmp1), stoi(tmp2), stoi(tmp3));
//        }
//        return true;
//    }
//    else {
//        cout << "FLAG 1";
//    }
//}
//
//int startProgram(TaskData& task) {
//    int thremeColor = 2;
//    string tmp;
//
//    while (tmp != "y" && tmp != "Y") {
//        system("cls");
//        cout << "1. White \n2. Black \n3. Red \n4. Blue \n5. Yellow \n6. File\nEnter \"y\" to continue \n Select threme: ";
//        getline(cin, tmp);
//        if (tmp == "1") {
//            system("color F0");
//            thremeColor = 240;
//        }
//        else if (tmp == "2") {
//            system("color 0F");
//            thremeColor = 0;
//        }
//        else if (tmp == "3") {
//            system("color CF");
//            thremeColor = 192;
//        }
//        else if (tmp == "4") {
//            system("color 9F");
//            thremeColor = 144;
//        }
//        else if (tmp == "5") {
//            system("color E0");
//            thremeColor = 224;
//        }
//        else if (tmp == "6") {
//            /*system("cls");
//            string tmp;
//            cout << "Drag the file into the window: ";
//            getline(cin, tmp);
//            ifstream hh;
//            hh.open(tmp);
//            openFile(hh, task);
//            hh.close();*/
//        }
//    }
//    system("cls");
//    return thremeColor;
//}

int main() {
    //HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
    TaskData task;
    Task newValue;
    string date;
    int tmp;
    //int thremeColor = startProgram(task);

    while (1) {
        //SetConsoleCP(1251);
        //SetConsoleOutputCP(1251);
        system("cls");
        cout << endl;
        cout << " ==== MENU ==== \n\n";
        cout << " 1. New task \n 2. Edit task \n 3. Delete task \n 4. Cout task \n 5. Find task \n 6. Exit \n > Enter num: ";
        cin >> tmp;
        switch (tmp) {
        case 1:
            system("cls");
            cin.ignore();
            cout << "\n ==== Create task ==== \n\n";
            cout << " Enter name: ";
            getline(cin, newValue.name);
            cout << " Enter description: ";
            getline(cin, newValue.description);
            do {
                cout << " Enter priority: ";
                cin >> newValue.priority;
            } while (newValue.priority < 1 || newValue.priority > 5);
            cin.ignore();
            int d, m, y;
            do {
                cout << " Enter deadline: ";
                getline(cin, date);
            } while (validateDate(date, d, m, y) == false);
            newValue.deadline.d = d, newValue.deadline.m = m, newValue.deadline.y = y, newValue.deadline.size = dateSize(d, m, y), newValue.index = task.size + 1;
            pushBack(&task, newValue);
            cout << " Successfully!\n";
            system("pause");
            break;
        case 2:
            for (int i = 0; i < task.size; i++){
                cout << "Task index: " << task.tasks[i].index << endl;
                cout << "Name: " << task.tasks[i].name << endl;
                cout << "Description: " << task.tasks[i].description << endl;
                cout << "Priority: " << task.tasks[i].priority << endl;
                cout << "Date: " << task.tasks[i].deadline.d << "/" << task.tasks[i].deadline.m << "/" << task.tasks[i].deadline.y << " -- " << task.tasks[i].deadline.size << endl;
            }
            cout << " Successfully!\n";
            system("pause");
            break;
        case 3:
            system("cls");
            cout << "\n ==== Delete task ==== \n\n";
            while (1) {
                cout << " Enter number task: ";
                cin >> tmp;
                for (int i = 0; i < task.size; i++){
                    if (task.tasks[i].index == tmp) { 
                        delTask(task, tmp-1); 
                        tmp = 0;
                        break;
                    }
                }
                if (tmp == 0) { break; }
                cout << " Task not found, please try again :(" << endl;
                cout << " Type \"0\" to exit" << endl;
            }
            cout << " Successfully!" << endl;
            system("pause");
            break;
        //case 2:
        //    system("cls");
        //    for (int i = 0; i < w / 2 - 22; i++) { cout << " "; }
        //    cout << endl;
        //    cout << " ==== Edit task ==== \n\n";
        //    cout << " 2. Name \n 3. Description \n 4. Priority \n 5. Deadline \n 6. All \n > Select an option: ";
        //    cin >> tmp;
        //    {
        //        string editName, editDescription, editDeadline;
        //        int editPriority;
        //        if (tmp == 2) {
        //            cout << " Enter number task: ";
        //            cin >> tmp;
        //            cout << " Enter name: ";
        //            cin.ignore();
        //            getline(cin, editName);
        //            if (editTask(task, tmp, editName, "-", -1, "-") == false) { cout << " You have entered incorrect data :(\n"; }
        //        }
        //        else if (tmp == 3) {
        //            cout << " Enter number task: ";
        //            cin >> tmp;
        //            cout << " Enter description: ";
        //            cin.ignore();
        //            getline(cin, editDescription);
        //            if (editTask(task, tmp, "-", editDescription, -1, "-") == false) { cout << " You have entered incorrect data :(\n"; }
        //        }
        //        else if (tmp == 4) {
        //            cout << " Enter number task: ";
        //            cin >> tmp;
        //            cout << " Enter priority: ";
        //            cin >> editPriority;
        //            if (editTask(task, tmp, "-", "-", editPriority, "-") == false) { cout << " You have entered incorrect data :(\n"; }
        //        }
        //        else if (tmp == 5) {
        //            cout << " Enter number task: ";
        //            cin >> tmp;
        //            cout << " Enter deadline: ";
        //            cin.ignore();
        //            getline(cin, editDeadline);
        //            if (editTask(task, tmp, "-", "-", -1, editDeadline) == false) { cout << " You have entered incorrect data :(\n"; }
        //        }
        //        else if (tmp == 6) {
        //            cout << " Enter number task: ";
        //            cin >> tmp;
        //            cout << " Enter name: ";
        //            cin.ignore();
        //            getline(cin, newName);
        //            cout << " Enter description: ";
        //            getline(cin, newData);
        //            cout << " Enter priority: ";
        //            cin >> editPriority;
        //            cin.ignore();
        //            cout << " Enter deadline: ";
        //            getline(cin, editDeadline);
        //            if (editTask(task, tmp, newName, newData, editPriority, editDeadline) == false) { cout << " You have entered incorrect data :(\n"; }
        //        }
        //    }
        //    system("pause");
        //    break;
        //case 4:
        //    system("cls");
        //    for (int i = 0; i < w / 2 - 22; i++) { cout << " "; }
        //    cout << endl;
        //    cout << " ==== Cout task ==== \n\n";
        //    cout << " [N] Name  [E] Deadline  [C] Date create  [U] Number  [D] Day  [W] Week  [M] Month  [<]A..Z  [>]Z..A\n > Select an option: ";
        //    cin.ignore();
        //    getline(cin, select);
        //    coutTask(task, color, thremeColor, select);
        //    cout << " Successfully!" << endl;
        //    system("pause");
        //    break;
        //case 5:
        //    system("cls");
        //    for (int i = 0; i < w / 2 - 22; i++) { cout << " "; }
        //    cout << endl;
        //    cout << " ==== Find task ==== \n\n";
        //    cout << " > Enter a search query: ";
        //    cin.ignore();
        //    getline(cin, select);
        //    findTask(task, color, select, thremeColor);
        //    cout << " Successfully!" << endl;
        //    system("pause");
        //    break;
        //case 6:
        //    txtColor(color, 4, 240, " Exit ");
        //    /*ofstream fout;
        //    fout.open("dataTask.txt");
        //    saveFile(fout, task);
        //    fout.close();*/

        //    delete[] task.priority;
        //    delete[] task.index;
        //    delete[] task.createDateSize;
        //    delete[] task.deadlineSize;
        //    for (int i = 0; i < task.ROWS; i++) {
        //        delete[] task.createDate[i];
        //        delete[] task.deadline[i];
        //    }
        //    delete[] task.createDate;
        //    delete[] task.deadline;
        //    delete[] task.name;
        //    delete[] task.description;
        //    return 0;
        }
    }

}