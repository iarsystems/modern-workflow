# Modern Development Workflow with IAR
[![CXARM CI](https://github.com/iarsystems/modern-workflow/actions/workflows/iar.yaml/badge.svg)](https://github.com/iarsystems/modern-workflow/actions/workflows/iar.yaml)

This repository contains a project example that can be developed from within a Dev Container using Visual Studio Code with its remote development extensions.

A Dev Container provides a pre-configured development environment. It allows you to work in a development environment that has been specifically configured for your repository. It will have all the tools, scripts and configurations you need to work on that project. Everyone who works on that repository will have the same environment, reducing the ocurrence of environment-related problems. Each repository can have settings that will give contributors a ready-to-use, fit-for-purpose environment, and the environment on your local machine will be unchanged.

The target is set to work with the IAR STM32F429II-ACA board although can be modified for working with other boards.

## IAR public container images
This project example makes use of one of the [IAR public container images](https://github.com/iarsystems/containers) for Arm with ST device support.

## Getting started
Perform the following:

1. Launch [Visual Studio Code](https://code.visualstudio.com/).
2. If running from Windows, [connect to WSL](https://code.visualstudio.com/docs/remote/wsl).

<img width="349" height="124" alt="Code_uC77i5JnhG" src="https://github.com/user-attachments/assets/00be3f75-48d2-45e3-baf1-74dd9fc540bb" />
<img width="603" height="116" alt="Code_dbNBZZXXQ3" src="https://github.com/user-attachments/assets/014f5ace-220b-497d-a7e2-518deaa3c22d" />

3. [Clone](https://code.visualstudio.com/docs/sourcecontrol/overview) and open this repository.

<img width="360" height="297" alt="image" src="https://github.com/user-attachments/assets/efa87139-54d0-4978-beb4-e8dce4316734" />

>[!TIP]
>This functionality depends on having Git installed. You might need to `sudo apt install git` or equivalent on your Linux distribution.

4. A toaster notification in the lower right corner will offer to reopen the folder to develop in a container.

<img width="454" height="110" alt="image" src="https://github.com/user-attachments/assets/7435a085-77a1-42bc-8bab-94a70495a987" />

>[!TIP]
>The toaster nofitication only appears for a short while. If you miss it, you can use the pallete (CTRL+SHIFT+P) and use, for example, "Dev Containers: reopen in container".

5. Install the recommended extensions from IAR and Microsoft.

6. The CMake Tools extension will offer to select a preset for configuring the project. A drop-down selection box will offer __cxarm-linux__ as an option for building with the IAR Build Tools.

## Authenticate to the IAR Cloud License service
The IAR Build Tools require an user license to operate and, for that reason, the project will not build at first. Choose one of the following methods:
### Via Entra ID
This method uses the [Microsoft Entra ID](https://learn.microsoft.com/en-us/entra/fundamentals/whatis) technology and it requires your user mail account associated to this service.
1. Choose Terminal/Run task.../IAR Cloud login.

2. Select the authentication code and copy it to the clipboard (CTRL+C). 

3. CTRL+Click on the provided link, enter with the provided code, click "Connect" and then "Continue".

<img width="392" height="299" alt="image" src="https://github.com/user-attachments/assets/0ff718b8-4c43-4ad7-a91d-e6d5cb1dd63d" />

4. Go back to Visual Studio Code and build the project using the IAR Build Tools.

### Via Evaluation Token
Alternatively, it is possible to use a time-limited Evaluation Token provided by IAR.
1. In your host environment, set the following variable:
```bash
export IAR_LMS_BEARER_TOKEN=<the-evaluation-token-you-received>
```
2. From within your Dev Container, access the command pallete and select "Dev Containers: Rebuild Container".

It should now be possible to build the project using the IAR Build Tools.

## Summary
Dev Containers simplify bootstrapping the whole development environment with the IAR Build Tools in Visual Studio Code.

## Additional reference information
- [Introduction to VS Code Remote Development](https://code.visualstudio.com/docs/remote/remote-overview)
- [Introduction to VS Code Dev Containers](https://code.visualstudio.com/docs/devcontainers/containers)
- [Dev Container specification](https://containers.dev/)
- [VS Code - Remote Development Extension Pack](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.vscode-remote-extensionpack)
- [VS Code - IAR Extension Pack](https://marketplace.visualstudio.com/items?itemName=iarsystems.iar-extension-pack)






