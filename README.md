# Console-Based Notepad with AVL Tree Spell Checker

## Overview
This project implements a console-based notepad application with an integrated spell checker using an AVL tree dictionary. The notepad allows users to type, edit, load, and save text while performing real-time spell checking. The AVL tree ensures efficient word storage and quick search operations.

## Features
### 1. AVL Tree Dictionary
- Loads words from a provided text file in alphabetical order.
- Stores words in a self-balancing AVL tree for efficient searches.
- Supports balanced insertion and search operations.

### 2. Console-Based Notepad
- **Text Addition**: Each letter typed is stored as a node in a linked list.
- **Text Deletion**: Supports Backspace for deleting the last letter typed.
- **Text Loading**: Load text from a file using `Ctrl + L`.
- **Text Saving**: Save the current text to `save.txt` using `Ctrl + S`.
- **Quit**: Exit the application with `Esc`, releasing allocated memory.

### 3. Spell Checker with Word Tracking
- Tracks typed words using a stack or queue.
- Performs spell-checking on word completion (when a space is entered).
- Suggests corrections using:
  - **Letter Substitution**: Replaces characters in the misspelled word.
  - **Letter Omission**: Removes characters to form valid words.
  - **Letter Insertion**: Inserts characters to form valid words.
  - **Letter Reversal**: Swaps adjacent letters to correct spelling.

### 4. Data Structures Used
- **Linked List**: Stores the notepad text.
- **Stack/Queue**: Tracks recent words for spell-checking.
- **AVL Tree**: Stores the dictionary for efficient lookups.

### 5. Memory Management
- All dynamically allocated memory (linked list nodes, AVL tree nodes, stack/queue elements) is released when exiting the program.

## Commands & Usage
| Command | Function |
|---------|----------|
| Typing | Adds letters to the linked list (notepad) |
| Backspace | Deletes the last typed letter |
| Space | Triggers spell-checking for the last word |
| Ctrl + L | Loads text from a file into the notepad |
| Ctrl + S | Saves the text to `save.txt` |
| Esc | Exits the application and frees memory |

## Installation & Execution
1. Clone the repository:
   ```sh
   git clone <repository-url>
   cd <repository-name>
   ```
2. Compile the program (if applicable, specify compilation steps).
3. Run the executable.

## Contributing
Feel free to fork this repository, submit issues, and contribute improvements!
