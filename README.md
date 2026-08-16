# 🎓 University Event Management System

**Department of Software Engineering • Daffodil International University (DIU)**  
**Capstone Project 4th Semester**

---

### 📑 Table of Contents
* 📌 Executive Summary
* 👥 Team Members & Contribution Matrix
* ✨ Key System Features
* 🏗️ System Architecture
* 💾 Data Persistence & File Schema
* 🔒 Password Security & Hashing
* 🔄 User Roles & Portals
* 🚀 Compilation & Execution Guide
* 📁 Repository Organization

---

### 📌 Executive Summary
The **DIU University Event Management System** is a modular, high-performance Command Line Interface (CLI) software application engineered in C (C99). Developed as the final Capstone Project for the Department of Software Engineering at Daffodil International University (DIU), the system provides an end-to-end management platform for university clubs, event coordinators, student volunteers, and administrative authorities.

Key capabilities include secure MD5 hashed authentication, event browsing and discovery, student registration, volunteer recruitment and application workflows, coordinator event operations, certificate issuance, and centralized administrator controls.

> **Zero External Database Dependency (Flat-File Engine):**  
> The system operates without external database servers (No SQL/NoSQL engine required). All data is persisted using custom flat files processed via native C File I/O operations.

---

### 👥 Team Members & Contribution Matrix

| Contributor | Student ID | Workload Share | Core Functional Responsibilities & Contribution Scope |
| :--- | :--- | :--- | :--- |
| **Md Tahmid Uddin** | 252-35-228 | 35% | • **Authentication & Security Engine:** Complete login portal (`studentLogin.c`, `studentLogin.h`), session handling, and MD5 password hashing integration (`md5.c`, `md5.h`).<br>• **Coordinator Operations (Part 2):** Coordinator final review and participant management / certificate allocation handler (`coordinatorPanel.c`, `coordinatorPanel.h`).<br>• **Core Engine & Menu Navigation:** Main application lifecycle loop and master menu routing (`main.c`, `menu.c`, `menu.h`, `common.h`). |
| **Marzia Fardous** | 252-35-198 | 35% | • **Event Catalog & Discovery:** Event browser, schedule viewer, and public listings engine (`viewEvents.c`, `viewEvents.h`).<br>• **Volunteer Management System:** Volunteer dashboard, volunteer event applications, task distribution, and volunteer status tracking (`volunteer.c`, `volunteer.h`).<br>• **Participation History:** Student activity log viewer and participation tracking (`student_history.txt`). |
| **Omor Farukh Shariar** | — | 30% | • **Full Admin Panel:** Complete administrative oversight, event approvals, coordinator assignments, user permissions, and master file data handling (`adminPanel.c`, `adminPanel.h`).<br>• **Coordinator Operations (Part 1):** Primary event creation, coordinator request processing, and preliminary event configuration (`coordinatorPanel.c`, `coordinatorPanel.h`). |

---

### ✨ Key System Features

**1. 🛡️ Role-Based Authentication & Access Control**
* Multi-role authentication separating Students, Volunteers, Event Coordinators, and System Administrators.
* 128-bit cryptographic MD5 password hashing for credential protection.

**2. 📅 Event Browsing & Discovery Catalog**
* View active, upcoming, and past university events.
* Real-time slot inspection and participant capacity tracking.

**3. 🤝 Volunteer Application & Workflow Management**
* Dedicated volunteer dashboard allowing students to apply for operational roles across active events.
* Dynamic tracking of application status (Applied, Approved, Completed).

**4. 📋 Coordinator Panel & Event Execution**
* Coordinator-level tooling for submitting new event proposals and configuring agendas.
* Participant roster review and certificate issuance pipelines.

**5. 👑 Comprehensive Admin Control Panel**
* High-level authority dashboard to approve/reject events, manage coordinators, inspect overall registration records, and audit logs.

**6. 📜 Certificate Verification & History Engine**
* Automated generation and logging of participation and volunteer certificates.
* Instant verification records mapped to Student IDs.

---

### 🏗️ System Architecture
