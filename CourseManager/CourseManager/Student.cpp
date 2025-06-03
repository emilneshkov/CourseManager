#include "Student.h"

Student::Student(int id, const MyString& firstName, const MyString& lastName, const MyString& email, const MyString& password, const MyVector<Message>& inbox) : User(id, firstName, lastName, email, password, inbox, Role::Student)
{
}

Student::Student(int id, const MyString& firstName, const MyString& lastName, const MyString& password) :User(id, firstName, lastName, MyString(), password, MyVector<Message>(), Role::Student)
{
}

User* Student::clone() const
{
    return new Student(*this);
}

void Student::enrollInCourse(const MyString& courseName, const MyString& coursePassword, CourseRepository& courseRepo)
{
    Course& course = courseRepo.findByName(courseName);

    if (!course.canEnroll(coursePassword)) {
        return;
    }

    if (course.isStudentEnrolled(getId())) {
        return;
    }

    course.enroll(getId());
}

void Student::submitAssignment(const MyString& courseName, const MyString& assignmentTitle, const MyString& content, CourseRepository& courseRepo) const
{
    Course& course = courseRepo.findByName(courseName);
    Assignment& assignment = course.getAssigmentByTittle(assignmentTitle);

    Submission submission(course.getId(), assignment.getAssignmentId(),getId(), content);

    assignment.addSubmission(submission);
}

MyVector<Grade> Student::viewMyGrades(const CourseRepository& courseRepo) const
{
    MyVector<Grade> result;

    const MyVector<Course>& allCourses = courseRepo.getAll();
    for (size_t ci = 0; ci < allCourses.getSize(); ++ci) {
        const Course& c = allCourses[ci];

        if (!c.isStudentEnrolled(this->getId())) {
            continue;
        }

        const MyVector<Assignment>& assigns = c.getAssignments();
        for (size_t ai = 0; ai < assigns.getSize(); ++ai) {
            const Assignment& a = assigns[ai];

            const MyVector<Submission>& subs = a.getSubmissions();
            bool found = false;
            for (size_t si = 0; si < subs.getSize(); ++si) {
                const Submission& s = subs[si];
                if (s.getStudentId() == this->getId()) {
                    found = true;

                    const MyVector<Grade>& gv = s.getGradeVector();
                    for (size_t gi = 0; gi < gv.getSize(); ++gi) {
                        result.pushBack(gv[gi]);
                    }
                    break; 
                }
            }
        }
    }

    return result;
}

void Student::sendMessage(int toUserId, const MyString& content, UserRepository& userRepo)
{
    Message message(getId(), content, time(nullptr));

    userRepo.findById(toUserId).receiveMessage(message);
}