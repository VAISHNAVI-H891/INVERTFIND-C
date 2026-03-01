# 🔎 Inverted Find in C

A high-performance **Inverted Search Engine** built using C that enables fast and efficient text retrieval across multiple files. This project implements **Hashing** and **Linked List–based Inverted Indexing**, a core concept used in modern search engines.

---

## 📌 Overview

An **Inverted Index** maps words to the list of documents in which they appear.
Instead of scanning every file during search, the system directly retrieves the relevant documents using indexed data, significantly improving search speed.

This project demonstrates practical implementation of:

* Data Structures
* Hashing techniques
* File handling
* Dynamic memory management

---

## ⚙️ Key Features

* 🔍 Fast keyword-based search
* 🗂️ Index multiple files into a single database
* ⚡ Hash-based storage for efficient lookup
* 🔁 Avoids duplicate word storage
* 💾 Save and reload database
* 📄 Displays files containing the searched word
* 🧩 Modular and reusable code design
* 🖥️ Menu-driven user interface

---

## 🏗️ Working Principle

### 1️⃣ Indexing (Database Creation)

* Input multiple text files
* Parse and extract words
* Store words using **Hash Table + Linked List**
* Map each word to:

  * File name
  * Occurrence details
* Save the index into a database file

---

### 2️⃣ Querying (Search)

* Load database into memory
* User enters a search word
* Hash-based lookup retrieves matching files
* Displays results instantly

---

## 🧠 Data Structures Used

* Hash Table
* Linked List
* Dynamic Memory Allocation
* File Handling

---

## 🧩 Functional Modules

1. Create Database
2. Display Database
3. Search Word
4. Save Database
5. Update Database
6. Exit

---

## 📁 Project Structure (Typical)

```id="f7q4m9"
.
├── main.c
├── create_db.c
├── search.c
├── display.c
├── file_handling.c
├── hash.c
├── inverted_search.h
├── Makefile
└── README.md
```

---

## 🚀 Compilation & Execution

### Compile

```id="8yq3hs"
gcc *.c -o inverted_search
```

### Run

```id="g2t4pd"
./inverted_search
```

---

## 💡 Sample Flow

```id="q5v1nz"
1. Create Database
   Enter file names: file1.txt file2.txt

2. Database created successfully

3. Search Word
   Enter word: data

   Found in:
   file1.txt
   file2.txt
```

---

## 📊 Advantages

* Faster than linear file searching
* Efficient memory usage
* Scalable for large document collections
* Core concept behind real-world search engines

---

## 🌍 Applications

* Search Engines
* Document Retrieval Systems
* Log Analysis Tools
* Text Processing Systems

---

## 🎯 Learning Outcomes

* Implementation of Inverted Index
* Hashing and collision handling
* Linked List operations
* File processing in C
* Modular programming practices

---

## 🔮 Future Enhancements

* Phrase-based search
* Ranking using word frequency
* Position-based indexing
* Stop-word filtering
* GUI version

---

## 👩‍💻 Author

**Vaishnavi**

---

