## visualize-c-memory

Real-time visualization of the memory of a C program during debugging in VSCode,
using [vscode-debug-visualizer](https://github.com/hediet/vscode-debug-visualizer)
and [GDB's Python API](https://sourceware.org/gdb/current/onlinedocs/gdb/Python-API.html).


![](demo.png)


### To try it

- Install graphviz.
  ```
  sudo apt install graphviz
  ```

- In VSCode, install [vscode-debug-visualizer](https://github.com/hediet/vscode-debug-visualizer).
  ```
  Ctrl-P / ext install hediet.debug-visualizer
  ```

- Clone this repository, open it in VSCode and start debugging (`F5`).

  If the debugger doesn't start, make sure that `gdb`, `make` and VSCode's [ms-vscode.cpptools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) are installed.

- Select `F1 / Debug Visualizer : New View` and
  write `"memory"` (__including__ the quotes) in the visualization window
  that opens.

- A visualization of both the stack and the heap will appear, and it will
  update as you step through the code (`F10`, `F11`, etc).

- Modify [`examples/examples.c`](examples/examples.c) to try your own code.

Tested in Ubuntu 20.04 and Windows 10 under WSL.
macOS is not supported (to make it work one would need to workaround the
linker's lack of `--wrap`, and the fact that Apple makes it
[particularly painful](https://dev.to/jasonelwood/setup-gdb-on-macos-in-2020-489k) to use
GDB in macOS).


### To use it in your own project

- Link your code with `visualize-c-memory/malloc-wrapper.c`.
- Pass `-Wl,--wrap=malloc -Wl,--wrap=free` to gcc when linking, which allows to watch the 
  heap by wrapping `malloc/free` calls. You can also optionally wrap any of the following
  functions:
  ```
  calloc realloc strdup strndup
  ```
  by passing `-Wl,--wrap=<function>` (once for each function).

- Load `visualize-c-memory/visualize-c-memory.py` in GDB when it launches, by adding
  the following to your `launch.json`:
  ```
  "setupCommands": [
    {
      "text": "source ${workspaceFolder}/<path-to>/visualize-c-memory.py"
    }
  ],
  ```
  See [.vscode/launch.json](.vscode/launch.json) for an example.






