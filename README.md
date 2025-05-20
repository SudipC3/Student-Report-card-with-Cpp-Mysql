# Student Report Card System

A C++ application that manages student report cards using MySQL database for storage.

## Features

- Store student information (name, roll number)
- Calculate and store student grades based on subject marks
- Generate report cards with average marks and grades
- Simple console-based user interface

## Requirements

- C++ compiler (supporting C++11 or later)
- MySQL server
- MySQL Connector/C++ library

## Setup

1. Install MySQL server and create a database named `mydb`
2. Update the database connection details in the code (HOST, USER, PASSWORD)
3. Compile the program with MySQL libraries:
   ```
   g++ student_report_card.cpp -o report_card -lmysqlclient
   ```
4. Run the executable:
   ```
   ./report_card
   ```

## Database Schema

The program uses a single table named `Student` with the following structure:
- RollNo (VARCHAR): Primary key, unique identifier for each student
- Name (VARCHAR): Student's name
- Avg (FLOAT): Average marks of the student
- Grade (VARCHAR): Grade calculated based on average marks

## Grading System

- A+: 90-100
- A: 80-89
- B+: 70-79
- B: 60-69
- C: 50-59
- D: 40-49
- F: Below 40
