# Dentomatic
A software to automate the work of dentists

## Description
Dentomatic is a simple yet powerful dental practice management system written in C++. It helps dental practices manage patients and appointments efficiently.

## Features
- **Patient Management**
  - Add new patients with complete contact information
  - View all patients in a formatted list
  - Search for patients by name or ID
  - Store medical history and notes

- **Appointment Management**
  - Schedule appointments for existing patients
  - View all appointments with details
  - Update appointment status (scheduled, completed, cancelled)
  - Track appointment reasons and times

- **Data Persistence**
  - Automatic saving of patient and appointment data
  - Data is stored in simple text files for easy backup
  - Data is automatically loaded on startup

## Requirements
- C++ compiler with C++11 support (g++, clang++, etc.)
- Make (for building the project)

## Installation

1. Clone the repository:
```bash
git clone https://github.com/JeremieBL/Dentomatic.git
cd Dentomatic
```

2. Build the project:
```bash
make
```

## Usage

Run the program:
```bash
make run
```

Or run the executable directly:
```bash
./dentomatic
```

## Main Menu Options
1. **Patient Management** - Add, view, and search for patients
2. **Appointment Management** - Schedule, view, and update appointments
3. **Exit** - Save data and exit the program

## Data Storage
- Patient data is stored in `patients.dat`
- Appointment data is stored in `appointments.dat`
- Both files are automatically created and managed by the program
- Data files use pipe-delimited format for easy parsing

## Building and Cleaning

Build the project:
```bash
make
```

Clean build artifacts and data files:
```bash
make clean
```

## License
This project is licensed under the MIT License - see the LICENSE file for details.

## Contributing
Contributions are welcome! Please feel free to submit a Pull Request.
