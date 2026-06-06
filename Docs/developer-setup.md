# Swisstrain Developer Setup Guide

## Prerequisites

- Unreal Engine 5.5
- Git with Git LFS
- Windows 10/11 (64-bit)

## Setup Instructions

1. Clone the repository:
```
git clone <repository-url>
cd swisstrain
```

2. Install Git LFS:
```
git lfs install
git lfs pull
```

3. Set up Unreal Engine 5.5:
- Download and install Unreal Engine 5.5 from Epic Games Launcher
- Launch the editor and open the Swisstrain project

4. Build the project:
```
cd Scripts/Build
./build.sh
```

## Directory Structure

```
/Content
  /Landscape  - Terrain and environment assets
  /Rail       - Railway system assets and blueprints
  /UI         - User interface elements
  /Plugins    - Custom plugin modules
  /Maps       - Level files
/Source       - C++ source files
/Docs         - Documentation
/Scripts      - Build and utility scripts
```

## Git Workflow

- Feature branch model with pull requests
- Git LFS for large binary assets (textures, meshes, heightmaps)
- Follow Unreal Engine best practices for asset management

## Build Process

1. Run the build script in Scripts/Build/build.sh
2. The build script will compile C++ modules and package assets
3. Output will be placed in the /Binaries directory

## Common Issues

- If Git LFS files are not properly pulled, run `git lfs pull`
- If the project fails to load in Unreal Engine, verify Unreal Engine 5.5 is installed
- For build issues, check the console output and Unreal Engine logs

## Contributing

1. Create a feature branch from main
2. Make your changes
3. Ensure all tests pass
4. Submit a pull request for review