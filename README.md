# Modern Development Workflow with IAR

This repository contains a project example that can be developed from within a Dev Cotainer using Visual Studio Code with its remote development extensions.

A Dev Container provides a pre-configured development environment. It allows you to work in a development environment that has been specifically configured for your repository. It will have all the tools, scripts and configurations you need to work on that project. Everyone who works on that repository will have the same environment, reducing the ocurrence of environment-related problems. Each repository can have settings that will give contributors a ready-to-use, fit-for-purpose environment, and the environment on your local machine will be unchanged.

The target is set to work with the IAR STM32F429II-ACA board although can be modified for working with other boards.

## IAR public container images
This project example make use of one of the [IAR public container image](https://github.com/iarsystems/containers) for Arm with ST device support.

## Getting started
1. Launch [Visual Studio Code](https://code.visualstudio.com/).
2. Connect to WSL.
3. Clone this repository.
4. Reopen Visual Studio Code in a Dev Container.
5. Install the recommended extensions from IAR and Microsoft.
6. Select a configure preset for modern-workflow: __cxarm-linux__ (Build with IAR).

### Login to the IAR Cloud License service
The IAR Build Tools require an user license to operate and, for that reason, the project will not build at first. Proceed as follows:
1. Choose Terminal/Run task.../IAR Cloud login.

2. Select the authentication code and copy it to the clipboard (CTRL+C). 

3. CTRL+Click on the provided link, enter with the provided code, click "Connect" and then "Continue".

<img width="392" height="299" alt="image" src="https://github.com/user-attachments/assets/72c3888b-c71b-4eb7-a4fa-99dc0289e128" />

4. Go back to Visual Studio Code and rebuild the CMake project.

## Summary
Dev Containers simplify bootstrapping the whole development environment with the IAR Build Tools in Visual Studio Code.

## Additional reference information
- [Introduction to VS Code Remote Development](https://code.visualstudio.com/docs/remote/remote-overview)
- [Introduction to VS Code Dev Containers](https://code.visualstudio.com/docs/devcontainers/containers)
- [Dev Container specification](https://containers.dev/)
- [VS Code - Remote Development Extension Pack](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.vscode-remote-extensionpack)
- [VS Code - IAR Extension Pack](https://marketplace.visualstudio.com/items?itemName=iarsystems.iar-extension-pack)

