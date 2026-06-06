# Swisstrain Windows Build Host Setup Guide

## Overview

This guide describes how to set up a Windows host for building and authoring the Swisstrain Unreal Engine project. The Linux Hermes host is responsible for preparation work, while the Windows host handles the actual Unreal Engine authoring and packaging.

## Prerequisites

1. Windows 10 or Windows 11
2. Unreal Engine 5.5 installed
3. Git for Windows
4. Git LFS

## Setup Steps

### 1. Install Unreal Engine 5.5

1. Download Epic Games Launcher from https://www.unrealengine.com/download
2. Install Epic Games Launcher
3. Open Epic Games Launcher and go to Unreal Engine tab
4. Install Unreal Engine 5.5

### 2. Install Git for Windows

1. Download Git for Windows from https://git-scm.com/download/win
2. Install Git with default settings
3. Make sure Git Bash is installed

### 3. Install Git LFS

1. Open Git Bash or Command Prompt
2. Run the following command:
   ```
   git lfs install
   ```

### 4. Clone the Repository

1. Open Git Bash or Command Prompt
2. Navigate to your desired workspace directory
3. Clone the repository:
   ```
   git clone <repository-url>
   cd swisstrain
   ```
4. Pull LFS files:
   ```
   git lfs pull
   ```

### 5. Verify Project Structure

Ensure the following directories exist:
- `Content/` - Contains all assets
- `Source/` - Contains C++ code
- `Scripts/` - Contains processing and build scripts

### 6. Open Project in Unreal Engine

1. Launch Unreal Engine 5.5
2. Open the project by selecting the `Swisstrain.uproject` file
3. Allow Unreal Engine to compile any necessary modules

## Build Process

### Manual Build

1. Open Command Prompt or PowerShell
2. Navigate to the project directory
3. Run the build script:
   ```
   Scripts\Build\build.bat
   ```

### Packaging

1. In Unreal Engine Editor, go to File > Package Project
2. Select target platform (Windows)
3. Choose output directory
4. Start packaging process

## Directory Conventions

### Asset Storage

- `Content/Landscape/` - Terrain and landscape assets
- `Content/Rail/` - Rail system assets
- `Content/Maps/` - Map files

### Code Structure

- `Source/SwisstrainLandscape/` - Landscape system module
- `Source/SwisstrainRail/` - Rail system module

## LFS Configuration

The repository uses Git LFS for large binary files:
- Textures (*.png, *.jpg, *.tga, etc.)
- Meshes (*.fbx, *.obj, etc.)
- Unreal binary assets (*.uasset, *.umap)
- Audio files (*.wav, *.mp3, *.ogg)

Always run `git lfs pull` after cloning or pulling to ensure all LFS files are downloaded.

## Troubleshooting

### Git LFS Issues

If LFS files are not downloading:
```
git lfs pull
```

If LFS is not installed:
```
git lfs install
git lfs pull
```

### Unreal Engine Compilation Issues

1. Delete `Binaries/` folder
2. Delete `Intermediate/` folder
3. Reopen project in Unreal Engine

### Missing Modules

If Unreal Engine complains about missing modules:
1. Go to Edit > Plugins
2. Enable any disabled plugins related to the project
3. Restart Unreal Engine