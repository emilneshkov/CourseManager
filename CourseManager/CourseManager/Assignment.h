#pragma once
#include "MyString.h"
#include "MyVector.hpp"
#include "Submission.h"

class Assignment
{
    int courseId;
    int assignmentId;
    MyString title;
    MyString description;
    MyVector<Submission> submissions;

public:
    Assignment();
    Assignment(int courseId, int assignmentId, const MyString& title);
    Assignment(int courseId,
        int assignmentId,
        const MyString& title,
        const MyString& description,
        const MyVector<Submission>& submissions);

    int getCourseId() const;
    int getAssignmentId() const;
    const MyString& getTitle() const;
    const MyString& getDescription() const;

    void addSubmission(const Submission& submission);
    const MyVector<Submission>& getSubmissions() const;
    const Submission& getSubbmissionByStudentId(int studentId)const;
    Submission& getSubbmissionByStudentId(int studentId);

    void saveToBinary(std::ofstream& ofs) const;
    void loadFromBinary(std::ifstream& ifs);
};

