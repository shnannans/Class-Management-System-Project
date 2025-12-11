# Class Management System (CMS) 📚💾

![C Language](https://img.shields.io/badge/Language-C-blue)
![File-Based DB](https://img.shields.io/badge/Database-Text--File-green)
![Status](https://img.shields.io/badge/Status-Completed-success)

## 📋 Project Overview

Simple file-based Database Management System (DBMS) built in C for managing student records. Implements CRUD operations (Create, Read, Update, Delete) through a command-line interface with persistent text file storage.

**Course**: INF1002 Programming Fundamentals  
**Team**: P14-2  
**Institution**: Singapore Institute of Technology  
**Submission**: November 2024

---

## 🎯 Core Operations

| Command | Description | Example |
|---------|-------------|---------|
| **OPEN** | Load database file | `OPEN` |
| **SHOW ALL** | Display all student records | `SHOW ALL` |
| **INSERT** | Add new student record | `INSERT ID=9876543 Name=Mary Winston Avery Sim Programme=Engineering Mark=67.6` |
| **QUERY** | Search by student ID | `QUERY ID=9876543` |
| **UPDATE** | Modify existing record | `UPDATE ID=9876543 Mark=69.0` |
| **DELETE** | Remove student record | `DELETE ID=9876543` |
| **SAVE** | Write changes to file | `SAVE` |

---

## 📊 Database Structure

### StudentRecords Table Schema

| Column | Data Type | Description | Example |
|--------|-----------|-------------|---------|
| **ID** | Integer | Unique 7-digit student ID | 2403464 |
| **Name** | String (50 chars) | Student full name | Venecia Weng |
| **Programme** | String (50 chars) | Degree program | Applied Computing |
| **Mark** | Float | Grade score (0-100) | 80.0 |

### Sample Database File (`P14_2-CMS - Original.txt`)
```
Database Name: Sample-CMS
Authors: Faculty (Frank Guan, Zhengchen, Jacob)

Table Name: StudentRecords
ID      Name             Programme               Mark
2301234	Joshua Chen	     Software Engineering	   70.5
2201234	Isaac Teo	       Computer Science	       63.4
2304567	John Levoy	     Digital Supply Chain	   85.9
```

---

## 🛠️ Technical Implementation

### Data Structures
```c
typedef struct {
    int id;
    char name[50];
    char programme[50];
    float mark;
} StudentRecord;

StudentRecord records[MAX_RECORDS];  // Array to store records
int recordCount = 0;                  // Current number of records
```

### Key Functions
```c
void openDatabase(char *filename);     // Load records from file
void showAllRecords();                 // Display all records
int insertRecord(StudentRecord *rec);  // Add new record
int queryRecord(int id);               // Search by ID
int updateRecord(int id, ...);         // Update record fields
int deleteRecord(int id);              // Remove record
void saveDatabase(char *filename);     // Write to file
```

---

## 💻 Installation & Usage

### Compilation

**Windows (MinGW)**:
```bash
gcc P14_2-Main.c -o P14_2-Main.exe
P14_2-Main.exe
```

**Linux/Mac**:
```bash
gcc P14_2-Main.c -o P14_2-Main
./P14_2-Main
```

### Running the Program

1. **Start the program**:
```bash
   ./P14_2-Main
```

2. **Open database**:
```
   CMS> OPEN
   The database file "P14_2-CMS.txt" is successfully opened.
```

3. **Perform operations** (see examples below)

4. **Save before exit**:
```
   CMS> SAVE
   The database file "P14_2-CMS.txt" is successfully saved.
```

---

## 📖 Usage Examples

### Insert New Record
```
CMS> INSERT ID=2403464 Name=Venecia Weng Programme=Applied Computing Mark=80.0
A new record with ID=2403464 is successfully inserted.
```

### Query Student
```
CMS> QUERY ID=2606006
The record with ID=2606006 is found in the data table.
ID      Name            Programme               Mark
2606006 Kelvin Hang    Applied Computing       80.0
```

### Update Record
```
CMS> UPDATE ID=2403464 Mark=85.5
The record with ID=2403464 is successfully updated.
```

### Delete with Confirmation
```
CMS> DELETE ID=2403464
Are you sure you want to delete record with ID=2403464? Type "Y" to Confirm or "N" to cancel.
Y
The record with ID=2403464 is successfully deleted.
```

### Show All Records
```
CMS> SHOW ALL
Here are all the records found in the table "StudentRecords".
ID      Name                    Programme               Mark
1010101 Mary                    Computing Science       100.0
1212121 Michelle Yeo            AI                      45.5
2201234 Isaac Teo               Computer Science        63.4
```

---

## 📁 Project Files
```
class-management-system/
├── P14_2-Main.c                                # Main source code
├── P14_2-Main.exe                              # Compiled Windows executable
├── P14_2-Main.o                                # Object file
├── P14_2-CMS.txt                               # Database file (team data)
├── P_14-2-CMS_-_Original.txt                   # Sample database template
└── README.md                                   # This file
```

---

## 🔒 Input Validation & Error Handling

### Validation Rules
- **ID**: 7-digit integer, must be unique
- **Name**: Alphanumeric + spaces, max 50 characters
- **Programme**: Alphanumeric + spaces, max 50 characters
- **Mark**: Float between 0.0 and 100.0

### Error Messages
```c
// Duplicate ID
"The record with ID=XXXXXXX already exists."

// Record not found
"The record with ID=XXXXXXX does not exist."

// Invalid input format
"Error: Invalid input format. Please check your command."

// File not found
"Error: Database file 'P14_2-CMS.txt' not found."
```

---

## 🎓 Learning Outcomes

**C Programming Skills**:
- ✅ File I/O operations (`fopen`, `fscanf`, `fprintf`, `fclose`)
- ✅ String manipulation (`strcpy`, `strcmp`, `strtok`)
- ✅ Structures and arrays
- ✅ Command parsing and input validation
- ✅ Memory management

**Software Design**:
- ✅ Modular function design
- ✅ CRUD operation implementation
- ✅ File-based data persistence
- ✅ Error handling and user feedback
- ✅ Command-line interface design

---

## 🚀 Key Features

✅ **File-Based Database** - Persistent storage in human-readable text format  
✅ **CRUD Operations** - Complete Create, Read, Update, Delete functionality  
✅ **Input Validation** - Duplicate ID checks, data type validation  
✅ **Error Handling** - Comprehensive error messages and boundary checks  
✅ **Confirmation Prompts** - Double-check before deleting records  
✅ **Formatted Output** - Clean tabular display of records  
✅ **Case-Insensitive Commands** - Accepts uppercase/lowercase input  

---

## 👥 Team P14-2 Contributors

| Name | Contributions |
|------|---------------|
| Shannon Yum | INSERT/QUERY operations, file I/O |
| Jeanie Chua | UPDATE/DELETE operations, validation |
| Goh Jing Wen | OPEN/SAVE operations, data structures |
| Venecia Weng | SHOW ALL, command parsing, testing |

**Course**: INF1002 Programming Fundamentals  
**Institution**: Singapore Institute of Technology

---

## 📊 Assessment Criteria

| Component | Weight | Focus |
|-----------|--------|-------|
| **Code Completeness** | 50% | All CRUD operations working correctly |
| **Code Clarity** | 15% | Well-structured, commented, readable |
| **Code Reliability** | 15% | Error handling, boundary cases |
| **Technical Report** | 15% | Clear documentation of design |
| **Presentation** | 5% | Live demo and Q&A |

---

## 🐛 Known Limitations

- **Single Table**: Only supports `StudentRecords` table
- **Fixed Capacity**: Maximum 100 records (array-based)
- **No Indexing**: Linear search O(n) for queries
- **Text Format**: No data encryption or compression
- **No Transactions**: No rollback on save failure

---

## 🚀 Future Enhancements

- [ ] Multiple table support
- [ ] Dynamic array resizing (linked lists)
- [ ] Binary search for faster queries
- [ ] Data encryption for security
- [ ] CSV export functionality
- [ ] Batch import from file
- [ ] Grade statistics (average, min, max)
- [ ] Sorting by name/mark/programme

---

## 📚 Compilation Notes

**Standard**: C99  
**Compiler**: GCC 8.1.0+  
**Recommended flags**:
```bash
gcc -std=c99 -Wall -Wextra -pedantic P14_2-Main.c -o P14_2-Main
```

---

*Developed with 💻 at Singapore Institute of Technology | November 2024*
