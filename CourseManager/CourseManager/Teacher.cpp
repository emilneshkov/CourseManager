#include "Teacher.h"

Teacher::Teacher(int id, const MyString& firstName, const MyString& lastName, const MyString& email, const MyString& password, const MyVector<Message>& inbox) : User(id, firstName, lastName, email, password, inbox, Role::Teacher)
{
}
Teacher::Teacher(int id, const MyString& firstName, const MyString& lastName, const MyString& defaultPass) : User(id, firstName, lastName, MyString(), defaultPass, MyVector<Message>(), Role::Teacher)
{
}

User* Teacher::clone() const
{
	return new Teacher(*this);
}

int Teacher::createCourse(const MyString& courseName, CourseRepository& courseRepo)
{
	int newId = courseRepo.getNewCourseId();
	Course course(newId, courseName, this->getId());

	courseRepo.add(course);

	return newId;
}

void Teacher::setCourseEnrollmentPassword(int courseId, const MyString& newPassword, CourseRepository& courseRepo)
{
	Course& course = courseRepo.findById(courseId);

	course.setEnrollmentPassword(newPassword);
}

int Teacher::addAssignment(const MyString& courseName, const MyString& title, CourseRepository& courseRepo)
{
	Course& course = courseRepo.findByName(courseName);

	int assignmentId = course.getNewAssigmentId();
	Assignment assignment(course.getId(), assignmentId, title);
	course.addAssignment(assignment);

	return assignmentId;
}

void Teacher::enrollStudentManually(int courseId, int studentId, CourseRepository& courseRepo)
{
	Course& course = courseRepo.findById(courseId);

	course.enroll(studentId);
}

void Teacher::gradeSubmission(int courseId, int assignmentId, int studentId, double score, const MyString& comment, CourseRepository& courseRepo)
{
	Course& course = courseRepo.findById(courseId);
	Assignment& assignment = course.getAssigmentById(assignmentId);
	Submission& submission = assignment.getSubbmissionByStudentId(studentId);

	Grade grade(score, comment);

	submission.gradeSubmission(grade);
}

void Teacher::viewSubmissions(const MyString& courseName, const MyString& assignmentTitle, const CourseRepository& courseRepo, const UserRepository& userRepo) const
{
	const Course& course = courseRepo.findByName(courseName);
	if (course.getTeacherId() != getId()) {
		std::cout << "Error: you are not the instructor for this course.\n";
		return;
	}

	const Assignment& assignment = course.getAssigmentByTittle(assignmentTitle);

	const MyVector<Submission>& submissions = assignment.getSubmissions();
	if (submissions.getSize() == 0) {
		std::cout << "No submissions for \"" << assignmentTitle.getString() << "\" in course \"" << courseName.getString() << "\".\n";
		return;
	}


	for (size_t i = 0; i < submissions.getSize(); ++i) {
		const Submission& submission = submissions[i];
		int studentId = submission.getStudentId();
		const User& student = userRepo.findById(studentId);

		std::cout << student.getFirstName().getString() << " " << student.getLastName().getString() << " " << studentId << ": " << submission.getContent().getString() << "\n";
	}
}

void Teacher::messageCourseStudents(const MyString& courseName, const MyString& content, CourseRepository& courseRepo, UserRepository& userRepo)
{
	Course course = courseRepo.findByName(courseName);

	const MyVector<int>& studentIds = course.getStudentIds();

	Message message(this->getId(), content, std::time(nullptr));

	for (size_t i = 0; i < studentIds.getSize(); ++i) {
		int sid = studentIds[i];
		User& user = userRepo.findById(sid);

		if (user.getRole() != User::Role::Student) {
			continue;
		}

		user.receiveMessage(message);
	}
}