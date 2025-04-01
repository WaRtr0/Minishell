![GitHub top language](https://img.shields.io/github/languages/top/WaRtr0/Minishell) ![GitHub repo size](https://img.shields.io/github/repo-size/WaRtr0/Minishell) ![GitHub Repo stars](https://img.shields.io/github/stars/WaRtr0/Minishell) ![GitHub repo directory count](https://img.shields.io/github/directory-file-count/WaRtr0/Minishell) ![GitHub watchers](https://img.shields.io/github/watchers/WaRtr0/Minishell) ![GitHub followers](https://img.shields.io/github/followers/WaRtr0) ![GitHub contributors](https://img.shields.io/github/contributors/WaRtr0/Minishell)  ![GitHub last commit](https://img.shields.io/github/last-commit/WaRtr0/Minishell) 

<h1 align="center">Minishell</h1>

---

## 🚀 About

**Minishell** is a 42 school project that challenges you to recreate a simplified UNIX shell. This implementation supports pipes, redirections, environment variables, and other essential shell features - all while being limited to a select group of standard functions.

Realized by [Androlink](https://github.com/androlink) && [WaRtr0](https://github.com/WaRtr0)

![Example](https://github.com//WaRtr0/Minishell/raw/assets/screens/screen1.png)

---

## 🛠️ Installation

1. **Clone with submodules**:
   ```bash
   git clone --recursive https://github.com/WaRtr0/Minishell.git
   cd Minishell
   ```
2. **Build**:
   ```
   make
   ```
3. **Run**:
   ```
   ./minishell
   ```
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
| `\|` (Pipe)        | `ls \| grep .c`                   |
| `&&` (And)        | `make && ./app`                 |
| `\|\|` (Or)         | `invalid_cmd \|\| echo "Error"`   |
| `()` (Grouping)   | `(ls \|\| echo Fail) && echo Done`|

### 🕹️ Interactive Mode
- Handles unclosed quotes/multiline commands
- **Ctrl+C**: New prompt on fresh line
- **Ctrl+D**: Clean exit
- Non-blocking **Ctrl+\\**

---

## 🔍 Debug Mode

You can compile **Minishell** in debug mode using the following command:

```bash
make debug
```

This enables `DEBUG_MODE`, which prints the **Abstract Syntax Tree (AST)** of the parsed command in a structured JSON format — useful for debugging and understanding how the shell interprets your input.

### 🧪 Example

For the command:

```bash
echo hello world! && true && (false || echo hello) && echo 1 | echo 2 | echo * > test
```

The AST will be displayed in JSON like this:

<details>
<summary>Click to show AST output (JSON)</summary>

```json
[
	{
		"type": "14-CMD_JOIN",
		"content": [
			{ "type": "13-CMD_TEXT", "content": "echo" },
			{ "type": "16-CMD_EMPTY" },
			{ "type": "13-CMD_TEXT", "content": "hello" },
			{ "type": "16-CMD_EMPTY" },
			{ "type": "13-CMD_TEXT", "content": "world!" },
			{ "type": "16-CMD_EMPTY" }
		]
	},
	{
		"type": "6-CMD_AND_IF",
		"content": [
			{
				"type": "14-CMD_JOIN",
				"content": [
					{ "type": "13-CMD_TEXT", "content": "true" },
					{ "type": "16-CMD_EMPTY" }
				]
			}
		]
	},
	{
		"type": "6-CMD_AND_IF",
		"content": [
			{
				"type": "10-CMD_PARENTHESIS",
				"content": [
					{
						"type": "14-CMD_JOIN",
						"content": [
							{ "type": "13-CMD_TEXT", "content": "false" },
							{ "type": "16-CMD_EMPTY" }
						]
					},
					{
						"type": "8-CMD_OR",
						"content": [
							{
								"type": "14-CMD_JOIN",
								"content": [
									{ "type": "13-CMD_TEXT", "content": "echo" },
									{ "type": "16-CMD_EMPTY" },
									{ "type": "13-CMD_TEXT", "content": "hello" }
								]
							}
						]
					}
				]
			}
		]
	},
	{
		"type": "6-CMD_AND_IF",
		"content": [
			{
				"type": "0-CMD_PIPE",
				"content": [
					{
						"type": "14-CMD_JOIN",
						"content": [
							{ "type": "13-CMD_TEXT", "content": "echo" },
							{ "type": "16-CMD_EMPTY" },
							{ "type": "13-CMD_TEXT", "content": "1" },
							{ "type": "16-CMD_EMPTY" }
						]
					},
					{
						"type": "14-CMD_JOIN",
						"content": [
							{ "type": "13-CMD_TEXT", "content": "echo" },
							{ "type": "16-CMD_EMPTY" },
							{ "type": "13-CMD_TEXT", "content": "2" },
							{ "type": "16-CMD_EMPTY" }
						]
					},
					{
						"type": "14-CMD_JOIN",
						"content": [
							{ "type": "13-CMD_TEXT", "content": "echo" },
							{ "type": "16-CMD_EMPTY" },
							{ "type": "17-CMD_WILDCARD" },
							{ "type": "16-CMD_EMPTY" },
							{ "type": "2-CMD_REDIR_OUT", "content": 0 }, // init 0
							{ "type": "16-CMD_EMPTY" },
							{ "type": "13-CMD_TEXT", "content": "test" } // name file
						]
					}
				]
			}
		]
	}
]
```

</details>

---

## 🔧 Constraints

- Limited functions
- Only 1 global variable allowed
- Strict 42 norm
- Zero memory leaks
