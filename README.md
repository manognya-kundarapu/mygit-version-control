# mygit

**mygit** is a lightweight version control system implemented in C++.  
It provides a simplified model of how modern VCS tools (like Git) work internally, including object storage, staging, snapshot-based commits, status comparison, restoration of previous versions, and diffing between commits.

---

## Features

- `init` - creates the `.mygit/` repository structure  
- `add <file>` - stages a file by saving its version into the object store  
- `delete <file>` - stages the deletion of a file  
- `commit "<message>"` - records a full snapshot of all staged changes  
- `status` - shows staged, modified, clean, deleted, and untracked files  
- `log` - displays commit history  
- `restore <file> <commit-id>` - restores a file from a chosen commit  
- `diff <file> <commit1> <commit2>` - shows line-by-line differences  
- `unstage <file>` - removes a file from the staging area

---

## Building

Requires a C++17-compatible compiler.

```bash
make clean
make
```

This produces the executable:
```bash
./mygit
```

<h2>Usage</h2>

<h3>Initialize a repository:</h3>
<pre>
./mygit init
</pre>

<h3>Stage a file:</h3>
<pre>
./mygit add file.txt
</pre>

<h3>Commit staged changes:</h3>
<pre>
./mygit commit "initial commit"
</pre>

<h3>Check status:</h3>
<pre>
./mygit status
</pre>

<h3>Delete a file:</h3>
<pre>
./mygit delete file.txt
./mygit commit "removed file"
</pre>

<h3>Restore a previous version:</h3>
<pre>
./mygit restore file.txt 1
</pre>

<h3>Diff two versions:</h3>
<pre>
./mygit diff file.txt 1 3
</pre>
<h2>Repository Structure</h2>

<pre>
mygit-version-control/
├── include/        # Header files
├── src/            # Source files
├── Makefile
└── mygit           # Executable (after build)
</pre>

<p>After initialization:</p>

<pre>
.mygit/
├── index           # Staging area
├── log             # Commit history
└── objects/        # Stored file versions
</pre>

