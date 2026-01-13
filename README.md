# 📚 Course Manager

A **C++ console-based course management system** for managing users, courses, assignments, grades, and internal messaging.  
The project is developed as a **course project** for the *Introduction to Programming* course at the **Faculty of Mathematics and Informatics**, part of **Sofia University "St. Kliment Ohridski"**.

The system supports three user roles: **Administrator**, **Teacher**, and **Student**.  
All data (users, courses, messages, assignments, grades) is stored and loaded from files at program startup.

---

## 👨‍🎓 Student Information

- **Name:** Emil Neshkov  
- **Faculty ID:** 0MI0600506  
- **Undergraduate Program:** Software Engineering at FMI of Sofia University "St. Kliment Ohridski"  
- **Semester:** 1  

---

## **🚀 Features**

### **Administrator**
- 👤 Create teachers and students  
- ❌ Delete users  
- 🔐 Set default passwords for new users  
- 📩 Send messages to all users  
- 📬 Access all user mailboxes  
- 👑 One administrator with ID = 0 and default password = 0000  

### **Teacher**
- 📚 Create courses  
- 📝 Create assignments in their courses  
- 👨‍🎓 Add students to courses  
- 🔐 Set passwords for self-enrollment  
- 📊 Grade student assignments  
- 📥 View assignment submissions  
- 📩 Send messages to students in their courses  

### **Student**
- 🔐 Enroll in courses using a password  
- 📝 Submit homework assignments  
- 📊 View grades and feedback  
- 📩 Send messages to other users  
- 📬 View and clear mailbox  

---

## **🛠️ Installation**

### **Clone the repository:**
```sh
git clone https://github.com/emilneshkov/CourseManager.git
cd CourseManager/CourseManager
g++ -o course_manager main.cpp *.cpp -std=c++11
./course_manager
```



### **Compile the project:**
```sh
g++ -o course_manager main.cpp User.cpp Course.cpp Assignment.cpp Message.cpp System.cpp Utils.cpp -std=c++11
```
### **Run the program:**
```sh
./course_manager
```

---


## **📝 Usage**
1. **Log in using your ID and password** *(Administrator, Teacher or Student)*.
2. **Follow the on-screen commands** to navigate through the system.
3. **Enter valid inputs** when prompted *(IDs, course names, passwords, grades, etc.)*.
4. **Teachers create courses and assignments** and manage enrolled students.
5. **Students enroll in courses, submit homework and view their grades.**
6. **All users can communicate through the built-in messaging system.**
7. **All data is saved automatically and restored on the next program start.**

---

