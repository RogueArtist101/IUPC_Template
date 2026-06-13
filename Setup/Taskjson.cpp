// Section: Setup
// Topic:   Task.json

{"label": "Compile & Run with IO",
    "type": "shell",
    "command": "bash",
    "args": [
        "-c",
        "g++ \"${file}\" -o \"${fileDirname}/${fileBasenameNoExtension}\" && \"${fileDirname}/${fileBasenameNoExtension}\" < \"${fileDirname}/input.txt\" > \"${fileDirname}/output.txt\""
    ],
    "group": {
        "kind": "build",
        "isDefault": true
    },
    "problemMatcher": [],
    "presentation": {
        "echo": true,
        "reveal": "always",
        "focus": false,
        "panel": "shared"
    }}
