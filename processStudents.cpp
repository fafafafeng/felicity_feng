#include "processStudents.h"

/*
   This file should compile with processStudentsSampleMain.cpp.
   Of course, it does not implement the required functionality.
*/

void addStudent(studentList *& l,
                string lastname,
                string firstname,
                int quizMarks[],
                int nQuizzes)
{
    int currentID = 0;
    const studentList *temp = l;
    while (temp != nullptr) {
        if(temp->sr->id > currentID) {
            currentID = temp->sr->id;
        }
        temp = temp->next;
    }

    char* lastnameCStr = new char[lastname.length() + 1];
    std::strcpy(lastnameCStr, lastname.c_str());

    char* firstnameCstr = new char[firstname.length() +1];
    std::strcpy(firstnameCstr, firstname.c_str());

    int* quizMarksCopy = new int[nQuizzes];
    for(int i = 0; i < nQuizzes; ++i) {
        quizMarksCopy[i] = quizMarks[i];
    }

    studentRecord* newStudent = new studentRecord;
    newStudent->id = currentID + 1;
    newStudent->lastname = lastnameCStr;
    newStudent->firstname = firstnameCstr;
    newStudent->quizMarks = quizMarksCopy;

    studentList* newNode = new studentList;
    newNode->sr = newStudent;
    newNode->next = l;
    l =  newNode;
}

void removeStudent(studentList *& l,
                   int studentID)
{
    studentList* current = l;
    studentList* prev = nullptr;

    while (current != nullptr) {
        if (current->sr->id == studentID){
            if (prev != nullptr) {
                prev->next = current->next;
            }
            else {
                l = current->next;
            }
            current->next = nullptr;
            delete current;

            break;
        }
        prev = current;
        current = current->next;
    }
}

studentRecord *findStudentByID(const studentList *l,
                               int studentID)
{
    const studentList *current = l;

    while (current != nullptr) {
        if(current->sr->id != studentID) {
            current = current->next;
        }
        else {
            return current->sr;
        }
    }
    return nullptr;
}

studentList *findStudentsByLastName(const studentList *l,
                                    string lastname,
                                    int nQuizzes)
{
    studentList* matchedList = nullptr;

    while (l != nullptr) {
        if (std::strcmp(l->sr->lastname, lastname.c_str()) == 0) {
            int* quizMarksCopy = new int[nQuizzes];
            for (int i = 0; i < nQuizzes; ++i) {
                quizMarksCopy[i] = l->sr->quizMarks[i];
            }

            char* lastnameCopy = new char[std::strlen(l->sr->lastname) + 1];
            std::strcpy(lastnameCopy, l->sr->lastname);

            char* firstnameCopy = new char[std::strlen(l->sr->firstname) + 1];
            std::strcpy(firstnameCopy, l->sr->firstname);

            studentRecord* newStudent = new studentRecord;
            newStudent->id = l->sr->id;
            newStudent->lastname = lastnameCopy;
            newStudent->firstname = firstnameCopy;
            newStudent->quizMarks = quizMarksCopy;

            studentList* newNode = new studentList;
            newNode->sr = newStudent;
            newNode->next = matchedList;
            matchedList = newNode;
        }

        l = l->next;
    }
    return matchedList;
}

double quizAverage(const studentList *l, int quizNum)
{
    if(l == nullptr) {
        return 0.0;
    }

    int totalStudents = 0;
    int sum = 0;

    const studentList *current = l;
    while (current != nullptr) {
        sum += current->sr->quizMarks[quizNum];
        totalStudents++;
        current = current->next;
    }

    return static_cast<double>(sum) / totalStudents;
}
