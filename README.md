📚 Course Manager

A C++ console-based course management system for managing users, courses, assignments, grades, and internal messaging.
The project is developed as a course project for the Introduction to Programming course at the Faculty of Mathematics and Informatics, part of Sofia University "St. Kliment Ohridski".

The system supports three user roles: Administrator, Teacher, and Student.
All data (users, courses, messages, assignments, grades) is stored and loaded from files at program startup.

👨‍🎓 Student Information
Name: Emil Neshkov  
Faculty ID: 0MI0600506  
Undergraduate Program: Software Engineering  
University: Sofia University "St. Kliment Ohridski"  
Semester: 1

🚀 Features
👨‍💼 Administrator

➕ Create teachers and students

❌ Delete users

🔐 Set default passwords for new users

📩 Send messages to all users

📬 Access all user mailboxes

👑 The administrator has a fixed ID = 0 and default password = 0000

👨‍🏫 Teachers

📚 Create new courses

📝 Create assignments in their courses

👨‍🎓 Enroll students in their courses

🔐 Set enrollment passwords for courses

📊 Grade student assignments

📥 View all assignment submissions for their courses

📩 Send messages to students in their courses

👨‍🎓 Students

🔐 Enroll in courses using course password

📝 Submit assignment solutions

📊 View their grades and feedback

📩 Send messages to other users

📬 View and clear their mailbox

✉️ Messaging System

Each user has a personal mailbox that stores messages with:

Sender

Content

Date

Time

Messages are saved and loaded from files.
Students, teachers, and administrators can communicate through the built-in messaging system.

🛠️ Installation

Clone the repository:

git clone https://github.com/emilneshkov/CourseManager.git
cd CourseManager/CourseManager


Compile the project:

g++ -o course_manager main.cpp User.cpp Course.cpp Assignment.cpp Message.cpp System.cpp Utils.cpp -std=c++11


Run the program:

./course_manager

📂 Project Structure
📦 CourseManager
 ┣ 📜 main.cpp              # Entry point of the application
 ┣ 📜 User.h / User.cpp     # User base class and roles
 ┣ 📜 Admin.h / Admin.cpp   # Administrator logic
 ┣ 📜 Teacher.h / Teacher.cpp # Teacher functionality
 ┣ 📜 Student.h / Student.cpp # Student functionality
 ┣ 📜 Course.h / Course.cpp # Course management
 ┣ 📜 Assignment.h / Assignment.cpp # Homework and submissions
 ┣ 📜 Message.h / Message.cpp # Messaging system
 ┣ 📜 System.h / System.cpp # Main system controller
 ┣ 📜 Utils.h / Utils.cpp   # Helper functions
 ┣ 📜 users.txt             # Stored users
 ┣ 📜 courses.txt           # Stored courses
 ┣ 📜 messages.txt          # Stored messages
 ┣ 📜 assignments.txt       # Stored assignments and grades
 ┣ 📜 README.md             # Project documentation

📝 Usage

Log in with:

login <ID> <password>


Perform actions depending on your role:

Admin can create users and send global messages

Teachers manage courses and assignments

Students enroll, submit homework, and view grades

Log out with:

logout


All changes are saved automatically and restored on the next startup.

📜 License

This project is licensed under the
GNU General Public License v3.0 or later – see the LICENSE file for details.

⭐ If you like this project, consider giving it a star on GitHub! 🚀