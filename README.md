# 🎓 Student Management System in C

![C](https://img.shields.io/badge/language-C-blue.svg)
![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-green.svg)
![License](https://img.shields.io/badge/license-MIT-lightgrey.svg)

A simple console-based **Student Management System** built in the C programming language. The program stores data in a structured text file (`students.txt`) and allows operations like adding, viewing, searching, updating, and deleting student records.

---

## 🔧 Features

- ✅ Add a student record
- 📋 View all students
- 🔍 Search a student by roll number
- ✏️ Update an existing student record
- ❌ Delete a student record
- 💾 File-based persistence in CSV format

---

## 🧑‍🎓 Data Format

Each student is stored in `students.txt` like:
rollNumber,name,mark1,mark2,mark3,mark4,mark5

### Example:
101,John Doe,85.50,90.00,78.00,92.00,88.00

---

## 🛠️ Function Reference
#### Function
- addStudent()
- viewStudents()
- searchStudent()
- updateStudent()
- deleteStudent()

---

## 📌 Requirements
- GCC or any C compiler
- Basic terminal usage
- C standard libraries: stdio.h, stdlib.h, string.h

---

## 🪪 License
This project is released under the [MIT License](https://github.com/Codris-exe/Student_Management).