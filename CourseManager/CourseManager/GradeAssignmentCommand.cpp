#include "GradeAssignmentCommand.h"
#include "Teacher.h"

void GradeAssignmentCommand::execute(const MyVector<MyString>& arguments, CourseManagerApp& courseApp) const
{
	if (arguments.getSize() < 6) {
		std::cout << "Usage: grade_assignment <courseName> <assignmentTitle> " "<studentId> <score> <comment>\n";
		return;
	}

	User* currentUser = courseApp.getCurrentUser();
	if (!currentUser || currentUser->getRole() != User::Role::Teacher) {
		std::cout << "Error: only a teacher may grade assignments.\n";
		return;
	}
	Teacher& teacher = static_cast<Teacher&>(*currentUser);

	const MyString& courseName = arguments[1];
	const MyString& assignmentTitle = arguments[2];
    int studentId;
    double score;

    try {
        studentId = arguments[3].parseToInt();
        score = arguments[4].parseToDouble();
    }
    catch (...) {
        std::cout << "Error: studentId must be an integer and score must be a number.\n";
        return;
    }
    if (studentId < 0) {
        std::cout << "Error: studentId must be non-negative.\n";
        return;
    }
    if (score < 0.0) {
        std::cout << "Error: score must be non-negative.\n";
        return;
    }

    try {
        User& candidate = courseApp.getUserRepo().findById(studentId);
        if (candidate.getRole() != User::Role::Student) {
            std::cout << "Error: user with ID " << studentId << " is not a student.\n";
            return;
        }
    }
    catch (const std::exception&) {
        std::cout << "Error: no such student with ID " << studentId << ".\n";
        return;
    }

    MyString comment;
    for (size_t i = 5; i < arguments.getSize(); ++i) {
        comment += arguments[i];
        if (i + 1 < arguments.getSize()) {
            comment.pushBack(' ');
        }
    }

    try {
        Course& course = courseApp.getCourseRepo().findByName(courseName);
        if (course.getTeacherId() != teacher.getId()) {
            std::cout << "Error: you are not the instructor for course \""
                << courseName.getString() << "\".\n";
            return;
        }

        Assignment& assignment = course.getAssigmentByTittle(assignmentTitle);
        int assignmentId = assignment.getAssignmentId();
        int courseId = course.getId();

        teacher.gradeSubmission(courseId,assignmentId,studentId,score,comment,courseApp.getCourseRepo()
        );

        std::cout << "Graded assignment \"" << assignmentTitle.getString()<< "\" for student " << studentId<< " with score " << score << ".\n";
    }
    catch (const std::exception& ex) {
        std::cout << "Failed to grade assignment: " << ex.what() << "\n";
    }
}
