# 🐚 Mini-Shell 42

<div align="center">

**Mini-Shell** is a core project in the **42 School** curriculum. The goal is to recreate a **minimalist UNIX shell** that simulates the behavior of Bash, focusing on the correct implementation of **parsing**, **execution**, **pipelines**, **redirections**, and **built-in commands**, along with managing **environment variables** and handling **signals**.

> _"The objective of this project is to create a simple shell, reproducing the behavior of Bash as closely as possible, with a focus on understanding how a shell works internally."_

---

<div align="center">
  <h3>Contributor Stats</h3>
  
  <table>
    <tr>
      <td align="center">
        <a href="https://github.com/vinimoura99">
          <img src="https://github-readme-stats.vercel.app/api?username=vinimoura99&show_icons=true&theme=react&rank_icon=github&hide_rank=true&layout=compact" alt="vinimoura99's GitHub Stats" />
        </a>
      </td>
      <td align="center">
        <a href="https://github.com/jvrs2002">
          <img src="https://github-readme-stats.vercel.app/api?username=jvrs2002&show_icons=true&theme=dark&rank_icon=github&hide_rank=true&layout=compact" alt="jvrs2002's GitHub Stats" />
        </a>
      </td>
    </tr>
  </table>

</div>

---

## 📑 Table of Contents

- [Implemented Features](#implemented-features)
- [Installation](#installation)
- [Usage](#usage)
- [Implemented Built-ins](#implemented-built-ins)
- [Parsing & Execution](#parsing--execution)
- [Signals & Error Handling](#signals--error-handling)
- [Known Issues](#known-issues)
- [Authors](#authors)

---

## ✨ Implemented Features

The **Mini-Shell** supports the following essential functionalities:

* **Prompt** display in interactive mode.
* Command line **Parsing**, including:
    * Quotes (single and double).
    * Environment variable expansion (`$VAR`).
* Execution of **simple commands** and **pipelines** (`|`).
* Support for **redirections** (`>`, `>>`, `<`, `<<`).
* **Built-in commands** (see section below).
* Management of **environment variables** (`export`, `unset`, `env`).
* **Error handling** (syntax, execution, etc.).
* **Signal handling** for `SIGINT` (Ctrl+C), `SIGQUIT` (Ctrl+\) and *heredoc*.
* Management of command **exit status** (`$?`).
* **No memory leaks** (tested with Valgrind).

---

## 💻 Installation

### Requirements

* Unix-based system (Linux/macOS).
* **GCC** compiler (or compatible).
* **`make`**.
* **`readline`** library (`libreadline-dev` on Ubuntu).

### Build

```sh
git clone [https://github.com/vinimoura99/Mini-Shell-42.git](https://github.com/vinimoura99)
cd Mini-Shell-42
make
````

The executable will be created as **`./minishell`**.

-----

## 🚀 Usage

Start the shell by running:

```sh
./minishell
```

You will see a prompt similar to:

```
minishell$ 
```

Type commands as you would in Bash:

  * **Execute binaries:**
      `  minishell$ ls -la /tmp  `
  * **Use pipes:**
      `  minishell$ ls | grep src  `
  * **Use redirections:**
      `  minishell$ echo hello > file.txt   minishell$ cat < file.txt  `
  * **Use environment variables:**
      `  minishell$ export MYVAR=42   minishell$ echo $MYVAR  `

Exit with **`exit`**, **`Ctrl+D`**, or by typing `exit <code code>`.

-----

## 🔧 Implemented Built-ins

The following shell built-in commands are implemented:

| Built-in | Description |
| :--- | :--- |
| **`echo`** | Prints arguments to standard output. |
| **`cd`** | Changes the current working directory. |
| **`pwd`** | Prints the current working directory. |
| **`export`** | Sets environment variables. |
| **`unset`** | Removes environment variables. |
| **`env`** | Displays environment variables. |
| **`exit`** | Exits the shell. |

-----

## ⚙️ Parsing & Execution

The shell's core is divided into three main modules:

  * **Lexer**:
      * Scans and tokenizes user input, correctly handling quotes, escape characters, and special symbols (like `|`, `>`, `<`).
  * **Parser**:
      * Constructs an internal representation (like an **Abstract Syntax Tree**) from the tokens, supporting pipelines, redirections, and performing environment variable expansion.
      * Detects and reports syntax errors comprehensively.
  * **Executor**:
      * Executes commands: built-ins internally and external programs using `fork` and `execve`.
      * Establishes **pipes** and sets up file descriptors for **redirections** and *heredocs*.
      * Manages file creation and verifies access permissions.
      * Cleans up resources and restores the shell state after execution.

-----

## 🚥 Signals & Error Handling

  * **`SIGINT` (Ctrl+C)**: Interrupts the current command or clears the prompt.
  * **`SIGQUIT` (Ctrl+)**: Ignored in interactive mode, handled in the child process.
  * **Heredoc**: Handles `SIGINT` to safely interrupt input.
  * **Exit Codes**: Mini-Shell maintains the command **exit status**, consistent with Bash whenever possible.

-----

## ⚠️ Known Issues

The following functionalities are not implemented or may behave differently from Bash:

  * **Wildcard expansion** (`*`, `?`, `[]`) is not implemented.
  * Logical operators (`&&`, `||`) are not implemented.
  * Some advanced Bash features (subshells, process substitution, etc.) are out of scope.
  * May behave differently in edge cases (such as `export` without arguments).

-----

## 👥 Authors

  * [vinimoura99](https://github.com/vinimoura99)
  * [jvrs2002](https://github.com/jvrs2002)
 

<!-- end list -->
