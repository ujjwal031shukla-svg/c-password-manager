# c-password-manager
A C-based command-line password manager implementing master authentication, XOR encryption, and binary file storage for credentials.

# C Password Manager

A secure, menu-driven **command-line password manager** written in C that allows users to store, view, and delete credentials locally. This project uses a **master password**, **XOR encryption**, and **binary file handling** to manage credentials securely.

---

## Features

- **Master password protection** – One-time setup for secure access.
- **Add credentials** – Save website, username, and password.
- **View credentials** – Display stored credentials in a readable format.
- **Delete credentials** – Remove a site’s credentials safely.
- **Password masking** – Hide passwords while typing (`*****`).
- **Local storage** – Credentials saved in an encrypted binary file.

---

## Technologies Used

- **Language:** C
- **File Handling:** `fopen`, `fread`, `fwrite`
- **Data Structures:** `struct` for credentials
- **Encryption:** XOR-based simple encryption
- **Console I/O:** `getch()` for masked input
- **Binary File Storage:** Secure credential management

---

c-password-manager/
├── code.c # Source code
├── vault.dat # Encrypted credentials (created at runtime)
├── master.dat # Encrypted master password
├── README.md # Project documentation
└── screenshots/ # Optional: add program screenshots

Run

password_manager.exe


On first run, the program will ask you to create a master password.
**
**Usage Example****

Create a master password (on first run).

Log in using the master password.

Use the menu to:

Add a new credential

View saved credentials

Delete credentials

Exit the program

**Screenshots**

<img width="434" height="144" alt="output1" src="https://github.com/user-attachments/assets/50b9a890-2cc0-4b6e-9062-77a747e57189" />
<img width="746" height="314" alt="output2" src="https://github.com/user-attachments/assets/24ce319b-b8b2-474a-b9be-12229f7d257f" />

**Future Improvements**

Add search by site name

Implement stronger encryption (AES or SHA)

Add GUI version using C++ or Python

Password auto-generation

Cross-platform compatibility without getch()

**Author**

Name: Ansh Shukla

GitHub: https://github.com/ujjwal031shukla-svg

**##License**

This project is for learning and educational purposes.





