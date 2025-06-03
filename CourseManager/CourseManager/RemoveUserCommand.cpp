#include "RemoveUserCommand.h"

void RemoveUserCommand::execute(const MyVector<MyString>& arguments, CourseManagerApp& courseApp) const
{
	if (arguments.getSize() != 2) {
		std::cout << "Usage: remove_user <userId>\n";
		return;
	}

	User* current = courseApp.getCurrentUser();
	if (!current || current->getRole() != User::Role::Admin) {
		std::cout << "Error: only the administrator may remove users.\n";
		return;
	}

	int userId;
	try {
		userId = arguments[1].parseToInt();
	}
	catch (...) {
		std::cout << "Error: userId must be an integer.\n";
		return;
	}
	if (userId < 0) {
		std::cout << "Error: userId must be non-negative.\n";
		return;
	}

	UserRepository& userRepo = courseApp.getUserRepo();
	CourseRepository& courseRepo = courseApp.getCourseRepo();

	User* target = nullptr;
	try {
		target = &userRepo.findById(userId);
	}
	catch (const std::exception&) {
		std::cout << "Error: no such user with ID " << userId << ".\n";
		return;
	}


	if (target->getRole() == User::Role::Admin && userId == 0) {
		std::cout << "Error: cannot remove the administrator.\n";
		return;
	}

	if (target->getRole() == User::Role::Teacher) {

		MyVector<Course> all = courseRepo.getAll();
		for (size_t i = 0; i < all.getSize(); ++i) {
			const Course& c = all[i];
			if (c.getTeacherId() == userId) {

				courseRepo.removeById(c.getId());
			}
		}
	}

	else if (target->getRole() == User::Role::Student) {
		MyVector<Course>& all = courseRepo.getAll();

		for (size_t i = 0; i < all.getSize(); ++i) {
			Course& c = all[i];

			if (c.isStudentEnrolled(userId)) {
				MyVector<int>& ids = c.getStudentIds();

				for (size_t si = 0; si < ids.getSize(); ++si) {
					if (ids[si] == userId) {
						ids.erase(si);
						break;
					}
				}
			}
			MyVector<Assignment>& assigns = const_cast<MyVector<Assignment>&>(c.getAssignments());
			for (size_t ai = 0; ai < assigns.getSize(); ++ai) {
				Assignment& a = assigns[ai];
				MyVector<Submission>& subs = const_cast<MyVector<Submission>&>(a.getSubmissions());
				for (size_t sj = 0; sj < subs.getSize(); ++sj) {
					if (subs[sj].getStudentId() == userId) {
						subs.erase(sj);
						--sj;
					}
				}
			}
		}
	}

	try {
		userRepo.removeById(userId);
		std::cout << "User " << userId << " removed successfully.\n";
	}
	catch (const std::exception& ex) {
		std::cout << "Failed to remove user: " << ex.what() << "\n";
	}
}
