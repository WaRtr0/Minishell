![GitHub top language](https://img.shields.io/github/languages/top/WaRtr0/Minishell) ![GitHub repo size](https://img.shields.io/github/repo-size/WaRtr0/Minishell) ![GitHub Repo stars](https://img.shields.io/github/stars/WaRtr0/Minishell) ![GitHub repo directory count](https://img.shields.io/github/directory-file-count/WaRtr0/Minishell) ![GitHub watchers](https://img.shields.io/github/watchers/WaRtr0/Minishell) ![GitHub followers](https://img.shields.io/github/followers/WaRtr0) ![GitHub contributors](https://img.shields.io/github/contributors/WaRtr0/Minishell)  ![GitHub last commit](https://img.shields.io/github/last-commit/WaRtr0/Minishell) 

<h1 align="center">Minishell</h1>

---

## 🚀 About

**Minishell** is a 42 school project that challenges you to recreate a simplified UNIX shell. This implementation supports pipes, redirections, environment variables, and other essential shell features - all while being limited to a select group of standard functions.

Realized by [Androlink](https://github.com/androlink) && [WaRtr0](https://github.com/WaRtr0)

![Example](https://github.com//WaRtr0/Minishell/raw/assets/screens/screen1.png)

---

## ⚙️ Features

### 📜 Built-in Commands
| Command     | Options Supported          |
|-------------|-----------------------------|
| `echo`      | -n (no newline)             |
| `cd`        | Relative/Absolute paths     |
| `pwd`       | No options                  |
| `export`    | Variable assignment         |
| `unset`     | Variable removal            |
| `env`       | No arguments                |
| `exit`      | Exit with status code       |

### 🔄 Operators
| Operator          | Example                          |
|-------------------|----------------------------------|
| `<` (Input)       | `grep 'test' < file.txt`         |
| `>` (Output)      | `ls > output.txt`                |
| `>>` (Append)     | `echo "text" >> file.txt`        |
| `<<` (Here doc)   | `cat << LIMITER`                 |
| `\|` (Pipe)        | `ls | grep .c`                   |
| `&&` (And)        | `make && ./app`                 |
| `\|\|` (Or)         | `invalid_cmd \|\| echo "Error"`   |
| `()` (Grouping)   | `(ls \|\| echo Fail) && echo Done`|

### 🕹️ Interactive Mode
- Handles unclosed quotes/multiline commands
- **Ctrl+C**: New prompt on fresh line
- **Ctrl+D**: Clean exit
- Non-blocking **Ctrl+\**

---

## 🛠️ Installation

1. **Clone with submodules**:
   ```bash
   git clone --recursive https://github.com/WaRtr0/Minishell.git
   cd Minishell
   ```
2. **Build**:
   ```
   make -k
   ```
3. **Run**:
   ```
   ./minishell
   ```
---

## 🔧 Constraints

- Limited functions
- Only 1 global variable allowed
- Strict 42 norm
- Zero memory leaks
