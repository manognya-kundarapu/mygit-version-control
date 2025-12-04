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

Initialize a repository:
<pre>
./mygit init
</pre>

Stage a file:
<pre>
./mygit add file.txt
</pre>

Commit staged changes:
<pre>
./mygit commit "initial commit"
</pre>

Check status:
<pre>
./mygit status
</pre>

Delete a file:
<pre>
./mygit delete file.txt
./mygit commit "removed file"
</pre>

Restore a previous version:
<pre>
./mygit restore file.txt 1
</pre>

Diff two versions:
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

