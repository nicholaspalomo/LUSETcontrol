<!-- This template was taken from:
https://gist.github.com/fvcproductions/1bfc2d4aecb01a834b46#file-samplereadme-md -->

<a href="https://ethz.ch/en.html"><img src="https://github.com/nicholaspalomo/LUSETcontrol/blob/master/docs/eth_zurich_logo.jpg&s=200" title="ETH Zurich" alt="ETH Zurich"></a>

<!-- [![FVCproductions](https://avatars1.githubusercontent.com/u/4284691?v=3&s=200)](http://fvcproductions.com) -->

***INSERT GRAPHIC HERE (include hyperlink in image)***

# LUSET Control and Collision Detection ROS C++/Gazebo Project

> This is the ROS implementation in C++ with a Gazebo simulation for the software-side of LUSET project at ETH Zurich, Switzerland. This project replaces the original control system, which was programmed in MATLAB.

> For more information on the LUSET project, go to https://kaufmann.ibk.ethz.ch/research/LUSET.html. Also check out this informational video (in German) featuring Professor Walter Kaufmann, head of the Structural Engineering Institute (IBK) at ETH, explaining the LUSET project: https://vimeo.com/355932476.

<!-- > include terms/tags that can be searched -->

<!-- **Badges will go here** -->

<!-- - build status
- issues (waffle.io maybe)
- devDependencies
- npm package
- coverage
- slack
- downloads
- gitter chat
- license
- etc.

[![Build Status](http://img.shields.io/travis/badges/badgerbadgerbadger.svg?style=flat-square)](https://travis-ci.org/badges/badgerbadgerbadger) [![Dependency Status](http://img.shields.io/gemnasium/badges/badgerbadgerbadger.svg?style=flat-square)](https://gemnasium.com/badges/badgerbadgerbadger) [![Coverage Status](http://img.shields.io/coveralls/badges/badgerbadgerbadger.svg?style=flat-square)](https://coveralls.io/r/badges/badgerbadgerbadger) [![Code Climate](http://img.shields.io/codeclimate/github/badges/badgerbadgerbadger.svg?style=flat-square)](https://codeclimate.com/github/badges/badgerbadgerbadger) [![Github Issues](http://githubbadges.herokuapp.com/badges/badgerbadgerbadger/issues.svg?style=flat-square)](https://github.com/badges/badgerbadgerbadger/issues) [![Pending Pull-Requests](http://githubbadges.herokuapp.com/badges/badgerbadgerbadger/pulls.svg?style=flat-square)](https://github.com/badges/badgerbadgerbadger/pulls) [![Gem Version](http://img.shields.io/gem/v/badgerbadgerbadger.svg?style=flat-square)](https://rubygems.org/gems/badgerbadgerbadger) [![License](http://img.shields.io/:license-mit-blue.svg?style=flat-square)](http://badges.mit-license.org) [![Badges](http://img.shields.io/:badges-9/9-ff6799.svg?style=flat-square)](https://github.com/badges/badgerbadgerbadger) -->

[![License](http://img.shields.io/:license-mit-blue.svg?style=flat-square)](http://badges.mit-license.org)

<!-- - For more on these wonderful ~~badgers~~ badges, refer to <a href="http://badges.github.io/badgerbadgerbadger/" target="_blank">`badgerbadgerbadger`</a>. -->

***INSERT ANOTHER GRAPHIC HERE***

[![INSERT YOUR GRAPHIC HERE](http://i.imgur.com/dt8AUb6.png)]()

<!-- - Most people will glance at your `README`, *maybe* stare it, and leave
- Ergo, people should understand instantly what your project is about based on your repo

> Tips

- HAVE WHITE SPACE
- MAKE IT PRETTY
- GIFS ARE REALLY COOL

> GIF Tools

- Use <a href="http://recordit.co/" target="_blank">**Recordit**</a> to create quicks screencasts of your desktop and export them as `GIF`s.
- For terminal sessions, there's <a href="https://github.com/chjj/ttystudio" target="_blank">**ttystudio**</a> which also supports exporting `GIF`s. -->

<!-- **Recordit**

![Recordit GIF](http://g.recordit.co/iLN6A0vSD8.gif)

**ttystudio**

![ttystudio GIF](https://raw.githubusercontent.com/chjj/ttystudio/master/img/example.gif) -->

---

## Table of Contents

<!-- > If your `README` has a lot of info, section headers might be nice. -->

- [Installation](#installation)
- [Features](#features)
- [Contributing](#contributing)
- [Team](#team)
- [FAQ](#faq)
- [Support](#support)
- [License](#license)

<!-- ## Example (Launching simulation) -->

<!-- ```javascript
// code away!

let generateProject = project => {
  let code = [];
  for (let js = 0; js < project.length; js++) {
    code.push(js);
  }
};
``` -->
---

## Installation

- The code has only been tested in ROS Melodic running on Ubuntu 18.04 (Linux recommended, but may work with WSL - see https://jack-kawell.com/2019/06/24/setting-up-a-ros-development-environment-in-windows/ and https://github.com/Microsoft/WSL/issues/3368 for more information).
- Follow the guide at http://wiki.ros.org/Installation/Ubuntu and complete the installation of ROS Melodic on your system.

### Clone

- Clone this repo to your local machine using 
- Install Eigen by entering the following in a terminal:
```
~/LUSETcontrol
git clone https://gitlab.com/libeigen/eigen.git
```

### Setup

- To run the simulation with dummy inputs, open a new terminal and navigate to the catkin workspace where this repo has been cloned.
```
cd ~/LUSETcontrol
```
- Build and launch the project.
```
catkin_make
roslaunch indel_update_pkg indel_update_pkg.launch
```
The Gazebo simulation will open in a new window. In the toolbar at the top, you can select `Edit > Reset World` to reset the simulation.

- Open a new terminal and type
```
cd ~/LUSETcontrol
source devel/setup.bash
rostopic echo /LusetContacts
```
to get print statements to the terminal every time a collision occurs between two or more components.

---

## Features

### Tested and working features

- Run a Gazebo simulation with actuator inputs supplied by the `/IndelUpdate` rostopic. These messages are routed to the `/LusetControl` node via the `/LusetState` node.
- Use `rqt_graph` to visualize the network or ros topics, subscriptions, publications, and nodes.

### Pending features

- Implementation of unit and integration tests
- Investigating Rviz support
- Troubleshooting the multithreaded ROS subscriptions, particularly in the `luset_control_pkg_node`
- Add custom plots in `rqt_plot` for visualizing (graphically) the messages being passed between the nodes

---
## Usage
---
## Documentation

All of the code is documented. You can find the Doxygen documentation in the `~/LUSETcontrol/doxygen` folder (C++ only). For more information about Doxygen, visit http://www.doxygen.nl/.

<!-- ## Tests (Optional)

- Going into more detail on code and technologies used
- I utilized this nifty <a href="https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet" target="_blank">Markdown Cheatsheet</a> for this sample `README`. -->

---
## Contributing

> To get started...

### Step 1

- **Option 1**
    - 🍴 Fork this repo!

- **Option 2**
    - 👯‍♂️ Clone this repo to your local machine using `git clone`

### Step 2

- **HACK AWAY!** 🔨🔨🔨

### Step 3

- 🔃 Raise an issue, assign some tags, and create a new branch (with the issue number in the title) for new features to be added or for bugs to be fixed. Submit a pull request once the issue has been fixed and thoroughly tested.

<!-- - 🔃 Create a new pull request using <a href="https://github.com/joanaz/HireDot2/compare/" target="_blank">`https://github.com/joanaz/HireDot2/compare/`</a>. -->

---

## Contributors

| <a href="http://fvcproductions.com" target="_blank">**Nicholas Palomo**</a> |
| :---: |
| [![FVCproductions](https://avatars1.githubusercontent.com/u/4284691?v=3&s=200)](http://fvcproductions.com)    |
| <a href="http://github.com/fvcproductions" target="_blank">`github.com/fvcproductions`</a> |

---

## FAQ

- **How do I debug this project?**
  - ROS logging
    - You can always place `ROS_INFO()`, `ROS_DEBUG()`, and `ROS_ERROR()` statements throughout the C++ code.
    - These functions have the same signature as `printf()`
    - They will appear in the ROS log files for the nodes in which they have been placed as soon as you shut down the `roscore`. The log files are stored at `~/.ros/log`.
  - GDB
    - I highly recommend using Visual Studio Code for code development and debugging. For more information, visit https://code.visualstudio.com/.
    - To get started with debugging in GDB, open the repo in Visual Studio Code
    - Open `.vscode/tasks.json` in the root of your workspace.
    - Add a new task:
```json
  {
      "label": "ROS: catkin_make",
      "type": "shell",
      "command": "catkin_make",
      "args": [
          "-j4",
          "-DCMAKE_BUILD_TYPE=Debug"
      ],
      "problemMatcher": [],
      "group": {
          "kind": "build",
          "isDefault": true
      }
  }
```
    - Save and close `tasks.json`. In the same directory, open `launch.json`.
    - Add the following block:
```json
  {
      "name": "(gdb) Launch",
      "type": "cppdbg",
      "request": "launch",
      "program": "${workspaceFolder}/devel/lib/luset_control_pkg/luset_control_pkg_node",
      "args": [],
      "stopAtEntry": false,
      "cwd": "${workspaceFolder}",
      "environment": [],
      "externalConsole": false,
      "MIMode": "gdb",
      "setupCommands": [
          {
              "description": "Enable pretty-printing for gdb",
              "text": "-enable-pretty-printing",
              "ignoreFailures": true
          }
      ]
  }
```
    - You can replace the value of the `"program"` tag to that of another node executable, e.g. `"${workspaceFolder}/devel/lib/luset_state_pkg/luset_state_pkg_node"`, etc., in order to debug that node instead.
    - To begin debugging the node, place a breakpoint in the source code of the node.
    - Open the debugging tab on the left-hand side of the VS Code editor, select `(gdb) Launch` from the dropdown menu and click `Run` to start debugging the code. The call stack will be executed up until the breakpoint at which point execution is paused.

- **I want to change the valve configuration that is loaded to the parameter server. How do I load my new YAML file?**

    - Change line 9 of `luset_control_pkg.launch` to match the name and path of your new YAML file.
---

## Support

Reach out to me on LinkedIn!

- LinkedIn profile at <a href="https://www.linkedin.com/in/nicholaspalomo/" target="_blank">`linkedin.com`</a>

Checkout ETH Zurich!

- ETH Zurich homepage <a href="https://ethz.ch/en.html" target="_blank">`ethz.ch`</a>
- Master of Science in Robotics, Systems and Control <a href="https://master-robotics.ethz.ch" target="_blank">`master-robotics.ethz.ch`</a>
- Institute of Structural Engineering (IBK) <a href="https://ibk.ethz.ch/" target="_blank">`ibk.ethz.ch`</a>

---

## License

[![License](http://img.shields.io/:license-mit-blue.svg?style=flat-square)](http://badges.mit-license.org)

- **[MIT license](http://opensource.org/licenses/mit-license.php)**
- Copyright 2020 © <a href="mail:npalomo@student.ethz.ch" target="_blank">Nicholas J. Palomo</a>.
