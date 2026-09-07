# Student Grade Calculator

A command-line C program that records a student's subject-wise marks, calculates grades, GPA, and overall result, then displays and optionally saves a formatted report card.

## Features

- Interactive input of student name, roll number, and 1–10 subjects
- Input validation for subject count (1–10) and marks (0–100)
- Automatic per-subject letter grade and grade point calculation
- Overall total, percentage, GPA (10-point scale), and final grade computation
- Fail-safe result logic: any failed subject results in an overall **FAIL**
- Clean, tabular report card printed to the console
- Optional export of the report card to a text file (`<rollNo>_report.txt`)

## Grading Scale

| Marks Range | Grade | Grade Point |
|-------------|-------|--------------|
| 90–100      | O     | 10.0         |
| 80–89       | A     | 9.0          |
| 70–79       | B     | 8.0          |
| 60–69       | C     | 7.0          |
| 50–59       | D     | 6.0          |
| 40–49       | E     | 5.0          |
| 0–39        | F     | 0.0 (Fail)   |

- **Percentage** = (Total Marks Obtained / Total Possible Marks) × 100
- **GPA** = Sum of Grade Points / Number of Subjects
- **Final Grade** is computed from the overall percentage, but is forced to `F` if the student fails any single subject.

## Requirements

- A C compiler (GCC recommended)
- Works on Linux, macOS, and Windows (with a C compiler such as MinGW or WSL)

## Building

```bash
gcc -o grade_calculator grade_calculator.c
```

## Usage

Run the compiled binary:

```bash
./grade_calculator
```

You will be prompted for:

1. Student name and roll number
2. Number of subjects (1–10)
3. For each subject: subject name and marks (0–100)

The program will then display a report card and ask whether you'd like to save it to a file.

### Example Session

```
========== STUDENT GRADE CALCULATOR ==========
Enter Student Name: Anshita Sharma
Enter Roll Number: 111
Enter Number of Subjects (1-10): 2

--- Subject 1 ---
Enter Subject Name: Mathematics
Enter Marks for Mathematics (0-100): 92

--- Subject 2 ---
Enter Subject Name: Physics
Enter Marks for Physics (0-100): 78

===================================================
 STUDENT REPORT CARD
===================================================
Name : Anshita Sharma
Roll No : 111
---------------------------------------------------
SUBJECT              MARKS      GRADE      GP
---------------------------------------------------
Mathematics          92         O          10.0
Physics               78         B          8.0
---------------------------------------------------
Total Marks : 170 / 200
Percentage : 85.00%
GPA : 9.00 / 10.0
Final Grade : A
Result : PASS
===================================================

Do you want to save report to file? (y/n): y

[Success] Report saved to file: 101_report.txt

Thank you for using Grade Calculator!
```

## Output File Format

When saved, a text file named `<rollNo>_report.txt` is created in the working directory with a condensed summary:

```
Report Card - Anshita Sharma (Roll: 111)
Total: 170, Percentage: 85.00, GPA: 9.00, Grade: A
```

## Project Structure

```
.
├── Student-Grade-Calculator.c   # Main source file
└── README.md            # Project documentation
```

## Code Overview

| Function | Responsibility |
|----------|-----------------|
| `calculateGrade()` | Converts marks into a letter grade |
| `getGradePoint()` | Maps a letter grade to its 10-point grade point |
| `validateMarks()` | Ensures marks fall within 0–100 |
| `inputStudentData()` | Collects and validates student & subject input |
| `calculateResults()` | Computes totals, percentage, GPA, and final grade |
| `displayReportCard()` | Prints a formatted report card to the console |
| `saveToFile()` | Writes a summarized report card to disk |
| `clearInputBuffer()` | Clears leftover input from the stdin buffer |

## Known Limitations

- Maximum of 10 subjects per student (configurable via `MAX_SUBJECTS`)
- Subject and student names are limited to 49 characters (`MAX_NAME_LEN`)
- Handles a single student per run; no batch or multi-student support
- No persistent database — each save creates/overwrites a single text file per roll number

## License

This project is available for personal and educational use. Feel free to modify and extend it.
