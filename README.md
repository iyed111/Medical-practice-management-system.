# Medical Practice Management System

This is a simple C-based system for managing a medical practice, handling operations related to **patients**, **doctors**, and **appointments (RDVs)**. The system allows users to add, delete, modify, and view information about patients, doctors, and appointments. It uses a file-based storage system to store patient, doctor, and appointment data.

---

## Table of Contents

- [Features](#features)
- [Technologies](#technologies)
- [Installation](#installation)
- [Usage](#usage)
- [File Structure](#file-structure)
- [Contributing](#contributing)
- [License](#license)

---

## Features

- **Patient Management**:
  - Add a new patient
  - Delete an existing patient
  - Validate patient data (e.g., ID, phone number, date of birth)

- **Doctor Management**:
  - Add a new doctor
  - Delete an existing doctor
  - Search for a doctor by ID
  - View doctor details (name, specialty, availability)

- **Appointment (RDV) Management**:
  - Schedule an appointment (book a time slot with a doctor)
  - Cancel an appointment
  - Modify an appointment
  - View appointments by doctor or by date

- **File-Based Storage**: Data is stored in binary files (`patient.dat`, `medecin.dat`, `RDV.dat`) for persistent storage.

---

## Technologies

- **C Programming Language**: The entire system is built in C.
- **File Handling**: Uses file operations (`fopen`, `fwrite`, `fread`, etc.) for persistent data storage.
- **Standard Libraries**: Includes libraries such as `stdio.h`, `stdlib.h`, `string.h`, and `stdbool.h`.


