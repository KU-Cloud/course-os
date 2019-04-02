## Prerequisites

- gcc
- git


## Install _gcc_ and _git_

> Tested on Ubuntu 18.04.2 LTS by Windows Subsystem for Linux (WSL).

```sh
# Before install, check if they already installed using
# $ gcc --version
# $ git --version

$ sudo apt-get update
$ sudo apt-get install gcc git

$ gcc --version
gcc (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0
Copyright (C) 2017 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

$ git --version
git version 2.17.1

# If gcc doesn't work:
$ sudo apt-get install build-essential
```

## Getting Started

> Tested on Ubuntu 18.04.2 LTS by Windows Subsystem for Linux (WSL).
 
```sh
$ git clone https://github.com/KU-Cloud/course-os.git
$ cd course-os
```

You can run examples using `./run.sh XXX`.

```sh
# Give execute permission to `run.sh` by `chmod +x ./run.sh` if you needed.
$ chmod +x ./run.sh
$ ./run.sh 
build...010/main.c: In function ‘main’:
010/main.c:28:9: error: expected expression before ‘<’ token
         <?1/>:
         ^
010/main.c:34:9: error: expected expression before ‘<’ token
         <?2/>:
         ^
Failed to compile 010/main.c. Aborting
```
In this example, you can see one or more errors caused by unexpected expression, `<?X/>`. This is blank. You should replace it with the proper code.

Some examples are assigned objectives that need to be achieved. In those examples, there may be a portion of the code missing, so be sure to write the missing code in the proper location. e.g. `120`.

```sh
$ vim ./010/main.c

#
# fill blanks...
#

$ ./run.sh 010
build...done

My pid is 10985 (child)
The answer to the ultimate question of life the universe and everything is 0.
But Arthur replied that it was 0.

My pid is 10984 (parent)
The answer to the ultimate question of life the universe and everything is 42.
But Arthur replied that it was 54.
```
You can edit `XXX/main.c` using _vim_, _nano_ or [_vscode_](https://code.visualstudio.com/).

> _vim_ is pre-installed in Linux based OS.

> _vscode_ requires desktop GUI.