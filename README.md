# Calculator

A desktop calculator with **Standard** and **Scientific** modes, built in C++ with the [Qt](https://www.qt.io/) framework using Qt Creator.

This project was completed as homework for the *"Fundamentals of C++ Programming"* course at BMSTU (Bauman Moscow State Technical University).

> **Note:** The interface labels are in Russian — *Обычный* ("Standard") and *Инженерный* ("Scientific").

## Features

The calculator runs in two switchable modes, selected via radio buttons.

### Standard mode
- Digits `0`–`9` and a decimal point
- Basic arithmetic: addition `+`, subtraction `−`, multiplication `×`, division `÷`
- Square root `√`
- Reciprocal `x⁻¹`
- Clear `C` and equals `=`

### Scientific mode
All of the above, plus:
- Trigonometric functions: `sin`, `cos`, `tan`
- Hyperbolic functions: `sh`, `ch`, `th`
- Logarithms and exponential: `ln`, `log`, `Exp`
- Powers: `x²`, `x³`, `xⁿ`
- Roots: `³√`, `ⁿ√`
- Factorial `n!`
- The constant `π`

### Error handling
The display shows `Err` for invalid operations such as division by zero, `ln`/`log` of a non-positive number, and factorial of a negative or non-integer value.

## Tech Stack

- **Language:** C++ (C++11)
- **Framework:** Qt 5 (Qt Widgets)
- **Build system:** qmake
- **IDE:** Qt Creator

## Project Structure

```
calculator/
├── Calculator.pro          # qmake project file
├── main.cpp                # application entry point
├── mainwindow.h            # MainWindow class declaration
├── mainwindow.cpp          # calculator logic, layouts, and button handlers
├── mainwindow.ui           # Qt Designer UI (LCD display + mode radio buttons)
│
├── screenshots/            # application screenshots
│   ├── Calculator-result1.jpg
│   └── Calculator-result2.jpg
│
└── README.md
```

## Getting Started

### Prerequisites

- [Qt 5](https://www.qt.io/download) with Qt Creator
- A C++ compiler (GCC, Clang, or MSVC)

### Build & Run

**Using Qt Creator:**

1. Clone the repository:
   ```bash
   git clone https://github.com/popkova-a/calculator.git
   ```
2. Open `Calculator.pro` in Qt Creator.
3. Configure a kit if prompted, then click **Run** (or press `Ctrl+R`).

**From the command line:**

```bash
git clone https://github.com/popkova-a/calculator.git
cd calculator
qmake Calculator.pro
make
./Calculator
```

## How It Works

The display is a `QLCDNumber` widget. Numbers and operations are managed with a `QStack<QString>`: when a binary operation is entered, the operand and operator are pushed onto the stack, and `calculate()` pops them to produce the result. The Standard and Scientific layouts are built as separate `QWidget`s and swapped in and out of the main grid layout when the mode is changed.

## Screenshots

Screenshots are available in the [`screenshots/`](screenshots) directory.

## License

This project was created for educational purposes as a university assignment.
