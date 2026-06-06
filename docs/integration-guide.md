# Swisstrain Project Integration Guide

## Overview

This document describes the integrated structure of the Swisstrain project, including repository organization, documentation, build skeleton, and validation steps. This integration prepares the project for clean transfer to an external Windows build machine.

## Repository Structure

The repository is organized to support clean separation between Linux preparation work and Windows build work:

```
/root/workspace/swisstrain/
├── Content/                    # All Unreal Engine assets
│   ├── Landscape/             # Terrain system assets
│   │   ├── Heightmaps/        # Terrain heightmap data
│   │   ├── Materials/         # Landscape materials
│   │   ├── Textures/          # Landscape textures
│   │   ├── Water/             # Water system assets
│   │   └── Foliage/           # Vegetation assets
│   ├── Rail/                  # Rail system assets
│   └── Maps/                  # Level files
├── Source/                    # C++ source code
│   ├── SwisstrainLandscape/   # Landscape system module
│   └── SwisstrainRail/        # Rail system module
├── Scripts/                   # Processing and build scripts
│   ├── Build/                 # Build scripts for Linux and Windows
│   │   ├── build.sh           # Linux build script
│   │   └── build.bat          # Windows build script
│   └── validate_project_structure.sh  # Project validation script
├── docs/                      # Documentation
│   └── windows-build-host-setup.md    # Windows build host setup guide
├── .github/                   # GitHub workflows
│   └── workflows/             # CI/CD workflows
├── .gitattributes             # Git LFS configuration
├── .gitignore                 # Git ignore patterns
├── README.md                  # Project overview
└── Swisstrain.uproject        # Unreal Engine project file
```

## Git LFS Configuration

The repository uses Git LFS (Large File Storage) for binary assets to keep the repository lightweight while maintaining references to large files. The following file types are configured for LFS:

- Textures: *.png, *.jpg, *.jpeg, *.tga, *.bmp, *.tif, *.tiff
- Meshes: *.fbx, *.obj, *.dae
- Heightmaps and large data files: *.raw, *.exr, *.iff, *.resS, *.resA
- Unreal binary assets: *.uasset, *.umap
- Audio files: *.wav, *.mp3, *.ogg

Always run `git lfs pull` after cloning or pulling to ensure all LFS files are downloaded.

## Build System

The project includes build scripts for both Linux (placeholder) and Windows (target) environments:

- `Scripts/Build/build.sh` - Linux build script
- `Scripts/Build/build.bat` - Windows build script

Both are placeholders for the actual build process which will integrate with Unreal Engine's build system.

## Documentation

Key documentation includes:

1. `README.md` - Project overview and status
2. `docs/windows-build-host-setup.md` - Guide for setting up Windows build environment
3. All previous phase documentation in the `docs/` directory

## CI/CD Integration

The project includes a GitHub Actions workflow configuration for automated builds:

- `.github/workflows/build.yml` - Build pipeline configuration

This workflow:
1. Checks out code with LFS support
2. Sets up Git LFS
3. Sets up the build environment
4. Runs the build script
5. Runs tests
6. Packages the project

## Validation

The project includes a validation script to ensure proper structure:

- `Scripts/validate_project_structure.sh` - Checks for required directories and files

Run this script to verify the project structure is complete:
```bash
./Scripts/validate_project_structure.sh
```

## Integration with External Build Machine

This integration prepares the project for transfer to an external Windows build machine by:

1. Maintaining clean separation between preparation and build work
2. Providing clear documentation for Windows setup
3. Including both Linux and Windows build scripts
4. Ensuring proper Git LFS configuration for large asset handling
5. Providing validation tools to verify project integrity

The Linux Hermes host is responsible for:
- Repo management
- Documentation
- Data acquisition and preprocessing
- Script development and validation
- Project preparation for Windows transfer

The Windows build host is responsible for:
- Unreal Engine 5.5 installation
- Opening and editing the Unreal project
- Importing assets
- Look development in the editor
- Build, cook, and package for Windows