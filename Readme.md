# 🔐 Mini Login System using Hashing

A console-based **User Login and Registration System** built in C++ to understand and implement **Hashing, Collision Handling, Linear Probing, Password Hashing, and File Handling**.

This project was developed as a practical application of Hash Table concepts learned in Data Structures and Algorithms.

---

## 📌 Features

- 🔑 User Registration
- 🔐 Password Hashing
- 👤 User Login Authentication
- 🚫 Duplicate Username Detection
- 🗂️ File-based Data Storage
- 📥 Load Users from File at Program Startup
- ⚡ Hash Table-based User Lookup
- 🔄 Collision Handling using Linear Probing
- 📊 Hash Table Display
- 💾 Persistent User Data

---

## 🧠 Data Structures & Concepts Used

### Hash Table

The system uses a fixed-size hash table to store users in memory.

```text
Table Size = 10
                    LOGIN SYSTEM
                         │
             ┌───────────┴───────────┐
             │                       │
        Registration                Login
             │                       │
             ▼                       ▼
         Username                 Username
             │                       │
             ▼                       ▼
      Hash Function             Hash Function
             │                       │
             ▼                       ▼
        Hash Table              Find User
                                     │
                              Enter Password
                                     │
                                     ▼
                              Password Hash
                                     │
                                     ▼
                              Compare Hashes
                                     │
                         ┌───────────┴───────────┐
                         ▼                       ▼
                    Login Success          Invalid Login