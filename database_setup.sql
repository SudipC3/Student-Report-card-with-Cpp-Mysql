-- Create database if it doesn't exist
CREATE DATABASE IF NOT EXISTS mydb;

-- Use the database
USE mydb;

-- Create Student table
CREATE TABLE IF NOT EXISTS Student (
    RollNo VARCHAR(10) PRIMARY KEY,
    Name VARCHAR(50) NOT NULL,
    Avg FLOAT DEFAULT 0.0,
    Grade VARCHAR(5) DEFAULT ''
);

-- Sample data (optional)
-- Uncomment to insert sample data
/*
INSERT INTO Student (RollNo, Name, Avg, Grade) VALUES
('ab123', 'Ali', 0.0, ''),
('bc234', 'Ahmad', 0.0, ''),
('cd345', 'Kabeer', 0.0, '');
*/
